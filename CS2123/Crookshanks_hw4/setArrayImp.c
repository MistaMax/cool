#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

struct setCDT
{
	setElementT x[100];
	int count;
};

setADT setNew()
{
	setADT tmp;
	tmp = (setADT)malloc(sizeof(struct setCDT));
	tmp->count = 0;
	if (tmp == NULL)return NULL;
	return tmp;
}

void setFree(setADT S)
{
	free(S);
}

int setInsertElementSorted(setADT S, setElementT E)
{
	if (S->count > 0)
	{
		if (setBinarySearch(S, E) >= 0)return 0;
		S->x[S->count++] = E;
		SELECTION_SORT(S, S->count);
                return S->count;
	}
	else
	{
		S->x[S->count++] = E;
		return S->count;
	}
}

setADT setUnion(setADT A, setADT B)
{
	setADT C = setNew();
	int ia = 0, ib = 0, ic = 0;//tracks the progression of the array
	C->count = A->count + B->count;
	for (ic = 0;ic < C->count;ic++)//for loop for the c array
	{
		if (A->count <= ia || B->count <= ib)//if either of these variables exeed the limit then the array is automatically filled with the rest of the opposite array
		{
			if (A->count <= ia)
			{
				C->x[ic] = B->x[ib];
				ib++;
			}
			else if (B->count <= ib)
			{
				C->x[ic] = A->x[ia];
				ia++;
			}
		}
		else if (A->x[ia] < B->x[ib])//if a is less than b then you need to increace the a[ia] and add a to the c array
		{
			C->x[ic] = A->x[ia];
			ia++;
		}
		else if (A->x[ia] > B->x[ib])//vice versa of the if statement above
		{
			C->x[ic] = B->x[ib];
			ib++;
		}
		else if (A->x[ia] == B->x[ib])//if the 2 values are equal, you add both to c
		{
			C->x[ic] = A->x[ia];
			C->count--;
			ia++;
			ib++;
		}
	}
	return C;
}

setADT setIntersection(setADT A, setADT B)
{
	setADT C = setNew();
	int ia = 0, ib = 0;//tracks the progression of the array
	while (true)//for loop for the c array
	{
		if (A->count <= ia || B->count <= ib)return C;//if either of these variables exeed the limit then the array is automatically filled with the rest of the opposite array
		else if (A->x[ia] < B->x[ib])ia++;//if a is less than b then you need to increace the a[ia] and add a to the c array
		else if (A->x[ia] > B->x[ib])ib++;//vice versa of the if statement above
		else if (A->x[ia] == B->x[ib])//if the 2 values are you add both to c
		{
			C->x[C->count++] = A->x[ia];
			ia++;
			ib++;
		}
	}
}

setADT setDifference(setADT A, setADT B)
{
	setADT C = setNew();
	int ia = 0, ib = 0, k;//tracks the progression of the array
	for (ia = 0;ia < A->count;ia++)
	{
		k = 0;
		for (ib = 0;ib < B->count;ib++)
		{
			if (A->x[ia] == B->x[ib])
				k++;
		}
	if (k == 0)
		C->x[C->count++] = A->x[ia];
	}
}

int setCardinality(setADT S)
{
	return S->count;
}

void setPrint(setADT S, char *name)
{
	int i;
	printf("%s: {", name);
	for (i = 0;i < S->count;i++)
	{
		printf("%i", S->x[i]);
		if (S->count - 1 != i)printf(", ");
	}
	printf("}\n");
}


void SELECTION_SORT(setADT S, int n)//I just wrote a simple sorting algorithm that uses recursion
{
	int maxloc, max, i, temp;
	if (n > 1)
	{
		for (i = 0;i < n;i++)//scans for the maximum value in the array
		{
			if (i == 0)
			{
				max = S->x[0];
				maxloc = 0;
			}
			else if (S->x[i] > max)
			{
				max = S->x[i];//stores the max value
				maxloc = i;//stores the location of the max value
			}
		}
		temp = S->x[n - 1];
		S->x[n - 1] = max;
		S->x[maxloc] = temp;
		SELECTION_SORT(S, n - 1);
	}
	else printf("\n");
}

int setBinarySearch(setADT S,int e)
{
	if (S->count > 0)
	{
		int i;
		i = (S->count - 1) / 2;
		while (true)
		{
			if (i + 1 != S->count && !(i < 0))
			{
				if (S->x[i] == e)return i;
				else if (S->x[i] < e)i++;
				else if (S->x[i] > e)i--;
			}
			else if (S->x[S->count] == e)return S->count;
			else return -1;
		}
	}
	else if (S->x[0] == e) return 0;
	else return -2;
}
