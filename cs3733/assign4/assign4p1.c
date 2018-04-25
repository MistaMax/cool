#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"

//pthread_mutex_t printf_mutex = PTHREAD_MUTEX_INITIALIZER; //unused but allows make all to be used happily

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Not enough args\n");
        exit(-1);
    }

    int nthreads = atoi(argv[1]);
    printf("Max Crookshanks\nAssignment 4: # of threads = %i\n",nthreads);
    creatPhilosophers(nthreads);
    return 0;
}