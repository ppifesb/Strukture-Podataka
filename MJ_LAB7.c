#include<stdio.h>
#include<stdlib.h>
#define FILE_ERROR "File not opened properly"
#define READING_ERROR "Content of file not read properly"
#define CLOSING_FILE_ERROR "File not closed properly"
#define READING_BUFFER_FAILURE "Error while reading from buffer"
#define MALLOC_ERROR "Failure while allocating memory"
#define EMPTY_STACK_WARNING "Warning,elements can't be poped from empty stack"
#define WRITTING_ERROR "Error while writting to file Postfix.txt"

typedef struct Stog* ptr;  
struct Stog {
	char operator;
	ptr next;
};
void IsFileOpened(FILE*);
void ReadingFromFileCheck(char*);
void Push(ptr);
void IsFileClosed(int);
void ReadingFromBufferCheck(int);
int IsStackEmpty(pointer); //Returns -1 if stack is empty
void IfElse(char, ptr);
int Condition(int); //Returns -1 when condition is not satisfied
void SetPointersAndValues(char, ptr);
ptr Malloc();
void MallocCheck(ptr);
char Pop(ptr); //Returns -1 when stack is empty
void LastElementInOut(ptr);
void PostfixToInfix(char,int); //Second argument differs from 0 if cast to char is needed
void WrittingCheck(int);
ptr FindLastElement(ptr);
ptr FollowerOfLastElement(ptr, ptr);
void CheckStateOfStack(ptr);
void CheckPriorities(ptr,ptr,ptr);
void CharToInt(ptr, ptr);

int main() {
	struct Stog head;
	FILE* pointer = NULL;
	head.next = NULL;
	Push(&head);

	return 0;
	system("PAUSE");
}

void IsFileOpened(FILE* pointer) {
	if (pointer == NULL) {
		printf("%s", FILE_ERROR);
		return -1;
	}
}
void ReadingFromFileCheck(char* to_be_checked) {
	if (*to_be_checked == NULL || *to_be_checked == EOF) {
		printf("%s", READING_ERROR);
		return -1;
	}
}

void IsFileClosed(int to_be_checked)
{
	if (to_be_checked == EOF) {
		printf("%s", CLOSING_FILE_ERROR);
		return -1;
	}
}

void ReadingFromBufferCheck(int to_be_checked)
{
	if (to_be_checked == EOF) {
		printf("%s",READING_BUFFER_FAILURE);
		return -1;
	}
}

int Condition(int to_be_checked)
{
	if (to_be_checked != '+' && to_be_checked != '-' && to_be_checked != '*' && to_be_checked != ')' && to_be_checked != '(')
		return -1;
	else
		return 0;
}

void SetPointersAndValues(char operator, ptr head)
{
	ptr temporary_var = Malloc();
	temporary_var->next = head->next;
	head->next = temporary_var;
	temporary_var->operator=operator;
	
}

void Push(ptr head)
{
	int check = 0;
	FILE* postfix_pointer = fopen("Postfix.txt", "r");
	IsFileOpened(postfix_pointer);
	FILE* infix_pointer = fopen("Infix.txt", "w");
	IsFileOpened(infix_pointer);
	int close_check = 0;
	do {
		check = fgetc(postfix_pointer);
		check = (char)check;
		if (Condition(check) != -1) 
			IfElse(check, head);
		
		else {
			fprintf(infix_pointer, "%c", check);
			WrittingCheck(check);
		}
			
	} while (check != '\n');

	//close_check = fclose(pointer);
	//IsFileClosed(close_check);
}

void IfElse(char operator, ptr head)
{
	if (IsStackEmpty(head) == -1)
		SetPointersAndValues(operator,head);
	else
		CheckStateOfStack(head);
}

int IsStackEmpty(ptr head) {
	if (head->next == NULL) {
		printf("Stack is empty\n");
		return -1;
	}
	else
		return 0;
}

ptr Malloc() {
	ptr allocation_var = NULL;
	allocation_var = (ptr)malloc(sizeof(struct Stog));
	MallocCheck(allocation_var);
	return allocation_var;
}

void MallocCheck(ptr allocation_var) {
	if (allocation_var == NULL) {
		printf("%s\n", MALLOC_ERROR);
		return -1;
	}
}

char Pop(ptr head) {
	char last_in;
	if (IsStackEmpty == -1) {
		printf("%s", EMPTY_STACK_WARNING);
		return -1;
	}
	last_in = head->next->operator;
	LastElementInOut(head);
	return last_in;
}

void LastElementInOut(ptr head) {
	ptr temporary_var = NULL;
	temporary_var = head->next;
	head->next = temporary_var->next;
	free(temporary_var);
}


/*void PostfixToInfix(char op_var,int recognition)  //operator or operand variable
{
	int check = 0;
	FILE* pointer = fopen("Infix.txt", "w");
	IsFileOpened(pointer);
	if (recognition != 0) {
		check = fprintf(pointer, "%c", op_var);
	}
	if (recognition == 0)
		check=fprintf(pointer, "%c", op_var);
	WrittingCheck(check);
	if (recognition == 0)
		fseek(pointer, 4, SEEK_CUR);
	else
		fseek(pointer, 1, SEEK_CUR);
	//check=fclose(pointer);
	//IsFileClosed(check);

}*/

void WrittingCheck(int to_be_checked)
{
	if (to_be_checked != 1 || to_be_checked < 0) {
		printf("%s", WRITTING_ERROR);
		return -1;
	}
}

ptr FindLastElement(ptr head) {
	IsStackEmpty(head);
	while (head->next != NULL)
		head = head->next;
	return head;
}
ptr FollowerOfLastElement(ptr head, ptr last_element) {
	IsStackEmpty(head);
	while (head->next != last_element)
		head = head->next;
	return head;
}

void CheckStateOfStack(ptr head) {
	ptr last_element = FindLastElement(head);
	ptr follower_last_el = FollowerOfLastElement(head, last_element);
	if (follower_last_el == head)
		return 0;
	else
		CheckPriorities(last_element,follower_last_el,head);
}

void CheckPriorities(ptr last_element,ptr follower_last_el,ptr head) {
	CharToInt(last_element, follower_last_el);
	if (last_element <= follower_last_el)
		PostfixToInfix(Pop(head),1);
	else if (last_element > follower_last_el)
		return 0;

}

void CharToInt(ptr last_element, ptr follower_last_el) {
	last_element->operator=(int)last_element->operator;
	follower_last_el->operator=(int)follower_last_el->operator;
}
