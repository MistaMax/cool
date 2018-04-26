#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void philosopherThread(void *pVoid);
void creatPhilosophers(int nthreads);
void thinking();
void pickUpChopsticks(int threadIndex);
void eating();
void putDownChopsticks(int threadIndex);

static pthread_mutex_t *chopsticks;
static pthread_cond_t *cond;
int threadCount;

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
    printf("This is philosopher %i\n", *((int *)pVoid));
    printf("Philosopher %i: Thinking\n", *((int *)pVoid));
    thinking();
    pickUpChopsticks(*((int *)pVoid));
    printf("Philosopher %i: Eating\n", *((int *)pVoid));
    eating();
    printf("Philosopher %i: Done Eating\n", *((int *)pVoid));
    putDownChopsticks(*((int *)pVoid));
    free(pVoid);
    return NULL;
}

void creatPhilosophers(int nthreads)
{
    pthread_t *tids;
    tids = (pthread_t *)malloc(nthreads * sizeof(pthread_t *));
    chopsticks = (pthread_mutex_t *)malloc(nthreads * sizeof(pthread_mutex_t));
    cond = (pthread_cond_t *)malloc(nthreads * sizeof(pthread_cond_t));
    threadCount = nthreads;
    
    int i;
    for(i=0;i<nthreads;i++)
        pthread_mutex_init(chopsticks+i,NULL);
    
    for(i=0;i<nthreads;i++)
        pthread_cond_init(cond+i,NULL);
    
    for (i = 0; i < nthreads; i++){
        int *n = (int *)malloc(sizeof(int));
        *n = i;
        if (pthread_create(tids + i, NULL, philosopherThread, (void *)n))
        {
            printf("Error creating thread %i\n", i + 1);
            exit(1);
        }
    }

    for (i = 0; i < nthreads; i++)
        if (pthread_join(tids[i], NULL))
        {
            fprintf(stderr, "Error joining thread %i\n", i + 1);
            exit(1);
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