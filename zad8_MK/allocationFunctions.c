#ifndef ALLOCATION_FUNCTION_DEF
#define ALLOCATION_FUNCTION_DEF
#define _CRT_SECURE_NO_WARNINGS
#include "structDeclarations.h"
#include <stdio.h>
#include <malloc.h>
#define ALLOCATION_ERROR "\n\n***Allocation error***\n\n"


_Tree* AllocationTree(_Tree* element)//NULL -> Allocation error; Element -> All good;
{
	element = (_Tree*)malloc(sizeof(_Tree));
	if (element == NULL) {
		printf("%s", ALLOCATION_ERROR);
		return NULL;
	}
	element->dir = NULL;
	element->subDir = NULL;

	return element;
}

_Stack* AllocationStack(_Stack* element)//NULL -> Allocation error; Element -> All good;
{
	element = (_Stack*)malloc(sizeof(_Stack));
	if (element == NULL) {
		printf("%s", ALLOCATION_ERROR);
		return NULL;
	}
	element->next = NULL;
	element->addressOfElementInTree = NULL;

	return element;
}

#endif