#ifndef DIRECTORIY_FUNCTIONS_DEF
#define DIRECOTRIY_FUNCTIONS_DEF
#define _CRT_SECURE_NO_WARNINGS
#define STACK_FUNCTIONS_DEF
#include "structDeclarations.h"
#include <stdio.h>

_Tree* GoInPreviousDir(_Stack* head, _Tree* root)
{
	PopStack(head, root);
	return GoToCurrent(head);
}

_Tree* FindDir(_Stack* head, char* dirChoose)
{
	_Stack* pointToElementOnStack = head->next;
	int numOfMoves = 0;

	while (pointToElementOnStack != NULL) {
		if (strcmp(pointToElementOnStack->currentDirName, dirChoose) == 0)
			return pointToElementOnStack;
		pointToElementOnStack = pointToElementOnStack->next;
		numOfMoves++;
	}

	return NULL;
}

int PrintPath(_Stack* head)
{
	_Stack* ptr = head->next;

	if (ptr != NULL) {
		PrintPath(ptr);
		printf("%s/", ptr->currentDirName);
	}

	return 0;
}

int AddDir(_Tree* root, _Stack* head)
{
	_Tree* newDir = NULL;
	_Tree* currentPos = NULL;

	newDir = AllocationTree(newDir);
	if (head->next != NULL)
		currentPos = head->next->addressOfElementInTree;
	else
		currentPos = root;
	printf("Unesite ime direktorija: ");
	scanf("%s", newDir->dirName);

	TreeDirLinker(currentPos, newDir);
	Push(head, newDir);
}

int AddSubDir(_Tree* root, _Stack* head)
{
	_Tree* newDir = NULL;
	_Tree* currentPos = NULL;

	newDir = AllocationTree(newDir);

	if (head->next != NULL)
		currentPos = head->next->addressOfElementInTree;
	else
		currentPos = root;

	printf("Unesite ime direktorija: ");
	scanf("%s", newDir->dirName);

	TreeSubDirLinker(currentPos, newDir);
	Push(head, newDir);
}

int GoInDir(_Tree* root, _Stack* head)
{
	_Tree* entryDir = NULL;
	char dirChoose[32] = { 0 };

	PrintPath(head);
	scanf("%s", dirChoose);
	entryDir = FindDir(head, dirChoose);
	Push(head, entryDir);

	return 0;
}
#endif