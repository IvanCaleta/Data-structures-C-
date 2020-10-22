#include <stdio.h>
#include<stdlib.h>

struct student {
	char ime[20];
	char prezime[20];
	int bodovi;
};

typedef struct student student;

int ispis(int broj, char *naziv) {
	int i, max;
	double relativno;
	student* lista;
	FILE *dat;

	dat = fopen(naziv, "r");
	if (dat == NULL) {                 //provjera
		printf("Nije dobor otvoreno");
		return -1;
	}
	else
		printf("Dobro\n");

	printf("Definiraj maksimalni broj bodova: ");
	scanf("%d", &max);

	lista = (student*)malloc(broj * sizeof(student));

	printf("\nIme\tPrezime\tApsolutni broj bodova\tRelativni broj bodova");

	for (i = 0; i < broj; i++) {
		fscanf(dat, "%s %s %d", lista[i].ime, lista[i].prezime, &lista[i].bodovi);

		relativno = (double)lista[i].bodovi / max * 100;

		printf("\n%s\t%s\t%d\t%3f\n", lista[i].ime, lista[i].prezime, lista[i].bodovi, relativno);
	}
	fclose(dat);

	return 0;
}

int brojac_redaka(char *naziv) {
	int broj = 0;
	FILE *dat;
	char spremnik[100];

	dat = fopen(naziv, "r");

	if (dat = NULL)                               //provjera
	{
		printf("Datoteka nije ispravno otvorena!");
		return -1;
	}
	else
		printf("Dobro je!");

	while (fgets(spremnik, 20, dat) != NULL) {
		broj++;
	}

	free(spremnik);
	fclose(dat);

	return broj;
}

int main()
{
	char *naziv = "popis.txt";
	int red;

	red = brojac_redaka(naziv);

	ispis(red, naziv);

	return 0;
}
