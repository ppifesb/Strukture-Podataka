//Mislav Kovac
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Element {
	int number;
	struct Element* next;
}_Element;

int FromFileToList(_Element*, _Element*, int*, int*, int*);
int FgetsCheck(int);
int FileFunctionsCheck(int);
int PrintfAndScanfCheck(int, int);
int FunctionCallFuncitons(_Element*, char*, int*, int*);
int Print(_Element*);
int EraseElement(_Element*, _Element*);
int* BufferCorrector(char*, int*, int*);
int* BufferSort(int*, int);
int* Switch(int*, int*);
int* UnionBufferMaker(int*, int*, int, int, int*);
_Element* Union(_Element*, int*, int);
_Element* MoveToEnd(_Element*);
_Element* Cut(_Element*, _Element*, int*, int*);
_Element* ListCheck(int);
_Element* BufferToList(_Element*, int*, int);
_Element* Allocation(_Element*);
_Element* Linker(_Element*, _Element*);
_Element* MultipleNumbersCorrector(_Element*, int*);

int main()
{
	_Element* firstHead = NULL;
	_Element* secondHead = NULL;
	_Element* cutHead = NULL;
	_Element* unionHead = NULL;
	int numberOfFirstElements = 0;
	int numberOfSecondElements = 0;
	int numberOfUnionElements = 0;
	int unionBuffer[1024] = { 0 };
	int printfCheck = 0;

	firstHead = Allocation(firstHead);
	secondHead = Allocation(secondHead);
	unionHead = Allocation(unionHead);

	firstHead->next = NULL;
	secondHead->next = NULL;
	unionHead->next = NULL;

	FromFileToList(firstHead, secondHead, &numberOfFirstElements, &numberOfSecondElements, unionBuffer);
	printfCheck = printf("***Prva lista***\n");
	if (PrintfAndScanfCheck(printfCheck, 1))
		return -5;
	if(Print(firstHead))
		return -2;
	printfCheck = printf("\n\n***Druga lista***\n");
	if (PrintfAndScanfCheck(printfCheck, 1))
		return -5;
	if (Print(secondHead))
		return -2;

	if (MultipleNumbersCorrector(firstHead, &numberOfFirstElements) == NULL)
		return -1;
	printfCheck = printf("\n\n***Prva lista (Bez duplih brojeva)***\n");
	if (PrintfAndScanfCheck(printfCheck, 1))
		return -5;
	if (Print(firstHead))
		return -2;
	if (MultipleNumbersCorrector(secondHead, &numberOfSecondElements) == NULL)
		return -1;
	printfCheck = printf("\n\n***Druga lista (Bez duplih brojeva)***\n");
	if (PrintfAndScanfCheck(printfCheck, 1))
		return -5;
	if (Print(secondHead))
		return -2;

	cutHead = Cut(firstHead, secondHead, &numberOfFirstElements, &numberOfSecondElements);
	if (cutHead == -1)
		return -3;
	printfCheck = printf("\n\n***Presjek***\n");
	if (PrintfAndScanfCheck(printfCheck, 1))
		return -5;
	if (Print(cutHead))
		return -2;

	numberOfUnionElements = numberOfFirstElements + numberOfSecondElements;
	unionHead = Union(unionHead, unionBuffer, numberOfUnionElements);
	if (unionHead == -1)
		return -4;
	if (MultipleNumbersCorrector(unionHead, &numberOfUnionElements) == 0)
		return -1;
	printfCheck = printf("\n\n***Unija***\n");
	if (PrintfAndScanfCheck(printfCheck, 1))
		return -5;
	if (Print(unionHead))
		return -2;

	return 0;
}
int FromFileToList(_Element* firstHead, _Element* secondHead, int* numberOfFirstElements, int* numberOfSecondElements, int* unionBuffer)//Return: -1 -> fopen error; -4 -> fclose error
{
	FILE* numbersFile = fopen("numbers.txt", "r");
	int check = 0;
	int numbersArray[1024] = { 0 };
	int unionCheck = 0;
	char buffer[1024] = { 0 };

	if (FileFunctionsCheck(numbersFile) != 0)
		return -1;

	if (!(fgets(buffer, 1024, numbersFile))) {
		FgetsCheck(NULL);
		return -2;
	}

	if (!(fgets(buffer, 1024, numbersFile))) {
		FgetsCheck(NULL);
		return -2;
	}
	if ((FunctionCallFuncitons(firstHead, buffer, numbersArray, numberOfFirstElements)) == -1)
		return -3;
	UnionBufferMaker(unionBuffer, numbersArray, *numberOfFirstElements, 0, &unionCheck);

	memset(numbersArray, 0, sizeof(numbersArray));
	if (!(fgets(buffer, 1024, numbersFile))) {
		FgetsCheck(NULL);
		return -2;
	}
	if ((FunctionCallFuncitons(secondHead, buffer, numbersArray, numberOfSecondElements)) == -1)
		return -3;
	UnionBufferMaker(unionBuffer, numbersArray, *numberOfFirstElements, *numberOfSecondElements, &unionCheck);

	check = fclose(numbersFile);
	if (FileFunctionsCheck(check) != 0)
		return -4;

	return 0;
}
int FgetsCheck(int check)//Return: -1 -> fgets error; 0 -> All good;
{						 //Arguments: NULL -> fgets error;
	int printfCheck = 0;
	if (check == NULL) {
		printfCheck = printf("\n***Greska u fgets!***\n");
		if (PrintfAndScanfCheck(check, 1))
			return -1;
	}

	return 0;
}
_Element* BufferToList(_Element* head, int* buffer, int numberOfElements)// Return: -1 -> Allocation error; 0 -> All good;
{
	_Element* newElement = NULL;
	_Element* previousElement = NULL;
	int i = 0;

	previousElement = head;

	for (i = 0; i < numberOfElements; i++) {
		newElement = Allocation(newElement);
		if (newElement == NULL)
			return -1;
		Linker(previousElement, newElement);
		previousElement = previousElement->next;
		newElement->number = buffer[i];
	}

	return 0;
}
int FileFunctionsCheck(int check) //Return: -1 -> fopen error; -2 -> fclose error; 0 -> All good;
{								  //Argument: NULL -> fopen error; EOF -> fclose error;
	int printfCheck = 0;

	if (check == NULL && check != 0) {
		printfCheck = printf("\n***Greska u fopen!!***\n");
		if (PrintfAndScanfCheck(check, 1))
			return -1;
	}

	if (check == EOF) {
		printfCheck = printf("\n***Greska u fclose!***\n");
		if (PrintfAndScanfCheck(check, 1))
			return -1;
	}

	return 0;
}
int PrintfAndScanfCheck(int printfCheck, int scanfCheck)// Return: -1 -> printf error; -2 -> scanf error; 0 -> All good;
{
	if (printfCheck < 0) {
		printf("\n***Greska u printf!***\n");
		return -1;
	}
	if (scanfCheck == EOF || scanfCheck == 0) {
		printf("\n***Greska u scanf!***\n");
		return -2;
	}

	return 0;
}
int* BufferSort(int* buffer, int numberOfElements)
{
	int i = 0;
	int j = 0;
	int temp;

	for (i = 0; i < numberOfElements - 1; i++)
		for (j = i + 1; j < numberOfElements; j++)
			if (buffer[i] < buffer[j])
				Switch(&buffer[i], &buffer[j]);

	return buffer;
}
int* Switch(int* firstNumber, int* secondNumber)
{
	char temp = 0;

	temp = *firstNumber;
	*firstNumber = *secondNumber;
	*secondNumber = temp;
}
int* UnionBufferMaker(int* unionBuffer, int* numbersArray, int numberOfFirstElements, int numberOfSecondElements, int* unionCheck)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = *unionCheck; i < numberOfFirstElements + numberOfSecondElements; i++) {
		unionBuffer[i] = numbersArray[k];
		k++;
		j++;
	}
	*unionCheck = j;

	return unionBuffer;
}
_Element* Union(_Element* unionHead, int* unionBuffer, int numberOfUnionBufferElements)
{
	BufferSort(unionBuffer, numberOfUnionBufferElements);
	if ((BufferToList(unionHead, unionBuffer, numberOfUnionBufferElements)) == -1)
		return -1;

	return unionHead;
}
int FunctionCallFuncitons(_Element* head, char* buffer, int* numbersArray, int* numberBufferElements)
{
	BufferCorrector(buffer, numbersArray, numberBufferElements);
	BufferSort(numbersArray, *numberBufferElements);
	if ((BufferToList(head, numbersArray, *numberBufferElements)) == -1)
		return -1;

	return 0;
}
int* BufferCorrector(char* buffer, int* numbers, int* numberOfNumbers)
{
	int i = 0;

	for (i = 0; i < strlen(buffer); i++)
		if (buffer[i] > 47 && buffer[i] < 58) {
			numbers[*numberOfNumbers] = buffer[i] - 48;
			(*numberOfNumbers)++;
		}
	return numbers;
}
int Print(_Element* head) //-1 -> printf error; -2 -> List is empty; 0 -> All good
{
	_Element* pointToElement = head->next;
	int check = 0;

	if (head->next == NULL) {
		ListCheck(-1);
		return 1;
	}

	while (pointToElement != NULL) {
		check = printf("%d ", pointToElement->number);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		pointToElement = pointToElement->next;
	}
	check = printf("\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;

	return 0;
}
_Element* Cut(_Element* firstHead, _Element* secondHead, int* firstNumberOfElements, int* secondNumberOfElements)// Return: -1 -> Allocation error 
{
	_Element* pointToFirstList = NULL;
	_Element* pointToSecondList = NULL;
	_Element* pointToThirdList = NULL;
	_Element* thirdHead = NULL;
	_Element* newElement = NULL;
	int i = 0;
	int j = 0;

	thirdHead = Allocation(thirdHead);
	if (thirdHead == NULL)
		return -1;
	thirdHead->next = NULL;

	pointToFirstList = firstHead->next;
	pointToSecondList = secondHead->next;
	pointToThirdList = thirdHead;

	for (i = 0; i < *firstNumberOfElements; i++) {
		for (j = 0; j < *secondNumberOfElements; j++) {
			if ((pointToFirstList->number) == (pointToSecondList->number)) {
				newElement = Allocation(newElement);
				Linker(pointToThirdList, newElement);
				pointToThirdList = pointToThirdList->next;
				pointToThirdList->number = pointToFirstList->number;
			}
			pointToSecondList = pointToSecondList->next;
		}
		pointToFirstList = pointToFirstList->next;
		pointToSecondList = secondHead->next;
	}

	return thirdHead;
}
_Element* ListCheck(int check)//Return: NULL -> List error;
{							  //Arguments: -1 -> Empty list; -2 -> Element not found
	if (check == -1) {
		printf("\n***Lista je prazna!!***\n");
		return NULL;
	}

	if (check == -2) {
		printf("\n***Element nije pronaden!!***\n");
		return NULL;
	}
}
_Element* Allocation(_Element* element)//NULL -> Allocation error; Element -> All good;
{
	int check = 0;

	element = (_Element*)malloc(sizeof(_Element));
	if (element == NULL) {
		check = printf("***Greska u alociranju memorije!***");
		PrintfAndScanfCheck(check, 1);
		return NULL;
	}

	return element;
}
_Element* Linker(_Element* previousElement, _Element* nextElement)
{
	nextElement->next = previousElement->next;
	previousElement->next = nextElement;

	return nextElement;
}
_Element* MultipleNumbersCorrector(_Element* head, int* numberOfElements)// Return: -1 -> Erasing element failed; 
{
	_Element* previousElement = NULL;
	_Element* nextElement = NULL;

	previousElement = head->next;
	nextElement = head->next->next;

	while (previousElement->next != NULL && nextElement != NULL) {
		if (previousElement->number == nextElement->number) {
			if (EraseElement(nextElement, head))
				return NULL;
			(*numberOfElements)--;
			nextElement = previousElement->next;
		}
		if (previousElement->number != nextElement->number) {
			previousElement = previousElement->next;
			nextElement = nextElement->next;
		}
	}

	return head;
}
_Element* MoveToEnd(_Element* pointToElement) //Moving pointer to the end of the list;
{
	while (pointToElement->next != NULL)
		pointToElement = pointToElement->next;

	return pointToElement;
}
int EraseElement(_Element* element, _Element* head) // Return: -1 -> printf error; 1 -> Empty list; 2 -> No element; 0 -> All good;
{
	_Element* pointToElement = head;
	int check = 0;

	if (pointToElement == NULL) {
		ListCheck(-1);
		return 1;
	}
	while (pointToElement != NULL && pointToElement->next != element)
		pointToElement = pointToElement->next;

	if (pointToElement == NULL) {
		ListCheck(-2);
		return 2;
	}

	pointToElement->next = element->next;
	free(element);

	return 0;
}
