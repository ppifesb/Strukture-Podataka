//Mislav Kovac
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
int UnosElementaNaKraj(_Student *);
int Unos(_Student *);
int Ispis(_Student *);
int Brisi(_Student *, _Student *);
int Provjera(char *);
_Student *Pronadi(_Student *, char *);
_Student *Alociraj(_Student *);

int main()
{
	_Student *Head = NULL;
	int check = 0;
	char izbor_1 = 0, izbor_2 = 0;
	char buffer[128] = { 0 };
	_Student *Trazi = NULL;

	Head = Alociraj(Head);
	Head->next = NULL;
	
	do {
		izbor_1 = 0;
		izbor_2 = 0;
		while (toupper(izbor_1) != 'D' && toupper(izbor_1) != 'N') {
			while (toupper(izbor_2) != 'P' && toupper(izbor_2) != 'K') {
				printf("Zelite li dodati element na pocetak ili kraj? (P/K): ");
				check = scanf(" %c", &izbor_2);
				if (check == EOF) {
					printf("***Greska!***");
					system("PAUSE");
					return -1;
				}
				if (toupper(izbor_2) == 'P') {
					check = UnosElementaNaPoc(Head);
					if (check == -1) {
						printf("\n***Greska!***\n");
						system("PAUSE");
						return -1;
					}
					if (izbor_1 != '\0') {
						printf("\n***Greska***\n");
						system("PAUSE");
						return -1;
					}
				}
				else if (toupper(izbor_2) == 'K') {
					check = UnosElementaNaKraj(Head);
					if (check == -1) {
						printf("\n***Greska!***\n");
						system("PAUSE");
						return -1;
					}
					if (izbor_1 != '\0') {
						printf("\n***Greska***\n");
						system("PAUSE");
						return -1;
					}
				}
			}
			printf("Zelitel li unijeti jos jedan element? (D/N)");
			check = scanf(" %c", &izbor_1);
			if (check == EOF) {
				printf("***Greska!***");
				system("PAUSE");
				return -1;
			}
		}
	} while (toupper(izbor_1) == 'D');

	Ispis(Head);

	printf("\nUnesite prezime: ");
	check = scanf(" %s", buffer);
	if (check == EOF) {
		printf("***Greska!***");
		system("PAUSE");
		return -1;
	}

	Trazi = Pronadi(Head, buffer);
	if (Trazi == NULL) {
		system("PAUSE");
		return 1;
	}

	printf("\nIme: %s\nPrezime: %s\nGodina rodenja: %d\n", Trazi->ime, Trazi->prezime, Trazi->godina_rodenja); 
	
	Brisi(Trazi, Head);  //Moze se brisat po bilo kojem elementu ali treba prilagodit buffer

	check = Ispis(Head);
	if (check == -1) {
		printf("***Greska u brisanju elementa!!***");
		system("PAUSE");
		return 1;
	}

	system("PAUSE");

	return 0;
}
_Student *Alociraj(_Student *Element)
{
	Element = (_Student *)malloc(sizeof(_Student));
	if ((Element == NULL) || (Element->ime == NULL) || (Element->prezime == NULL) ||(Element->godina_rodenja == NULL)) {
		printf("***Greska u alociranju memorije!***");
		return NULL;
	}

	return Element;
}
int UnosElementaNaPoc(_Student *Head)
{
	int check = 0; 

	_Student *Element = NULL;
	Element = Alociraj(Element);
	if (Element == NULL)
		return -1;

	Element->next = Head->next;
	Head->next = Element;

	check = Unos(Element);
	if (check == -1)
		return -1;

	return 0;
}
int UnosElementaNaKraj(_Student *Head)
{
	_Student *Element = NULL;
	_Student *P = Head;
	int check;

	Element = Alociraj(Element);
	if (Element == NULL)
		return -1;

	while (P->next != NULL)
		P = P->next;

	Element->next = P->next;
	P->next = Element;

	check = Unos(Element);
	if (check == -1)
		return -1;

	return 0;
}
int Unos(_Student *Element)
{
	int check = 0;

	printf("Unos studenta:\nIme: ");
	check = scanf("%s", Element->ime);
	if (check == EOF || Provjera(Element->ime) == 1)
		return -1;
	printf("Prezime: ");
	check = scanf("%s", Element->prezime);
	if (check == EOF || Provjera(Element->prezime) == 1)
		return -1;
	printf("Godina rodenja: ");
	check = scanf("%d", &Element->godina_rodenja);
	while ((getchar()) != '\n');						//Ciscenje buffera;
	if (check == EOF)
		return -1;

	return 0;
}
int Ispis(_Student *Element)
{
	_Student *P = Element->next;
	while (P != NULL) {
		printf("\nIme: %s\nPrezime: %s\nGodina rodenja: %d\n", P->ime, P->prezime, P->godina_rodenja);
		P = P->next;
	}

	return 0;
}
_Student *Pronadi(_Student *Head, char *buffer)
{
	_Student *P = Head->next;

	if (P == NULL) {
		printf("\n***Lista je prazna!!***\n");
		return NULL;
	}

	while (P != NULL && strcmp(buffer, P->prezime))
		P = P->next;

	if (P == NULL) {
		printf("\n***Element nije pronaden!!***\n");
		return NULL;
	}

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
	free(Element);

	return 0;
}
int Provjera(char *string) //Vraca 1 ako je unesen broj; Vraca 0 Ako su svi elementi char
{
	int i = 0;

	for (i = 0; i < strlen(string); i++) {
		if (!isalpha(string[i]))
			return 1;						
	}
	
	return 0;
}
