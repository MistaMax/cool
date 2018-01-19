#include "myio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_INPUT_SIZE 120

int ReadInteger()
{
    string line;
    int iVal;
    char termch;

    while (true) {
        printf("Please enter an integer:\n");
        line = ReadLine();
        switch (sscanf(line, " %d %c", &iVal, &termch)) {
          case 1:
            free(line);
            return (iVal);
          case 2:
            printf("Unexpected character: '%c'\n", termch);
            break;
          default:
            printf("Error: not an integer");
            break;
        }
        free(line);
    }
}

double ReadDouble()
{
    string line;
    double dVal;
    char termch;

    while (true) {
        printf("Please enter a double:\n");
        line = ReadLine();
        switch (sscanf(line, " %lf %c", &dVal, &termch)) {
          case 1:
            free(line);
            return (dVal);
          case 2:
            printf("Unexpected character: '%c'\n", termch);
            break;
          default:
            printf("Error: not a double\n");
            break;
        }
        free(line);
    }
}
/*****************************************************************
 * ReadLine()
 * 
 * Description:
 *  reads in a line from stdin
******************************************************************/
string ReadLine()
{
    return ReadLineFile(stdin);
}
/*****************************************************************
 * ReadLineFile(FILE *fIn)
 * 
 * Description:
 *  reads in a line from a file
 * 
 * Parameters:
 *  - FILE *fIn:
 *      should contain a preopened file
******************************************************************/
string ReadLineFile(FILE *fIn)
{
    string szTmpLine, line;
    int n, iCharacter, iSize;
    n = 0;
    iSize = DEFAULT_INPUT_SIZE;
    line = malloc(iSize + 1);
    while ((iCharacter = getc(fIn)) != '\n' && iCharacter != EOF) {
        if (n == iSize) {
            iSize *= 2;
            szTmpLine = (string) malloc(iSize + 1);
            strncpy(szTmpLine, line, n);
            free(line);
            line = szTmpLine;
        }
        line[n++] = iCharacter;
    }
    if (n == 0 && iCharacter == EOF) {
        free(line);
        return (NULL);
    }
    line[n] = '\0';
    szTmpLine = (string) malloc(n + 1);
    strcpy(szTmpLine, line);
    free(line);
    return (szTmpLine);
}