#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "cs3423p8.h"

#define MAX_COMMANDS 5

int concCmd(Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt){
    int iExitStatus = 0;
    long lPid;
    char *execArgv[20];
    int i;
    printf("Started Propperly\n");
    for(i = 0; i < iCmdCnt; i++)
    {
        lPid = fork();

        switch(lPid){
            case -1:
                errExit("fork failed: %s\n", "sterror(errno)");
            break;
            case 0:
                //child fork
                //printf("it me a child %i\n", i);
                if(cmdM[i].iBeginIdx != 0)
                {
                    int iS;
                    for(iS = cmdM[i].iBeginIdx; iS <= cmdM[i].iEndIdx; iS++)
                        execArgv[iS-cmdM[i].iBeginIdx] = tokenM[iS];
                    
                    execArgv[iS-cmdM[i].iBeginIdx] = NULL;
                }
                else
                    execArgv[0] = NULL;
                
                int out = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_CREATE | O_RDWR);
                dup2(out,STDOUT_FILENO);
                close(out);
                execvp(cmdM[i].szCmdNm, execArgv);
                exit(0);
            break;
            default:
                //runs if parent function
                //printf("it me da parent %li\n", lPid);
                printf("%i %i\n", cmdM[i].iBeginIdx, cmdM[i].iEndIdx);
            break;
        }
    }
    if(lPid == 0)
        exit(0);

    wait(&iExitStatus);
    return 0;
}

int pipeCmd(Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt){
    int i;
}