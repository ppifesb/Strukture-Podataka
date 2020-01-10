#ifndef DIRECOTRY_FUNCTIONS
#define DIRECOTRY_FUNCTIONS
#include "structDeclarations.h"

_Tree* GoInPreviousDir(_Stack* head, _Tree* root);
_Tree* FindDir(_Stack* head, char* dirChoose);
int PrintPath(_Stack* head);
int AddDir(_Tree* root, _Stack* head);
int AddSubDir(_Tree* root, _Stack* head);
int GoInDir(_Tree* root, _Stack* head);

#endif
