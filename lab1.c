//Marko Jankuleski
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
}_studenti;

int BrojStudenata(FILE *,char *);
void Podatci(FILE *, _studenti *,char *,int);
void Ispis(_studenti *,int);


int main() {

	int brojac = 0;
	FILE *studenti_ptr;
	char buffer[128] = { 0 };
	_studenti *niz_ptr;

	studenti_ptr = fopen("studenti.txt", "r");
	if (studenti_ptr == NULL)
		puts("GRESKA");
	if (fclose(studenti_ptr) != 0)
		puts("GRESKA");
	brojac = BrojStudenata(studenti_ptr,buffer);

	niz_ptr = (_studenti *)malloc(brojac * sizeof(_studenti));
	if (niz_ptr == NULL)
		puts("GRESKA");
	memset(buffer, ' ', 128);
	Podatci(studenti_ptr,niz_ptr,buffer,brojac);

	Ispis(niz_ptr, brojac);


	system("PAUSE");
	return 0;
}

int BrojStudenata(FILE *ptr,char *niz) {
	int brojac = 0,velicina=0;
	ptr = fopen("studenti.txt", "r");
	if (ptr == NULL)
		puts("GRESKA U FUNKCIJI BROJSTUDENATA");

	do {
		fgets(niz, 128, ptr);
		if (strlen(niz) != 0)
			brojac++;
		memset(niz, ' ', 128);
	} while(feof(ptr)==0);

	fclose(ptr);
	return brojac;

}

void Podatci(FILE *ptr,_studenti *pok,char *buffer,int brojac) {
	int i = 0,n=0,j=0;
	ptr = fopen("studenti.txt", "r");
	if (ptr == NULL)
		puts("GRESKA U FUNKCIJI PODATCI");

	do {
		fgets(buffer, 128, ptr);
		sscanf(buffer, "%d %s %s", &pok[i].bodovi, pok[i].ime, pok[i].prezime);
		i++;
	} while ((feof(ptr) == 0) && (i<brojac));

	fclose(ptr);

}

void Ispis(_studenti *ptr,int brojac) {
	int i = 0;
	for (i = 0; i < brojac; i++) {
		printf("%s %s\t%d\t%f", ptr[i].ime, ptr[i].prezime, ptr[i].bodovi, (float)ptr[i].bodovi / 50 * 100);
		puts(" ");
	}
}
