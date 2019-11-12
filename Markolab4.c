#include<stdio.h>
#include<stdlib.h>

typedef struct Polinom* pointer;
struct Polinom {
	int koeficijent;
	int eksponent;
	pointer Next;
};

void ReadingFromFile(pointer,pointer);
int Counter(int *);
void SetElementOnBeg(pointer);
void PrintElements(pointer);
void Save_Elements(pointer,pointer);

int main() {
	struct Polinom head;

	struct Polinom polinom;

	head.Next = NULL;

	polinom.Next = NULL;

	ReadingFromFile(&head,&polinom);

	system("PAUSE");

	return 0;
}

void ReadingFromFile(pointer head_p1,pointer head_p2)
{
	FILE* pointer=NULL;
	int check = 0;
	int brojac1 = 0;
	int brojac2 = 0;
	int* brojac2_ptr;
	int i;

	brojac2_ptr = &brojac2;

	brojac1 = Counter(brojac2_ptr);

	printf("%d\n", brojac1);
	printf("%d\n\n", brojac2);

	for (i = 0; i < brojac1; i++)
		SetElementOnBeg(head_p1);

	for (i = 0; i < brojac2; i++)
		SetElementOnBeg(head_p2);

	if (head_p1->Next == NULL) {
		printf("Greska u fji ReadingFromFile pri postavljanju clanova\n");
		return -1;
	}

	if (head_p2->Next == NULL) {
		printf("Greska u fji ReadingFromFile pri postavljanju clanova\n");
		return -1;
	}

	Save_Elements(head_p1,head_p2);


	PrintElements(head_p1);

	puts("");

	PrintElements(head_p2);
}

int Counter(int *brojac2_ptr) {
	FILE* pointer = NULL;
	int check = 0;
	int brojac1 = 0;
	int temporary_var = 0;
	int  temporary_var1 = 0;
	char buffer[128];
	char* ptr_buffer;

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
		ptr_buffer = fgets(buffer, 128, pointer);
		    check = 0;
			check = sscanf(buffer, "%d %d", &temporary_var, &temporary_var1);
			if (check == 2 && strlen(buffer)!=0) {
				brojac1++;
				temporary_var = 0;
				temporary_var1 = 0;
			}

			else if (check != 2) {
				check = 0;
				ptr_buffer = fgets(buffer, 128, pointer);
				do {
					check = sscanf(buffer, "%d %d", &temporary_var, &temporary_var1);
					if (check == 2)
						(*brojac2_ptr)++;
					else
						;
					temporary_var = 0;
					temporary_var1 = 0;

					ptr_buffer = fgets(buffer, 128, pointer);

				} while (feof(pointer) == 0);
			}

			else
				;
		
	
	} while (feof(pointer) == 0);

	

	check = fclose(pointer);

	if (check == EOF) {
		printf("Greska pri zatvaranju datoteke u fji Counter\n");
		return -1;
	}

	return brojac1;

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

	Head->Next = Temporary_var;
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

void Save_Elements(pointer head_p1,pointer head_p2) {

	FILE* ptr = NULL;
	int check = 0;
	int temporary_var = 0;
	int temporary_var1 = 0;
	char buffer[128];
	char* ptr_buffer;
	int counter = 0;
	int counter1 = 0;

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

	head_p1 = head_p1->Next;
	head_p2 = head_p2->Next;
	do {
		ptr_buffer = fgets(buffer, 128, ptr);
		check = 0;
		check = sscanf(buffer, "%d %d", &temporary_var, &temporary_var1);
		if (check == 2 && strlen(buffer) != 0) {
			head_p1->koeficijent = temporary_var;
			head_p1->eksponent = temporary_var1;
			temporary_var = 0;
			temporary_var1 = 0;
			counter++;
		}

		else if (check != 2) {
			check = 0;
			ptr_buffer = fgets(buffer, 128, ptr);
			do {
				check = sscanf(buffer, "%d %d", &temporary_var, &temporary_var1);
				if (check == 2) {
					head_p2->koeficijent = temporary_var;
					head_p2->eksponent = temporary_var1;
					counter1++;
				}
				else
					;
				temporary_var = 0;
				temporary_var1 = 0;

				ptr_buffer = fgets(buffer, 128, ptr);
				
				if(counter!=0)
				head_p1 = head_p1->Next;

				if(counter1!=0)
				head_p2 = head_p2->Next;

			} while (feof(ptr) == 0 && (head_p1 != NULL) && (head_p2 != NULL));
		}

		else
			;


	} while (feof(ptr) == 0);

	check = fclose(ptr);

	if (check == EOF) {
		printf("Greska pri zatvaranju datoteke u fji Counter\n");
		return -1;
	}
	
}
