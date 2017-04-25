#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "exception.h"
#include "gcalloc.h"
#include "genlib.h"
#define MAX_FGETS_STRING_SIZE 1000
#define true 1
#define false 0

void printUsageInfo();
void spliceString(char *s, int start, int end, char **str);
int getInputSwitches(int argc, char *argv[], char **inputFile);

int main(int argc, char *argv[])
{
	FILE *inFile;
	char *cInFile, *cTemp, *szInputBuffer;
	stackElementT eTemp;

	szInputBuffer = NewArray(MAX_FGETS_STRING_SIZE + 1, char);
	cInFile = NewArray(100, char);


	if (getInputSwitches(argc, argv, &cInFile) == false)
	{
		printUsageInfo();
		return 1;
	}
	/*spliceString(cInFile, strlen(cInFile) - 5, strlen(cInFile) - 1, &temp);
	if (strcmp(temp,"html")!=0)
	{
		printf("the file must end in .html");
		printUsageInfo();
		return 2;
	}
*/

	inFile = fopen(cInFile, "r");
	stackADT stack;
	stack = NewStack();

	while (fgets(szInputBuffer, MAX_FGETS_STRING_SIZE, inFile) != NULL)
	{
		int i, j, run;
		for (i = 0;i < strlen(szInputBuffer);i++)
		{
			j = 0;
			run = 1;
			//prelim checks
			if (szInputBuffer[i] == NULL)break;
			else if (szInputBuffer[i] == '\n')break;
			//runs the rest of the code
			if (szInputBuffer[i] == '<')//begins the sequence to check the tag
			{
				i++;
				cTemp = NewArray(4, char);
				spliceString(szInputBuffer, i, i + 2, &cTemp);
				if (strcmp(cTemp, "!--") == 0)
				{
					while (run == 1)
					{
						if (szInputBuffer[i] == '-')
						{
							spliceString(szInputBuffer, i, i + 2, &cTemp);
							if (strcmp(cTemp, "-->") == 0)
							{
								run = 0;
								i=i + 2;
							}
						}
						i++;
					}
					run = 1;
				}
				else
				{
					if (szInputBuffer[i] == '/')//end tag
					{
						eTemp = NewArray(100, char);
						i++;
						while (szInputBuffer[i] != '>')
						{
							eTemp[j] = szInputBuffer[i];
							j++;
							i++;
						}
						eTemp[j] = '\0';
						if (strcmp(eTemp, stack->elements[stack->count]) == 0)
						{
							Pop(stack);
						}
						else
						{
							printf("The %s and %s tags do not match so the program will end\n", eTemp, stack->elements[stack->count]);
							return 3;
						}
						free(eTemp);
					}
					else//start tag
					{
                                                stack->elements[stack->count]=NewArray(100,char);
						eTemp = NewArray(100, char);
						while (run == 1)
						{
							if ((szInputBuffer[i] != ' ' && szInputBuffer[i] != '>') && szInputBuffer[i] != '/')
							{
								eTemp[j] = szInputBuffer[i];
								j++;
								i++;
							}
							else run = 0;
						}
						run = 1;
                                                eTemp[j] = '\0';
						if (szInputBuffer[i] != '>')
						{
							while (run == 1)
							{
								if (szInputBuffer[i] != '>' && szInputBuffer[i] != '/')i++;
								else if (szInputBuffer[i] == '>')
								{
									Push(stack, eTemp);
									run = 0;
								}
								else if (szInputBuffer[i] == '/')//seperates the single tag from the start /end tag
								{
									while (szInputBuffer[i] != '>')i++;
									run = 0;
								}
							}
							run = 1;
						}
                                                i++;
						free(eTemp);//frees the eTemp
					}
				}
				free(cTemp);//frees the ctemp
			}
		}
	}
	printf("the html tags are in place\n");
	FreeStack(stack);//frees the stack
	fclose(inFile);//closes the file
	return 0;
}

int getInputSwitches(int argc, char *argv[], char **inputFile)
{
	int i;
	char *temp;
	temp = NewArray(1000,char);
	if (argc != 3)return false;//returns false to end the program if there are missing commands
	for (i = 1;i < argc;i++)
	{
		spliceString(argv[i], 1, (strlen(argv[i]) - 1), &temp);
		if (argv[i][0] == '-')//processes the command switches
		{
			if (strcmp(temp, "input") == 0)
			{
				i++;
				spliceString(argv[i], 0, (strlen(argv[i]) - 1), inputFile);
			}
			else return false;//ends if there is no useful command
		}
		else
		{
			printf("Improper Input, ending program\n");//ends if there is no propper input
			return false;
		}
	}
	return true;
}
//makes substrings
void spliceString(char *s, int start, int end, char **str)
{
	int i, count = 0;
	for (i = start;i <= end;i++)
	{
		str[0][count] = s[i];
		count++;
	}
	str[0][count] = '\0';
}

void printUsageInfo()
{
	printf("just type the input using:\ngcc -input (put html file here)");
}
