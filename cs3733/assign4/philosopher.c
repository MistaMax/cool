#include "philosopher.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

thread_info_t newThreadInfo()
{
    thread_info_t tmp;
    tmp = (thread_info_t)malloc(sizeof(ti));
    return tmp;
}

tInfoArr newThreadInfoArray(int size)
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
}

void get_array_string(int *list, int n, char *s)
{
    int x;

    for (x = 0; x < n; x++)
        sprintf(s + strlen(s), "%4d", list[x]);

    sprintf(s + strlen(s), "\n");
}