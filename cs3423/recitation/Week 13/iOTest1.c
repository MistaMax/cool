#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define INPUT_FILE_PATH "input.dat"

typedef struct
{
    char firstName[32];
    char lastName[32];
    double gpa;
} StudentRecord;

int main()
{
    FILE *inputFile;
    StudentRecord *studentM;
    struct stat statBuf;
    int iRecordCount;

    if(stat(INPUT_FILE_PATH, &statBuf) != 0)
    {
        errExit("Could not stat file : %s", strerror(errno));
    }

    iRecordCount = statBuf.st_size / sizeof(StudentRecord);
    if(iRecordCount == 0)
        errExit("File containts less than 1 record");
    
    inputFile = fopen(INPUT_FILE_PATH, "rb");

    studentM = malloc(sizeof(StudentRecord)*iRecordCount);

    fread(studentM, sizeof(StudentRecord), iRecordCount, inputFile);

    int i;
    for(i = 0; i < iRecordCount; i++)
    {
        if (studentM[i].gpa > 3.0)
            printf("%s %s %lf\n", studentM[i].firstName, studentM[i].lastName, studentM[i].gpa);
    }
    
    free(studentM);
    fclose(inputFile);
    return 0;
}