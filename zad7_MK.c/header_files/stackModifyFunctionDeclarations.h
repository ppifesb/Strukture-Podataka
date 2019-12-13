#ifndef STACK_MODIFY_FUNCTIONS
#define STACK_MODIFY_FUNCTIONS

_Stack* Allocation(_Stack* Element);
_Stack* Linker(_Stack* previousElement, _Stack* nextElement);
int Pop(_Stack* head);
int Push(_Stack* head, int buffer);
int StoreResultInStack(_Stack* head, int buffer, int oprationNumber);
int ReadNumberFromString(char* stringBuffer, int option, int* numberOfBytesReadedInTotal);
int NumberFromStringToStack(_Stack* head, char* stringBuffer);

#endif
