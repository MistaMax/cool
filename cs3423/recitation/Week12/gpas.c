#include <stdio.h>


int main(int argc, char *argv[]){
	char *file_path "gpas.txt";
	FILE *outputFile;

	char szInputBuffer[101];
	char first_name[42];
	char last_name[42];
	double gpa;

	outputFile = fopen(file_path, "w");
	while(fgets(szInputBuffer, 100, stdin) != NULL){
		sscanf(szInputBuffer, "%s %s %lf", first_name, last_name, &gpa);
		fprintf(outputFile, "%s %s %lf\n", first_name, last_name, gpa);
	}

	return 0;
}
