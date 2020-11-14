#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct skup;
typedef struct skup* Pozicija;

typedef struct skup{

	int el;
	Pozicija next;

}skup;

void ucitavanjeDat(char*,Pozicija);
Pozicija kreirajNovi(int);
void unos(Pozicija,Pozicija);
void ispis(Pozicija);
void presjek(Pozicija,Pozicija,Pozicija);
void unija(Pozicija,Pozicija,Pozicija);

int main(void) {
	skup pHead;
	pHead.next = NULL;

	skup qHead;
	qHead.next = NULL;

	skup rHead;
	rHead.next = NULL;

	skup sHead;
	sHead.next = NULL;

	ucitavanjeDat("skup1.txt",&pHead);
	ucitavanjeDat("skup2.txt",&qHead);

	printf("Prvi skup: ");
	ispis(&pHead);

	printf("Drugi skup: ");
	ispis(&qHead);

	printf("Presjek: ");
	presjek(&pHead, &qHead, &rHead);
	ispis(&rHead);

	printf("Unija: ");
	unija(&pHead, &qHead, &sHead);
	ispis(&sHead);

}
void ucitavanjeDat(char* naziv,Pozicija head) {
	Pozicija p = NULL;
	Pozicija pom = NULL;

	int a = 0;

	FILE *dat;
	dat = fopen(naziv,"r");

	if (NULL == dat)
		printf("Greska pri otvaranju!");

	while (!feof(dat)) {
		fscanf(dat,"%d",&a);
		p = kreirajNovi(a);
		pom = head;
			while (pom->next != NULL && pom->next->el < a) {
			pom = pom->next;
			}
		unos(p, pom);
	}

}
Pozicija kreirajNovi(int a) {
	Pozicija p = NULL;

	p = (Pozicija)malloc(sizeof(skup));

	if (NULL == p) {
		printf("Neuspjesno alociranje memorije!");
		return NULL;
	}

	p->el = a;
	p->next = NULL;

	return p;
}
void unos(Pozicija p, Pozicija head) {
	p->next = head->next;
	head->next = p;
}
void ispis(Pozicija head) {
	for (head = head->next; head != NULL; head = head->next)
		printf("%d ",head->el);

	printf("\n");
}
void presjek(Pozicija p, Pozicija q, Pozicija r) {
	Pozicija q_prvi = q;

	p = p->next;
	q = q->next;

	Pozicija pom = NULL;

	while (p != NULL) {
		q = q_prvi->next;
		while (q != NULL) {
			if (p->el == q->el) {
				pom = kreirajNovi(p->el);
				while (r->next != NULL) {
					r = r->next;
				}
				unos(pom, r);
			}

			q = q->next;
		}
		p = p->next;
	}
}

void unija(Pozicija p,Pozicija q,Pozicija s) {
	p = p->next;
	q = q->next;

	Pozicija pom = NULL;

	while (p != NULL && q != NULL) {
		if (p->el == q->el) {
			pom = kreirajNovi(p->el);
				while (s->next != NULL) {
				s = s->next;
				}
			unos(pom, s);
			p = p->next;
			q = q->next;
		}
		if ((p != NULL && q != NULL) && p->el > q->el) {
			pom = kreirajNovi(q->el);
				while (s->next != NULL) {
				s = s->next;
				}
			unos(pom, s);
			q = q->next;
		}
		if ((p != NULL && q != NULL) && p->el < q->el) {
			pom = kreirajNovi(p->el);
				while (s->next != NULL) {
				s = s->next;
				}
			unos(pom, s);
			p = p->next;
		}

	}
	while (p != NULL && q == NULL) {
		pom = kreirajNovi(p->el);
			while (s->next != NULL) {
			s = s->next;
			}
		unos(pom, s);
		p = p->next;
	}
	while(p == NULL && q != NULL) {
		pom = kreirajNovi(q->el);
			while (s->next != NULL) {
			s = s->next;
			}
		unos(pom, s);
		q = q->next;
	}

}