#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_SIZE 128

typedef struct {
	char ime[32];
	char prezime[32];
	float bodovi;
	float r_bodovi;
}_student;

int RowCount(void);
int ReadingFromFile(_student *, int);
void Print(_student *);

int main()
{
	int broj_redaka, i, check;
	_student *p_student;

	broj_redaka = RowCount();
	if (broj_redaka == -1){
		printf("Greska u citanju iz datoteke!");
		goto exit;
	}

	p_student = (_student *)malloc(broj_redaka * sizeof(_student));

	check = ReadingFromFile(p_student, broj_redaka);

	if (check == -1)
		goto exit;

	printf("Bodovi (R/A)\t\tIme Prezime\n");
	for (i = 0; i < broj_redaka; i++)
		Print(p_student + i);

exit:
	system("PAUSE");
	return 0;
}
int RowCount(void)
{
	FILE *p_studenti;
	int broj_redaka = 0;
	char buffer[BUFFER_SIZE] = { 0 };

	p_studenti = fopen("Studenti.txt", "r");

	if (p_studenti == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	do {
		fgets(buffer, BUFFER_SIZE, p_studenti);
		if (strlen(buffer) != 0)
			broj_redaka++;
		memset(buffer, 0, sizeof(buffer));
	} while (!feof(p_studenti));

	fclose(p_studenti);

	return broj_redaka;
}
int ReadingFromFile(_student *p_student, int broj_redaka)
{
	FILE *p_studenti;
	int i;

	p_studenti = fopen("Studenti.txt", "r");
	if (p_studenti == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	for (i = 0; i<broj_redaka; i++) {
		fscanf(p_studenti, "%f %s %s", &p_student[i].bodovi, p_student[i].ime, p_student[i].prezime);
		p_student[i].r_bodovi = (p_student[i].bodovi / 50 ) * 100;
	}

	fclose(p_studenti);

	return 0;
}
void Print(_student *p_student)
{
	printf("%.2f     %d/50  \t%s %s", p_student->r_bodovi, (int)p_student->bodovi, p_student->ime, p_student->prezime);
	printf("\n");
}
