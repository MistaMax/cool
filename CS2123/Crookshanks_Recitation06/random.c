/*
 * File: random.c
 * --------------
 * This file implements the random.h interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 /* #include "genlib.h" */
#include "random.h"

/*
 * Function: RandomInteger
 * -----------------------
 * This function begins by using rand to select an integer
 * in the interval [0, RAND_MAX] and then converts it to the
 * desired range by applying the following steps:
 *
 * 1. Normalize the value to a real number in the interval [0, 1)
 * 2. Scale the resulting value to the appropriate range size
 * 3. Truncate the scaled value to an integer
 * 4. Translate the integer to the appropriate starting point
 */

int RandomInteger(int low, int high)
{
	int k;
	double d;

	d = (double)rand() / ((double)RAND_MAX + 1);
	k = (int)(d * (high - low + 1));
	return (low + k);
}

/*
 * Function: RandomReal
 * --------------------
 * The implementation of RandomReal is similar to that
 * of RandomInteger, without the truncation step.
 */

double RandomReal(double low, double high)
{
	double d;

	d = (double)rand() / ((double)RAND_MAX + 1);
	return (low + d * (high - low));
}

/*
 * Function: RandomChance
 * ----------------------
 * This function uses RandomReal to generate a real number
 * in the interval [0, 1) and then compares that value to p.
 */

int RandomChance(double p)
{
	return (RandomReal(0, 1) < p);
}

/*
 * Function: Randomize
 * -------------------
 * This function operates by setting the random number
 * seed to the current time.  The srand function is
 * provided by the <stdlib.h> library and requires an
 * integer argument.  The time function is exported by
 * the <time.h> interface.
 */

void Randomize(void)
{
	srand((int)time(NULL));
}

//gets the digits from a and puts them into an array at the *s array
void getDigits(int a, int **s, int maxDiv)
{
        int c=0;
	if (a < maxDiv || a >= maxDiv * 10)//Error preventation
        {
            printf("Please use a number between 1000 and 9999\n");
            return;
        }
	while (1)
	{
		//break the loop when the max div is 1
		//if a has a zero in it then it will cancel out where ever the zero is and proceed to the next item, this if statement will fix it
		if (a >= maxDiv && a < maxDiv * 10)
			(*s)[c] = a/maxDiv;//seperates the first intiger in a
		else
			(*s)[c] = 0;
		a = a - ((*s)[c] * maxDiv);//moves a to the next digit
                if(maxDiv==1)break;
                else
                {
		    maxDiv = maxDiv / 10;//moves maxDiv to scan for the next digit
		    c++;//increaces the address by one
                }
	}
}

//checks to see if there is a difference between the digits in the array
bool isDifferent(int *s)
{
	int count = 0, i;
	for (i = 0;i < 4;i++)
	{
		for (count = 0;count < 4;count++)
		{
			if (i != count)
			{
				if (s[i] == s[count])
					return false;//returns false if there is a matching digit in the same array
			}
		}
	}
	return true;
}
