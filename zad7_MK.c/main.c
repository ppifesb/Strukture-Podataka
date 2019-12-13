#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stackDeclaration.h"
#include "checkFunctionDeclarations.h"
#include "stackModifyFunctionDeclaration.h"
#include "operationFunctionDeclaration.h"
#include "fileFunctionDeclarations.h"
#define FILE_ERROR_OPEN "\n\n***Error in FileCheck function (fopen)***\n\n"
#define FILE_ERROR_CLOSE "\n\n***Error in FileCheck function (fclose)***\n\n"
#define ALLOCATION_ERROR "\n\n***Error in Allocation function***\n\n"
#define OUTPUT_ERROR "\n\n***Error in printf function***\n\n"
#define INPUT_ERROR "\n\n***Error in scanf function***\n\n"
#define MAIN_ERROR "\n\n***Error in main (ReadOneChar)\n\n***"
#define CHAR_TO_INT_ERROR "\n\n***Error in CharToInt function***\n\n"
#define PUSH_ERROR "\n\n***Error in Push function***\n\n"
#define HEAD_ERROR "\n\n***Error in Pop function***\n\n"
#define SSCANF_ERROR "\n\n***Error in ReadNumberFromString function***\n\n"

int main()
{
	_Stack* head = NULL;
	char bufferString[1024] = { 0 };

	head = Allocation(head);

	head->next = NULL;

	NumberFromStringToStack(head, FromFileToString(bufferString));

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
int FromFileToString(char* bufferString)//Return: -1 -> fopen error; -2 -> fclose error; bufferString -> All good;
{
	FILE* postfixFile = fopen("postfix.txt", "r");
	int check = 0;
	int i = 0;

	if (postfixFile == NULL) {
		FileCheck(-1);
		return -1;
	}

	fgets(bufferString, 1024, postfixFile);

	check = fclose(postfixFile);
	if (check == EOF) {
		FileCheck(-2);
		return -2;
	}

	return bufferString;
}
/******************Stack operations********************/
int StoreResultInStack(_Stack* head, int number, int oprationNumber)//Return: -1 -> Push error (Allocation); -2 -> CharToInt error; 0 -> All good; 
{
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
		if (Push(head, number) == -1)
			return -1;
	}

	return 0;
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
int OperationCheck(char operation)//Returns number(value) of operation
{

	if ((int)operation == 43)// +
		return 1;
	else if ((int)operation == 42)// *
		return 2;
	else if ((int)operation == 45)// -
		return 3;
	else if ((int)operation == 32)//SPACE
		return 4;
	else
		return 5;

}
int OptionChooser(char* stringBuffer, int* numberOfBytesReadedInTotal)
{
	int number = 0;
	int numberOfBytesReaded = 0;

	stringBuffer += *numberOfBytesReadedInTotal;
	if (strlen(stringBuffer) == 0)
		return -1;
	sscanf(stringBuffer, "%d %n", &number, &numberOfBytesReaded);

	if (numberOfBytesReaded != 0)
		return 1;
	if (numberOfBytesReaded == 0)
		return 2;

	return 0;
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
/*************Number opration functions****************/
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
int NumberFromStringToStack(_Stack* head, char* stringBuffer)// Return: -1 -> StoreResultInStack error (Push); -2 -> ReadNumberFromString error; 0 -> All good;
{
	int check = 0;
	int number = 0;
	int operation = 0;
	int numberOfBytesReaded = 0;

	do {
		check = OptionChooser(stringBuffer, &numberOfBytesReaded);
		if (check == 1) {
			number = ReadNumberFromString(stringBuffer, 1, &numberOfBytesReaded);
			if (StoreResultInStack(head, number, 5) == -1)
				return -1;
		}
		if (check == 2) {
			operation = ReadNumberFromString(stringBuffer, 2, &numberOfBytesReaded);
			if (StoreResultInStack(head, number, OperationCheck(operation)) == -1)
				return -1;
		}
	}while (check != -1);

	return 0;
}
int ReadNumberFromString(char* stringBuffer, int option, int* numberOfBytesReadedInTotal)// Return: -1 -> sscanf error; -2 -> printf error; number/operation -> All good
{
	char operation = 0;
	int number = 0;
	int numberOfBytesReaded = 0;

	switch (option) {
	case 1:
		stringBuffer += *numberOfBytesReadedInTotal;
		if (sscanf(stringBuffer, "%d %n", &number, &numberOfBytesReaded) == EOF) break;
		*numberOfBytesReadedInTotal += numberOfBytesReaded;
		return number;
	case 2:
		stringBuffer += *numberOfBytesReadedInTotal;
		if (sscanf(stringBuffer, "%c %n", &operation, &numberOfBytesReaded) == EOF) break;
		*numberOfBytesReadedInTotal += numberOfBytesReaded;
		return (int)operation;
	}
	
	if (PrintfAndScanfCheck(printf("%s", SSCANF_ERROR), 1))
		return -2;

	return -1;
}
