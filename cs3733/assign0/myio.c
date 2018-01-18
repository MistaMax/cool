#include "myio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_VALUE 100

#define true 1
#define false 0
typedef int bool;

int ReadInteger()
{
    int i = 0;
    int iScanfCnt = 0;
    int iLoopCnt;
    char *lineIn = NULL;
    while(1)
    {
        iLoopCnt = 0;
        printf("Please input a single integer:\n");
        lineIn = ReadLine();
        sscanf(lineIn, "%d", &i);
        break;
        /*if(iLoopCnt == 1)break;
        else printf("ERROR: Imporopper Input, please try again\n");*/
    }
    return i;
}

double ReadDouble()
{
    double d = 0;
    int iScanfCnt = 0;
    int iLoopCnt;
    char *lineIn = NULL;
    while(1)
    {
        iLoopCnt = 0;
        printf("Please input a single integer:\n");
        lineIn = ReadLine();
        sscanf(lineIn, "%lf", &d);
        break;
        /*if(iLoopCnt == 1)break;
        else printf("ERROR: Imporopper Input, please try again\n");*/
    }
    return d;
}

char *ReadLine()
{
    char *line = NULL;
    size_t size = 0;
    getline(&line, &size, stdin);
    line[strlen(line)-1] = '\0';
    return line;
}

char *ReadLineFile(FILE *infile)
{
    char *line = NULL;
    size_t size = 0;
    getline(&line, &size, infile);
    line[strlen(line)-1] = '\0';
    return line;
}


int main()
{
    //printf("%s\n",ReadLine());
    printf("%d\n",ReadDouble());
    return 0;
}