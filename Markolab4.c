#include<stdio.h>
#include<stdlib.h>

typedef struct Polinom* pointer;
struct Polinom {
	int koeficijent;
	int eksponent;
	pointer Next;
};




void ReadingFromFile(pointer);
int Counter();
void SetElementOnBeg(pointer);
void PrintElements(pointer);
void Save_Elements(pointer);
void Replace(pointer, pointer,pointer);
pointer FindFollower(pointer, pointer);
pointer Minimum(pointer);
pointer Maximum(pointer);

int main() {
	struct Polinom Head;

	Head.Next = NULL;

	ReadingFromFile(&Head);

	system("PAUSE");

	return 0;
}

void ReadingFromFile(pointer Head)
{
	FILE* pointer=NULL;
	int check=0,brojac=0,i;

	brojac = Counter();

	for (i = 0; i < brojac; i++)
		SetElementOnBeg(Head);

	if (Head->Next == NULL) {
		printf("Greska u fji ReadingFromFile pri postavljanju clanova\n");
		return -1;
	}

	Save_Elements(Head);

	PrintElements(Head);
}

int Counter() {
	FILE* pointer = NULL;
	int check, brojac = 0,temporary_var=0,temporary_var1=0;
	char buffer[128];

	pointer = fopen("polinomi.txt", "r");
	if (pointer == NULL) {
		printf("Greska u fji Counter pri otvaranju datoteke\n");
		return -1;
	}

	do {

		check = fgetc(pointer);

	} while ((char)check != '\n');

	if (check == EOF) {
		printf("Greska pri citanju iz datoteke\n");
		return -1;
	}

	do {
		check = fscanf(pointer, "%d %d", &temporary_var, &temporary_var1);
		if (check == 2)
			brojac++;
		else
		{
			printf("Greska pri ucitavanju iz datoteke u fji Counter\n");
			return -1;
		}
		temporary_var = 0;
		temporary_var1 = 0;
	
	} while (feof(pointer) == 0);


	check = fclose(pointer);

	if (check == EOF) {
		printf("Greska pri zatvaranju datoteke u fji Counter\n");
		return -1;
	}

	return brojac;

}

void SetElementOnBeg(pointer Head) {
	pointer Temporary_var=NULL;

	Temporary_var = Head->Next;

	Head->Next = (pointer)malloc(1 * sizeof(struct Polinom));
	if (Head->Next == NULL) {
		printf("Greska pri alociranju memorije u fji SetElementsOnBeg\n");
		return -1;
	}
	Head = Head->Next;

	if (Temporary_var != NULL)
		Head->Next = Temporary_var;
	else
		Head->Next = NULL;
}

void PrintElements(pointer Head) {
	if (Head->Next == NULL) {
		printf("Lista nema elemenata\n");
		return -1;
	}

	Head = Head->Next;

	while (Head != NULL) {
		printf("%d %d\n", Head->koeficijent, Head->eksponent);
		Head = Head->Next;
	}
}

void Save_Elements(pointer Head) {

	FILE* ptr = NULL;
	int check = 0;
	pointer Temporary_var = NULL, Temporary_var1 = NULL, Max_variable = NULL, Min_variable = NULL;

	Temporary_var1 = Head;

	ptr = fopen("polinomi.txt", "r");
	if (ptr == NULL) {
		printf("Greska u fji ReadingFromFile pri otvaranju datoteke\n");
		return -1;
	}


	do {

		check = fgetc(ptr);

	} while ((char)check != '\n');

	if (check == EOF) {
		printf("Greska pri citanju iz datoteke\n");
		return -1;
	}

	Head = Head->Next;

		do {
			check = fscanf(ptr, "%d %d", &Head->koeficijent, &Head->eksponent);
			if (check == EOF || check == 0 || check != 2) {
				printf("Greska pri ucitavanju elemenata iz datoteke u fji Save_Elements\n");
				return -1;
			}

			Head = Head->Next;

		} while (feof(ptr) == 0 && Head != NULL);

		Head = Temporary_var1->Next;

		Max_variable = Maximum(Temporary_var1);
		Min_variable = Minimum(Temporary_var1);
	
		while ((Head != NULL) || (Temporary_var1->Next != Max_variable) || (Min_variable->Next!=NULL))  {
			if (Head->Next != NULL) {
				if (Head->eksponent < Head->Next->eksponent) {
					Temporary_var = FindFollower(Temporary_var1, Head);

					Replace(Temporary_var1, Head, Temporary_var);

					if (Temporary_var1->Next == NULL) {
						printf("Greska nakon poziva fje Replace,lista nije povezana");
						return -1;
					}

				}

			}
			Head = Head->Next;
		}

	check = fclose(ptr);

	if (check == EOF) {
		printf("Greska pri zatvaranju datoteke u fji Counter\n");
		return -1;
	}

}

void Replace(pointer Head, pointer Replace_var, pointer Prethodni) {
	pointer Temporary_var = NULL,Temporary_var1=NULL;

	Temporary_var1 = Replace_var->Next;
	Temporary_var = Temporary_var1->Next;

	if (Head->Next == NULL) {
		printf("Greska u fji Replace,lista nema elemenata");
		return 0;
	}

	Prethodni->Next = Temporary_var1;
	Temporary_var1->Next = Replace_var;
	Replace_var->Next = Temporary_var;
	

}

pointer FindFollower(pointer Head, pointer Following) {
	
	if (Head->Next == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	while (Head != NULL) {
		if (Head->Next == Following) 
			return Head;
		Head = Head->Next;
	}

	printf("Prethodni nije pronaden\n");
}

pointer Minimum(pointer Head) {
	pointer Minimum = NULL;


	if (Head->Next == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	Head = Head->Next;

	Minimum = Head;

	while ( Head->Next!=NULL) {
		if (Minimum->eksponent > Head->Next->eksponent)
			Minimum = Head;

		Head = Head->Next;
	}

	if (Minimum->eksponent > Head->eksponent)
		return Head;


	else if (Minimum->eksponent < Head->eksponent)
		return Minimum;

	else {
		printf("Greska,minimum nije pronaden");
		return -1;
	}

}

pointer Maximum(pointer Head) {
	pointer Maximum = NULL;


	if (Head->Next == NULL) {
		printf("Lista nema elemenata");
		return 0;
	}

	Head = Head->Next;

	Maximum = Head;

	while (Head->Next != NULL ) {
		if (Maximum->eksponent < Head->Next->eksponent)
			Maximum = Head;

		Head = Head->Next;
	}

	if (Maximum->eksponent < Head->eksponent)
		return Head;

	else if (Maximum->eksponent > Head->eksponent)
		return Maximum;

	else{
		printf("Greska,maksimum nije pronaden");
		return -1;
	}

}

