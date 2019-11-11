//Mislav Kovac
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct polinom {
	int coefficient;
	int exponent;
	struct polinom* next;
}_polinom;

int PrintfAndScanfCheck(int, int);
int FgetsCheck(int);
int FileFunctionsCheck(int);
int ReadRow(int*);
int BufferCheck(char*);
int FprintfAndFscanfCheck(int, int);
int Print(_polinom*);
int Sort(_polinom*);
_polinom* ListCheck(int);
_polinom* Switch(_polinom*, _polinom*, _polinom*);
_polinom* Linker(_polinom*, _polinom*);
_polinom* PolinomsToListEntry(_polinom*, int);
_polinom* Allocation(_polinom*);
_polinom* MoveToEnd(_polinom*);
_polinom* ThirdListMaker(_polinom*, _polinom*);
_polinom* Multiplicator(_polinom*, int*, int*);
_polinom* Addition(_polinom*);

int main() // Return: -1 -> printf error; -2 -> Allocation error; -3 -> ReadRow error; -4 -> PolinomsToListEntry error; -5 -> Print error; -6 -> ThirdListMaker; -7 -> Multiplicator error; -8 -> Sort error; -9 -> Addition error
 {
	_polinom* firstHead = NULL;
	_polinom* secondHead = NULL;
	_polinom* thirdHead = NULL;
	_polinom* finalHead = NULL;
	int check = 0;
	int firstCounter = 0;
	int secondCounter = 0;
	char* buffer[128] = { 0 };

	if (!(firstHead = Allocation(firstHead)))
		return -2;
	if (!(secondHead = Allocation(secondHead)))
		return -2;
	firstHead->next = NULL;
	secondHead->next = NULL;

	if (check = ReadRow(&firstCounter) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -3;
	}
	if (check = ReadRow(&secondCounter) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -3;
	}
	if (check = PolinomsToListEntry(firstHead, firstCounter) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -4;
	}
	if (check = PolinomsToListEntry(secondHead, secondCounter) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -4;
	}

	check = printf("\n\n***Prvi polinom***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;

	if (check = Print(firstHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}
	check = printf("\n\n***Drugi polinom***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	Print(secondHead);
	if (check = Print(secondHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}

	check = printf("\n\n***Treci polinom***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	thirdHead = ThirdListMaker(firstHead, secondHead);
	if (thirdHead < 0) {
		check = printf("\n***ERROR: %d***\n", (int)thirdHead);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -6;
	}
	if (check = Print(thirdHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}

	check = printf("\n\n***Umnozak polinoma***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	finalHead = Multiplicator(thirdHead, &firstCounter, &secondCounter);
	if (finalHead < 0) {
		check = printf("\n***ERROR: %d***\n", (int)finalHead);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -7;
	}
	if (check = Print(finalHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}

	check = printf("\n\n***Sortirani umnozak polinoma***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	if (check = Sort(finalHead) != 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -8;
	}
	if (check = Print(finalHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}

	check = printf("\n\n***Sredeni umnozak polinoma***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	finalHead = Addition(finalHead);
	if (finalHead == 1 || finalHead == -1) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -9;
	}
	
	if (check = Print(finalHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}

	check = printf("\n\n***Zbroj polinoma***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	if (check = Sort(finalHead) != 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -8;
	}
	if (check = Print(thirdHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
	}

	check = printf("\n\n***Sredeni zbroj polinoma***\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;
	thirdHead = Addition(thirdHead);
	if (thirdHead == 1 || thirdHead == -1) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -9;
	}
	if (check = Print(thirdHead) < 0) {
		check = printf("\n***ERROR: %d***\n", check);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -5;
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
int FileFunctionsCheck(int check) //Return: -1 -> fopen error; -2 -> fclose error; 0 -> All good;
{								  //Argument: NULL -> fopen error; EOF -> fclose error;
	int printfCheck = 0;

	if (check == NULL) {
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
int ReadRow(int *rowCounter)// Return: -1 -> fopen error; -2 -> fgets error; -3 -> fclose error; 0 -> All good;
{
	FILE* polinomFile = NULL;
	char buffer[1024] = { 0 };
	int check = 0;
	static int counter = 0;

	polinomFile = fopen("polinoms.txt", "r");
	if (!polinomFile) {
		FileFunctionsCheck(NULL);
		return -1;
	}

	if (!(fgets(buffer, 1024, polinomFile))) {
		FgetsCheck(NULL);
		return -2;
	}

	do {
		if (counter == 1)
			while (BufferCheck(buffer) == 0)
				if(!(fgets(buffer, 1024, polinomFile))){
					FgetsCheck(NULL);
					return -2;
				}
		if (!(fgets(buffer, 1024, polinomFile))) {
			FgetsCheck(NULL);
			return -2;
		}
		if (BufferCheck(buffer) == 1) {
			counter++;
			break;
		}
		counter = 0;
		(*rowCounter)++;
	} while (!feof(polinomFile));

	check = fclose(polinomFile);
	if (check == EOF) {
		FileFunctionsCheck(EOF);
		return -3;
	}

	return 0;
}
int BufferCheck(char* buffer) // Return: 1 -> buffer == '\n'; 0 -> buffer != '\n'
{
	if (strcmp(buffer, "\n") == 0)
		return 1;

	return 0;
}
int Print(_polinom* head) //-1 -> printf error; -2 -> List is empty; 0 -> All good
{
	_polinom* pointToElement = head->next;
	int check = 0;

	if (head->next == NULL) {
		ListCheck(-1);
		return 1;
	}

	check = printf("f(x) =");
	if (PrintfAndScanfCheck(check, 1))
		return -1;

	while (pointToElement != NULL) {
		check = printf(" %dx^%d ", pointToElement->coefficient, pointToElement->exponent);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		if (pointToElement->next != NULL) {
			check = printf("+");
			if (PrintfAndScanfCheck(check, 1))
				return -1;
		}
		pointToElement = pointToElement->next;
	}
	check = printf("\n");
	if (PrintfAndScanfCheck(check, 1))
		return -1;

	return 0;
}
int Sort(_polinom* head) // Return: 1 -> Empty list; 0 -> All good
{
	_polinom* prevElement = head;
	_polinom* element = head->next;
	_polinom* postElement = head->next->next;
	_polinom* end = NULL;

	if (head->next == NULL) {
		ListCheck(-1);
		return 1;
	}

	while (prevElement->next != end) {
		while (postElement != end) {
			if (element->exponent < postElement->exponent) {
				prevElement = Switch(prevElement, element, postElement);
				element = prevElement->next;
				postElement = element->next;
			}
			else {
				postElement = postElement->next;
				element = element->next;
				prevElement = prevElement->next;
			}
		}
		end = element;
		prevElement = head;
		element = head->next;
		postElement = head->next->next;
	}

	return 0;
}
int FprintfAndFscanfCheck(int fprintfCheck, int fscanfCheck)// Return: -1 -> fprintf error; -2 -> fscanf error; 0 -> All good; 
{
	int check = 0;

	if (fprintfCheck < 0) {
		check = printf("\n***Greska u fprintf!***\n");
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -1;
	}
	if (fscanfCheck == EOF) {
		check = printf("\n***Greska u fscanf!***\n");
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		return -2;
	}

	return 0;
}
int EraseElement(_polinom* element, _polinom* head) // Return: -1 -> printf error; 1 -> Empty list; 2 -> No element; 0 -> All good;
{
	_polinom* pointToElement = head;
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
_polinom* PolinomsToListEntry(_polinom* head, int rowCounter) //Return: 1 -> Empty list; -1 -> fopen error; -2 -> fgets error; -3 -> Allocation error; -4 -> fscanf error; 0 -> All good; 
{
	FILE* polinomFile = fopen("polinoms.txt", "r");
	_polinom* pointToElement = NULL;
	_polinom* newElement = NULL;
	char buffer[1024] = { 0 };
	int check = 0;
	static int counter = 0;

	pointToElement = head;
	pointToElement = MoveToEnd(pointToElement);

	polinomFile = fopen("polinoms.txt", "r");
	if (!polinomFile) {
		FileFunctionsCheck(NULL);
		return -1;
	}

	if (!(fgets(buffer, 1024, polinomFile))) {
		FgetsCheck(NULL);
		return -2;
	}

	if (counter == 1)
		while (BufferCheck(buffer) == 0)
			if (!(fgets(buffer, 1024, polinomFile))) {
				FgetsCheck(NULL);
				return -2;
			}

	while (rowCounter > 0) {
		if (counter == 1)
			while (BufferCheck(buffer) == 0)
				if (!(fgets(buffer, 1024, polinomFile))) {
					FgetsCheck(NULL);
					return -2;
				}
		if (rowCounter == 1)
			counter++;
		if (!(newElement = Allocation(newElement)))
			return -3;
		pointToElement = MoveToEnd(pointToElement);
		Linker(pointToElement, newElement);
		check = fscanf(polinomFile, "%d %d", &newElement->exponent, &newElement->coefficient);
		if (check == EOF) {
			FprintfAndFscanfCheck(0, EOF);
			return -4;
		}
		rowCounter--;
	}

	return 0;
}
_polinom* Allocation(_polinom* element)//NULL -> Allocation error; Element -> All good;
{
	int check = 0;

	element = (_polinom*)malloc(sizeof(_polinom));
	if (element == NULL) {
		check = printf("***Greska u alociranju memorije!***");
		PrintfAndScanfCheck(check, 1);
		return NULL;
	}

	return element;
}
_polinom* MoveToEnd(_polinom* pointToElement) //Moving pointer to the end of the list;
{
	while (pointToElement->next != NULL)
		pointToElement = pointToElement->next;

	return pointToElement;
}
_polinom* ThirdListMaker(_polinom* firstHead, _polinom* secondHead)// Return: -1 -> Allocation error; 0 -> All good;
{
	_polinom* thirdHead = NULL;
	_polinom* pointToFirstList = NULL;
	_polinom* pointToSecondList = NULL;
	_polinom* pointToThirdList = NULL;
	
	if (firstHead->next == NULL && secondHead->next == NULL) {
		ListCheck(-1);
		return 1;
	}

	pointToFirstList = firstHead->next;
	pointToSecondList = secondHead->next;

	if (!(thirdHead = Allocation(thirdHead)))
		return -1;

	thirdHead->next = pointToFirstList;
	pointToThirdList = thirdHead->next;

	pointToThirdList = MoveToEnd(pointToThirdList);

	pointToThirdList->next = pointToSecondList;

	return thirdHead;
}
_polinom* Multiplicator(_polinom* head, int* firstCounter, int* secondCounter) // Return: -1 -> Allocation error; 1 -> Empty list; 0 -> All good;
{
	_polinom* firstListCounter = NULL;
	_polinom* secondListCounter = NULL;
	_polinom* finalListPointer = NULL;
	_polinom* newElement = NULL;
	_polinom* finalList = NULL;
	int i = 0;
	int j = 0;
	int k = 0;

	if (head->next == NULL) {
		ListCheck(-1);
		return 1;
	}

	if (!(finalList = Allocation(finalList)))
		return -1;
	finalList->next = NULL;
	finalListPointer = finalList;

	firstListCounter = head->next;
	secondListCounter = head->next;

	for (i = 0; i < (*firstCounter); i++)
		secondListCounter = secondListCounter->next;

	for (i = 0; i < (*firstCounter); i++) {
		for (j = 0; j < (*secondCounter); j++) {
			if (!(newElement = Allocation(newElement)))
				return -1;
			finalListPointer = MoveToEnd(finalListPointer);
			Linker(finalListPointer, newElement);

			newElement->coefficient = firstListCounter->coefficient * secondListCounter->coefficient;
			newElement->exponent = firstListCounter->exponent + secondListCounter->exponent;

			secondListCounter = secondListCounter->next;
		}
		firstListCounter = firstListCounter->next;
		secondListCounter = head->next;
		for (k = 0; k < (*firstCounter); k++)
			secondListCounter = secondListCounter->next;
	}

	return finalList;
}
_polinom* Addition(_polinom* head) // Return: 1 -> Empty list; -1 -> Erasing element unsuccessful; 0 -> All good; 
{
	_polinom* pointToElement = NULL;
	_polinom* pointToPostElement = NULL;

	if (head->next == NULL) {
		ListCheck(-1);
		return 1;
	}

	pointToElement = head->next;
	pointToPostElement = head->next->next;

	while (pointToPostElement != NULL) {
		if (pointToElement->exponent == pointToPostElement->exponent) {
			pointToElement->coefficient = pointToElement->coefficient + pointToPostElement->coefficient;
			if (EraseElement(pointToPostElement, head))
				return -1;
			pointToPostElement = pointToElement->next;
		}
		if (pointToElement != NULL && pointToPostElement != NULL && pointToElement->exponent != pointToPostElement->exponent) {
			pointToElement = pointToElement->next;
			pointToPostElement = pointToPostElement->next;
		}
	}

	return head;
}
_polinom* Linker(_polinom* previousElement, _polinom* nextElement)
{
	nextElement->next = previousElement->next;
	previousElement->next = nextElement;

	return nextElement;
}
_polinom* Switch(_polinom* prevP, _polinom* p, _polinom* postP)
{
	prevP->next = postP;
	p->next = postP->next;
	postP->next = p;

	postP = p->next;
	prevP = prevP->next;

	return prevP;
}
_polinom* ListCheck(int check)//Return: NULL -> List error;
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
