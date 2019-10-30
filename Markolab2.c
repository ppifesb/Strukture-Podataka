#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Osoba * ptr;

struct Osoba {
	char ime[20];
	char prezime[20];
	int godina_rodenja;
	ptr veza;
};

void UnosP(ptr);
void Podatci(ptr);
void Ispis(ptr);
void UnosK(ptr);
ptr Trazi(ptr);
void IspisEl(ptr);
void Brisi(ptr,ptr);
ptr PronadiPrethodni(ptr,ptr);


int main() {

	char odabir=NULL,provjera=NULL;

	struct Osoba Head;

	int c;

	Head.veza = NULL;

	do {

		printf("Unesite:P(unos na pocetak),K(unos na kraj),I(ispis liste),T(trazi element i brisi istovremeno):");

		scanf("%c", &odabir);

		if (islower(odabir)!=0)
			odabir = (char)toupper(odabir);

		switch (odabir) {
		     case 'P':
			   UnosP(&Head);
			   puts("");
			   break;

		     case 'K':
			  UnosK(&Head);
		          break;

		     case 'I':
			  Ispis(&Head);
			  puts("");
			  break;

		     case 'T':
			  printf("Trazenje te Brisanje elementa\n");
			  Brisi(Trazi(&Head), &Head);
			  break;

		     default:
		         printf("Greska,unijeli ste krivo slovo\n");
			 break;
		}

		while ((c = getchar()) != '\n' && c != EOF);

		printf("Zelite li unijeti jos elemenata(D za Da,N za Ne):");
		scanf("%c", &provjera);

		if (islower(provjera) != 0)
		provjera = (char)toupper(provjera);

		while ((c = getchar()) != '\n' && c != EOF);


	} while (provjera != 'N');

	system("PAUSE");

	return 0;

}

void UnosP(ptr P) {

	ptr Temp=NULL;

	if ((P->veza) != NULL) {
		Temp = P->veza;
		P->veza = NULL;
	}
	
	P->veza = (ptr)malloc(1 * sizeof(struct Osoba));
	if ((P->veza) == NULL) {
		printf("Greska pri alociranju memorije u fji UnosP");
		return -1;
	}
	Podatci(P->veza);
	P = P->veza;
	if (Temp != NULL) 
		P->veza = Temp;

	else
		P->veza = NULL;

}

void Podatci(ptr P) {
	printf("Ime:");
	scanf("%s", P->ime);
	printf("Prezime:");
	scanf("%s", P->prezime);
	printf("Godina rodenja:");
	scanf("%d", &P->godina_rodenja);

}

void Ispis(ptr P) {
	P = P->veza;
	while (P != NULL) {
		printf("Ime:%s\nPrezime:%s\nGod rodenja:%d\n",P->ime,P->prezime,P->godina_rodenja);
		P = P->veza;
	}

}

void UnosK(ptr P) {
	if ((P->veza) == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}
	P = P->veza;
	while (P->veza != NULL)
		P = P->veza;
	UnosP(P);

}

ptr Trazi(ptr P) {
	char buffer[30];
	int brojac = 0;
	ptr Temp=NULL;

	if ((P->veza) == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	printf("Unesite prezime koje zelite pronaci:");
	scanf("%s", buffer);
	P = P->veza;

	while ((P != NULL) && brojac==0) {
		if (strcmp(P->prezime, buffer) == 0) {
			IspisEl(P);
			Temp = P;
			brojac++;
			break;
		}
		else
			 P = P->veza;
	}
	if (brojac == 0) {
		printf("Navedeno prezime ne postoji u listi\n");
		return NULL;
	}
	else
		return Temp;

}

void IspisEl(ptr P) {
	printf("Podatci za prezime pronadeni\n");
	printf("Ime:%s\nPrezime:%s\nGod rodenja:%d\n", P->ime, P->prezime, P->godina_rodenja);
}

void Brisi(ptr P,ptr R) {
	ptr Pomocna=NULL,Temp=NULL;
	if (P == NULL) {
		printf("Greska,prezime ne postoji");
		return 0;
	}

	Temp = P -> veza;
	Pomocna = PronadiPrethodni(P, R);
	if (Pomocna == NULL) {
		printf("Greska u fji PronadiPrethodni\n");
		return -1;
	}
	free(P);
	Pomocna->veza = Temp;
	
}

ptr PronadiPrethodni(ptr P,ptr R) {
	ptr Temp=NULL;
	int brojac = 0;

	if (R == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	while ((R != NULL) && brojac==0) {
		if ((R->veza) == P) {
			Temp = R;
			brojac++;
			break;
		}
		 R = R->veza;
	}
	if (brojac == 0) {
		printf("Prethodni nije pronaden\n");
		return NULL;
	}
	else
	    return Temp;
}
