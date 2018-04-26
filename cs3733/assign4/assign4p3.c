#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"

void philosopherThread(void *pVoid);
void creatPhilosophers(int nthreads);
void thinking();
void pickUpChopsticks(int threadIndex);
void eating();
void putDownChopsticks(int threadIndex);

static pthread_mutex_t syncro = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t *chopsticks;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int threadCount;
static int nextIndex;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Not enough args\n");
        exit(-1);
    }

    int nthreads = atoi(argv[1]);
    printf("Max Crookshanks\nAssignment 4: # of threads = %i\n", nthreads);
    creatPhilosophers(nthreads);
    return 0;
}

void philosopherThread(void *pVoid)
{
    printf("This is philosopher %li\n", ((thread_info_t) pVoid)->n);

    printf("Philosopher %i: Thinking\n", ((thread_info_t) pVoid)->n);
    thinking();

    pthread_mutex_lock(&syncro);

    while(nextIndex!=((thread_info_t) pVoid)->n)
    {
        pthread_cond_wait(&cond,&syncro);
        pthread_cond_signal(&cond);
    }

    pickUpChopsticks(((thread_info_t) pVoid)->n);

    printf("Philosopher %i: Eating\n", ((thread_info_t) pVoid)->n);
    eating();

    printf("Philosopher %i: Done Eating\n", ((thread_info_t) pVoid)->n);
    putDownChopsticks(((thread_info_t) pVoid)->n);

    nextIndex++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&syncro);

    free(pVoid);
    return NULL;
}

void creatPhilosophers(int nthreads)
{
    pthread_t *tids;
    tids = (pthread_t *)malloc(nthreads * sizeof(pthread_t *));
    chopsticks = (pthread_mutex_t *)malloc(nthreads * sizeof(pthread_mutex_t));
    threadCount = nthreads;
    nextIndex = 0;

    int i;
    for(i=0;i<nthreads;i++)
        pthread_mutex_init(chopsticks+i,NULL);
    
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

void thinking()
{
    int randy = (rand() % 499) + 1;
    usleep(randy);
}

void pickUpChopsticks(int threadIndex)
{
    pthread_mutex_lock(chopsticks+threadIndex);
    pthread_mutex_lock(chopsticks+((threadIndex+1) % threadCount));
}

void eating()
{
    int randy = (rand() % 499) + 1;
    usleep(randy);
}

void putDownChopsticks(int threadIndex)
{
    pthread_mutex_unlock(chopsticks+threadIndex);
    pthread_mutex_unlock(chopsticks+((threadIndex+1) % threadCount));
}