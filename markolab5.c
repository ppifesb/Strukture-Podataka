#include<stdio.h>
#include<string.h>

typedef struct Congregation * cng_pointer;
struct Congregation {
	int number;
	cng_pointer next;
};

int Counter(cng_pointer);
void SortedEntry(cng_pointer);

int main() {
	struct Congregation head ;
	head.next = NULL;
	Counter(&head);

	return 0;
}
int Counter(cng_pointer head) {
	FILE *pointer;
	char buffer[128];
	int check;
	char *ptr_buffer;
	int temporary_var;
	int number_of_bytes;
	
	pointer = fopen("Elements.txt", "r");
	if (pointer == NULL) {
		printf("Greska pri alociranju memorije u fji Counter");
		return -1;
	}


	ptr_buffer = fgets(buffer, 128, pointer);
	check = sscanf(ptr_buffer, "%d %n", &temporary_var, &number_of_bytes);
	SortedEntry(head);
	ptr_buffer += number_of_bytes;


}

void SortedEntry(cng_pointer head) {
	cng_pointer temporary_var=NULL;
	temporary_var = head->next;

	head->next = (cng_pointer)malloc(1 * sizeof(struct Congregation));

	head->next->next = temporary_var;

	if (temporary_var != NULL) {
		if()
	}

}
