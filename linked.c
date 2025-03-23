#include "linked.h"

boolean isEmpty(address P){
	return (P == Nil);
}

boolean ListEmpty(List L) {
    return (First(L) == Nil);     /* Mengirim true jika List Kosong */
}

/**** Konstruktor/Kreator List Kosong ****/
void CreateList(List *L) {
    /* IS : L sembarang */
    /* FS : Terbentuk List Kosong */
    First(*L) = Nil;
}

/**** Manajemen Memory ****/
address Alokasi(infotype X) {
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = (address) malloc(sizeof(ElmtList));
    if (P != Nil) {
        /* Alokasi berhasil */
        info(P) = X;
        next(P) = Nil;
    }
    return (P);
}

void DeAlokasi(address P) {
    if (P != Nil) {
        free(P);
    }
}    

/**** Pencarian sebuah elemen List ****/
address Search(List L, infotype X) {
    address P;
    boolean found = false;
    /* algoritma */
    P = First(L);
    while ((P != Nil) && (!found)) {
        if (info(P) == X) {
            found = true; 
        } else {
            P = next(P); 
        }
    } 
    return (P);
}

boolean FSearch(List L, address P) {
    /* Kamus Lokal */
    boolean found = false;
    address PSearch;
    /* Algortima */
    PSearch = First(L);
    while ((PSearch != Nil) && (!found)) {
        if (PSearch == P) {
            found = true;
        } else {
            PSearch = next(PSearch);
        }
    } /* PSearch = Nil atau Ketemu */
    return (found);
}

address SearchPrec(List L, infotype X) {
    /* Kamus Lokal */
    address Prec, P;
    boolean found = false;
    /* Algoritma */
    Prec = Nil;
    P = First(L);
    while ((P != Nil) && (!found)) {
        if (info(P) == X) {
            found = true;
        } else {
            Prec = P;
            P = next(P);
        }
    } /* P = Nil atau Ketemu */
    if (found) {
        return (Prec);
    } else {
        return (Nil);
    }
}

void IsiValueElmt (address *p , infotype nilai){

	if (*p != Nil){
		info(*p) = nilai;
		next(*p) = Nil;
	}
	else
	{
		printf("Memory belum dialokasikan");
	}
}

void TampilList (List L){
	address P;
	
	if (ListEmpty(L)) {
		printf("List Kosong .... \a\n");
	}
	else { 
        P = First(L);
        for (;;) {
            if (P == Nil) {
                printf("\n");
                break;
            } else {
                printf("%d ", info(P));
                P = next(P);
            }
        }
    }
}

void InsVFirst(List *L, infotype X) {
    address P;
    /* Aloritma */
    P = Alokasi(X);
    if (P != Nil) {
        InsertAwal(&(*L), P);
    }
}

void InsVLast(List *L, infotype X) {

    address P;
    /* Algoritma */
    P = Alokasi(X);
    if (P != Nil) {
        InsertAkhir(&(*L), P);
    }
}

/**** Penghapusan Elemen ****/
void DelVFirst(List *L, infotype *X) {

    address P;
    /* Algoritma */
    P = First(*L);
    *X = info(P);
    First(*L) = next(First(*L));
    DeAlokasi(P);
}

void DelVLast(List *L, infotype *X) {
    // Jika list kosong
    if (ListEmpty(*L)) {
        printf("Error: List kosong\n");
        return;
    }
    
    // Hapus elemen terakhir
    Del_Akhir(L, X);
}

void InsertAwal (List *L, address PNew){
	
	if (PNew == NULL){
		printf("Insert Gagal!");
	}
	next(PNew) = First(*L);
    First(*L) = PNew;	
}

void InsertAkhir (List *L, address PNew){
	
	address Last;
	
	if (First(*L) != Nil){
		Last = First(*L);
		while(next(Last) != Nil){
			Last = next(Last);
		}
		next(Last) = PNew;
	}
	else{
		First(*L) = PNew;
	}
}

void InsertAfter (address * pBef, address PNew){
	
	next(PNew) = next(*pBef);
	
	next(*pBef) = PNew;
}

void InsertBefore (address * pAft, address * p, address PNew){
	
	address temp = *p;
	if (!isEmpty(temp)){
		while(true){
			if (next(temp) == *pAft ){
				next(PNew) = *pAft;
				next(temp) = PNew;
				break;		
			}
			else{
				temp = next(temp);
			}
		}
		
	}	
}

