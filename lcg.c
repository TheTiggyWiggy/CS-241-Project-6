/*************************************
* Tanner Wagner
*
* This file is used to store all the 
* necessary code that properly implements
* lcg.h. There is no interaction with this
* file on the users end.
*
*************************************/

#include "lcg.h"

/*************************************
* Each parameter’s type and name:
*   - unsigned long m (input): Represents the number for which we need to find the product of its unique prime factors.
* input and/or output,
*   - Input.
* its meaning,
*   - m: The number for which we need to find the product of its unique prime factors.
* its range of values.
*   - m: Positive integer value greater than 1.
* Function’s return value.
*   - unsigned long: The product of the unique prime factors of the input number.
* Description of what the function does.
*   - This function calculates the product of the unique prime factors of a given positive integer.
* Function’s algorithm
*   - Initialize myProduct to 1.
*   - Iterate through numbers starting from 2 up to the square root of m.
*     - If i divides m evenly:
*       - Multiply myProduct by i.
*       - Divide m by i until it is no longer divisible by i.
*   - If there's any remainder left in m greater than 1 after the loop:
*     - Multiply myProduct by the remaining value of m.
*   - Return myProduct, which represents the product of the unique prime factors of m.
*************************************/

unsigned long productOfUniquePrimes(unsigned long m)
{
  unsigned long myProduct = 1;
  unsigned long i;

  for (i = 2; i * i <= m; i++)
  {
    if (m % i == 0)
    {
      myProduct *= i;
      while (m % i == 0)
      {
	m /= i;
      }
    }
  }

  if (m > 1)
  {
    myProduct *= m;
  }

  return myProduct;
}

/*************************************
* Each parameter’s type and name:
*   - unsigned long m (input): Represents the modulus value for the Linear Congruential Generator (LCG).
*   - unsigned long c (input): Represents the increment value for the LCG.
* input and/or output,
*   - Inputs.
* its meaning,
*   - m: The modulus value for the LCG.
*   - c: The increment value for the LCG.
* its range of values.
*   - m: Positive integer value.
*   - c: Positive integer value.
* Function’s return value.
*   - struct LinearCongruentialGenerator: A structure representing the Linear Congruential Generator initialized with the given parameters.
* Description of what the function does.
*   - This function creates and initializes a Linear Congruential Generator (LCG) with the given modulus and increment values.
* Function’s algorithm
*   - Initialize a new LinearCongruentialGenerator structure (lcg).
*   - Initialize variables p and a to 0.
*   - Set lcg.m, lcg.c, lcg.a, and lcg.x to 0.
*   - If m is 0 or c is greater than or equal to m:
*     - Return the initialized lcg structure.
*   - Calculate the product of unique primes of m and assign it to p using the productOfUniquePrimes function.
*   - Calculate a based on the condition: if m is divisible by 4, a is set to (1 + 2 * p), otherwise, it's set to (1 + p).
*   - If a is greater than or equal to m:
*     - Return the initialized lcg structure.
*   - Set lcg.m to m, lcg.c to c, lcg.a to a, and lcg.x to c.
*   - Return the initialized lcg structure.
*************************************/

struct LinearCongruentialGenerator makeLCG(unsigned long m, unsigned long c)
{
  struct LinearCongruentialGenerator lcg;
  unsigned long p;
  unsigned long a;

  lcg.m = 0;
  lcg.c = 0;
  lcg.a = 0;
  lcg.x = 0;

  if (m == 0 || c >= m)
  {
    return lcg;
  }

  p = productOfUniquePrimes(m);
  a = (m % 4 == 0) ? (1 + 2 * p) : (1 + p);

  if (a >= m)
  {
    return lcg;
  }

  lcg.m = m;
  lcg.c = c;
  lcg.a = a;
  lcg.x = c;

  return lcg;
}

/*************************************
* Each parameter’s type and name:
*   - struct LinearCongruentialGenerator *lcg (input): Pointer to a LinearCongruentialGenerator structure representing the LCG.
* input and/or output,
*   - Input and output.
* its meaning,
*   - lcg: Pointer to a LinearCongruentialGenerator structure representing the LCG.
* its range of values.
*   - lcg: A valid pointer to a LinearCongruentialGenerator structure.
* Function’s return value.
*   - unsigned long: The previous value of the LCG before the update.
* Description of what the function does.
*   - This function generates the next random value in the sequence for the given Linear Congruential Generator (LCG) and updates the state of the LCG.
* Function’s algorithm
*   - Store the current value of lcg->x in the variable currentVal.
*   - Update lcg->x according to the LCG formula: (a * currentVal + c) % m.
*   - Return the stored currentVal, which represents the previous value of the LCG before the update.
*************************************/

unsigned long getNextRandomValue(struct LinearCongruentialGenerator *lcg)
{
  unsigned long currentVal = lcg->x;
  
  lcg->x = (lcg->a * lcg->x + lcg->c) % lcg->m;

  return currentVal;
}
