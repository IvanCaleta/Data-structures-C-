#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct polinom;
typedef struct polinom* Pozicija;

typedef struct polinom {
	int coef;
	int exp;
	Pozicija next;

}polinom;

void ucitavanjeDat(char*,Pozicija);
Pozicija kreirajNovi(int, int);
void unos(Pozicija, Pozicija);
void ispis(Pozicija);
void zbroji(Pozicija,Pozicija,Pozicija);
void mnozi(Pozicija,Pozicija,Pozicija);

int main(void) {
	polinom pHead;
	pHead.next = NULL;

	polinom qHead;
	qHead.next = NULL;

	polinom rHead;
	rHead.next = NULL;

	polinom sHead;
	sHead.next = NULL;

	ucitavanjeDat("koeficijenti1.txt", &pHead);
	ucitavanjeDat("koeficijenti2.txt", &qHead);

	printf("Polinom p(x)= ");
	ispis(&pHead);

	printf("Polinom q(x)= ");
	ispis(&qHead);

	printf("Zbroj r(x)= ");
	zbroji(&pHead,&qHead,&rHead);
	ispis(&rHead);

	printf("Umnozak s(x)= ");
	mnozi(&pHead, &qHead, &sHead);
	ispis(&sHead);

	return 0;
}
void ucitavanjeDat(char*f,Pozicija head) {
	Pozicija p = NULL;
	Pozicija pom = head;

	int a=0, b=0;

	FILE *dat;
	dat = fopen(f, "r");

	if (NULL == dat)
		printf("Greska pri ucitavanju!");

	while (!feof(dat)) {
		fscanf(dat, "%d %d", &a, &b);
		p = kreirajNovi(a, b);

		pom = head;
		while (pom->next != NULL&&pom->next->exp > p->exp) {
			pom = pom->next;
		}
		unos(pom, p);
		
	}
	fclose(dat);

}
Pozicija kreirajNovi(int a, int b) {
	Pozicija p = NULL;

	p = (Pozicija)malloc(sizeof(polinom));

	if (NULL == p) {
		printf("Neuspjesno alociranje memorije!");
		return NULL;
	}

	p->coef = a;
	p->exp = b;
	p->next = NULL;

	return p;
}

void unos(Pozicija head, Pozicija p) {

	p->next = head->next;
	head->next = p;
}
void ispis(Pozicija head) {

	for (head = head->next; head != NULL; head = head->next){ 
		if(head->coef!=0)
			printf("+%dX^%d", head->coef, head->exp);
	}
	printf("\n");

}
void zbroji(Pozicija p, Pozicija q, Pozicija r) {
	Pozicija pom = NULL;

	int a = 0, b = 0;
	p = p->next;
	q = q->next;


	while (p != NULL && q != NULL) {
		if (p->exp == q->exp) {
			a = (p->coef) + (q->coef);
			b = p->exp;

			pom = kreirajNovi(a, b);

			while (r->next != NULL) {
				r = r->next;
			}

			unos(r, pom);
			p = p->next;
			q = q->next;
		}

		if ((p!=NULL&&q!=NULL)&&(p->exp > q->exp)) {
			a = p->coef;
			b = p->exp;

			pom = kreirajNovi(a, b);

			while (r->next != NULL) {
					r = r->next;
				}

			unos(r, pom);
			p = p->next;
		}

		if ((p!=NULL&&q!=NULL)&&(p->exp < q->exp)) {
			a = q->coef;
			b = q->exp;

			pom = kreirajNovi(a, b);

			while (r->next != NULL) {
				r = r->next;
			}

			unos(r, pom);
			q = q->next;
		}

	}

	while (p== NULL && q!= NULL) {
		pom = kreirajNovi(q->coef, q->exp);
		while (r->next != NULL) {
			r = r->next;
		}
		unos(r, pom);
		q = q->next;
	}

	while (p != NULL && q== NULL) {

		pom = kreirajNovi(p->coef, p->exp);
		while (r->next != NULL) {
			r = r->next;
		}
		unos(r, pom);
		p = p->next;
	}

}
void mnozi(Pozicija p, Pozicija q, Pozicija s) {
	Pozicija pom = NULL;
	Pozicija q_prvi = q;
	Pozicija s_prvi = s;
	Pozicija x = NULL;

	int a = 0, b = 0;

	p = p->next;

	while (p != NULL) { 
		q = q_prvi->next;
		while (q != NULL) {

			a = (p->coef)*(q->coef);
			b = (p->exp) + (q->exp);
			x = kreirajNovi(a, b);
			pom = s_prvi;
			while (pom->next != NULL && pom->next->exp > x->exp) {
				pom = pom->next;
			}
			unos(pom, x);
			q = q->next;
		}
		p = p->next;
	}


	while (s->next != NULL) {
		pom = s->next;
		while (pom != NULL) {
			if ((s->exp == pom->exp) && pom != NULL){
				s->coef += pom->coef;
				pom->coef = 0;
				pom = pom->next;
		}
			if ((s->exp != pom->exp) && pom != NULL)
				pom = pom->next;

		}
		s = s->next;
	}
	
		
}