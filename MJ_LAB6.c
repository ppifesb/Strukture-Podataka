#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ERROR "Failure in allocating memory"
#define CHAR_ERROR "Wrong letter"
#define READING_ERROR "Failure while saving saving feedback from user"

typedef struct Stog* pointer;   //same pointer for queue as functions are the same,except for deleting elements
struct Stog {
	int element;
	pointer next;
};

struct Queue {
	int element;
	pointer next;
};

void Push(pointer);
pointer Malloc(pointer);
void CheckMemoryAllocation(pointer);
int Pop(pointer); //Returns -1 when stack is empty
void SetPointersAndValues(pointer, pointer,int);
void LastElementInOut(pointer);
void LowerToUpper(char*);
int GenerateRandomNumber(void);
void CheckStateOfStack(pointer);
int IsStackEmpty(pointer); //Same function for Queue
void ReadingCheck(int);
void DecisionCheck(char*);
void BufferClean(void);
void Decision(char*);
void SwitchCase(pointer,pointer);
void CheckSwitchCase(char,pointer,pointer);
int PopQueue(pointer); //Returns -1 when queue is empty
pointer FindLastElement(pointer);
pointer FollowerOfLastElement(pointer,pointer);
void FirstElementInOut(pointer,pointer);

int main() {
	struct Stog head;
	struct Queue dummy;
	head.next = NULL;
	dummy.next = NULL;
	char decision;
	int check = 0;
	do {
		SwitchCase(&head, &dummy);
		BufferClean();
		Decision(&decision);
		BufferClean();
	} while (decision == 'Y');

	system("PAUSE");
	return 0;
}
void Push(pointer head)
{
	pointer temporary_var = NULL;
	int random_num =GenerateRandomNumber();
	temporary_var=Malloc(head);
	SetPointersAndValues(head,temporary_var ,random_num);
}

pointer Malloc(pointer head)
{
	pointer temporary_var=NULL;
	temporary_var = (pointer)malloc(sizeof(struct Stog));
	CheckMemoryAllocation(temporary_var);
	return temporary_var;
}
void CheckMemoryAllocation(pointer ptr_allocated) {
	if (ptr_allocated == NULL) {
		printf("%s", ERROR);
		return -1;
	}
	else
		return 0;
}
int Pop(pointer head) {
	int last_in = 0;
	if (IsStackEmpty(head) == 0)
		return -1;
	last_in = head->next->element;
	LastElementInOut(head);
	return last_in;
}
void SetPointersAndValues(pointer head, pointer ptr_allocated, const int random_num) {
	ptr_allocated->next = head->next;
	head->next = ptr_allocated;
	ptr_allocated->element = random_num;
}
void LastElementInOut(pointer head) {
	pointer temporary_var = NULL;
	temporary_var = head->next;
	head->next = temporary_var->next;
	free(temporary_var);
}

void LowerToUpper(char* ptr)
{
	if (islower(*ptr))
		*ptr=(char)toupper(*ptr);
}

int GenerateRandomNumber(void)
{
	int random_num = 0;
	srand((unsigned int)time(NULL));
	random_num = rand() % 101;
	while (random_num < 10)
		random_num = rand() % 101;
	return random_num;
}
void CheckStateOfStack(pointer head) {
	IsStackEmpty(head);
	head = head->next;
	while (head != NULL) {
		printf("%d\n", head->element);
		head = head->next;
	}
}

int IsStackEmpty(pointer head) {
	if (head->next == NULL) {
		printf("Stack is empty\n");
		return 0;
	}
}

void ReadingCheck(int to_be_checked)
{
	if (to_be_checked != 1 || to_be_checked == EOF) {
		printf("%s", READING_ERROR);
		return - 1;
	}
}

void DecisionCheck(char* to_be_checked)
{
	if (*to_be_checked != 'Y' && *to_be_checked != 'N') {
		printf("%s\n", CHAR_ERROR);
		BufferClean();
		Decision(to_be_checked);
	}
}

void BufferClean(void)
{
	int buffer_check = 0;
	while ((buffer_check = getchar()) != '\n' && buffer_check != EOF);
}

void Decision(char* to_be_returned) {
	int check = 0;
	printf("Do you want to add or delete more elemets?(Y for yes,N for no): ");
	check = scanf("%c", to_be_returned);
	ReadingCheck(check);
	LowerToUpper(to_be_returned);
	DecisionCheck(to_be_returned);
}
void SwitchCase(pointer head,pointer dummy) {

	int check = 0;
	char choice;
	int poped_element = 0;
	printf("P(put new element on stack), D(delete element from the top of the stack), C(check state of stack),Q(put new element on queue),S(check state of queue),E(delete element from thr beginning of queue)\n");
	printf("Enter a letter: ");
	check = scanf("%c", &choice);
	ReadingCheck(check);
	LowerToUpper(&choice);
	switch (choice) {
	case 'P':
		Push(head);
		break;
	case 'Q':
		Push(dummy);
		break;
	case 'S':
		CheckStateOfStack(dummy);
		break;
	case 'E':
		if (poped_element=PopQueue(dummy) != -1) {
			printf("Poped element is %d\n",poped_element);
			break;
		}
		printf("Warning,elements can't be poped from empty queue\n");
		break;
	case 'D':
		if (poped_element = Pop(head) != -1) {
			printf("Poped element is %d\n", poped_element);
			break;
		}
		printf("Warning,elements can't be poped from empty stack\n");
		break;
	case 'C':
		CheckStateOfStack(head);
		break;
	default:
		printf("%s", CHAR_ERROR);
		CheckSwitchCase(choice, head,dummy);
		break;
	}
}

void CheckSwitchCase(char to_be_checked,pointer head,pointer dummy)
{
	if (to_be_checked != 'P' && to_be_checked != 'D' && to_be_checked != 'C' && to_be_checked != 'Q' && to_be_checked != 'E' &&  to_be_checked != 'S') {
		printf("%s", CHAR_ERROR);
		BufferClean();
		SwitchCase(head,dummy);
	}
}
int PopQueue(pointer dummy) {
	int to_be_poped=0;
	pointer last_el=NULL;
	pointer follower_last_el = NULL;
	if (IsStackEmpty(dummy) == 0)
		return -1;
	last_el=FindLastElement(dummy);
	follower_last_el = FollowerOfLastElement(dummy, last_el);
	to_be_poped = last_el->element;
	FirstElementInOut(last_el, follower_last_el);
	return to_be_poped;
}

pointer FindLastElement(pointer dummy) {
	while (dummy->next != NULL)
		dummy = dummy->next;
	return dummy;
}
pointer FollowerOfLastElement(pointer dummy,pointer element) {
	IsStackEmpty(dummy);
	while (dummy->next != element)
		dummy = dummy->next;
	return dummy;
}
void FirstElementInOut(pointer last_el, pointer follower_last_el) {
	follower_last_el->next = last_el->next;
	free(last_el);
}
