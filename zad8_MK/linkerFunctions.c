#ifndef LINKER_FUNCTIONS_DEF
#define LINKER_FUNCTIONS_DEF
#define _CRT_SECURE_NO_WARNINGS
#include "structDeclarations.h"

_Tree* TreeDirLinker(_Tree* firstElement, _Tree* secondElement)
{
	secondElement->dir = firstElement->dir;
	firstElement->dir = secondElement;

	return firstElement;
}

_Tree* TreeSubDirLinker(_Tree* firstElement, _Tree* secondElement)
{
	secondElement->subDir = firstElement->subDir;
	firstElement->subDir = secondElement;

	return firstElement;
}

_Stack* StackLinker(_Stack* firstElement, _Stack* secondElement)
{
	secondElement->next = firstElement->next;
	firstElement->next = secondElement;

	return firstElement;
}

#endif