#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<ctype.h>

typedef struct Osoba* ptr;

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

void Brisi(ptr, ptr);

ptr PronadiPrethodni(ptr, ptr);

void DodajIza(ptr);

void DodajIspred(ptr);

void Sortiranje(ptr);

ptr Zamjena(ptr, ptr,ptr);

ptr MinimalniEl(ptr);

ptr MaksimalniEl(ptr);

void Upis_Dat(ptr);

void Ucitavanje_Dat(ptr);

void Provjera_ucitavanja(int);

int Brojac();

void UnosP_Dat(ptr);

int main() {

	char odabir=NULL,provjera=NULL;

	struct Osoba Head;

	struct Osoba Head_dat;

	int c;
	
	Head.veza = NULL;

	Head_dat.veza = NULL;

	do {

		printf("Unesite:P(unos na pocetak),K(unos na kraj),I(ispis liste),S(unos ispred),Z(unos iza),T(trazi element):");

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

			case 'S':
				printf("Dodavanje elementa ispred\n");
				DodajIspred(&Head);
				puts("");
				break;

			case 'Z':
				printf("Dodavanje elementa iza\n");
				DodajIza(&Head);
				puts("");
				break;

			case 'T':
				printf("Brisanje elementa\n");
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


	Sortiranje(&Head);

	printf("Ispis sortirane liste\n\n");

	Ispis(&Head);
    
	Upis_Dat(&Head);

	printf("\nUcitavanje iz datoteke\n");

	Ucitavanje_Dat(&Head_dat);

	system("PAUSE");

	return 0;

}

void UnosP(ptr P) {

	ptr Temp = NULL;

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

		printf("Ime:%s\nPrezime:%s\nGod rodenja:%d\n", P->ime, P->prezime, P->godina_rodenja);

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

	ptr Temp = NULL;


	if ((P->veza) == NULL) {

		printf("Lista nema elemenata\n");

		return 0;

	}

	printf("Unesite prezime koje zelite pronaci:");
	puts("");

	scanf("%s", buffer);

	P = P->veza;

	while ((P != NULL) && brojac == 0) {

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

	printf("\nPodatci za prezime pronadeni\n\n");

	printf("Ime:%s\nPrezime:%s\nGod rodenja:%d\n\n", P->ime, P->prezime, P->godina_rodenja);

}

void Brisi(ptr P, ptr R) {

	ptr Pomocna = NULL, Temp = NULL;

	if (P == NULL) {

		printf("Greska,prezime ne postoji\n");

		return 0;

	}

	Temp = P->veza;

	Pomocna = PronadiPrethodni(P, R);

	if (Pomocna == NULL) {

		printf("Greska u fji PronadiPrethodni\n");

		return -1;

	}

	free(P);

	Pomocna->veza = Temp;

}

ptr PronadiPrethodni(ptr P, ptr R) {

	ptr Temp = NULL;

	int brojac = 0;

	if (R == NULL) {

		printf("Lista nema elemenata\n");

		return 0;

	}

	while (R != NULL) {

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

void DodajIza(ptr P) {
	
	ptr Temp=NULL,Pomocna=NULL;

	Temp = Trazi(P);

	Pomocna = PronadiPrethodni(Temp, P);
	
	UnosP(Pomocna);
}

void DodajIspred(ptr P) {
	ptr Temp = NULL;
	
	Temp = Trazi(P);

	UnosP(Temp);
}

void Sortiranje(ptr P) {
	ptr Temp = NULL, Pomocna = NULL, Var = NULL,Dodatna=NULL;
	int brojac = 0;
	
	Pomocna = P;
	if (P->veza == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	Dodatna = PronadiPrethodni(MaksimalniEl(Pomocna), Pomocna);

	if (Dodatna == NULL) {
		printf("Greska u fji MaksimalniEl");
		return -1;
	}

	P = P->veza;

	while((Pomocna->veza != MinimalniEl(Pomocna) && (Dodatna->veza != MaksimalniEl(Pomocna)))){
		P = Pomocna;
		P = P->veza;
		while ((P != NULL) && (P->veza != NULL)) {
			if (strcmp(P->prezime, P->veza->prezime) > 0) {
				Temp = PronadiPrethodni(P, Pomocna);
				if (Temp == NULL) {
					printf("Greska u fji PronadiPrethodni\n");
					return -1;
				}
				Var = Zamjena(P, P->veza, Temp);
				if (Var == NULL) {
					printf("Greska u fji Zamjena\n");
					return -1;
				}
				brojac++;

			}

			if (brojac >= 1)
				P = Var;

			else
				P = P->veza;
		}
		
	}
}

ptr Zamjena(ptr Zamjenik, ptr Zamjenitelj, ptr Prethodni) {

	ptr Temp = NULL;

	Temp = Zamjenitelj->veza;

	Prethodni->veza = Zamjenitelj;

	Zamjenik->veza = Temp;

	Zamjenitelj->veza = Zamjenik;

	return Zamjenik;

}

ptr MinimalniEl(ptr P) {
	ptr Minimalni=NULL,Pomocna=NULL,brojac=0;

	if (P->veza == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}
	P = P->veza;

	Minimalni = P;

	while ((P != NULL) && (P->veza)!= NULL) {
		if (strcmp(P->prezime, P->veza->prezime) > 0) {
			Minimalni = P->veza;
			brojac++;
		}

		P = P->veza;
	}
	if (brojac > 0)
		return Minimalni;
	else
		return P;
	
}

ptr MaksimalniEl(ptr P) {

	ptr Maksimalni = NULL,Pomocna=NULL;
	int brojac = 0;

	Pomocna = P;

	if (P->veza == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}
	P = P->veza;

	Maksimalni = P;

	while ((P != NULL) && P->veza!=NULL) {
		if (strcmp(P->prezime, P->veza->prezime) < 0) {
			Maksimalni = P->veza;
			brojac++;
		}

		P = P->veza;
	}
	if (brojac > 0)
		return Maksimalni;
	else
		return P;
}

void Upis_Dat(ptr P) {
	FILE* ptr = NULL;
	int provjera=0,check=0;

	if (P->veza == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	ptr = fopen("vezanalista.txt", "w");

	if (ptr == NULL) {
		printf("Greska pri otvaranju datoteke");
		return -1;
	}


	provjera=fprintf(ptr, "Ime\t\tPrezime\t\tGodina rodenja\n");

	if (provjera < 0) {
		printf("Greska pri pisanju u datoteku(1)");
		return -1;
	}
	
    
	P = P->veza;

	while (P != NULL && feof(ptr) == 0) {
		check=fprintf(ptr, "%s\t%s\t%d\n", P->ime, P->prezime, P->godina_rodenja);
		if (check < 0) {
			printf("Greska pri pisanju u datoteku(2)");
			return -1;
		}

		P = P->veza;
	}

        provjera=fclose(ptr);

	if (provjera == EOF) {
		printf("Greska pri zatvaranju datoteke");
		return -1;
	}
}


void Ucitavanje_Dat(ptr P) {

	FILE* pok = NULL;
	int provjera = 0, brojac = 0,i,check=0;
	ptr Temp = NULL;

	Temp = P;

	brojac = Brojac();
	
	for (i = 0; i < brojac; i++)
		UnosP_Dat(P);


		pok = fopen("studenti.txt", "r");

		if (pok == NULL) {
			printf("Greska pri otvaranju datoteke");
			return -1;
		}

		rewind(pok);

		P = P->veza;

		do {
			provjera = fscanf(pok, "%s%s%d", P->ime, P->prezime, &P->godina_rodenja);
			Provjera_ucitavanja(provjera);
			P = P->veza;

		} while ((feof(pok) == 0) && (P != NULL));

		Ispis(Temp);

		check = fclose(pok);

		if (check == EOF) {
			printf("Greska pri zatvaranju datoteke u fji Ucitavanje_Dat");
			return -1;
		}

	}

void Provjera_ucitavanja(int povratna_vr) {

	if (povratna_vr == EOF) {
		printf("Greska pri ucitavanju");
		return -1;
	}

}

int Brojac()
{
	FILE* pok=NULL;
	char buffer[128];
	int brojac = 0,provjera=0;

	pok = fopen("Studenti.txt", "r");

	if (pok == NULL) {
		printf("Greska pri otvaranju datoteke");
		return -1;
	}


	do {
		fgets(buffer, 128, pok);

		if (strlen(buffer) != 0)
			brojac++;

		memset(buffer, '\0', 128);

	} while (feof(pok) == 0);

	provjera = fclose(pok);

	if (provjera == EOF) {
		printf("Greska pri zatvaranju datoteke u fji Brojac");
		return -1;
	}

	return brojac;
}

void UnosP_Dat(ptr P) {

	ptr Temp=NULL;

	Temp = P->veza;

	P->veza = (ptr)malloc(1 * sizeof(struct Osoba));
	if (P == NULL) {
		printf("Greska pri alociranju memorije");
		return -1;

	}

	P = P->veza;

	if (Temp != NULL)
		P->veza = Temp;
	else
		P->veza = NULL;
}
