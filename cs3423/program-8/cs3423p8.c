#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "cs3423p8.h"

#define MAX_COMMANDS 5
#define true 1
#define false 0
typedef int bool;

int concCmd(Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt)
{
    int iExitStatus = 0;
    long lPid;
    char *execArgv[20];
    long lChildrenPid[iCmdCnt];
    int i;
    //printf("Started Propperly\n");
    for (i = 0; i < iCmdCnt; i++)
    {
        lPid = fork();
        switch (lPid)
        {
        case -1:
            errExit("fork failed: %s\n", "sterror(errno)");
            break;
        case 0:
            //child fork
            //preps the argvs for the execvp function
            execArgv[0] = cmdM[i].szCmdNm;
            int iV = 1;
            int iS;
            //loops through to add all the args to the array of the command
            for (iS = cmdM[i].iBeginIdx; iS <= cmdM[i].iEndIdx; iS++)
            {
                execArgv[iV] = tokenM[iS];
                iV++;
            }
            //ends the array with NULL so execvp knows when to stop
            execArgv[iV] = NULL;
            //runs if iStdinRedirect is not 0, itredirects all the standard input to a specified file
            if (cmdM[i].iStdinRedirectIdx)
            {
                int in;
                if (!isExistingFile(tokenM[cmdM[i].iStdinRedirectIdx]))
                    errExit("File DNE %s\n", "sterror(errno)");

                in = open(tokenM[cmdM[i].iStdinRedirectIdx], O_RDONLY);
                dup2(in, STDIN_FILENO);
                close(in);
            }

            //making the output file and redirecting it
            if (cmdM[i].iStdoutRedirectIdx)
            {
                int out;
                if (isExistingFile(tokenM[cmdM[i].iStdoutRedirectIdx]))
                    remove(tokenM[cmdM[i].iStdoutRedirectIdx]);

                out = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
                dup2(out, STDOUT_FILENO);
                close(out);
            }
            //runs the command with all the args
            execvp(cmdM[i].szCmdNm, execArgv);
            exit(0);
            break;
        default:
            //runs if parent function, adds the child lPid to the array
            lChildrenPid[i] = lPid;
            break;
        }
    }
    if (lPid == 0)
        exit(0);

    int iDeadChildCount = 0;
    while (iDeadChildCount != iCmdCnt)
    {
        if (longInArray(wait(&iExitStatus), lChildrenPid, iCmdCnt))
            iDeadChildCount++;
    }
    return 0;
}

int makeForkPipe(int in, int out, char *args[])
{
    long pid;

    if ((pid = fork()) == 0)
    {
        if (in != STDIN_FILENO)
        {
            dup2(in, STDIN_FILENO);
            close(in);
        }

        if (out != STDOUT_FILENO)
        {
            dup2(out, STDOUT_FILENO);
            close(out);
        }

        execvp(args[0], args);
        exit(0);
    }

    return pid;
}

//int fork_pipes(int n, Cmd cmdM[])
int pipeCmd(Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt)
{
    int i, iS, iV;
    long pid;
    int in, out, fd[2];
    char *execArgv[50];
    int iExitStatus = 0;
    long lPidArr[iCmdCnt];
    //printf("\n%s\n\n\n",tokenM[cmdM[iCmdCnt-1].iStdoutRedirectIdx]);

    /* The first process should get its input from the original file descriptor 0.  */
    if (cmdM[0].iStdinRedirectIdx)
    {
        if (!isExistingFile(tokenM[cmdM[0].iStdinRedirectIdx]))
            errExit("File DNE %s\n", "sterror(errno)");

        if((in = open(tokenM[cmdM[0].iStdinRedirectIdx], O_RDONLY)) == -1)
            errExit("Open Failed: %s", tokenM[cmdM[0].iStdinRedirectIdx]);
    }
    else
    {
        in = STDIN_FILENO;
    }

    for (i = 0; i < iCmdCnt - 1; ++i)
    {
        execArgv[0] = cmdM[i].szCmdNm;
        iV = 1;
        //loops through to add all the args to the array of the command
        for (iS = cmdM[i].iBeginIdx; iS <= cmdM[i].iEndIdx; iS++)
        {
            execArgv[iV] = tokenM[iS];
            iV++;
        }
        execArgv[iV] = NULL;

        pipe(fd);

        lPidArr[i] = makeForkPipe(in, fd[1], execArgv);
        
        close(fd[1]);

        in = fd[0];
        //wait(&iExitStatus);
    }

    if (in != STDIN_FILENO)
        dup2(in, STDIN_FILENO);

    execArgv[0] = cmdM[i].szCmdNm;
    iV = 1;
    //loops through to add all the args to the array of the command
    for (iS = cmdM[i].iBeginIdx; iS <= cmdM[i].iEndIdx; iS++)
    {
        execArgv[iV] = tokenM[iS];
        iV++;
    }
    //ends the array with NULL so execvp knows when to stop
    execArgv[iV] = NULL;

    if (cmdM[i].iStdoutRedirectIdx)
    {
        if (isExistingFile(tokenM[cmdM[i].iStdoutRedirectIdx]))
            remove(tokenM[cmdM[i].iStdoutRedirectIdx]);
        
        if((out = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1)
            errExit("Open Failed on file: %s", tokenM[cmdM[i].iStdoutRedirectIdx]);
    }
    else
    {
        out = STDOUT_FILENO;
    }
    /* Execute the last stage with the current process. */
    lPidArr[i] = makeForkPipe(in, out, execArgv);
    wait(&iExitStatus);
    return 0;
}

bool longInArray(long l, long arr[], int arrLength)
{
    int i;
    for (i = 0; i < arrLength; i++)
    {
        if (l == arr[i])
            return true;
    }
    return false;
}

bool isExistingFile(char *szFName)
{
    if (access(szFName, F_OK) != -1)
        return true;
    return false;
}