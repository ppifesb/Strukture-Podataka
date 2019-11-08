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
void SortElements(pointer);
void SumOfElements(pointer);

int main() {
	struct Polinom Head;

	struct Polinom Polinom;

	Head.Next = NULL;

	Polinom.Next = NULL;

	ReadingFromFile(&Head);

	ReadingFromFile(&Polinom);

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
	pointer Temporary_head = NULL;

	Temporary_head = Head;

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


		SortElements(Temporary_head);

	check = fclose(ptr);

	if (check == EOF) {
		printf("Greska pri zatvaranju datoteke u fji Counter\n");
		return -1;
	}

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
	return -1;
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


void SortElements(pointer Head) {

	pointer Maximum_el = NULL, Minimum_el = NULL, Follower_max = NULL, Temporary_head = NULL;

	if (Head->Next == NULL) {
		printf("Lista nema elemenata(fja SortElements)");
		return 0;
	}

	Temporary_head = Head;

	Maximum_el = Maximum(Head);

	Minimum_el = Minimum(Head);

	Follower_max = FindFollower(Head,Maximum_el);

	if (Follower_max == NULL) {
		printf("Greska u fji SortElements,prethodni nije pronaden\n");
		return -1;
	}

	Head = Head->Next;

	do {
		if (Head->Next==NULL)
			Head = Temporary_head;

		if (Head->Next->eksponent > Head->eksponent)
			Replace(Head->Next, Head, Temporary_head);

		Head = Head->Next;


	} while (Temporary_head->Next != Maximum && Follower_max->Next != Maximum_el); 
			
		
	PrintElements(Temporary_head);

}

void Replace(pointer ToBeReplaced, pointer Replacer, pointer Head) {
	pointer Follower_replacer = NULL, Temporary_var = NULL;

	if (Head->Next == NULL) {
		printf("Greska u fji Replace,lista nema elemenata");
		return 0;
	}

	Temporary_var = ToBeReplaced->Next;

	Follower_replacer = FindFollower(Head, Replacer);

	Follower_replacer->Next = ToBeReplaced;

	ToBeReplaced->Next = Replacer;

	Replacer->Next = Temporary_var;

}

void SumOfElements(pointer Head) {
	if (Head->Next == NULL) {
		printf("Greska,lista nema elemenata");
		return -1;
	}
}
