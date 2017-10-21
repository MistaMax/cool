/*
 * File: random.h
 * --------------
 * This interface provides several functions for generating
 * pseudo-random numbers.
 */

#ifndef _random_h
#define _random_h
#include <stdlib.h>
#define New(type) ((type) malloc(sizeof *((type) NULL)))
#define NewArray(n, type) ((type *) malloc((n) * sizeof (type)))

 /* #include "genlib.h" */

 /*
  * Function: RandomInteger
  * Usage: n = RandomInteger(low, high);
  * ------------------------------------
  * This function returns a random integer in the range low to high,
  * inclusive.
  */

int RandomInteger(int low, int high);

/*
 * Function: RandomReal
 * Usage: d = RandomReal(low, high);
 * ---------------------------------
 * This function returns a random real number in the half-open
 * interval [low, high), meaning that the result is always
 * greater than or equal to low but strictly less than high.
 */

double RandomReal(double low, double high);

/*
 * Function: RandomChance
 * Usage: if (RandomChance(p)) . . .
 * ---------------------------------
 * The RandomChance function returns TRUE with the probability
 * indicated by p, which should be a floating-point number between
 * 0 (meaning never) and 1 (meaning always).  For example, calling
 * RandomChance(.30) returns TRUE 30 percent of the time.
 */

int RandomChance(double p);

/*
 * Function: Randomize
 * Usage: Randomize();
 * -------------------
 * This function initializes the random-number generator so that
 * its results are unpredictable.  If this function is not called,
 * the other functions will return the same values on each run.
 */

void Randomize(void);

#define true 1
#define false 0
typedef int bool;

//makes the random value into 4 seperate values
void getDigits(int a, int **s, int maxDiv);

//checks to see if all the digits are different
bool isDifferent(int *s);
#endif
