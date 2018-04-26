#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "cs3423p8.h"

#define MAX_COMMANDS 5
#define true 1
#define false 0
typedef int bool;

bool isExistingFile(char *szFName);
bool longInArray(long l, long arr[], int arrLength);
int makeForkPipe(int in, int out, Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt, int iLoc);

//Executes commands with thier arguments in parrallel using multiple forks
//Takes in cmdM which contains the command name and all the location of input, output, and args in tokenM
int concCmd(Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt)
{
    //initializing all the files
    int iExitStatus = 0;
    long lPid;
    char *execArgv[50];
    long lChildrenPid[iCmdCnt];
    int i;
    //for loop that creates all the forks
    for (i = 0; i < iCmdCnt; i++)
    {
        lPid = fork();
        //creates the fork and stores the pid in lPid, if lpid is 0 then it is the child that is running
        //if it is -1 then the pipe failed
        //otherwise the parent is running
        switch (lPid)
        {
        case -1: //exits if it is a bad fork
            errExit("fork failed: %s\n", "sterror(errno)");
            break;
        case 0:
            //child fork
            //preps the argvs for the execvp function
            execArgv[0] = cmdM[i].szCmdNm;
            int iV = 1; //stores the current index of execArgv
            int iS;     //used as the loop index
            fprintf(stderr, "%i %i: %s", getppid(), getpid(), cmdM[i].szCmdNm);
            //loops through to add all the args to the array of the command
            for (iS = cmdM[i].iBeginIdx; iS <= cmdM[i].iEndIdx; iS++)
            {
                fprintf(stderr, " %s", tokenM[iS]); //prints the argument
                execArgv[iV] = tokenM[iS];          //saves the argument in execArgv
                iV++;                               //increments iV
            }
            fprintf(stderr, "\n"); //ends the standard error with a new line for the next fork display
            //ends the array with NULL so execvp knows when to stop
            execArgv[iV] = NULL;
            //runs if iStdinRedirect is not 0, itredirects all the standard input to a specified file
            if (cmdM[i].iStdinRedirectIdx)
            {
                int in;
                //ensures that the file exists
                if (!isExistingFile(tokenM[cmdM[i].iStdinRedirectIdx]))
                    errExit("File DNE %s\n", tokenM[cmdM[i].iStdinRedirectIdx]);
                //ensures the file opened correctly
                if ((in = open(tokenM[cmdM[i].iStdinRedirectIdx], O_RDONLY)) == -1)
                    errExit("Open failed: %s", tokenM[cmdM[i].iStdinRedirectIdx]);
                //ensures the dup2 functioned correctly
                if (dup2(in, STDIN_FILENO) == -1)
                    errExit("Dup2 failed!");
                close(in); //closes the file
            }

            //making the output file and redirecting it
            if (cmdM[i].iStdoutRedirectIdx)
            {
                int out;
                //if the file exists, it will be removed
                if (isExistingFile(tokenM[cmdM[i].iStdoutRedirectIdx]))
                    remove(tokenM[cmdM[i].iStdoutRedirectIdx]);
                //ensures that the file was created successfully
                if ((out = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1)
                    errExit("File creation failed: %s", tokenM[cmdM[i].iStdoutRedirectIdx]);
                //ensures that dup2 functioned correctly
                if (dup2(out, STDOUT_FILENO) == -1)
                    errExit("Dup2 failed!");

                close(out); //closes file
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
    if (lPid == 0) //just insurance that all forks kill themselves
        exit(0);

    int iDeadChildCount = 0; //stores the ammount of dead children processes in relation to this function
    //ensures all the children exit before continuing
    while (iDeadChildCount != iCmdCnt)
    {
        if (longInArray(wait(&iExitStatus), lChildrenPid, iCmdCnt)) //checks to see if the dead child is in the array, if so increment iDeadChildCount
            iDeadChildCount++;
    }
    return 0; //returns 0 if everything worked propperly
}
//makes a fork to redirect the in and out of the pipes and run the command
int makeForkPipe(int in, int out, Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt, int iLoc)
{
    char *execArgv[50];
    //stores the pid of the fork
    long lPid;
    //redirects all the inputs and outputs after the fork is created
    if ((lPid = fork()) == 0)
    {
        //prints the parent pid, child pid, and the arguments that go along with it
        execArgv[0] = cmdM[iLoc].szCmdNm;
        int iV = 1;
        int iS;
        fprintf(stderr, "%i %i: %s", getppid(), getpid(), cmdM[iLoc].szCmdNm);
        //loops through to add all the args to the array of the command
        for (iS = cmdM[iLoc].iBeginIdx; iS <= cmdM[iLoc].iEndIdx; iS++)
        {
            fprintf(stderr, " %s", tokenM[iS]);
            execArgv[iV] = tokenM[iS];
            iV++;
        }
        fprintf(stderr, "\n");
        execArgv[iV] = NULL;
        //redirects the in if it is not the default of standard in
        if (in != STDIN_FILENO)
        {
            if (dup2(in, STDIN_FILENO) == -1)
                errExit("Dup2 Failed!");
            close(in);
        }
        //redirects the out if it is not the default of standard out
        if (out != STDOUT_FILENO)
        {
            if (dup2(out, STDOUT_FILENO) == -1)
                errExit("Dup2 Failed!");
            close(out);
        } 
        //runs the command
        execvp(execArgv[0], execArgv);
        exit(0);
    }
    else if (lPid == -1)
        errExit("Fork failed!");

    return lPid;
}

//int fork_pipes(int n, Cmd cmdM[])
int pipeCmd(Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt)
{
    int i;
    long pid;
    int in, out, fd[2];
    int iExitStatus = 0;
    long lPidArr[iCmdCnt];

    /* The first process should get its input from the original file descriptor 0.  */
    if (cmdM[0].iStdinRedirectIdx)
    {
        if (!isExistingFile(tokenM[cmdM[0].iStdinRedirectIdx]))
            errExit("File DNE %s\n", "sterror(errno)");

        if ((in = open(tokenM[cmdM[0].iStdinRedirectIdx], O_RDONLY)) == -1)
            errExit("Open Failed: %s", tokenM[cmdM[0].iStdinRedirectIdx]);
    }
    else
    {
        in = STDIN_FILENO; //defaults to the standard in if no input file is specified
    }
    //
    for (i = 0; i < iCmdCnt; ++i)
    {
        if (i < iCmdCnt - 1)//runs this if another pipe needs to be created
        {
            //generates a pipe with the file descriptor array
            pipe(fd);
            //creates a fork that redirects input and output for piping and executes the command
            lPidArr[i] = makeForkPipe(in, fd[1], cmdM, iCmdCnt, tokenM, iTokenCnt, i);
            //closes the output file as it is now the input
            close(fd[STDOUT_FILENO]);
            //sets n to the current input
            in = fd[STDIN_FILENO];
        }
        else
        {
            if (cmdM[i].iStdoutRedirectIdx)
            {
                if (isExistingFile(tokenM[cmdM[i].iStdoutRedirectIdx]))
                    remove(tokenM[cmdM[i].iStdoutRedirectIdx]);

                if ((out = open(tokenM[cmdM[i].iStdoutRedirectIdx], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1)
                    errExit("Open Failed on file: %s", tokenM[cmdM[i].iStdoutRedirectIdx]);
            }
            else
            {
                out = STDOUT_FILENO;
            }

            lPidArr[i] = makeForkPipe(in, fd[1], cmdM, iCmdCnt, tokenM, iTokenCnt, i);
        }
    }
    //stores the ammount of dead children processes in relation to this function
    int iDeadChildCount = 0;
    //ensures all the children exit before continuing
    while (iDeadChildCount != iCmdCnt)
    {
        if (longInArray(wait(&iExitStatus), lPidArr, iCmdCnt)) //checks to see if the dead child is in the array, if so increment iDeadChildCount
            iDeadChildCount++;
    }
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
