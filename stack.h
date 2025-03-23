#ifndef STACK_H
#define STACK_H
#include "linked.h"

typedef struct {
    List L;      
} Stack;


boolean IsStackEmpty(Stack S);
// Membuat stack baru (empty)
void CreateStack(Stack *S);

// Insert Khusus stack dimana selalu insert di Akhir
void StackAdd(Stack *S, infotype X);

// delete Khusus stack dimana selalu delete diakhir
void StackDel(Stack *S, infotype *X);


void PrintStack(Stack S);

int CountStack(Stack S);

infotype getPeak(Stack S);

#endif

