#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pslibrary.h"

void printIntArray(int in[], int size);
int sumSubIntArray(int in[], int start, int end);

int main(int argc, char *argv[])
{
    int iIn[7];
    if(argc != 8)
    {
        fprintf(stderr,"Wrong ammount of parameters\n Param Count: %i\n", argc);
        exit(1);
    }
    else
    {
        printf("Assignment 1 program was written by Max Crookshanks\n");
        printf("inputs:");
        int i;
        for(i=1;i<argc;i++)sscanf(argv[i],"%i",&iIn[i-1]);
        printIntArray(iIn, 7);
    }

    string s1, s2;
    s1 = (string) malloc(sumSubIntArray(iIn,1,6)+1);
    s2 = (string) malloc(sumSubIntArray(iIn,1,6)+1);
    //part0(s1,s2);
    fcfsa(s1,s2,iIn[1],iIn[2],iIn[3],iIn[4],iIn[5],iIn[6]);
    display("Part 1\n",s1,s2);
    return 0;
}

void printIntArray(int in[], int size)
{
    int i;
    for(i=0; i<size; i++)printf("%i ",in[i]);
    printf("\n");
}

int sumSubIntArray(int in[], int start, int end)
{
    int i,tmp;
    for(i=start; i<=end; i++)tmp+=in[i];
    return tmp;
}