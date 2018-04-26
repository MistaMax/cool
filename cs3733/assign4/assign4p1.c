#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"

void philosopherThread(void *pVoid);
void creatPhilosophers(int nthreads);

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

void philosopherThread(void *pVoid)
{
    printf("This is philosopher %li\n", ((thread_info_t) pVoid)->n);
    free(pVoid);
    return NULL;
}

void creatPhilosophers(int nthreads)
{
    pthread_t *tids;
    tids = (pthread_t *)malloc(nthreads * sizeof(pthread_t *));
    int i;
    for (i = 0; i < nthreads; i++){
        thread_info_t info = newThreadInfo();
        info->n = i;
        if (pthread_create(tids + i, NULL, philosopherThread, info))
        {
            printf("Error creating thread %i\n", i + 1);
            return 1;
        }
    }

    for (i = 0; i < nthreads; i++)
        if (pthread_join(tids[i], NULL))
        {
            fprintf(stderr, "Error joining thread %i\n", i + 1);
            return 1;
        }
    free(tids);
}