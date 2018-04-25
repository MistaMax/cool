#include "philosopher.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void philosopherThread(void *pVoid)
{
    printf("This is philosopher %li\n", ((thread_info_t) pVoid)->n+1);
    free(pVoid);
    return NULL;
}

thread_info_t newThreadInfo()
{
    thread_info_t tmp;
    tmp = (thread_info_t)malloc(sizeof(ti));
    return tmp;
}

//old idea
/*tInfoArr newThreadInfoArray(int size)
{
    tInfoArr tmp;
    tmp = (tInfoArr)malloc(sizeof(tiArr));
    tmp->size = size;
    tmp->arr = (thread_info_t *)malloc(size*sizeof(thread_info_t));
    int i;
    for(i=0;i<size;i++)
        *((tmp->arr)+i) = newThreadInfo();
    return tmp;
}


void freeThreadInfoArray(tInfoArr tmp)
{
    int i;
    for(i=0;i<tmp->size;i++)
        free(*((tmp->arr)+i));
    free(tmp->arr);
    free(tmp);
}*/

void creatPhilosophers(int nthreads)
{
    pthread_t *tids;
    tids = (pthread_t *)malloc(nthreads * sizeof(pthread_t *));
    int i;
    for (i = 0; i < nthreads; i++){
        printf("%i\n",i);
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

void thinking(){

}
void pickUpChopsticks(int threadIndex){

}
void eating(){

}
void putDownChopsticks(int threadIndex){

}

void get_array_string(int *list, int n, char *s)
{
    int x;

    for (x = 0; x < n; x++)
        sprintf(s + strlen(s), "%4d", list[x]);

    sprintf(s + strlen(s), "\n");
}