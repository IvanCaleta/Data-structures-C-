#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct stog;
typedef struct stog* Pozicija;

typedef struct stog {

	int el;
	Pozicija next;

}stog;

void push(Pozicija,int);
int pop(Pozicija);
void ispis(Pozicija);

int main() {

	srand(time(0));

	stog head;
	head.next = NULL;

	int odabir = 0, a = 0;

	printf("Odaberite:\n");
	printf("0)Za kraj\n1)Za dodavanje na stog\n2)Za brisanje sa stoga\n");

	while (1) {
		scanf("%d",&odabir);

		switch (odabir)
		{
		case 0: return 0;
			break;

		case 1:

			a = 10 + rand() % (100 - 10 + 1);

			push(&head,a);
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

void push(Pozicija p,int a) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(stog));

	q->el = a;

	q->next = p->next;
	p->next = q;

}

int pop(Pozicija p) {

	Pozicija temp;
	temp = p->next;

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

	if (p == NULL) {
		printf("Stog je prazan!\n");
		return;
	}

	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}
	printf("\n");
}
