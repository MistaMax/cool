#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "myio.h"

int main(int argc, char *argv[])
{
    int atm = open(argv[1],O_WRONLY | O_NONBLOCK);
    if(atm < 0)
    {
        printf("ERROR: Can not open pipe\n");
        exit(-1);
    }
    printf("%s\n", argv[1]);
    for(;;)
    {
        printf("Please enter a deposit:\n");
        int in = ReadInteger();
        printf("I read in %i\n",in);
        if(in < 0)break;
        else write(atm,&in,sizeof(int));
    }
    return 0;
}