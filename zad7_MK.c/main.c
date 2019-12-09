#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackDeclaration.h"
#include "checkFunctionDeclarations.h"
#include "stackModifyFunctionDeclaration.h"
#include "operationFunctionDeclaration.h"
#define FILE_ERROR_OPEN "\n\n***Error in FileCheck function (fopen)***\n\n"
#define FILE_ERROR_CLOSE "\n\n***Error in FileCheck function (fclose)***\n\n"
#define ALLOCATION_ERROR "\n\n***Error in Allocation function***\n\n"
#define OUTPUT_ERROR "\n\n***Error in printf function***\n\n"
#define INPUT_ERROR "\n\n***Error in scanf function***\n\n"
#define MAIN_ERROR "\n\n***Error in main (ReadOneChar)\n\n***"
#define CHAR_TO_INT_ERROR "\n\n***Error in CharToInt function***\n\n"
#define PUSH_ERROR "\n\n***Error in Push function***\n\n"
#define HEAD_ERROR "\n\n***Error in Pop function***\n\n"

int main()
{
	_Stack* head = NULL;
	_Stack* additionHead = NULL;

	head = Allocation(head);
	additionHead = Allocation(additionHead);

	head->next = NULL;
	additionHead->next = NULL;
	
	if (ReadOneChar(head, additionHead) != 0)
		return -1;

	if (PrintfAndScanfCheck(printf("Rezultat je: %d", head->next->element), 1))
		return -2;

	return 0;
}
/****************Stack/Queue functions*****************/
int Pop(_Stack* head)//Return: -1 -> Empty stack; -2 -> printf error; intBuffer -> All good;
{
	_Stack* element = NULL;
	int intBuffer = 0;

	if (head->next == NULL) {
		if(PrintfAndScanfCheck(printf("%s", HEAD_ERROR), 1))
			return -2;
		return -1;
	}

	element = head->next;
	intBuffer = element->element;

	if (head->next != NULL)
		head->next = element->next;
	free(element);

	return intBuffer;
}
int Push(_Stack* head, int buffer) //Return: -1 -> Allocation error; -2 -> printf error; element->number -> All good
{
	_Stack* element = NULL;

	element = Allocation(element);

	if (element == NULL || buffer == -1) {
		if (PrintfAndScanfCheck(printf("%s", PUSH_ERROR), 1))
			return -2;
		return -1;
	}

	element->element = buffer;
	Linker(head, element);

	return element->element;
}
/*******************File functions*********************/
int FileCheck(int check)//Arguments: -1 -> fopen check; -2 -> fclose check; -1 -> fopen error; -2 -> fclose error
{
	if (check == -1) {
		PrintfAndScanfCheck(printf("%s", FILE_ERROR_OPEN), 0);
		return -1;
	}
	else if (check == -2) {
		PrintfAndScanfCheck(printf("%s", FILE_ERROR_CLOSE), 0);
		return -2;
	}
}
int ReadOneChar(_Stack* head)//Return: -1 -> fopen error; -2 -> fclose error; -3 -> StoreResultInStack error;
{
	FILE* postfixFile = fopen("postfix.txt", "r");
	char buffer = 0;
	int check = 0;

	if (postfixFile == NULL) {
		FileCheck(-1);
		return -1;
	}

	do {
		buffer = fgetc(postfixFile);
		if (buffer == -1) break;
		if (StoreResultInStack(head, CharToInt(buffer), BufferCheck(head, buffer)) != 0)
			return -3;
	} while (buffer != EOF);

	check = fclose(postfixFile);
	if (check == EOF) {
		FileCheck(-2);
		return -2;
	}

	return 0;
}
/******************Stack operations********************/
int Sum(_Stack* head) //Return -1 -> Pop function error; Sum -> All good
{
	int firstNumber = Pop(head);
	int secondNumber = Pop(head);

	if (firstNumber == -1 || secondNumber == -1)
		return -1;

	return firstNumber + secondNumber;
}
int Multiplication(_Stack* head) //Return -1 -> Pop function error; Multiplication -> All good;
{
	int firstNumber = Pop(head);
	int secondNumber = Pop(head);

	if (firstNumber == -1 || secondNumber == -1)
		return -1;

	return firstNumber * secondNumber;
}
int Subtraction(_Stack* head)//Return -1 -> Pop function error; Substraction -> All good
{
	int firstNumber = Pop(head);
	int secondNumber = Pop(head);

	if (firstNumber == -1 || secondNumber == -1)
		return -1;

	return firstNumber - secondNumber;
}
int StoreResultInStack(_Stack* head, int buffer, int oprationNumber)//Return: -1 -> Push error (Allocation); -2 -> CharToInt error; 0 -> All good; 
{
	if (buffer == -1)
		return -2;

	if (oprationNumber == 1) {
		if (Push(head, Sum(head)) == -1)
			return -1;
	}
	else if (oprationNumber == 2) {
		if (Push(head, Multiplication(head)) == -1)
			return -1;
	}
	else if (oprationNumber == 3) {
		if (Push(head, Subtraction(head)) == -1)
			return -1;
	}
	else if (oprationNumber == 5) {
		if (Push(head, buffer) == -1)
			return -1;
	}

	return 0;
}
int CharToInt(char buffer)//Return: -1 -> strtol error; intBuffer -> All good;
{
	int intBuffer = 0;

	intBuffer = strtol(&buffer, NULL, 10);
	if (intBuffer == 0 && buffer != 32 && buffer != 43 && buffer != 42 && buffer != 45) {		
		if (PrintfAndScanfCheck(printf("%s", CHAR_TO_INT_ERROR), 1))
			return -2;
		return -1;
	}

	return intBuffer;
}
/******************Check functions*********************/
int PrintfAndScanfCheck(int printfCheck, int scanfCheck)
{
	if (printfCheck < 0) {
		if (PrintfAndScanfCheck(printf("%s", OUTPUT_ERROR), 1))
			return -2;
		return -1;
	}
	if (scanfCheck == EOF || scanfCheck == 0) {
		if (PrintfAndScanfCheck(printf("%s", INPUT_ERROR), 1))
			return -2;
		return -1;
	}

	return 0;
}
int BufferCheck(_Stack* head, char buffer)//Returns number(value) of operation
{

	if ((int)buffer == 43)// +
		return 1;
	else if ((int)buffer == 42)// *
		return 2;
	else if ((int)buffer == 45)// -
		return 3;
	else if ((int)buffer == 32)//SPACE
		return 4;
	else
		return 5;

}
/******************Memory functions********************/
_Stack* Allocation(_Stack* Element)//Argument: Pointer to structure
{								   //Return: NULL -> Allocation error; Element -> All good
	Element = (_Stack*)malloc(sizeof(_Stack));
	if (Element == NULL) {
		PrintfAndScanfCheck(printf("%s", ALLOCATION_ERROR), 1);
		return NULL;
	}

	return Element;
}
_Stack* Linker(_Stack* previousElement, _Stack* nextElement)
{
	nextElement->next = previousElement->next;
	previousElement->next = nextElement;

	return nextElement;
}
