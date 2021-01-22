#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VEL 11
#define MAX 256

struct cvor;
typedef struct cvor* Pozicija;

typedef struct cvor {

	char ime[MAX];
	char prezime[MAX];
	int matBr;
	Pozicija next;

}cvor;

void stvoriTablicu(Pozicija);
int kljuc(char*);
Pozicija ucitajDat(char*,Pozicija);
Pozicija kreirajNovi(char*,char*,int);
void unos(Pozicija, Pozicija);
void ispis(Pozicija);
Pozicija trazi(Pozicija);

int main() {

	cvor hash[VEL];
	Pozicija p = &hash;
	char naziv[MAX];
	int broj;

	printf("Unesi naziv datoteke: ");
	scanf("%s",naziv);

	stvoriTablicu(hash);
	p = ucitajDat(naziv,hash);

	if(p!=NULL)
		ispis(p);

	p = trazi(p);

	if (p != NULL)
		printf("Pronaden!\n%s\t%s\t%d\n\n", p->ime, p->prezime, p->matBr);
	else
		printf("Nije pronaden!\n\n");

	return 0;
}

void stvoriTablicu(Pozicija p) {

	int i = 0;

	for (i = 0; i < VEL; i++) {
		p[i].next = NULL;
	}

}
Pozicija kreirajnovi(char* ime, char* prezime, int br) {

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(cvor));

	if (NULL == q) {
		printf("Neuspjesna alokacija!");
		return NULL;
	}

	strcpy(q->ime, ime);
	strcpy(q->prezime,prezime);
	q->matBr = br;

	return q;
}

void unos(Pozicija p, Pozicija q) {
	
	while (p->next != NULL && strcmp(p->next->prezime, q->prezime) < 0) {
		p = p->next;
	}

	while (p->next != NULL && strcmp(p->next->prezime, q->prezime) == 0 && strcmp(p->next->ime, q->ime) < 0) {
		p = p->next;
	}

	q->next = p->next;
	p->next = q;
}

int kljuc(char* prezime) {

	int i = 0, sum = 0;

	for (i = 0; i < 5; i++)
		sum += (int)prezime[i];

	return sum % VEL;

}

Pozicija ucitajDat(char* naziv,Pozicija hash) {

	char ime[MAX], prezime[MAX];
	int br, index;

	Pozicija q = NULL;

	FILE* fp = fopen(naziv, "r");

	if (NULL == fp) {
		printf("Nije ispravno otvorena!\n");
		return NULL;
	}

	while (!feof(fp)) {

		fscanf(fp, "%s %s %d", ime, prezime, &br);

		index = kljuc(prezime);

		q = kreirajnovi(ime, prezime, br);

		unos(hash+index,q);
	}

	fclose(fp);

	return hash;
}

void ispis(Pozicija hash) {

	Pozicija p;
	int i;

	printf("Kljuc\tIme\tPrezime\tMaticni\n\n");

	for (i = 0; i < VEL; i++) {
		p = hash + i;
		p = p->next;

		while (p != NULL) {
			printf("%d\t%s\t%s\t%d\n",i,p->ime,p->prezime,p->matBr);
			p = p->next;
		}
		
	}
	printf("\n");
}

Pozicija trazi(Pozicija hash) {

	int index;

	char ime[MAX], prezime[MAX];

	printf("Unesi ime i prezime osobe koje trazis: ");
	scanf("%s %s", ime, prezime);

	index = kljuc(prezime);

	hash += index;

	while (hash != NULL && (strcmp(hash->ime, ime) || strcmp(hash->prezime, prezime))){
		hash = hash->next;
	}

	return hash;
}