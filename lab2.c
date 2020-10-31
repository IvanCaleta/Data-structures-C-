#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 256

struct student;
typedef struct student* Pozicija;

typedef struct student {
	char ime[M];
	char prezime[M];
	int godina;
	Pozicija next;
}Student;

Pozicija kreiraj_Studenta(char*, char*, int);
void ispisivanje(Pozicija);
void unosPocetak(Pozicija, Pozicija);
void unosKraj(Pozicija);
Pozicija traziPrezime(Pozicija,char*);
Pozicija traziPrethodnog(Pozicija, char*);
void brisanje(Pozicija,char*);

int main() {
	Student head;
	Pozicija p = NULL;
	char ime[M] = { 0 }, prezime[M] = { 0 };
	int godina = 0;
	head.next = NULL;
	int odabir = 0;

	printf("Odaberite neku od sljedecih opcija\n");
	printf("0) Za kraj programa\n");
	printf("1)Za unos studenta na pocetak vezane liste\n");
	printf("2)Za unos studenta na kraj vezane liste\n");
	printf("3)Za ispis liste\n");
	printf("4)Za pretragu po prezimenu\n");
	printf("5)Za brisanje studenta\n");
	while (1) {
		
		scanf("%d", &odabir);
		switch (odabir) {

		case 0: return 0;
		case 1:
			printf("\nUnesite ime ");
			scanf("%s", ime);

			printf("\nUnesite prezime ");
			scanf("%s", prezime);

			printf("\nUnesite godinu rodenja: ");
			scanf("%d", &godina);

			printf("\n");
			p = kreiraj_Studenta(ime, prezime, godina);
			unosPocetak(&head, p);
			break;
		case 2:
			printf("\nUnesite ime ");
			scanf("%s", ime);

			printf("\nUnesite prezime ");
			scanf("%s", prezime);

			printf("\nUnesite godinu rodenja: ");
			scanf("%d", &godina);

			printf("\n");
			p = kreiraj_Studenta(ime, prezime, godina);
			unosKraj(&head, p);
			break;
		case 3:
			ispisivanje(&head); break;
		case 4:
			printf("Unesite prezime studenta kojeg zelite traziti ");
			scanf("%s",prezime);
			p=traziPrezime(&head,prezime);

			if(p!=NULL)
			printf("\nTo je student\t %s %s %d\n",p->ime,p->prezime,p->godina);

			break;
		case 5:
			printf("Unesite prezime studenta kojeg zelite izbrisati: ");
			scanf("%s",prezime);
			brisanje(&head, prezime);

			break;
		default:
			printf("Unesite ispravan broj!\n"); break;
		}
	}




	return 0;
}

Pozicija kreiraj_Studenta(char *ime, char*prezime, int godina) {

	Pozicija p = NULL;

	p = (Pozicija)malloc(sizeof(Student));

	if (NULL == p) {
		printf("Neuspjesna alokacija memorije!");
		return NULL;
	}
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godina = godina;
	p->next = NULL;

	return p;
}
void ispisivanje(Pozicija head) {
	Pozicija p = NULL;
	printf("Slijedi ispis vezane liste\n");
	for (p = head->next; p != NULL; p = p->next)
		printf("%s %s %d\n", p->ime, p->prezime, p->godina);
}
void unosPocetak(Pozicija head, Pozicija p) {
	p->next = head->next;
	head->next = p;
}
void unosKraj(Pozicija p, Pozicija q) {


	while (p->next != NULL) {
		p = p->next;
	}
	unosPocetak(p, q);
}
Pozicija traziPrezime(Pozicija p,char* prezime) {
	while (p != NULL && strcmp(prezime, p->prezime)) {
		p = p->next;
	}
	if (NULL == p) {
		printf("Student s tim prezimenom ne postoji!\n");
		return NULL;
	}
	return p;
}
Pozicija traziPrethodnog(Pozicija p,char* prezime) {
	Pozicija pret = p;
	p = p->next;

	while (p != NULL && strcmp(prezime, p->prezime)) {
		pret = p;
		p = p->next;
	}
	if (NULL == p) {
		printf("Ne postoji!\n");
		return NULL;
	}
	return pret;
}
void brisanje(Pozicija p,char* prezime) {
	Pozicija pret = traziPrethodnog(p, prezime);

	if (pret != NULL) {
		p = pret->next;
		pret->next = p->next;
		free(p);
	}
}