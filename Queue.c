#include "Queue.h"

void CreateQueue(Queue *Q) {
    CreateList(&(Q->L));  
}

boolean IsQueueEmpty(Queue Q) {
    return ListEmpty(Q.L); 
}

void EnQueue(Queue *Q, infotype X) {
    InsVLast(&(Q->L), X); 
}

void CencelEnQueue(Queue *Q, infotype *X){
	DelVLast(&(Q->L), X);
}

void DeQueue(Queue *Q, infotype *X) {
    DelVFirst(&(Q->L), X);
}

void CencelDeQueue(Queue *Q, infotype X){
	InsVFirst(&(Q->L), X);
}

void PrintQueue(Queue Q) { 
    TampilList(Q.L); 
}

int CountQueue(Queue Q) {
    return NbElmt(Q.L);
}

infotype GetFrontValueQ(Queue Q){
	return GetFrontValue(Q.L);
}

infotype GetTailValueQ(Queue Q){
	return GetTailValue(Q.L);
}





