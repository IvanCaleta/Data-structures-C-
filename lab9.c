#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct stablo;
typedef struct stablo* Pozicija;

typedef struct stablo {

	int el;

	Pozicija L;
	Pozicija D;

}stablo;

Pozicija brisiSve(Pozicija);
Pozicija traziMin(Pozicija);
Pozicija traziMax(Pozicija);
Pozicija trazi(int,Pozicija);
Pozicija dodaj(int x,Pozicija);
void ispis(Pozicija);
Pozicija brisi(int, Pozicija);

int main() {

	Pozicija root = NULL;
	Pozicija trenutni;
	int odabir, br;

	printf("Odaberite:\n");
	printf("0)Za kraj programa\n");
	printf("1)Za unos novog elementa u stablo\n");
	printf("2)Za trazenje odredenog elementa\n");
	printf("3)Za ispis stabla\n");
	printf("4)Za brisanje nekog elementa\n");

	while (1) {
		scanf("%d", &odabir);

		switch (odabir) {

		case 0:
			root = brisiSve(root);

			return EXIT_SUCCESS;

			break;

		case 1:
			printf("Unesi broj: ");
			scanf("%d", &br);

			if (trazi(br, root) != NULL)
				printf("Broj vec postoji!\n");
			else
				root = dodaj(br, root);

			break;

		case 2:
			printf("Unesi broj: ");
			scanf("%d", &br);

			trenutni = trazi(br, root);

			if (trenutni == NULL)
				printf("Broj ne postoji\n");
			else
				printf("Pronaden je: %d\n",trenutni->el);

			break;

		case 3:
			printf("Slijedi ispis:\n");
			ispis(root);

			printf("\n");
			break;

		case 4:
			printf("Unesi element kojeg brises: ");
			scanf("%d",&br);

			trenutni = brisi(br, root);
			break;

		default:
			printf("Unesi ispravan broj!\n");
			break;
		}
	}

}

Pozicija brisiSve(Pozicija s) {

	if (s != NULL) {
		brisiSve(s->L);
		brisiSve(s->D);
		free(s);
	}

	return NULL;

}

Pozicija traziMin(Pozicija s) {

	if (NULL == s)
		return NULL;

	else if (NULL == s->L)
		return s;

	return traziMin(s->L);
	
}

Pozicija traziMax(Pozicija s) {

	while (NULL != s) {
		if (NULL != s->D)
			s = s->D;
		else
			return s;
	
	}

	return s;


}

Pozicija trazi(int x, Pozicija s) {

	if (NULL == s)
		return NULL;

	else if (x < s->el)
		return trazi(x, s->L);

	else if (x > s->el)
		return trazi(x, s->D);

	return s;

}

Pozicija dodaj(int x, Pozicija s) {

	if (NULL == s) {
		s = (Pozicija)malloc(sizeof(stablo));
		s->el = x;
		s->L = NULL;
		s->D = NULL;
	}

	else if (x < s->el)
		s->L = dodaj(x, s->L);
	else if (x > s->el)
		s->D = dodaj(x, s->D);

	return s;

}

void ispis(Pozicija s) { //inorder nacin

	if (s != NULL) {
		ispis(s->L);
		printf("%d ",s->el);
		ispis(s->D);
	}
}

Pozicija brisi(int x, Pozicija s) {

	Pozicija pom;

	if (NULL == s)
		printf("Broj ne postoji!\n");

	else if (x < s->el)
		s->L = brisi(x, s->L);

	else if (x > s->el)
		s->D = brisi(x, s->D);

	else
	{
		if (s->L != NULL && s->D != NULL) {//pronaden je i ima 2 djece

			pom = traziMin(s->D);
			s->el = pom->el;
			s->D = brisi(s->el, s->D);

		}
		else //pronaden je i ima 0 ili 1 dijete
		{
			pom = s;
			if (NULL == s->L)
				s = s->D;

			else
				s = s->L;

			free(pom);
		}

	}

	return s;
}