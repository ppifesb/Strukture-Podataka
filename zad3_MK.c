//Mislav Kovac
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Student {
	char firstName[32];
	char lastName[32];
	int year;
	struct Student* next;
}_Student;

int FirstElementEntry(_Student*);
int LastElementEntry(_Student*);
int Entry(_Student*);
int Print(_Student*);
int EraseElement(_Student*, _Student*);
int StringCheck(char*);
int AddAfterElement(_Student*, char*);
int AddBeforeElement(_Student*, char*);
int Sort(_Student*);
int ReadFromFile(_Student*, int);
int RowCount(char*);//char je buffer s imenom datoteke koju zelimo otvorit;
int FileCheck(int); //Radi provjeru sta vraca fopen/fclose funkcija;
int EntryListToFile(_Student*, int); // Upisuje listu u datoteku;
int PrintfAndScanfCheck(int, int);
int FprintfAndFscanfCheck(int, int);
_Student* Linker(_Student*, _Student*);
_Student* ListCheck(int);
_Student* Switch(_Student*, _Student*, _Student*); //Ispitati zasto ne radi preko funkcije Zamjena
_Student* Find(_Student*, char*);
_Student* Allocation(_Student*);
_Student* FindPrevious(_Student*, char*);
_Student* MoveToEnd(_Student*);

