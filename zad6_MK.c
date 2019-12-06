//Mislav Kovac
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define CHOICESTACK 5
#define LOWER 10
#define UPPER 100

typedef struct Element {
	int number;
	struct Element* next;
}_Element;

/****************Stack/Queue functions*****************/
int Push(_Element*);
int PushLoop(_Element*, char*);
int Print(_Element*, char*);
/*******************Modify functions*******************/
_Element* Linker(_Element*, _Element*);
_Element* Allocation(_Element*);
/*******************Stack functions********************/
int PopLoopStack(_Element*);
_Element* PopStack(_Element*);
/*******************Queue functions********************/
int PopLoopQueue(_Element* head);
_Element* PopQueue(_Element* head);
/*******************Check functions********************/
int PrintfAndScanfCheck(int, int);

int main()//Return: -1 -> Allocation error; 2 -> Empty stack; 1 -> Empty queue; 3 -> Type error(switch case default); -2 -> Print error;
{
	_Element* head = NULL;
	_Element* element = NULL;
	char choiceMeni = 0;
	char choice[CHOICESTACK] = { 0 };
	int printfCheck = 0;
	int scanfCheck = 0;
	srand(time(0));

	head = Allocation(head);
	if (head == NULL)
		return -1;

	while (toupper(choiceMeni) != 'S' && toupper(choiceMeni) != 'R') {
		printfCheck = printf("Zelite li koristiti stog ili red? (S/R)");
		scanfCheck = scanf(" %c", &choiceMeni);
		if (PrintfAndScanfCheck(printfCheck, scanfCheck) == -1)
			return -2;
	}

	switch (toupper(choiceMeni)) {
/**********************************************STACK************************************************/
	case 'S':
		printfCheck = printf("\n**************STACK*************\n");
		if (PrintfAndScanfCheck(printfCheck, 1) == -1)
			return -2;
		do {
			printfCheck = printf("Izaberite stavljanje na stog(Push) ili skidanje sa stoga(Pop); Exit za izlaz: (Push/Pop)");
			scanfCheck = scanf(" %s", choice);
			if (PrintfAndScanfCheck(printfCheck, scanfCheck) == -1)
				return -2;
			if (strcmp(choice, "Pop") == 0) {
				if (head->next == NULL) {
					printfCheck = printf("\n***Stog je prazan***\n");
					if (PrintfAndScanfCheck(printfCheck, 1) == -1)
						return -2;
					return 2;
				}
				if (PopLoopStack(head) == 1)
					return 2;
			}
			if (strcmp(choice, "Push") == 0) {
				if (PushLoop(head, "stog") < 0)
					return -1;
			}
		} while ((strcmp(choice, "Pop") == 0) || (strcmp(choice, "Push") == 0) || (strcmp(choice, "Exit")));
		if (Print(head, "stoga") == -1)
			return -2;
		break;
/**********************************************QUEUE************************************************/
	case 'R':
		printfCheck = printf("\n**************QUEUE*************\n");
		if (PrintfAndScanfCheck(printfCheck, 1) == -1)
			return -2;
		do {
			printfCheck = printf("Izaberite stavljanje na red(Push) ili skidanje sa reda(Pop); Exit za izlaz: (Push/Pop)");
			scanfCheck = scanf(" %s", choice);
			if (PrintfAndScanfCheck(printfCheck, scanfCheck) == -1)
				return -2;
			if (strcmp(choice, "Pop") == 0) {
				if (head->next == NULL) {
					printfCheck = printf("\n***Red je prazan***\n");
					if (PrintfAndScanfCheck(printfCheck, 1) == -1)
						return -2;
					return 1;
				}
				if (PopLoopQueue(head) == 1)
					return 1;
			}
			if (strcmp(choice, "Push") == 0) {
				if (PushLoop(head, "red") < 0)
					return -1;
			}
		} while ((strcmp(choice, "Pop") == 0) || (strcmp(choice, "Push") == 0) || (strcmp(choice, "Exit")));
		if (Print(head, "reda") == -1)
			return -2;
		break;
	default:
		printfCheck = printf("\n***Greska u odabiru***\n");
		if (PrintfAndScanfCheck(printfCheck, 1) == -1)
			return -2;
		return 3;
	}

	return 0;
}
/****************Stack/Queue functions*****************/
int Push(_Element* head) //Return: -1 -> Allocation error; element->number -> All good
{
	_Element* element = NULL;

	element = Allocation(element);
	if (element == NULL)
		return -1;
	element->number = (rand() % (LOWER - UPPER + 1) + LOWER);
	Linker(head, element);
	
	return element->number;
}
int PushLoop(_Element* head, char* buffer)//Return: -1 -> Allocation error; -2 -> Printf/Scanf error; 0 -> All good
{
	char choice = 0;
	int check = 0;
	int printfCheck = 0;
	int scanfCheck = 0;

	do {
		check = Push(head);
		if (check == -1)
			return -1;
		printfCheck = printf("\n***Element (%d) je stavljen na %s!***\nZelite li staviti jos jedan element? (D/N)", check, buffer);
		scanfCheck = scanf(" %c", &choice);
		if (PrintfAndScanfCheck(printfCheck, scanfCheck) == -1)
			return -2;
	} while (toupper(choice) == 'D');

	return 0;
}
int Print(_Element* head, char* buffer)//Return: -1 -> Printf/Scanf error; 0 -> All good; 
{
	_Element* pointToElement = head->next;
	int printfCheck = 0;

	printfCheck = printf("\n***Ispisivanje %s***\n", buffer);
	if (PrintfAndScanfCheck(printfCheck, 1) == -1)
		return -1;
	while (pointToElement != NULL) {
		printfCheck = printf("%2d\n", pointToElement->number);
		if (PrintfAndScanfCheck(printfCheck, 1) == -1)
			return -1;
		pointToElement = pointToElement->next;
	}

	return 0;
}
/*******************Modify functions*******************/
_Element* Linker(_Element* previousElement, _Element* nextElement)
{
	nextElement->next = previousElement->next;
	previousElement->next = nextElement;

	return nextElement;
}
_Element* Allocation(_Element* element)//NULL -> Allocation error; Element -> All good;
{
	element = (_Element*)malloc(sizeof(_Element));
	if (element == NULL) {
		printf("***Greska u alociranju memorije!***");
		return NULL;
	}
	element->next = NULL;

	return element;
}
/*******************Stack functions********************/
int PopLoopStack(_Element* head)//Return: 1 -> Empty stog; -1 -> Printf/Scanf error; 0 -> All good
{
	_Element* element = NULL;
	char choice = 0;
	int printfCheck = 0;
	int scanfCheck = 0;

	do {
		element = PopStack(head);
		if (element == NULL) {
			printfCheck = printf("\n***Stog je prazan***\n");
			if (PrintfAndScanfCheck(printfCheck, 1) == -1)
				return -1;
			return 1;
		}
		printfCheck = printf("\nBroj skinut sa stoga: %d\nZelite li skinuti jos jedan element? (D/N) ", element->number);
		scanfCheck = scanf(" %c", &choice);
		if (PrintfAndScanfCheck(printfCheck, scanfCheck) == -1)
			return -1;
		free(element);
	} while (toupper(choice) == 'D');

	return 0;
}
_Element* PopStack(_Element* head)
{
	_Element* element = NULL;
	_Element* returnElement = NULL;

	element = head->next;
	if (head->next != NULL)
		head->next = element->next;

	return element;
}
/*******************Queue functions********************/
int PopLoopQueue(_Element* head)//Return: 1 -> Empty queue; -1 -> Printf/Scanf error; 0 -> All good
{
	_Element* element = NULL;
	char choice = 0;
	int printfCheck = 0;
	int scanfCheck = 0;

	do {
		element = PopQueue(head);
		if (element == NULL) {
			printfCheck = printf("\n***Red je prazan***\n");
			if (PrintfAndScanfCheck(printfCheck, 1) == -1)
				return -1;
			return 1;
		}
		printfCheck = printf("\nBroj skinut sa reda: %d\nZelite li skinuti jos jedan element? (D/N) ", element->number);
		scanfCheck = scanf(" %c", &choice);
		if (PrintfAndScanfCheck(printfCheck, scanfCheck) == -1)
			return -1;
		free(element);
	} while (toupper(choice) == 'D');

	return 0;
}
_Element* PopQueue(_Element* head)
{
	_Element* element = head->next;
	_Element* returnElement = NULL;

	while (element->next->next != NULL)
		element = element->next;

	returnElement = element->next;
	element->next = NULL;

	return returnElement;
}
/*******************Check functions********************/
int PrintfAndScanfCheck(int printfCheck, int scanfCheck)
{
	if (printfCheck < 0) {
		printf("\n***Greska u printf!***\n");
		return -1;
	}
	if (scanfCheck == EOF || scanfCheck == 0) {
		printf("\n***Greska u scanf!***\n");
		return -1;
	}

	return 0;
}
