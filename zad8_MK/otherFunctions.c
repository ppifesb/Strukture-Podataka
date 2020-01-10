#ifndef OTHER_FUNCTIONS_DEF
#define OTHER_FUNCTIONS_DEF
#define _CRT_SECURE_NO_WARNINGS
#include "structDeclarations.h"

int functionCaller(_Tree* root, _Stack* head) /*Prominit ime :D*/
{
	int operationNum = 0;
	int exit = 1;

	while (exit) {
		printf("Izaberite zeljenu operaciju:\n 1 - 'md'\n 2 - 'cd dir'\n 3 - 'cd..'\n 4 - 'dir'\n 5 - izlaz\n");
		scanf("%d", &operationNum);

		switch (operationNum) {
		case 1:
			Add(root, head);
			break;
		case 2:
			GoInDir(root, head);
			break;
		case 3:
			GoInPreviousDir(head, root);
			break;
		case 4:
			printf("/root/");
			PrintPath(head);
			break;
		case 5:
			return 1;
		}
		printf("Za izlaz upisite 0");
		scanf("%d", &exit);
	}
}

_Tree* GoToCurrent(_Stack* head)
{
	_Tree* currentPos = head->next->addressOfElementInTree;

	return currentPos;
}


#endif