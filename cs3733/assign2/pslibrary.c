#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pslibrary.h"
static char stateChars[] = {'r', 'R', 'w', 0};

void display(string heading, string s1, string s2)
{
    //fprintf(stdout,"\n");
    fprintf(stdout, "%s\n", heading);
    fprintf(stdout, "%s\n", s1);
    fprintf(stdout, "%s\n", s2);
    int iReadyS1Cnt = 0, iReadyS2Cnt = 0, iRunCnt = 0, i;
    double dAvgReady = 0.0;
    float fRunning = 0.00000;

    for (i = 0; i < strlen(s1); i++)
    {
        if (s1[i] == 'r')
            iReadyS1Cnt++;
        else if (s1[i] == 'R')
            iRunCnt++;
    }

    for (i = 0; i < strlen(s2); i++)
    {
        if (s2[i] == 'r')
            iReadyS2Cnt++;
        else if (s2[i] == 'R')
            iRunCnt++;
    }

    dAvgReady = ((double)(iReadyS1Cnt + iReadyS2Cnt)) / 2;

    if (strlen(s1) < strlen(s2))
        fRunning = ((float)iRunCnt) / ((float)strlen(s2));
    else
        fRunning = ((float)iRunCnt) / ((float)strlen(s1));

    fprintf(stdout, "%i, %i, %.1lf, %.5f\n", iReadyS1Cnt, iReadyS2Cnt, dAvgReady, fRunning);
}

void fcfs(string s1, string s2, int x1, int y1, int z1, int x2, int y2, int z2)
{
    int i;              /* next string position (time) */
    int state1 = READY; /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1; /* P1 next CPU burst remaining */
    int cpuLeft2 = x2; /* P2 next CPU burst remaining */
    int ioLeft1 = y1;  /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;  /* P2 next IO burst remaining, 0 if no more IO */

    for (i = 0; (state1 != DONE) || (state2 != DONE); i++)
    {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1 == 0))
        {
            if (ioLeft1 == 0)
            {
                state1 = DONE;
                s1[i] = stateChars[state1]; /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0))
        {
            if (ioLeft2 == 0)
            {
                state2 = DONE;
                s2[i] = stateChars[state2]; /* terminate the string */
            }
            else
                state2 = WAITING;
        }
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0))
        {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0))
        {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ((state1 == READY) && (state2 == READY))
        {
            state1 = RUNNING;
        }
        /* handle one ready and CPU available */
        else if ((state1 == READY) && (state2 != RUNNING))
        {
            state1 = RUNNING;
        }
        else if ((state2 == READY) && (state1 != RUNNING))
        {
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    } /* end of main for loop */
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2)
{
    int i;              /* next string position (time) */
    int state1 = READY; /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1; /* P1 next CPU burst remaining */
    int cpuLeft2 = x2; /* P2 next CPU burst remaining */
    int ioLeft1 = y1;  /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;  /* P2 next IO burst remaining, 0 if no more IO */

    for (i = 0; (state1 != DONE) || (state2 != DONE); i++)
    {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1 == 0))
        {
            if (ioLeft1 == 0)
            {
                state1 = DONE;
                s1[i] = stateChars[state1]; /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0))
        {
            if (ioLeft2 == 0)
            {
                state2 = DONE;
                s2[i] = stateChars[state2]; /* terminate the string */
            }
            else
                state2 = WAITING;
        }
        /* running process has quantum expire */
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0))
        {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0))
        {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ((state1 == READY) && (state2 == READY))
        {
            if (cpuLeft1 > cpuLeft2)
                state2 = RUNNING;
            else
                state1 = RUNNING;
        }
        /* handle one ready and CPU available */
        else if ((state1 == READY) && (state2 != RUNNING))
        {
            state1 = RUNNING;
        }
        else if ((state2 == READY) && (state1 != RUNNING))
        {
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    } /* end of main for loop */
}

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2)
{
    int i;              /* next string position (time) */
    int state1 = READY; /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1; /* P1 next CPU burst remaining */
    int cpuLeft2 = x2; /* P2 next CPU burst remaining */
    int ioLeft1 = y1;  /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;  /* P2 next IO burst remaining, 0 if no more IO */

    for (i = 0; (state1 != DONE) || (state2 != DONE); i++)
    {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1 == 0))
        {
            if (ioLeft1 == 0)
            {
                state1 = DONE;
                s1[i] = stateChars[state1]; /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0))
        {
            if (ioLeft2 == 0)
            {
                state2 = DONE;
                s2[i] = stateChars[state2]; /* terminate the string */
            }
            else
                state2 = WAITING;
        }
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0))
        {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0))
        {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ((state1 == READY) && (state2 == READY))
        {
            if (cpuLeft1 > cpuLeft2)
                state2 = RUNNING;
            else
                state1 = RUNNING;
        }
        /* handle one ready and CPU available */
        else if ((state1 == READY) && (state2 != RUNNING))
        {
            state1 = RUNNING;
        }
        else if ((state2 == READY) && (state1 != RUNNING))
        {
            state2 = RUNNING;
        }
        else if ((state1 == READY) && (cpuLeft1 < cpuLeft2))
        {
            state2 = READY;
            state1 = RUNNING;
        }
        else if ((state2 == READY) && (cpuLeft2 < cpuLeft1))
        {
            state1 = READY;
            state2 = RUNNING;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    } /* end of main for loop */
}

void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2)
{
    int i;              /* next string position (time) */
    int state1 = READY; /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1; /* P1 next CPU burst remaining */
    int cpuLeft2 = x2; /* P2 next CPU burst remaining */
    int ioLeft1 = y1;  /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;  /* P2 next IO burst remaining, 0 if no more IO */
    int qleft;         /* quantum remaining */

    for (i = 0; (state1 != DONE) || (state2 != DONE); i++)
    {
        /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1 == 0))
        {
            if (ioLeft1 == 0)
            {
                state1 = DONE;
                s1[i] = stateChars[state1]; /* terminate the string */
            }
            else
                state1 = WAITING;
        }
        else if ((state2 == RUNNING) && (cpuLeft2 == 0))
        {
            if (ioLeft2 == 0)
            {
                state2 = DONE;
                s2[i] = stateChars[state2];
            }
            else
                state2 = WAITING;
        }
        /* running process has quantum expire */
        if ((state1 == RUNNING) && (qleft == 0))
        {
            state1 = READY;
            qleft = quantum;
            if (state2 == READY)
                state2 = RUNNING;
        }
        if ((state2 == RUNNING) && (qleft == 0))
        {
            state2 = READY;
            qleft = quantum;
            if (state1 == READY)
                state1 = RUNNING;
        }
        /* handle IO complete */
        if ((state1 == WAITING) && (ioLeft1 == 0))
        {
            state1 = READY;
            cpuLeft1 = z1;
        }
        if ((state2 == WAITING) && (ioLeft2 == 0))
        {
            state2 = READY;
            cpuLeft2 = z2;
        }
        /* if both ready, depends on algorithm */
        if ((state1 == READY) && (state2 == READY))
        {
            state1 = RUNNING;
            qleft = quantum;
        }
        /* handle one ready and CPU available */
        else if ((state1 == READY) && (state2 != RUNNING))
        {
            state1 = RUNNING;
            qleft = quantum;
        }
        else if ((state2 == READY) && (state1 != RUNNING))
        {
            state2 = RUNNING;
            qleft = quantum;
        }
        /* insert chars in string, but avoid putting in extra string terminators */
        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
        /* decrement counts */
        qleft--; /* OK to decrement even if nothing running */
        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;
    } /* end of main for loop */
}