void Del_Awal (List *L, infotype * X){
	
	if(First(*L) == Nil){
		printf("\nList Kosong Tidak bisa menghapus\n");
		return;
	}
	
	address temp = First(*L);
	First(*L) = next( First(*L));
	
	*X = info(temp);
	DeAlokasi(temp);
	
	
}

void Del_Akhir(List *L, infotype *X) {
    // Jika list kosong
    if (ListEmpty(*L)) {
        printf("\nList Kosong Tidak bisa menghapus\n");
        return;
    }
    
    address temp = First(*L);
    
    // Jika list hanya berisi 1 elemen
    if (next(temp) == Nil) {
        *X = info(temp);
        DeAlokasi(temp);
        First(*L) = Nil;
        return;
    }
    
    // Jika list berisi lebih dari 1 elemen
    // Cari node sebelum node terakhir
    while (next(next(temp)) != Nil) {
        temp = next(temp);
    }
    
    // Ambil nilai dari node terakhir
    *X = info(next(temp));
    
    // Dealokasi node terakhir
    DeAlokasi(next(temp));
    
    // Set next dari node sebelum terakhir menjadi Nil
    next(temp) = Nil;
}

void Del_After (address * pBef, infotype * X){
	

	*X = info(next(*pBef));
	address temp = next(*pBef);
	next(*pBef) = next(next(*pBef));
	DeAlokasi(temp);
}

void ClearList (List *L){
	
	if(First(*L) == Nil){
		printf("List Kosong Tidak bisa menghapus");
		return;
	}
	
	infotype Hapus;
	while (First(*L) != Nil){
		Del_Awal(L, &Hapus);
		printf("Node dengan isi %d telah dihapus!\n\n", Hapus);
	}
	printf("\nList Telah Kosong Head menunjuk kembali ke Nil\n");
}

int NbElmt (List L){
	address temp = First(L);
	int Jumlah = 0;
	while (temp != Nil){
		Jumlah += 1;
		temp = next(temp);
	}
	return Jumlah;
}

infotype Min (address p){
	
	infotype temp = 0;
	while (true){
		if (!isEmpty(p)){
			if (temp == 0){
				temp = info(p);
				p = next(p);
			}
			if (info(p) <= temp){
				temp = info(p);
			}
			p = next(p);
		}
		else{
			return temp;
		}
		
	}
}

infotype Rerata (address p){
	
	infotype jumlah = 0;
	infotype banyakData = 0;
	while (true){
		if (!isEmpty(p)){
			banyakData++;
			jumlah += info(p);
			p = next(p);
		}
		else{
			if (banyakData == 0){
				return 0;
			}
			else{
				return (jumlah/banyakData);
			}
		}		
	}	
}

address BalikList (List L){
	address p, temp, reverse;
	
	if (First(L) != Nil){
		p = First(L);
		temp = next(p);
		reverse = next(next(p));
		next(p) = Nil;
		while(true){
			next(temp) = p;
			p = temp;
			temp = reverse;
			reverse = next(reverse);
				
			if (isEmpty(next(reverse))){
				next(temp) = p;
				next(reverse) = temp;
				return reverse;
			}
		}		
	}
	else{
		printf("List Kosong");
	}		
}

void Modify_First (address *p, infotype nilai_baru) {
    if (!isEmpty(*p)) {
        info(*p) = nilai_baru;
    } else {
        printf("List Kosong");
    }
}

void Modify_After (address pBef, infotype nilai_baru) {
    if (!isEmpty(pBef) && !isEmpty(next(pBef))) {
        info(next(pBef)) = nilai_baru;
    } else {
        printf("Node tidak ditemukan");
    }
}

void Modify_Last (address p, infotype nilai_baru) {
    address temp = p;
    
    if (isEmpty(temp)) {
        printf("List Kosong");
        return;
    }
    while (!isEmpty(next(temp))) {
        temp = next(temp);
    }
    info(temp) = nilai_baru;
}

infotype GetFrontValue(List L){
	if (ListEmpty(L)){
		printf("List Kosong");
	}
	else{
		address temp = First(L);
		return (info(temp));
	}
}

infotype GetTailValue(List L){
	if (ListEmpty(L)){
		printf("List Kosong");
	}
	else{
		address temp = First(L);
		while(!isEmpty(next(temp))){
			temp = next(temp);
		}
		return (info(temp));
	}
}








