#ifndef STRUCT_DECLARATIONS
#define STRUCT_DECLARATIONS

typedef struct Tree {
	char dirName[32];
	struct Tree* dir;
	struct Tree* subDir;
}_Tree;

typedef struct Stack {
	char currentDirName[32];
	struct Tree* addressOfElementInTree;
	struct Stack* next;
}_Stack;

#endif