#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

struct stablo;

typedef struct stablo* Pozicija;

typedef struct stablo {

	char ime[MAX];
	Pozicija brat;
	Pozicija dijete;

}stablo;

struct stog;
typedef struct stog* PozStog;

struct stog {

	Pozicija el;
	PozStog next;

};

void lokacija(Pozicija);
void ispisDjece(Pozicija,Pozicija);
void unos(Pozicija);
Pozicija kreirajNovi(Pozicija,char*);
void ispisDir(Pozicija);
Pozicija trazi(Pozicija,PozStog,char*);
void push(Pozicija, PozStog);
Pozicija pop(Pozicija, PozStog);
void brisiSve(Pozicija);

int main() {

	stablo head;
	head.brat = NULL;
	head.dijete = NULL;
	strcpy(head.ime, "C:");

	Pozicija trenutni = &head;
	char ime[MAX];

	 struct stog sHead;
	sHead.next = NULL;
	sHead.el = NULL;

	int odabir;
	

	while (1) {

		printf("\nOdaberite:\n");
		printf("0)Za kraj programa\n");
		printf("1)Za unos novog clana\n");
		printf("2)Za ispis direktorija\n");
		printf("3)Za trazenje direktorija\n");
		printf("4)Za prikaz lokacije\n");
		printf("5)Za povratak u prethodni\n");
		printf("6)Za prikaz putanje\n");

		scanf("%d",&odabir);

		switch (odabir) {

		case 0: 
			brisiSve(&head);
			return EXIT_SUCCESS;
			break;

		case 1:
			unos(trenutni);
			break;

		case 2:
			ispisDir(trenutni);
			break;

		case 3:
			printf("Unesi ime direktorija kojeg trazis: ");
			scanf("%s", ime);

			trenutni = trazi(&head,&sHead, ime);

			if (trenutni != NULL)
				printf("Pronaden je!\n");
			else
				printf("Ne postoji!\n");
			break;

		case 4:
			lokacija(trenutni);
			break;

		case 5:
			trenutni = pop(trenutni, &sHead);
			lokacija(trenutni);
			break;
		case 6:
			ispisDjece(&head,trenutni);
			break;

		default:
			printf("Unesi ispravan broj!\n");
			break;

		}
	}

}

void ispisDjece(Pozicija head,Pozicija tr) {

	printf("%s\\ ", head->ime);
	head = head->dijete;

	while (head!=NULL && head != tr->dijete) {
		printf("%s\\ ", head->ime);
		head = head->dijete;
	}

	printf("\n");
}

Pozicija kreirajNovi(Pozicija p,char* ime) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(stablo));

	if (NULL == q) {
		printf("Neuspjesna alokacija\n");
		return NULL;
	}

	q->brat = NULL;
	q->dijete = NULL;
	strcpy(q->ime, ime);

	return q;
}

void unos(Pozicija p) {

	Pozicija prev = p;

	Pozicija q;
	char ime[MAX];

	printf("Unesi ime novog clana: ");
	scanf("%s",ime);

	q = kreirajNovi(p, ime);

	if (p->dijete == NULL) {

		q->brat = p->dijete;
		p->dijete = q;
		
		return;
	}

	p = p->dijete;

	if (strcmp(p->ime, q->ime) > 0) {

		q->brat = p;
		prev->dijete = q;
		
		return;
	}

	
	while (p != NULL&& strcmp(p->ime,q->ime)<0) {

		prev = p;
		p = p->brat;

	}

	q->brat = prev->brat;
	prev->brat = q;

}

void ispisDir(Pozicija p) {

	printf("U direktoriju %s imamo:\n",p->ime);
	p = p->dijete;

	if (NULL == p) {
		printf("Direktorij je prazan!\n");
		return;
	}

	while (p != NULL) {
		printf("%s\n",p->ime);
		p = p->brat;
	}
	
}

Pozicija trazi(Pozicija p,PozStog sHead,char* ime) {
	if (p == NULL) {

		printf("Ne postoji\n");
		return NULL;
	}

	if (p!=NULL && p->dijete != NULL && strcmp(p->ime, ime) != 0) {

		push(p, sHead);
		p = trazi(p->dijete,sHead ,ime);
	}
	if (p!=NULL && p->brat != NULL && strcmp(p->ime, ime) != 0) {

		p = trazi(p->brat,sHead, ime);
	}

	if (p!=NULL && strcmp(p->ime, ime) == 0) {
		return p;
	}
	else
		return NULL;

}

void lokacija(Pozicija trenutni) {

	if(trenutni!=NULL)
	printf("Trenutna lokacija: %s\n",trenutni->ime);
}

void push(Pozicija p,PozStog sHead) {

	PozStog q;
	q = (PozStog)malloc(sizeof(struct stog));

	if (NULL == q) {
		printf("Neuspjesna alokacija\n!");
		return;
	}

	q->el = p;
	q->next = sHead->next;
	sHead->next = q;

}

Pozicija pop(Pozicija p, PozStog sHead) {

	Pozicija q;
	PozStog pom;

	if (sHead->next == NULL) {
		printf("Stog je prazan!\n");
		return p;
	}

	q = sHead->next->el;

	pom = sHead->next;
	sHead->next = pom->next;
	free(pom);

	return q;

}

void brisiSve(Pozicija p) {

	if (p == NULL)
		return;

	brisiSve(p->dijete);
	brisiSve(p->brat);
	free(p);

}
