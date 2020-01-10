#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structDeclarations.h"
#include "stackFunctions.h"
#include "otherFunctions.h"
#include "linkerFunctions.h"
#include "directoryFunctions.h"
#include "allocationFunctions.h"
#define STACK_FUNCTIONS_DEF
#define OTHER_FUNCTIONS_DEF
#define LINKER_FUNCTIONS_DEF
#define ALLOCATION_FUNCTION_DEF


int main()
{
	_Tree* root = NULL;
	_Stack* head = NULL;

	root = AllocationTree(root);
	head = AllocationStack(head);

	functionCaller(root, head);

	return 0;
}