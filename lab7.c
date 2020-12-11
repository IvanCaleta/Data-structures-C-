#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct stog;

typedef struct stog* Pozicija;

typedef struct stog {

	int el;
	Pozicija next;

}stog;

void push(int,Pozicija);
int pop(Pozicija);
int racunaj(Pozicija);
void ispis(Pozicija);

int main() {

	stog head;
	head.next = NULL;

	int rez = 0;
	rez = racunaj(&head);

	printf("Rezultat je: %d\n",rez);

	return 0;
}

void push(int br, Pozicija p) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(stog));

	q->el = br;

	q->next = p->next;
	p->next = q;

	ispis(p);
}

int pop(Pozicija p) {

	Pozicija temp = p->next;
	int x = 0;

	if (temp == NULL) {
		printf("Greska! Stog je prazan.\n");
		return;
	}

	if (temp != NULL) {
		x = temp->el;
		p->next = temp->next;
		free(temp);

		return x;
	}
	ispis(p);
}

int racunaj(Pozicija p) {

	int rezultat = 0, var,broj, brojac;
	int a = 0, b = 0;
	char* buffer;
	char c;

	buffer = (char*)malloc(1000 * sizeof(char));

	FILE* dat = NULL;


	dat = fopen("postfix.txt","r");

	if (NULL == dat) {

		printf("Neuspjesno otvaranje datoteke!\n");
		return;

	}

	fgets(buffer, 1000, dat);

	while (*buffer != '\0') {

		var = sscanf(buffer,"%d%n",&broj,&brojac);

		if (var==1)
			push(broj, p);

		if (var==0) {
			sscanf(buffer," %c",&c);
			switch (c) {

			case '+':
				a = pop(p);
				b = pop(p);

				rezultat = a + b;
				push(rezultat, p);

				break;

			case '-':
				a = pop(p);
				b = pop(p);

				rezultat = b - a;
				push(rezultat, p);

				break;

			case '*':
				a = pop(p);
				b = pop(p);

				rezultat = a * b;

				push(rezultat, p);
				break;

			default: break;
			}
		}
		buffer += brojac;
	}

	fclose(dat);
	rezultat = p->next->el;

	return rezultat;
}

void ispis(Pozicija p) {
	p = p->next;

	printf("Stog: ");

	while (p != NULL) {

		printf("%d ",p->el);
		p = p->next;

	}

	printf("\n");
}