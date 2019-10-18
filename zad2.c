//Mislav Kovač
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Student {
	char ime[32];
	char prezime[32];
	int godina_rodenja;
	struct Student *next;
}_Student;

int UnosElementaNaPoc(_Student *);
int Unos(_Student *);
int Ispis(_Student *);
_Student *Pronadi(_Student *, char *);
int Brisi(_Student *, _Student *);

int main()
{
	_Student *Head = (_Student *)malloc(sizeof(_Student));
	int check;
	char izbor;
	char buffer[128] = { 0 };
	_Student *Trazi;

	Head->next = NULL;
	
	do {
		check = UnosElementaNaPoc(Head);
		if (check != 0) {
			printf("Greska!");
			return 0;
		}
		printf("Zelitel li unijeti jos jedan element? (D/N)");
		scanf(" %c", &izbor);
	} while (toupper(izbor) == 'D');

	Ispis(Head);

	printf("Unesite prezime: ");
	scanf(" %s", buffer);

	Trazi = Pronadi(Head, buffer);
	printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n", Trazi->ime, Trazi->prezime, Trazi->godina_rodenja);
	
	Brisi(Trazi, Head);  //Moze se brisat po bilo kojem elementu ali treba prilagodit buffer

	Ispis(Head);

	system("PAUSE");

	return 0;
}
int UnosElementaNaPoc(_Student *Head)
{
	int check = 0; 

	_Student *Element = (_Student *)malloc(sizeof(_Student));

	Element->next = Head->next;
	Head->next = Element;

	check = Unos(Element);
	if (check != 0) {
		printf("Greska!");
		return 0;
	}

	return 0;
}
int Unos(_Student *Element)
{
	printf("Unos studenta:\nIme: ");
	scanf("%s", Element->ime);
	printf("Prezime: ");
	scanf("%s", Element->prezime);
	printf("Godina rodenja: ");
	scanf("%d", &Element->godina_rodenja);

	return 0;
}
int Ispis(_Student *Element)
{
	_Student *P = Element->next;
	while (P != NULL) {
		printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n", P->ime, P->prezime, P->godina_rodenja);
		P = P->next;
	}

	return 0;
}
_Student *Pronadi(_Student *Element, char *buffer)
{
	_Student *P = Element->next;
	while (P != NULL && strcmp(buffer, P->prezime))
		P = P->next;

	return P;
}
int Brisi(_Student *Element, _Student *Head)
{
	_Student *P = Head;
	while (P != NULL && P->next != Element)
		P = P->next;

	if (P == NULL)
		return -1;

	P->next = P->next->next;
	free(P->next);

	return 0;
}
