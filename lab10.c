#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

struct stablo;
typedef struct stablo* PozStablo;

typedef struct stablo {

	char string [MAX];
	PozStablo L;
	PozStablo D;

}stablo;


struct stog;
typedef struct stog* PozStog;

typedef struct stog {

	PozStablo el;
	PozStog next;

}stog;

PozStablo ucitavanjeDat(char*);
PozStablo pop(PozStog);
int push(PozStablo,PozStog);
int provjera(char*);
PozStablo kreirajNovi(char*);
void upisDat(PozStablo,char*);
void upis(PozStablo,FILE*);
PozStablo brisiSve(PozStablo);

int main() {

	PozStablo root;
	char naziv[MAX];

	printf("Unesite naziv datoteke iz koje ucitavate: ");
	scanf("%s",naziv);

	root = ucitavanjeDat(naziv);

	printf("Unesite naziv datoteke u koju upisujete: ");
	scanf("%s", naziv);

	upisDat(root, naziv);

	root = brisiSve(root);

	return 0;
}

PozStablo ucitavanjeDat(char* naziv) {

	stog head;
	PozStablo rezultat, s;
	char znak[11];

	FILE* fp;
	fp = fopen(naziv,"r");

	if (NULL == fp) {
		printf("Nije otvorena!\n");
		return NULL;
	}

	while (!feof(fp)) {

		fscanf(fp,"%s ",znak);

		if (strlen(znak) == 0)
			break;
		
		s = kreirajNovi(znak);

		if (provjera(znak) == 1)
			push(s, &head);
		else {

			s->D = pop(&head);
			s->L = pop(&head);

			if (s->L == NULL || s->D == NULL) {
				printf("Krivi postfix izraz\n");
				return NULL;
			}

			push(s, &head);
		}

	}

	fclose(fp);

	rezultat = pop(&head);


	return rezultat;
}

PozStablo kreirajNovi(char* niz ) {

	PozStablo q;
	q = (PozStablo)malloc(sizeof(stablo));

	if (NULL == q) {
		printf("Greka pri alokaciji!\n");
		return NULL;
	}

	strcpy(q->string,niz);
	q->L = NULL;
	q->D = NULL;

	return q;
}

int push(PozStablo s, PozStog head) {

	PozStog prvi;
	prvi = (PozStog)malloc(sizeof(stog));

	if (NULL == prvi) {
		printf("Greka pri alokaciji!\n");
		return -1;
	}

	prvi->el = s;

	prvi->next = head->next;

	head->next = prvi;
	
}

PozStablo pop(PozStog head) {

	PozStog prvi = head->next;
	PozStablo s = NULL;

	if (NULL == prvi) {
		printf("Greska! Stog je prazan!\n");
		return NULL;
	}

	s = prvi->el;

	head->next = prvi->next;

	free(prvi);

	return s;
}

int provjera(char* znak) {

	int br;

	if (sscanf(znak, "%d",&br) == 1)
		return 1;
	else
		return 0;
}

void upisDat(PozStablo s,char* naziv) {

	FILE* fp;

	fp = fopen(naziv,"w");

	if (NULL == fp) {
		printf("Nije otvorena!\n");
		return;
	}

	upis(s, fp);
	
	fclose(fp);
}

void upis(PozStablo s,FILE* fp) {

	if (s != NULL) {

		fprintf(fp, "( ");

		upis(s->L, fp);

		fprintf(fp, "%s ", s->string);

		upis(s->D, fp);

		fprintf(fp, " )");

	}
}

PozStablo brisiSve(PozStablo s) {

	if (s != NULL) {

		brisiSve(s->L);

		brisiSve(s->D);

		free(s);
	}

	return NULL;
}
