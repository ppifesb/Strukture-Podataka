#include<stdio.h>
#include<stdlib.h>
#define READING_FILE_ERROR "Failure while reading from file"
#define CHARACTER_READING_ERROR "Failure while reading character from file"
#define MALLOC_ERROR "Failure while allocating memory"
#define EMPTY_STACK_ERROR "Warning,stack is empty"
#define FILE_NOT_CLOSED "Failure while closing file"
#define BUFFER_READDING_ERROR "Failure while reading from buffer"
#define POSTFIX_ERROR "Postfix expression isn't correctly written"

typedef struct Stog* ptr;
struct Stog {
	int operand;
	ptr next;
};
void ReadingFromFile(ptr);
void IsFileOpened(FILE*);
void Push(int, ptr);
ptr Malloc();
void CheckMemoryAllocation(ptr);
void SetPointersAndValues(int, ptr, ptr);
int Pop(ptr); //Removes last element from stack and pops its operand
void IstackEmpty(ptr);
void LastElementInOut(ptr); //Removes last element from stack
void RemoveTwoOperands(char, ptr);
char ApplyOperatorToOperands(char, int, int, ptr);
void IsFileClosed(FILE*);
void ReadingFromFileCheck(char*);
void ReadingFromBuffer(char*, ptr);
void ReadingFromBufferCheck(int, char*, ptr);
void ShiftBytes(char**, int, int); //Shift bytes depending on what was read from buffer,operand or operator
void PostfixExpressionResult(ptr);
void CorrectnessOfPostfix(ptr);

int main() {
	struct Stog head;
	head.next = NULL;
	ReadingFromFile(&head);
	PostfixExpressionResult(&head);
}

void ReadingFromFile(ptr head)
{
	int check = 0;
	char buffer[128] = { 0 };
	char* fgets_check = 0;

	FILE* pointer = fopen("Postifx.txt", "r");
	IsFileOpened(pointer);

	fgets_check = fgets(buffer, 128, pointer);

	check = fclose(pointer);
	IsFileClosed(pointer);

	ReadingFromFileCheck(fgets_check);
	ReadingFromBuffer(buffer, head);
}

void IsFileOpened(FILE* file_pointer) {
	if (file_pointer == NULL) {
		printf("%s", READING_FILE_ERROR);
		return -1;
	}
}

void Push(int operand, ptr head)
{
	ptr pointer_to_allocated = Malloc();
	SetPointersAndValues(operand, pointer_to_allocated, head);
}

ptr Malloc()
{
	ptr pointer_to_allocated = (ptr)malloc(sizeof(struct Stog));
	CheckMemoryAllocation(pointer_to_allocated);
	return pointer_to_allocated;
}

void CheckMemoryAllocation(ptr to_be_checked) {
	if (to_be_checked == NULL) {
		printf("%s", MALLOC_ERROR);
		return -1;
	}
}

void SetPointersAndValues(int operand, ptr pointer_to_allocated, ptr head)
{
	pointer_to_allocated->next = head->next;
	head->next = pointer_to_allocated;
	pointer_to_allocated->operand = operand;
}

int Pop(ptr head) {
	CorretnessOfPostfix(head);
	int to_be_poped = head->next->operand;
	IstackEmpty(head);
	LastElementInOut(head);
	return to_be_poped;
}

void IstackEmpty(ptr head) {
	if (head->next == NULL) {
		printf("%s", EMPTY_STACK_ERROR);
		return -1;
	}
}

void LastElementInOut(ptr head) {
	ptr to_be_removed = head->next;
	head->next = to_be_removed->next;
	free(to_be_removed);
}

void RemoveTwoOperands(char operator,ptr head) {
	int last_element = Pop(head);
	int following_last_element = Pop(head);
	ApplyOperatorToOperands(operator,last_element, following_last_element, head);
}

char ApplyOperatorToOperands(char operator,int first_operand, int second_operand, ptr head) {
	int result = 0;
	if (operator=='*')
		result = first_operand * second_operand;
	else if (operator == '+')
		result = first_operand + second_operand;
	else if (operator== '-')
		result = first_operand - second_operand;
	Push(result, head);
}

void IsFileClosed(FILE* to_be_checked) {
	if (to_be_checked == NULL) {
		printf("%s", FILE_NOT_CLOSED);
		return -1;
	}
}
void ReadingFromFileCheck(char* to_be_checked) {
	if (to_be_checked == NULL) {
		printf("%s", READING_FILE_ERROR);
		return -1;
	}
}

void ReadingFromBuffer(char* pointer_to_buffer, ptr head) //sscanf reads all numbers together which are positioned one by another in postfix expression
{                                                         //if two numbers are divided with blankspace then sscanf reads number and blankspace,but ignores blankspace
	int sscanf_check = 0;
	int character_from_buffer = 0;
	int number_of_bytes = 0;
	do {
		if (pointer_to_buffer[0] == ' ')
			ShiftBytes(&pointer_to_buffer, 0, 0);
		if (pointer_to_buffer[0] != '*' && pointer_to_buffer[0] != '+' && pointer_to_buffer[0] != '-')
			sscanf_check = sscanf(pointer_to_buffer, "%d %n", &character_from_buffer, &number_of_bytes);
		else
			sscanf_check = 0;
		ReadingFromBufferCheck(sscanf_check, pointer_to_buffer, head);
		if (sscanf_check != 0)
			Push(character_from_buffer, head);
		ShiftBytes(&pointer_to_buffer, sscanf_check, number_of_bytes);
	} while (strlen(pointer_to_buffer) != 0);
}

void ReadingFromBufferCheck(int to_be_checked, char* pointer_to_buffer, ptr head) //If to_be_checked==0->character read from buffer is operator
{
	char operator;
	if (to_be_checked == EOF) {
		printf("%s", BUFFER_READDING_ERROR);
	}
	else if (to_be_checked == 0) {
		operator=pointer_to_buffer[0];
		RemoveTwoOperands(operator, head);
	}
}

void ShiftBytes(char** pointer_to_buffer, int sscanf_check, int number_of_bytes) {
	if (sscanf_check == 0)
		*pointer_to_buffer = *pointer_to_buffer + 1;
	else if (sscanf_check != 0)
		*pointer_to_buffer = *pointer_to_buffer + number_of_bytes;
}

void PostfixExpressionResult(ptr head) {
	printf("Result of postfix expression is %d", Pop(head));
}

void CorrectnessOfPostfix(ptr head) {
	if (head->next == NULL) {
		printf("%s", POSTFIX_ERROR);
		return -1;
	}
}
