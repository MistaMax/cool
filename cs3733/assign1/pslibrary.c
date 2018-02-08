#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pslibrary.h"


void part0(string s1, string s2)
{
    strcpy(s1,"RRwwwwwRRRRRRRRR");
    strcpy(s2,"rrRRRRwwwwwwwwrrRRRRRRR");
}

void display(string heading, string s1, string s2)
{
    //fprintf(stdout,"\n");
    fprintf(stdout,"%s\n",heading);
    fprintf(stdout,"%s\n", s1);
    fprintf(stdout,"%s\n",s2);
    int iReadyS1Cnt = 0, iReadyS2Cnt = 0, iRunCnt = 0, i;
    double dAvgReady = 0.0;
    float fRunning = 0.00000;

    for(i=0; i<strlen(s1); i++)
    {
        if(s1[i] == 'r')iReadyS1Cnt++;
        else if(s1[i] == 'R')iRunCnt++;
    }

    for(i=0; i<strlen(s2); i++)
    {
        if(s2[i] == 'r')iReadyS2Cnt++;
        else if(s2[i] == 'R')iRunCnt++;
    }

    dAvgReady = (iReadyS1Cnt+iReadyS2Cnt)/2;

    if(strlen(s1) < strlen(s2))fRunning = ((float)iRunCnt)/((float)strlen(s2));
    else fRunning = ((float)iRunCnt)/((float)strlen(s1));

    fprintf(stdout,"%i, %i, %.1lf, %.5f\n", iReadyS1Cnt, iReadyS2Cnt, dAvgReady, fRunning);
}

void fcfsa(string s1, string s2, int x1, int y1, int z1, int x2, int y2, int z2)
{
    int i1=0, i2=0, i;
    for(i=0; i<x1; i++)
    {
        s1[i] = 'R';
        s2[i] = 'r';
    }

    i1 = i;
    i2 = i;

    for(i = i1+y1; i1 < i; i1++)
        s1[i1] = 'w';
    for(i = i2+x2; i2 < i; i2++)
        s2[i2] = 'R';
    
    if(i2+y2<i1)
    {
        for(i = i2+y2; i2 < i; i2++)
            s2[i2] = 'w';
        for(i = i2+z2; i2 < i; i2++)
            s2[i2] = 'R';
        for(; i1 < i2; i1++)
            s1[i1] = 'r';
        for(i = i1+z1; i1 < i; i1++)
            s1[i1] = 'R';
    }
    else
    {
        for(; i1 < i2; i1++)
            s1[i1] = 'r';
        for(i = i2+y2; i2 < i; i2++)
            s2[i2] = 'w';
        for(i = i1+z1; i1 < i; i1++)
            s1[i1] = 'R';
        for(; i2 < i1; i2++)
            s2[i2] = 'r';
        for(i = i2+z2; i2 < i; i2++)
            s2[i2] = 'R';
    }

    s1[i1] = '\0';
    s2[i2] = '\0';
}
