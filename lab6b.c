#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct red;
typedef struct red* Pozicija;

typedef struct red {

	int el;
	Pozicija next;

}red;

Pozicija push(Pozicija,int);
int pop(Pozicija);
void ispis(Pozicija);

int main() {

	srand(time(0));

	red head;
	head.next = NULL;
	Pozicija zadnji;

	int odabir = 0, a = 0;

	printf("Odaberite:\n");
	printf("0)Za kraj\n1)Za dodavanje u red\n2)Za brisanje s reda\n");

	while (1) {
		scanf("%d", &odabir);

		switch (odabir)
		{
		case 0: return 0;

			break;

		case 1:

			a = 10 + rand() % (100 - 10 + 1);

			zadnji=push(&head,a);
			ispis(head.next);

			break;

		case 2:

			pop(&head);
			ispis(head.next);

			break;
		
		default:

			printf("Unesite ispravan broj!\n");

			break;
		}

	}

}

Pozicija push(Pozicija p,int a) {

	Pozicija q;

	while (p->next != NULL) {
		p = p->next;
	}

	q = (Pozicija)malloc(sizeof(red));

	q->el = a;

	q->next = p->next;
	p->next = q;

	return q;

}

int pop(Pozicija p) {

	Pozicija temp = p->next;

	int a = 0;

	if (temp != NULL) {

		a = temp->el;
		p->next = temp->next;
		free(temp);
	}
	return a;
	
}
void ispis(Pozicija p) {

	printf("Ispis: ");

	if (p==NULL) {
		printf("Red je prazan\n");
		return;
	}

	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}

	printf("\n");
}
