#include <stdio.h>
#include "stack.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S)
{
	TopStack(*S) = NilStack;
}
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack(Stack S)
{
	return TopStack(S) == NilStack;
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFullStack(Stack S)
{
	return TopStack(S) == MaxElStack - 1;
}
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushStack(Stack *S, infotypeStack X)
{
	TopStack(*S)++;
	InfoTopStack(*S) = X;
}
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void PopStack(Stack *S, infotypeStack *X)
{
	(*X) = InfoTopStack(*S);
	TopStack(*S)--;
}
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void PrintStack(Stack S)
{
	int i;
	if (!IsEmptyStack(S))
	{
		for (i = TopStack(S); i >= 0; i--)
		{
			printf("%d\n", S.T[i]);
		}
	}
	else
	{
		printf("Stack kosong");
	}

	printf("\n");
}

Stack InverseStack(Stack S)
{
	Stack S1;
	CreateEmptyStack(&S1);
	infotypeStack X;
	while (!IsEmptyStack(S))
	{
		PopStack(&S, &X);
		PushStack(&S1, X);
	}
	return S1;
}
