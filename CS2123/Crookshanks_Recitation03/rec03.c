#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rec3.h"


int main()
{
	/* 1. Declare three integer arrays as follows */
	int a[50], b[70], c[120];
	/* 2. implement a function set_array_rand(int x[], int n)
	and call it to generate the values in array a and b
	randomly. */
	set_array_rand(a, 50);
	set_array_rand(b, 70);
        printf("done with a and b\n");
	/* 3. using the SELECTION_SORT(double x[], int n) function
	(see ch02.ppt), sort the elements in a and b arrays. */
	PRINT_ARRAY("Array a", a, 50);
        PRINT_ARRAY("Array b", b, 70);
        SELECTION_SORT(a, 50);
	SELECTION_SORT(b, 70);
        printf("done with sorting a and b\n");
        PRINT_ARRAY("Array a", a, 50);
        PRINT_ARRAY("Array b", b, 70);
	/* 4. implement a MERGE function and call it as follows to
	merge the values in arrays a and b into array c such that
	the values in c will be sorted after merging */
	MERGE(a, 50, b, 70, c, 120);
	/* 5. print the values in array c */
	PRINT_ARRAY("Array c", c, 120);
	return 0;
}

void set_array_rand(int x[], int n)
{
	/* 1. randomly generate elements of x array, e.g, */
	int i;
	for (i = 0; i< n; i++)x[i] = rand_int(30, 100);
}

int rand_int(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void SELECTION_SORT(int x[], int n)//I just wrote a simple sorting algorithm that uses recursion
{
	int maxloc, max, i, temp;
	if (n > 1)
	{
		for (i = 0;i < n;i++)//scans for the maximum value in the array
		{
			if (i == 0)
                        {
                            max=x[0];
                            maxloc=0;
                        }
			else if (x[i] > max)
			{
				max = x[i];//stores the max value
				maxloc = i;//stores the location of the max value
			}
		}
		temp = x[n - 1];
		x[n - 1] = max;
		x[maxloc] = temp;
		SELECTION_SORT(x, n - 1);
	}
        else printf("\n");
}

void MERGE(int a[], int na, int b[], int nb, int c[], int nc)
{
	/* merge the values in a and b into c while keeping the values
	sorted. For example, suppose we have the following two
	Arrays a = { 3, 7, 9, 12} and b = {4, 5, 10}
	When we merge these two arrays, we will get
	c = {3, 4, 5, 7, 9, 10, 12}
	*/
	int ia=0, ib=0, ic=0;//tracks the progression of the array
	for (ic = 0;ic < nc;ic++)//for loop for the c array
	{
		if (na <= ia || nb <= ib)//if either of these variables exeed the limit then the array is automatically filled with the rest of the opposite array
		{
			if (na <= ia)
			{
				c[ic] = b[ib];
				ib++;
			}
			else if (nb <= ib)
			{
				c[ic] = a[ia];
				ia++;
			}
		}
		else if (a[ia] < b[ib])//if a is less than b then you need to increace the a[ia] and add a to the c array
		{
			c[ic] = a[ia];
			ia++;
		}
		else if (a[ia] > b[ib])//vice versa of the if statement above
		{
			c[ic] = b[ib];
			ib++;
		}
		else if (a[ia] == b[ib])//if the 2 values are equal, you add both to c
		{
			c[ic] = a[ia];
			ic++;
			ia++;
			c[ic] = b[ib];
			ib++;
		}
	}
}

void PRINT_ARRAY(char *name, int x[], int nx)//prints the array
{
	int i;
	printf("%s \n", name);//prints the name
	for (i = 0;i < nx;i++)printf("%d ", x[i]);//for loop that lists all the array values of a specified array
	printf("\n");
}
