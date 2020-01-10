#ifndef STACK_FUNCTIONS_DEF
#define STACK_FUNCTIONS_DEF
#define _CRT_SECURE_NO_WARNINGS
#include "structDeclarations.h"
#include <stdio.h>

_Stack* PopStack(_Stack* head, _Tree* root)
{
	_Stack* element = NULL;

	element = head->next;
	if (head->next != NULL)
		head->next = element->next;
	else
		return root;

	return element->addressOfElementInTree;
}

int Push(_Stack* head, _Stack* newDir) //Return: -1 -> Allocation error; element->number -> All good
{
	_Stack* element = NULL;

	element = AllocationStack(element);
	if (element == NULL)
		return -1;

	strcpy(element->currentDirName, newDir->currentDirName);
	element->addressOfElementInTree = newDir;

	StackLinker(head, element);

	return 0;
}

int Add(_Tree* root, _Stack* head)
{
	int dir = 0;

	printf("Zelite li dodati direktorij ili poddirektorij: (1 / 2)");
	scanf("%d", &dir);

	switch (dir) {
	case 1:
		AddDir(root, head);
		break;
	case 2:
		AddSubDir(root, head);
		break;
	}
	return 0;
}

#endif