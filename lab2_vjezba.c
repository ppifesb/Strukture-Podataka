#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Student {
	char ime[32];
	char prezime[32];
	int godina_rodenja;
	struct Student *next;
}_Student;

int DodajNaPoc(_Student *);
int Unos(_Student *);
int Ispis(_Student *);

int main()
{
	_Student *Head;
	int check = 0;
	Head = (_Student *)malloc(sizeof(_Student));

	if(Head == NULL)
		printf("Greska pri alociranju memorije!!");

	check = DodajNaPoc(Head);
	if (!check)
		printf("Greska u dodavanju elemnta na pocetak!");
}
int DodajNaPoc(_Student *Head)
{
	_Student *Element = (_Student *)malloc(sizeof(_Student));

	if (Element == NULL)
		printf("Greska pri alociranju memorije!!");

	Element->next = Head->next;
	Head->next = Element;

	if (!Unos(Element))
		printf("Greska pri unosu!");

	return 0;
}
int Unos(_Student *Element)
{
	printf("Ime: ");
	scanf(" %s", Element->ime);
	printf("Prezime: ");
	scanf(" %s", Element->prezime);
	printf("Godina rodenja: ");
	scanf("%d", &Element->godina_rodenja);

	if ((Element->ime == NULL) && (Element->prezime) && (Element->godina_rodenja == NULL))
		return -1;

	return 0;
}
int Ispis(_Student *Head)
{
	_Student *P = Head->next;

	if (P == NULL) {
		printf("Nema elemenata u listi");
		return 0;
	}

	while (P != NULL) {
		printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d", P->ime, P->prezime, P->godina_rodenja);
		P = P->next;
	}
	return 0;
}
