#ifndef _queue_h
#define _queue_h
#include "genlib.h"

typedef int queueElementT;

typedef struct queueCDT *queueADT;

queueADT NewQueue(void);
void FreeQueue(queueADT queue);

void Enqueue(queueADT queue, queueElementT element);
queueElementT Dequeue(queueADT queue);

bool QueueIsEmpty(queueADT queue);
bool QueueIsFull(queueADT queue);
int QueueLength(queueADT queue);

queueElementT GetQueueElement(queueADT queue, int index);

#endif