int main()
{
	_Student* Head = NULL;
	_Student* foundElement = NULL;
	int functionCheck = 0;
	int printfCheck = 0, scanfCheck = 0;
	int rowCount = 0;
	char Meni_1 = 0, Meni_2 = 0;
	char buffer[128] = { 0 };

	Head = Allocation(Head);
	Head->next = NULL;

	while (toupper(Meni_1) != 'D' && toupper(Meni_1) != 'E') {
		printfCheck = printf("Zelite li koristiti datoteke ili ekran? (D/E)\n");
		scanfCheck = scanf(" %c", &Meni_1);
		if (PrintfAndScanfCheck(printfCheck, scanfCheck))
			return -1;
	}

	switch (toupper(Meni_1)) {
	case 'D':
		memset(buffer, 0, 128);
		while (strcmp(buffer, "StudentiUpis.txt") != 0 && strcmp(buffer, "Studenti.txt") != 0) {
			printfCheck = printf("\nZa upis u datoteku upisite StudentiUpis.txt, a za citanje Studenti.txt\n");
			scanfCheck = scanf(" %s", buffer);
			if (PrintfAndScanfCheck(printfCheck, scanfCheck))
				return -1;
		}

		if (!(strcmp(buffer, "Studenti.txt"))) {
			rowCount = RowCount(buffer);
			functionCheck = ReadFromFile(Head, rowCount);
			Print(Head);
			if (functionCheck != 0)
				return -1;
		}
		else if (!(strcmp(buffer, "StudentiUpis.txt"))) {
			do {
				functionCheck = LastElementEntry(Head);
				if (functionCheck != 0)
					return -1;

				printfCheck = printf("Zelitel li unijeti jos jedan element? (D/N)");
				scanfCheck = scanf(" %c", &Meni_2);
				if (PrintfAndScanfCheck(printfCheck, scanfCheck))
					return -1;		

				if (toupper(Meni_2) == 'N') {
					functionCheck = EntryListToFile(Head, rowCount);
					if (functionCheck != 0)
						return -1;
					
					return 0;
				}
			} while (toupper(Meni_2) == 'D');
		}
		break;
	case 'E':
		Meni_1 = 0;
		Meni_2 = 0;
		do {
			while (toupper(Meni_1) != 'P' && toupper(Meni_1) != 'K') {
				printfCheck = printf("\nZelite li unijeti element na pocetak ili kraj liste? (P/K)");
				scanfCheck = scanf(" %c", &Meni_1);
				if (PrintfAndScanfCheck(printfCheck, scanfCheck))
					return -1;
			}

			switch (toupper(Meni_1)) {
			case 'P':
				functionCheck = FirstElementEntry(Head);
				if (functionCheck != 0)
					return -1;
				break;
			case 'K':
				functionCheck = LastElementEntry(Head);
				if (functionCheck != 0)
					return -1;
				break;
			}
			
			Meni_2 = 0;
			while (toupper(Meni_2) != 'D' && toupper(Meni_2) != 'N') {
				printfCheck = printf("\nZelite li dodati jos jedan element? (D/N): ");
				scanfCheck = scanf(" %c", &Meni_2);
				if (PrintfAndScanfCheck(printfCheck, scanfCheck))
					return -1;
			}
			Meni_1 = 0;
		} while (toupper(Meni_2) == 'D');
		Meni_1 = 0;

		printf("\n***Ispis svih elemenata***\n\n");

		functionCheck = Print(Head);
		if (functionCheck != 0)
			return -1;

		memset(buffer, 0, 128);
		printfCheck = printf("Unesite prezime: ");
		scanfCheck = scanf(" %s", buffer);
		if (PrintfAndScanfCheck(printfCheck, scanfCheck))
			return -1;

		foundElement = Find(Head, buffer);
		printfCheck = printf("\n***Ispis pronadenog elementa***\nIme: %s\nPrezime: %s\nGodina rodenja: %d\n", foundElement->firstName, foundElement->lastName, foundElement->year);
		if (PrintfAndScanfCheck(printfCheck, 1))
			return -1;

		while (toupper(Meni_1) != 'P' && toupper(Meni_1) != 'N') {
			printfCheck = printf("\nZelite li dodati element prije ili nakon pronadenog elementa? (P/N): ");
			scanfCheck = scanf(" %c", &Meni_1);
			if (PrintfAndScanfCheck(printfCheck, scanfCheck))
				return -1;
		}

		switch (toupper(Meni_1)) {
		case 'P':
			functionCheck = AddBeforeElement(Head, buffer);
			if (functionCheck != 0)
				return -1;
			break;
		case 'N':
			functionCheck = AddAfterElement(Head, buffer);
			if (functionCheck != 0)
				return -1;
			break;
		}
		Meni_1 = 0;

		while (toupper(Meni_1) != 'D' && toupper(Meni_1) != 'N') {
			printfCheck = printf("\nZelite li obrisati pronadeni element? (D/N): ");
			scanfCheck = scanf(" %c", &Meni_1);
			if (PrintfAndScanfCheck(printfCheck, scanfCheck))
				return -1;
		}
		if (toupper(Meni_1) == 'D') {
			functionCheck = EraseElement(foundElement, Head);
			if (functionCheck != 0)
				return -1;
		}

		printf("\n***Ispis elemenata***\n");
		functionCheck = Print(Head);
		if (functionCheck != 0)
			return -1;

		printf("\n\**************************************************************\n\nSortirani ispis:\n");
		functionCheck = Sort(Head);
		if (functionCheck != 0)
			return -1;
		functionCheck = Print(Head);
		if (functionCheck != 0)
			return -1;
	}

	/*free(foundElement);
	free(Head);
	free(buffer);
	free(Meni_1);
	free(Meni_2);
	free(functionCheck);
	free(printfCheck);
	free(scanfCheck);
	free(rowCount);*/

	return 0;
}
_Student* Allocation(_Student* Element)//NULL -> Allocation error; Element -> All good;
{
	Element = (_Student*)malloc(sizeof(_Student));
	if (Element == NULL) {
		printf("***Greska u alociranju memorije!***");
		return NULL;
	}

	return Element;
}
int FirstElementEntry(_Student* Head) // -2 -> Allocation error; -1 -> Entry error; 0 -> All good
{
	int check = 0;
	_Student* Element = NULL;

	if (!(Element = Allocation(Element)))
		return -2;

	Linker(Head, Element);

	check = Entry(Element);
	if (check == -1)
		return -1;

	return 0;
}
int LastElementEntry(_Student* Head) // -2 -> Allocation error; -1 -> Entry error; 0 -> All good
{
	_Student* Element = NULL;
	_Student* PointToElement = Head;
	int check;

	Element = Allocation(Element);
	if (Element == NULL) 
		return -2;

	PointToElement = MoveToEnd(PointToElement);

	Element = Linker(PointToElement, Element);

	check = Entry(Element);
	if (check == -1)
		return -1;

	return 0;
}
int Entry(_Student* Element) //-1 -> Entry error; 0 -> All good
{
	int check_1 = 0;
	int check_2 = 0;

	check_1 = printf("Unos studenta:\nIme: ");
	check_2 = scanf("%s", Element->firstName);
	if (PrintfAndScanfCheck(check_1, check_2) || StringCheck(Element->firstName) == 1) {
		printf("\n***Greska u upisivanju podataka!***\n");
		return -1;
	}
	check_1 = printf("Prezime: ");
	check_2 = scanf("%s", Element->lastName);
	if (PrintfAndScanfCheck(check_1, check_2) || StringCheck(Element->lastName) == 1) {
		printf("\n***Greska u upisivanju podataka!***\n");
		return -1;
	}
	check_1 = printf("Godina rodenja: ");
	check_2 = scanf("%d", &Element->year);		//Napraviti provjeru int po %n!!;
	while ((getchar()) != '\n');				//Ciscenje buffera;
	if (PrintfAndScanfCheck(check_1, check_2)) {
		printf("\n***Greska u upisivanju podataka!***\n");
		return -1;
	}

	return 0;
}
int Print(_Student* Head) //-1 -> printf error; 0 -> All good
{
	_Student* PointToElement = Head->next;
	int check = 0;
	while (PointToElement != NULL) {
		check = printf("\nIme: %s\nPrezime: %s\nGodina rodenja: %d\n", PointToElement->firstName, PointToElement->lastName, PointToElement->year);
		if (PrintfAndScanfCheck(check, 1))
			return -1;
		PointToElement = PointToElement->next;
	}

	return 0;
}
int EraseElement(_Student* Element, _Student* Head) // Return: -1 -> printf error; 1 -> Empty list; 2 -> no element;
{
	_Student* PointToElement = Head;
	int check = 0;

	if (PointToElement == NULL) {
		ListCheck(-1);
		return 1;
	}
	while (PointToElement != NULL && PointToElement->next != Element)
		PointToElement = PointToElement->next;

	if (PointToElement == NULL) {
		ListCheck(-2);
		return 2;
	}

	PointToElement->next = Element->next;
	free(Element);

	return 0;
}
int StringCheck(char* string) //1 -> If number was entered; 0 -> All enements chars
{
	int i = 0;

	for (i = 0; i < strlen(string); i++) {
		if (!isalpha(string[i]))
			return 1;
	}

	return 0;
}
int AddAfterElement(_Student* Head, char* buffer) //Return: -1 -> Allocation error; -2 -> No element / empty list; -3 -> Entry error; 0 -> All good
{
	_Student* Element = NULL;
	_Student* PointToElement = NULL;
	int check = 0;

	Element = Allocation(Element);
	if (Element == NULL)
		return -1;

	PointToElement = Find(Head, buffer);
	if (PointToElement == NULL)
		return -2;

	Linker(PointToElement, Element);

	check = Entry(Element);
	if (check == -1)
		return -3;

	return 0;
}
int AddBeforeElement(_Student* Head, char* buffer) //Return: -1 -> Allocation error; -2 -> Previous element not found; -3 -> Entry error; 0 -> All good
{
	_Student* AddingElement = NULL;
	_Student* PointToPrevElement = NULL;
	int check = 0;

	AddingElement = Allocation(AddingElement);
	if (AddingElement == NULL)
		return -1;

	PointToPrevElement = FindPrevious(Head, buffer);
	if (PointToPrevElement == NULL)
		return -2;

	Linker(PointToPrevElement, AddingElement);

	check = Entry(AddingElement);
	if (check == -1)
		return -3;

	return 0;
}
int Sort(_Student *Head) // Return: 1 -> Only one element; 0 -> All good
{
	_Student* prevElement = Head;
	_Student* Element = Head->next;
	_Student* postElement = Head->next->next;
	_Student* End = NULL;

	if (Head->next == NULL) {
		ListCheck(-1);
		return 1;
	}
	
	while (prevElement->next != End) {
		while (postElement != End) {
			if (strcmp(Element->lastName, postElement->lastName) > 0) {
				prevElement = Switch(prevElement, Element, postElement);
				Element = prevElement->next;
				postElement = Element->next;
			}
			else {
				postElement = postElement->next;
				Element = Element->next;
				prevElement = prevElement->next;
			}
		}
		End = Element;
		prevElement = Head;
		Element = Head->next;
		postElement = Head->next->next;
	}

	return 0;
}
int ReadFromFile(_Student *Head, int rowCount)  //Return: -1 -> fopen error; -2 -> Allocation error; -3 -> fscanf error; -4 -> fclose error
{
	FILE* Studenti = fopen("Studenti.txt", "r");
	int i = 0;
	int check = 0;
	_Student* Element = NULL;
	_Student* prevElement = NULL;

	if (Studenti == NULL) {
		FileCheck(-1);
		return -1;
	}

	if (!(Element = Allocation(Element)))
		return -2;

	Head->next = Element;

	for (i = 0; i < rowCount; i++) {
		check = fscanf(Studenti, "%s %s %d", Element->firstName, Element->lastName, &Element->year);
		if (check == EOF)
			return -3;
		Element->next = Allocation(Element->next);
		Element = Element->next;
	}

	prevElement = FindPrevious(Head, Element->lastName);
	prevElement->next = NULL;

	free(Element);
	check = fclose(Studenti);
	if (check == EOF) {
		FileCheck(-2);
		return -2;
	}

	return 0;
}
int RowCount(char *bufferFile) //Return: rowCount -> All good; -1 -> fopen error; -2 -> fclose error;
{
	FILE* Studenti = fopen(bufferFile, "r");
	char buffer[128] = { 0 };
	int rowCount = 0;
	int check = 0;

	if (Studenti == NULL) {
		FileCheck(-1);
		return -1;
	}

	do {
		fgets(buffer, 128, Studenti);
		if (strlen(buffer) != 0) 
			rowCount++;
		memset(buffer, 0, sizeof(buffer));
	} while (!feof(Studenti));

	check = fclose(Studenti);
	if (check == EOF) {
		FileCheck(-2);
		return -2;
	}

	return rowCount;
}
int FileCheck(int check)
{
	int checkPrintf = 0;
	if (check == -1) {
		checkPrintf = printf("\n\n***Greska u otvaranju datoteke!!***\n\n");
		PrintfAndScanfCheck(checkPrintf, 0);
		system("PAUSE");
		return -1;
	}
	else if (check == -2) {
		checkPrintf = printf("\n\n***Greska pri zatvaranju datoteke!!***\n\n");
		PrintfAndScanfCheck(checkPrintf, 0);
		system("PAUSE");
		return -1;
	}
}
int EntryListToFile(_Student *Head, int broj_redaka) //Return: 0 -> All good; -1 -> fopen error; -2 -> fclose error; -3 -> fprintf error
{
	FILE* Studenti = fopen("StudentiUpis.txt", "w");
	_Student* Element = Head->next;
	int i = 0;
	int check = 0;

	if (Studenti == NULL) {
		FileCheck(-1);
		return -1;
	}

	check = fprintf(Studenti, "Ime\t\tPrezime\t\tGodina rodenja\n");
	if (check < 0) {
		FprintfAndFscanfCheck(check, 0);
		return -3;
	}
	while (Element != NULL) {
		check = fprintf(Studenti, "%s\t\t%s\t\t\t%d\n", Element->firstName, Element->lastName, Element->year);
		if (check < 0) {
			FprintfAndFscanfCheck(check, 0);
			return -3;
		}
		Element = Element->next;
	}

	check = fclose(Studenti);
	if (check == EOF) {
		FileCheck(-2);
		return -2;
	}

	return 0;
}
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
int FprintfAndFscanfCheck(int fprintfCheck, int fscanfCheck)
{
	if (fprintfCheck < 0) {
		printf("\n***Greska u fprintf!***\n");
		return -1;
	}
	if (fscanfCheck == EOF) {
		printf("\n***Greska u fscanf!***\n");
		return -1;
	}

	return 0;
}
_Student* ListCheck(int check)// -1 -> Empty list; -2 -> Element not found
{
	if (check == -1) {
		printf("\n***Lista je prazna!!***\n");
		return NULL;
	}

	if (check == -2) {
		printf("\n***Element nije pronaden!!***\n");
		return NULL;
	}
}
_Student* Find(_Student* Head, char* buffer) // NULL -> Empty list / Element not found
{
	_Student* PointToElement = Head->next;
	int check = 0;

	if (PointToElement == NULL) {
		ListCheck(-1);
		return NULL;
	}

	while (PointToElement != NULL && strcmp(buffer, PointToElement->lastName))
		PointToElement = PointToElement->next;

	if (PointToElement == NULL) {
		ListCheck(-2);
		return NULL;
	}

	return PointToElement;
}
_Student* Linker(_Student *previousElement, _Student *nextElement)
{
	nextElement->next = previousElement->next; 
	previousElement->next = nextElement;

	return nextElement;
}
_Student *Switch(_Student *Prev_P, _Student *P, _Student *Post_P) 
{
	Prev_P->next = Post_P;
	P->next = Post_P->next;
	Post_P->next = P;

	Post_P = P->next;
	Prev_P = Prev_P->next;
	
	return Prev_P;
}
_Student* FindPrevious(_Student* Head, char* buffer) //Return: pointer to previous element -> All good; NULL -> No specific element 
{
	_Student* PointToElement = Head;
	while (PointToElement->next->next != NULL && strcmp(buffer, PointToElement->next->lastName) != 0)
		PointToElement = PointToElement->next;

	if (PointToElement->next == NULL && strcmp(buffer, PointToElement->next->next) != 0) {
		ListCheck(-2);
		return NULL;
	}

	return PointToElement;
}
_Student* MoveToEnd(_Student *PointToElement) //Povlaci pointer na kraj liste
{
	while (PointToElement->next != NULL)
		PointToElement = PointToElement->next;

	return PointToElement;
}
