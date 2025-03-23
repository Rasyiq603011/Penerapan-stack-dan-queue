#ifndef QUEUE_H
#define QUEUE_H
#include "linked.h"

typedef struct {
    List L;      
} Queue;

void CreateQueue(Queue *Q);

boolean IsQueueEmpty(Queue Q);

void EnQueue(Queue *Q, infotype X);

void CencelEnQueue(Queue *Q, infotype *X);

void DeQueue(Queue *Q, infotype *X);

void CencelDeQueue(Queue *Q, infotype X);

void PrintQueue(Queue Q);

int CountQueue(Queue Q);

infotype GetFrontValueQ(Queue Q);

infotype GetTailValueQ(Queue Q);

#endif
