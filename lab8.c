#include <stdio.h>
#include <stdlib.h>	
#define ALLOCATION_ERROR "\n***Memory allocation error\n***"

typedef struct Tree {
	char dirName[256];
	struct Tree* dir;
	struct Tree* subDir;
}_Tree;

typedef struct Stack {
	struct Tree* current;
	struct Tree* next;
};

typedef enum {
	OK,
	FILE_DIDNT_OPEN
}StatusCode;

typedef struct {
	StatusCode code;
	char description[4096];
}Status;

Status okStatus()
{
	Status status = { OK, "Ok" };
	return status;
}

Status fileNotOpenStatus(char *filename)
{
	Status status = { FILE_DIDNT_OPEN };
	sprintf(status.description, "File %s did not open!\r\n", filename);
	return status;
}

int main()
{
	_Tree* root = Allocation(root);
	int moveToDir = 0;

	

}
_Tree* Allocation(_Tree* element)
{
	element = (_Tree*)malloc(sizeof(_Tree));
	if (element == NULL){
		printf("%s", ALLOCATION_ERROR);
		return NULL;
	}

	element->dir = NULL;
	element->subDir = NULL;

	return element;
}
Status AddDir(_Tree* addingDir)
{
	_Tree* dir = Allocation(dir);

	LinkerForDir(dir, addingDir);

	return okStatus();
}

int AddSubDir(_Tree* addingSubDir)
{
	_Tree* subDir = Allocation(subDir);

	printf("Napisite ime direktorija: ");
	scanf(" %s", subDir->dirName);
	LinkerForSubDir(subDir, addingSubDir);

	return 0;
}
_Tree* LinkerForDir(_Tree* firstElement, _Tree* secondElement)
{
	secondElement->dir = firstElement->dir;
	firstElement->dir = secondElement;

	return firstElement;
}
_Tree* LinkerForSubDir(_Tree* firstElement, _Tree* secondElement)
{
	secondElement->subDir = firstElement->subDir;
	firstElement->subDir = secondElement;

	return firstElement;
}
int Meni(_Tree* root)
{
	int command = 0;

	switch (command)
	{
	case 1:
		AddSubDir(root)

	default:
		break;
	}
}
