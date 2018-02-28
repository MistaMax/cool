#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_PERMS (S_IRWXU | S_IWGRP | S_IWOTH)

#define false 0
#define true 1
typedef int bool;

int main(int argc, char *argv[])
{
    int TOTAL = 0;

    if (doesPipeExist("ATM1") == false)
        mkfifo("ATM1", FIFO_PERMS);

    if (doesPipeExist("ATM2") == false)
        mkfifo("ATM2", FIFO_PERMS);

    int atm1 = 0, atm2 = 0;

    atm1 = open("ATM1", O_RDONLY | O_NONBLOCK);
    if (atm1 < 0)
    {
        printf("ERROR: unable to open file\n");
        exit(atm1);
    }

    atm2 = open("ATM2", O_RDONLY | O_NONBLOCK);
    if (atm2 < 0)
    {
        printf("ERROR: unable to open file\n");
        exit(atm2);
    }

    for (;;)
    {
        fd_set fds;
        int maxfd;
        int res;
        int buf;
        //char buf[256];

        FD_ZERO(&fds); // Clear FD set for select
        FD_SET(atm1, &fds);
        FD_SET(atm2, &fds);

        maxfd = atm1 > atm2 ? atm1 : atm2;
        select(maxfd + 1, &fds, NULL, NULL, NULL);

        if (FD_ISSET(atm1, &fds))
        {
            // We can read from atm1
            res = read(atm1, &buf, sizeof(int));
            if (res > 0)
            {
                TOTAL += buf;
                printf("Total: %i\n", TOTAL);
            }
        }
        if (FD_ISSET(atm2, &fds))
        {
            // We can read from atm2
            res = read(atm2, &buf, sizeof(int));
            if (res > 0)
            {
                TOTAL += buf;
                printf("Total: %i\n", TOTAL);
            }
        }
    }
    return 0;
}

bool doesPipeExist(char *name)
{
    struct stat info;
    return (stat(name, &info) == 0);
}
