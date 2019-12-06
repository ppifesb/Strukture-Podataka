#include<stdio.h>
#include<stdlib.h>
#define MEMORY_FAILURE "Failure while allocating memory"
#define FILE_OPENING_ERROR "Failure while opening file"
#define FILE_READING_ERROR "Failure while reading from file"


typedef struct Stog* ptr;
struct Stog {
	int element;
	ptr next;
};
int Push(ptr head);
void CheckMemoryAllocation(ptr);
ptr Malloc();
void IsFileOpened(FILE*);
void CheckReadingFromFile(int);
void CheckReadCharacter(int);


int main() {
	struct Stog head;
	head.next = NULL;
}
int Push(ptr head) {
	int check = 0;
	FILE *pointer = fopen("posfix.txt.txt", "r");
	IsFileOpened(pointer);
	check = fgetc(pointer);
}
void CheckMemoryAllocation(FILE *pointer_allocated) {
	if (pointer_allocated == NULL) {
		printf("%s", MEMORY_FAILURE);
		return -1;
	}
}
ptr Malloc() {
	ptr temporary_var = (ptr)malloc(sizeof(struct Stog));
	CheckMemoryAllocation(temporary_var);
}
void IsFileOpened(FILE* pointer) {
	if (pointer == NULL) {
		printf("%s", FILE_OPENING_ERROR);
		return -1;
	}
}
void CheckReadingFromfile(int to_be_checked) {
	if (to_be_checked == EOF) {
		printf("%s", FILE_READING_ERROR);
		return -1;
	}
}
void CheckReadCharacter(int to_be_checked) {
	to_be_checked = (char)to_be_checked;
	if(sizeof(to_be_checked)==4)
}
