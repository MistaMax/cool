#include <stdio.h>

typedef struct
{
    char firstName[32];
    char lastName[32];
    double gpa;
} StudentRecord;
void errExit(const char szFmt[], ... );

int main()
{
    char *file_path = "gpas.dat"
    FILE *gpaFile = fopen(file_path, "wb");
    StudentRecord student;

	while(fgets(szInputBuffer, 100, stdin) != NULL){
		sscanf(szInputBuffer, "%s %s %lf", student.firstName, student.lastName, &student.gpa);
        fwrite(&student, sizeof(StudentRecord), 1, gpaFile);
	}

    return 0;
}
