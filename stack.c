#include "stack.h"

void CreateStack(Stack *S) {
    CreateList(&(S->L));  
}

boolean IsStackEmpty(Stack S) {
    return ListEmpty(S.L); 
}

void StackAdd(Stack *S, infotype X) {
    InsVLast(&(S->L), X); 
}

void StackDel(Stack *S, infotype *X) {
    DelVLast(&(S->L), X);
}

void PrintStack(Stack S) { 
    TampilList(S.L); 
}

int CountStack(Stack S) {
    return NbElmt(S.L);
}

infotype getPeak(Stack S){
	return GetTailValue(S.L);
}

infotype GetFrontValueS(Stack S) {
	return GetFrontValue(S.L);
}

infotype GetTailValueS(Stack S) {
	return GetTailValue(S.L);
}

