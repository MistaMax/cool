#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define true 1
#define false 0
typedef int bool;

int main()
{
	listADT X, Y, Z;//declaration of these variabls
	//making lists
	X = NewList();
	Y = NewList();

	int i, iBuff;

	for (i = 0;i < 6;i++)//scanning for user int input
	{
		printf("Enter Number %i\n", i + 1);
		scanf("%d", &iBuff);
		list_insert_unsorted(X, iBuff);
		list_insert_sorted(Y, iBuff);
	}
	//printing lists
	list_print_values(X, "X");
	list_print_values(Y, "Y");
	//lists the average
	printf("X Average = %g\n  Y Average = %g\n", list_average(X), list_average(Y));
	//delete values from lists
	printf("Give me a number to delete in list X\n");
	scanf("%d", &iBuff);
	list_delete_by_value(X, iBuff);
	printf("Give me a number to delete in list Y\n");
	scanf("%d", &iBuff);
	list_delete_by_value(Y, iBuff);
	//print dis list
	list_print_values(X, "X");
	list_print_values(Y, "Y");
	//take the average
	printf("X Average = %g\n  Y Average = %g\n", list_average(X), list_average(Y));
        //Sets Z to a part of X
	Z = list_n_copy(X, 3);
	list_print_values(Z, "Z");
        //prints the Z average
	printf("Z Average = %g\n", list_average(Z));
        //free the lists
	FreeList(X);
	FreeList(Z);
	FreeList(Y);
	return 0;
}
