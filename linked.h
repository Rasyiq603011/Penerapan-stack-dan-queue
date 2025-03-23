#ifndef linked_H
#define linked_H
#include <stdio.h>
#include <malloc.h>
#include "boolean.h"
#define First(L) (L).First
#define info(P) (P)->info
#define next(P) (P)->next
#define Nil NULL

typedef int infotype; // membuat alias bernama infotype, tujaannya agar program ADT dapat beradaptasi dengan tipe data lain
typedef struct tElmtList *address;
typedef struct tElmtList {
	infotype info;
	address  next;
 } ElmtList;
 
typedef struct{
	address First;
}List;

boolean isEmpty(address P);

boolean ListEmpty (List L);

void CreateList (List * L);

address Alokasi (infotype X);

void DeAlokasi (address P);

address Search (List L, infotype X);

boolean FSearch (List L, address P);

address SearchPrec (List L, infotype X);

void IsiValueElmt (address *p , infotype nilai);

void TampilList (List L);

void InsVFirst (List * L, infotype X);

void InsVLast (List * L, infotype X);

void DelVFirst (List * L, infotype * X);

void DelVLast (List * L, infotype * X);

void InsertAwal (List *L, address PNew);

void InsertAkhir (List *L, address PNew);

void InsertAfter (address * pBef, address PNew);

void InsertBefore (address * pAft, address * p, address PNew);

void Del_Awal (List *L, infotype * X);

void Del_Akhir (List *L, infotype * X);

void Del_After (address * pBef, infotype * X);

void ClearList (List *L);

int NbElmt (List L);

infotype Min (address p);

infotype Rerata (address p);

address BalikList (List L);

void Modify_First (address *p, infotype nilai_baru);

void Modify_After (address pBef, infotype nilai_baru);

void Modify_Last (address p, infotype nilai_baru);

infotype GetFrontValue(List L);

infotype GetTailValue(List L);

#endif

