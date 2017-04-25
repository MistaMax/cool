#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header05.h"

int main(int argc, char *argv[])
{
	FILE *infp, *outfp;
	char *cInfp, *cOutfp;
	//dynamically allocating the strings for the files
	cInfp = (char *)malloc(50 * sizeof(char));
	cOutfp = (char *)malloc(50 * sizeof(char));
	//gets the input from the execution line and returns false if unsuccessful thus ending the program
	if (getInputSwitches(argc, argv, &cInfp, &cOutfp) == false)
	{
		printUsageInfo();
		return 1;
	}
	//opening files
	infp = fopen(cInfp, "r");
	outfp = fopen(cOutfp, "w");
	//general variables for the scanf cycle
	int ev, task, days, tDays = 0;
	//prints out the labels for the table
	fprintf(outfp, "Project Completion Table\n--------------------------------------------------\n|%-6s|%-16s|%-20s|\n--------------------------------------------------\n", "Event", "Num of tasks", "Max num. of days");
	while (fscanf(infp, "%d %d %d\n", &ev, &task, &days) == 3)//scans for the data until there is no more
	{
		fprintf(outfp, "|%-6i|%-16i|%-20i|\n", ev, task, days);
		tDays = days + tDays;
	}
	//ending of the table and the total number of days
	fprintf(outfp, "--------------------------------------------------\nTotal number of days to finish the project: ");
	if (tDays == 1)fprintf(outfp, "1 day\n");//prints 1 day if total days is 1
	else fprintf(outfp, "%i days\n", tDays);//prints all the days if it is more than one
	//closing the files
	fclose(infp);
	fclose(outfp);
	return 0;
}
//reads the execution line for inputs
bool getInputSwitches(int argc, char *argv[], char **inputFile, char **outputFile)
{
	int i;
	char *temp;
	temp = (char *)malloc(50 * sizeof(char));
	if (argc != 5)return false;//returns false to end the program if there are missing commands
	for (i = 1;i < argc;i++)
	{
		spliceString(argv[i], 1, (strlen(argv[i]) - 1), &temp);
		if (argv[i][0] == '-')//processes the command switches
		{
			if (strcmp(temp, "output") == 0)
			{
				i++;
				spliceString(argv[i], 0, (strlen(argv[i]) - 1), outputFile);
			}
			else if (strcmp(temp, "input") == 0)
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
//prints the usage info
void printUsageInfo()
{
	printf("to compile the code you must first type the input and output file for the code\n");
	printf("type:\n");
	printf("./r5 -output PUT_OUTPUT_HERE -input PUT_INPUT_HERE\n");
}
