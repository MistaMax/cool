#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
//void errExit(const char szFmt[], ... );
int main (int argc, char *argv[])
{
    long lForkPid;
    int iExitStatus = 0;    
    printf("Level 1!\n");
    lForkPid = fork();
    switch(lForkPid)
    {
        case -1:
            //errExit("fork failed: %s", strerror(errno));
        break;
        case 0:  // child process
            printf("Level 2!\n");
            if (fork() == 0)
            {
                printf("Level 3!\n");
                return 0;
            }
            wait(&iExitStatus);
        break;
        default: // parent process
            printf("Level 2!\n");
            wait(&iExitStatus);

    }
    printf("Level 0!\n");
    return 0;
}
