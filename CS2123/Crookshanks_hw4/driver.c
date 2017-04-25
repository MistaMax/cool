#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

void flushInputBuffer();

int main()
{
	setADT A, B, C; //names of sets
	int input;

	A = setNew(); //allocates sets 
	B = setNew();
	C = setNew();

	printf("Please Enter elements for set A\n Entering -1 will end input\n");
	while (1) {
		scanf("%d", &input); //gathers user input for A 
               if(input == -1)
                   break;
               setInsertElementSorted(A, input); //sends input to be stored in set
	}

	input = 0;
	printf("Please Enter elements for set B\nEntering -1 will end input\n");
	while (1) {
		scanf("%d", &input); //gathers user input for B 
		if(input == -1)
                    break;
                setInsertElementSorted(B, input); //sends input to be stored in set
	}

	input = 1;
        flushInputBuffer(); //resets input buffer
	while (input) {
		char user;
		printf("Please Enter a Command\n\n\tQ - ends program\n\tU - compares union\n\tI - compares intersection\n\tD - compares difference\n");
		scanf("%c", &user); //scans in user input
		switch (user) { //uses switch case to distinguish user input
		case ('Q') :
			input = 0;
			break;
		case ('U') : //union
			C=setUnion(A, B);
			setPrint(A, "A");
			setPrint(B, "B");
			setPrint(C, "C");
			break;
		case('I') : //intersection
                        C=setIntersection(A,B);
			setPrint(A, "A");
			setPrint(B, "B");
			setPrint(C, "C");
			break;
		case('D') : //difference
			C=setDifference(A, B);
			setPrint(A, "A");
			setPrint(B, "B");
			setPrint(C, "C");
			break;
		default: //if user input does not match case options
			printf("Please Re-Enter a stated value");
			break;
		}
        flushInputBuffer(); //clears user input
	}
        
	setFree(A);
	setFree(B);
	setFree(C);
	return 0;
}

/**** flushInputBuffer ****
    purpose: clears memory used for input buffer
*/
void flushInputBuffer()
{
char c;
do
    {
        c=getchar();
    }while(c!='\n'&& c!=EOF);
}


