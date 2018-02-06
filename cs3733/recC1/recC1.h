typedef struct PCB 
{
    int ProcId;
    int ProcPR;
    int CPUburst;
    int Reg[8];
    int queueEnterClock, waitingTime;
    struct PCB *next;
} node, *pNode;

pNode allocNode();