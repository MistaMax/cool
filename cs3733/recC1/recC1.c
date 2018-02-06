#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recC1.h"
#include "myio.h"

void insertNode(pNode tmp, pNode Head, pNode Tail);
pNode genNode();

int main(int argc, char *argv[])
{
    FILE *in;
    string line;
    in = fopen(argv[1],"r");
    fprintf(stderr,"Opened file\n");
    line=ReadLineFile(in);
    while(line != NULL)
    {
        int tmpProcId = 0, tmpProcPriority = 0, tmpCPUburstTime = 0;
        int iscanfCnt = sscanf(line,"%i %i %i \n", &tmpProcId, &tmpProcPriority, &tmpCPUburstTime);
        if(iscanfCnt != 3)
        {
            fprintf(stderr, "wrong ammount of ints\n");
            exit(2);
        }
        pNode tmp = genNode();

        tmp->ProcId = tmpProcId;
        tmp->ProcPR = tmpProcPriority;
        tmp->CPUburst = tmpCPUburstTime;
        tmp->queueEnterClock = 0;
        tmp->waitingTime=0;

        int i;
        for(i=0; i<8; i++)
        {
            tmp->Reg[i] =tmpProcId;
        }
        
        insertNode(tmp, Head, Tail);
        free(line);
        line=ReadLineFile(in);
    }

    fclose(in);
    printf("Max Crookshanks, Recitation 1, input.txt\n");
    FIFO_Scheduling(Head);
    return 0;
}

void FIFO_Scheduling(pNode Head)
{
    int CPUreg[8] = {0};
    pNode Head=NULL;
    pNode Tail=NULL;
    int Clock=0;
    int Total_waiting_time=0;
    int Total_turnaround_time=0;
    int Total_job=0;
    int i;
    pNode p;
    for(p = Head; p != NULL; p=p->next)
    {
        memcpy(CPUreg,p->Reg,8);
        for(i=0; i<8; i++)CPUreg[i]++;
        memcpy(p->Reg,CPUreg,8);
        p->waitingTime = p->waitingTime + Clock - p->queueEnterClock;
        Total_waiting_time = Total_waiting_time + p->waitingTime ;
        Clock = Clock + p->CPUburst;
        Total_turnaround_time = Total_turnaround_time + Clock;
        Total_job = Total_job + 1;
    }
}

pNode genNode()
{
    pNode tmp = NULL;
    tmp = (pNode) malloc(sizeof(node));
    tmp->next = NULL;
    if(tmp == NULL)
    {
        fprintf(stderr,"Failed to malloc\n");
        exit(1);
    }
    return tmp;
}

void insertNode(pNode tmp, pNode Head, pNode Tail)
{
    if(Head == NULL)
    {
        Head = tmp;
        Tail = tmp;
    }
    else
    {
        Tail->next = tmp;
        Tail = tmp;
    }
}
