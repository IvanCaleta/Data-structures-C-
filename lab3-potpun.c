
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
void unosKraj(Pozicija, Pozicija);
Pozicija traziPrezime(Pozicija, char*);
Pozicija traziPrethodnog(Pozicija, char*);
void brisanje(Pozicija, char*);
void unosIspred(Pozicija, Pozicija, char*);
void unosIza(Pozicija, Pozicija, char*);
void unosDatoteka(Pozicija);
void ucitavanje_dat(Pozicija);
void sortiranje(Pozicija);

int main() {
	Student head;
	Pozicija p = NULL;
	char ime[M] = { 0 }, prezime[M] = { 0 };
	int godina = 0;
	head.next = NULL;
	int odabir = 0;
	int n = 0;

	printf("Odaberite neku od sljedecih opcija\n");
	printf("0) Za kraj programa\n");
	printf("1)Za unos studenta na pocetak vezane liste\n");
	printf("2)Za unos studenta na kraj vezane liste\n");
	printf("3)Za ispis liste\n");
	printf("4)Za pretragu po prezimenu\n");
	printf("5)Za brisanje studenta\n");
	printf("6)Za unos ispred odredenog studenta\n");
	printf("7)Za unos iza odredenog studenta\n");
	printf("8)Za upisivanje u datoteku\n");
	printf("9)Za ucitat datoteku\n");
	printf("10)Za sortiranje\n");
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
			scanf("%s", prezime);
			p = traziPrezime(&head, prezime);

			if (p != NULL)
				printf("\nTo je student\t %s %s %d\n", p->ime, p->prezime, p->godina);

			break;
		case 5:
			printf("Unesite prezime studenta kojeg zelite izbrisati: ");
			scanf("%s", prezime);
			brisanje(&head, prezime);

			break;
		case 6:
			printf("Unesite prezime studenta ispred kojeg zelite upisati novog: ");
			scanf("%s", prezime);
			unosIspred(&head, p, prezime);

			break;
		case 7:
			printf("Unesite prezime studenta iza kojeg zelite upisati novog: ");
			scanf("%s", prezime);
			unosIza(&head, p, prezime);

			break;
		case 8:
			unosDatoteka(&head);
			break;
		case 9:
			ucitavanje_dat(&head);
			ispisivanje(&head);
			break;
		case 10:
			printf("Nakon sortiranja\n");
			sortiranje(&head);
			ispisivanje(&head);
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
Pozicija traziPrezime(Pozicija p, char* prezime) {
	while (p != NULL && strcmp(prezime, p->prezime)) {
		p = p->next;
	}
	if (NULL == p) {
		printf("Student s tim prezimenom ne postoji!\n");
		return NULL;
	}
	return p;
}
Pozicija traziPrethodnog(Pozicija p, char* prezime) {
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
void brisanje(Pozicija p, char* prezime) {
	Pozicija pret = traziPrethodnog(p, prezime);

	if (pret != NULL) {
		p = pret->next;
		pret->next = p->next;
		free(p);
	}
}
void unosIspred(Pozicija head, Pozicija p, char *prezime) {
	p = traziPrethodnog(head, prezime);
	char ime[M];
	char prez[M];
	int godina;
	Pozicija q = NULL;
	if (p != NULL) {

		printf("Unesi ime: ");
		scanf("%s", ime);

		printf("Unesi prezime: ");
		scanf("%s", prez);

		printf("Unesi godinu rodenja: ");
		scanf("%d", &godina);

		q = kreiraj_Studenta(ime, prez, godina);
		unosPocetak(p, q);
	}

}
void unosIza(Pozicija head, Pozicija p, char *prezime) {
	p = traziPrezime(head, prezime);
	char ime[M];
	char prez[M];
	int godina;
	Pozicija q = NULL;
	if (p != NULL) {

		printf("Unesi ime: ");
		scanf("%s", ime);

		printf("Unesi prezime: ");
		scanf("%s", prez);

		printf("Unesi godinu rodenja: ");
		scanf("%d", &godina);

		q = kreiraj_Studenta(ime, prez, godina);
		unosPocetak(p, q);
	}
}
void unosDatoteka(Pozicija head) {
	Pozicija p = NULL;
	FILE *dat = fopen("lista.txt", "w");

	if (NULL == dat)
		printf("Nije ispravno otvorena!\n");


	for (p = head->next; p != NULL; p = p->next)
		fprintf(dat, "%s %s %d\n", p->ime, p->prezime, p->godina);


	fclose(dat);
}
void ucitavanje_dat(Pozicija p) {
	char ime[M];
	char prezime[M];
	int godina = 0;

	Pozicija q = NULL;
	FILE *dat = fopen("lista.txt", "r");

	if (NULL == dat)
		printf("Nije ispravno otvorena!\n");

	while (!feof(dat)) {
		fscanf(dat, "%s %s %d", ime, prezime, &godina);
		q = kreiraj_Studenta(ime, prezime, godina);
		unosKraj(p, q);
	}

	fclose(dat);
}
void sortiranje(Pozicija p) {
	Pozicija q,pom, pret, kraj = NULL;

	while (p->next != kraj) {
		pret = p;
		q = p->next;
		while (q->next != kraj) {
			if (strcmp(q->prezime,q->next->prezime)>0) {
				pom = q->next;
				pret->next = pom;
				q->next = pom->next;
				pom->next = q;
				q = pom;
			}
			pret = q;
			q = q->next;
		}

		kraj = q;
	}
	
}