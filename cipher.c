/*************************************
* Tanner Wagner
* Professor Haugh
* CS 241
* Group 3RW
*
* This file is used to store all the 
* necessary code for cipher.c. This
* file utilizes functions from lcg.c
* in order to implement an LCG into 
* an encryptiona and decryption algo.
* To use it, simply adhere to the required
* format and pass input through the standard
* input and redirection flags <>.
*
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcg.h"
#define BUFFER_SIZE 1024

/*************************************
* Each parameter’s type and name:
*   - char myData: Input
*   - struct LinearCongruentialGenerator *lcg: Input
* input and/or output,
*   - Output
* its meaning,
*   - myData: The character to be processed.
*   - lcg: Pointer to the Linear Congruential Generator structure used for generating random values.
* its range of values.
*   - myData: Any character in the ASCII range (0 to 127).
*   - lcg: Valid pointer to a Linear Congruential Generator structure.
* Function’s return value.
*   - char: The processed character after encryption.
* Description of what the function does.
*   - This function takes a character and encrypts it using the Linear Congruential Generator provided. If the encrypted character is within the printable ASCII range (32 to 126), it is printed as is. If it falls outside this range, special characters are printed based on certain conditions.
* Function’s algorithm
*   - Generate a random value using getNextRandomValue function and the provided Linear Congruential Generator.
*   - Encrypt the input character using XOR with the random value modulus 128.
*   - Check if the encrypted character falls within the printable ASCII range:
*     - If yes, print the character.
*     - If not:
*       - If the encrypted character is less than 32, print '*','?', and the encrypted character plus 64.
*       - If the encrypted character is 127, print '*','$'.
*       - If the encrypted character is '*', print '*','*'.
*   - Return the encrypted character.
*************************************/

char processCharacter(char myData, struct LinearCongruentialGenerator *lcg)
{
  unsigned long randomValue = getNextRandomValue(lcg);
  char encryptedChar = myData ^ (randomValue % 128);

  if (encryptedChar < 32)
  {
    putchar('*');
    putchar('?');
    putchar(encryptedChar + 64);
  }

  else if (encryptedChar == 127)
  {
    putchar('*');
    putchar('$');
  }

  else if (encryptedChar == '*')
  {
    putchar('*');
    putchar('*');
  }

  else
  {
    putchar(encryptedChar);
  }

  return encryptedChar;
}

/*************************************
* Each parameter’s type and name:
*   - char *myLine: Input
*   - unsigned long *m: Output
*   - unsigned long *c: Output
*   - char **myData: Output
*   - char *myAction: Output
* input and/or output,
*   - Outputs: m, c, myData, myAction
* its meaning,
*   - myLine: The input string to be parsed.
*   - m: Pointer to store the parsed value of m.
*   - c: Pointer to store the parsed value of c.
*   - myData: Pointer to store the data to be encrypted or decrypted.
*   - myAction: Pointer to store the action type ('e' for encryption, 'd' for decryption).
* its range of values.
*   - myLine: Any valid null-terminated string.
*   - m, c: Any valid unsigned long value.
*   - myData: Pointer to a valid null-terminated string.
*   - myAction: 'e' or 'd'.
* Function’s return value.
*   - int: 1 if parsing is successful, 0 otherwise.
* Description of what the function does.
*   - This function parses a line of input containing an action type ('e' or 'd'), followed by two unsigned long integers separated by whitespace or commas, and finally followed by a string representing the data to be encrypted or decrypted.
* Function’s algorithm
*   - Check if the input pointers are valid. If not, return 0.
*   - Extract the action type from the input line and store it in myAction.
*   - If the action type is neither 'e' nor 'd', return 0.
*   - Extract the first unsigned long integer (m) from the input line and store it in *m.
*   - If m is not parsed correctly, return 0.
*   - Extract the second unsigned long integer (c) from the input line and store it in *c.
*   - If c is not parsed correctly, return 0.
*   - Extract the data string from the input line and store its pointer in *myData.
*   - If the data string is empty or ends with newline/carriage return characters, remove them.
*   - Return 1 to indicate successful parsing.
*************************************/

int parseInput(char *myLine, unsigned long *m, unsigned long *c, char **myData, char *myAction)
{
  char *myToken;
  char *endPtr;
  
  if (!myLine || !m || !c || !myData || !myAction) return 0;
  
  *myAction = myLine[0];

  if (*myAction != 'e' && *myAction != 'd') return 0;

  myToken = myLine + 1;

  while (*myToken && (*myToken == ' ' || *myToken == ',')) myToken++;

  *m = strtoul(myToken, &endPtr, 10);

  if (myToken == endPtr) return 0;

  myToken = endPtr;

  while (*myToken && (*myToken == ' ' || *myToken == ',')) myToken++;

  *c = strtoul(myToken, &endPtr, 10);
  
  if (myToken == endPtr) return 0;

  myToken = endPtr;
  
  while (*myToken && (*myToken == ' ' || *myToken == ',')) myToken++;

  if (*myToken == '\0' || *myToken == '\n') return 0;
  
  *myData = myToken;

  endPtr = *myData + strlen(*myData) - 1;

  while (endPtr > *myData && (*endPtr == '\n' || *endPtr == '\r'))
  {
    *endPtr = '\0';
    endPtr--;
  }
  
  return 1;
}

/*************************************
* Each parameter’s type and name:
*   - None
* input and/or output,
*   - Input: None
*   - Output: None
* its meaning,
*   - myLine: Buffer to store input lines.
*   - m: Variable to store the parsed value of m.
*   - c: Variable to store the parsed value of c.
*   - myData: Pointer to store the data to be encrypted or decrypted.
*   - myAction: Variable to store the action type ('e' for encryption, 'd' for decryption).
*   - lineCount: Counter to keep track of the line number.
*   - lcg: Linear Congruential Generator structure to store parameters.
* Function’s return value.
*   - int: 0 to indicate successful execution.
* Description of what the function does.
*   - This function reads input lines from standard input, parses them using parseInput function to extract action type, m, c, and data, initializes a Linear Congruential Generator using makeLCG function, and then processes the data using processCharacter function to encrypt or decrypt it.
* Function’s algorithm
*   - Initialize variables: myLine, m, c, myData, myAction, lineCount, and lcg.
*   - Read each line from standard input using fgets until EOF.
*   - Increment lineCount for each line read.
*   - Parse the input line using parseInput function to extract action type, m, c, and data.
*   - If parsing is successful:
*       - Initialize lcg using makeLCG function with m and c.
*       - If lcg.m is 0, print an error message and continue to the next line.
*       - Print the line number.
*       - Process each character of the data using processCharacter function and lcg.
*       - Print a newline character after processing all characters.
*   - If parsing fails, print an error message.
*   - Repeat the process until EOF is reached.
*   - Return 0 to indicate successful execution.
*************************************/

int main()
{
  char myLine[BUFFER_SIZE];
  unsigned long m;
  unsigned long c;
  char *myData;
  char myAction;
  int lineCount = 0;
  struct LinearCongruentialGenerator lcg;

  while (fgets(myLine, sizeof(myLine), stdin))
  {
    lineCount++;

    if (parseInput(myLine, &m, &c, &myData, &myAction))
    {
      lcg = makeLCG(m, c);
      if (lcg.m == 0)
      {
	printf("%5d: Error\n", lineCount);
	continue;
      }
      printf("%5d: ", lineCount);
      while (*myData && *myData != '\n')
      {
	processCharacter(*myData, &lcg);
	myData++;
      }
      printf("\n");
    }
    else
    {
      printf("%5d: Error\n", lineCount);
    }
  }

  return 0;
}
