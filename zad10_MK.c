#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define ALLOCATION_ERROR "\n\n***Allocation error***\n\n"
#define FOPENERROR "\n\n***File open error***\n\n"
#define FCLOSEERROR "\n\n***File close error***\n\n"

typedef struct Tree {
	char expression;
	struct Tree* left;
	struct Tree* right;
}_Tree;

typedef struct TreeStack {
	_Tree* expression;
	struct TreeStack* next;
}_TreeStack;

_TreeStack* AllocationStack(_TreeStack* element, char* buffer);
_Tree* AllocationTree(_Tree* element);
_Tree* TreeLeftLinker(_Tree* firstElement, _Tree* secondElement);
_Tree* TreeRightLinker(_Tree* firstElement, _Tree* secondElement);
char* ReadFromFile(char* buffer);
int BufferElementCheck(char* buffer, _TreeStack* head);
int IsNumOrExpression(char bufferElement);
int IsNotNum(_TreeStack* head, char bufferElement, char* buffer);
int PushNode(_Tree* expressionNode, _TreeStack* head, char* buffer);
int Push(_TreeStack* head, char bufferElement);
_TreeStack* StackLinker(_TreeStack* firstElement, _TreeStack* secondElement);
_Tree* PopStack(_TreeStack* head);
_Tree* PrintToArray(_Tree* startPosition, char* inorderArray, int* i);

int main()
{
	char buffer[1024] = { 0 };
	char inorderArray[1024] = { 0 };
	int i = 0;
	_TreeStack* head = NULL;

	ReadFromFile(&buffer);
	head = AllocationStack(head, NULL);


	BufferElementCheck(buffer, head);

	PrintToArray(head->next->expression, inorderArray, &i);

	PrintToFile(inorderArray, i);

}
_Tree* AllocationTree(_Tree* element)//NULL -> Allocation error; Element -> All good;
{
	element = (_Tree*)malloc(sizeof(_Tree));
	if (element == NULL) {
		printf("%s", ALLOCATION_ERROR);
		return NULL;
	}
	element->left = NULL;
	element->right = NULL;
	element->expression = 0;

	return element;
}
_TreeStack* AllocationStack(_TreeStack* element, char* buffer)//NULL -> Allocation error; Element -> All good;
{
	element = (_TreeStack*)malloc(sizeof(_TreeStack));
	if (element == NULL) {
		printf("%s", ALLOCATION_ERROR);
		return NULL;
	}
	element->next = NULL;
	element->expression = 0;

	return element;
}
_Tree* TreeLeftLinker(_Tree* firstElement, _Tree* secondElement)
{
	//secondElement->left = firstElement->left;
	firstElement->left = secondElement;

	return firstElement;
}
_Tree* TreeRightLinker(_Tree* firstElement, _Tree* secondElement)
{
	//secondElement->right = firstElement->right;
	firstElement->right = secondElement;

	return firstElement;
}
char* ReadFromFile(char* buffer)
{
	FILE* postfixFile = fopen("postfix.txt", "r");
	/*char buffer[1024] = { 0 };*/

	if (postfixFile == NULL) {
		printf("%s", FOPENERROR);
		return -1;
	}

	fgets(buffer, 1024, postfixFile);

	if (fclose(postfixFile) == EOF) {
		printf("%s", FCLOSEERROR);
		return -1;
	}

	return buffer;
}
int BufferElementCheck(char* buffer, _TreeStack* head)
{
	char* pointToElementInBuffer = buffer;
	int i = 0;
	int numOfBytes = 0;

	do {
		if (*(buffer + i) != ' ' && IsNumOrExpression(*(buffer + i))) {
			Push(head, *(buffer + i));
		}
		else if (*(buffer + i) != ' ' && IsNumOrExpression(*(buffer + i)) == 0) {
			IsNotNum(head, *(buffer + i), buffer);
		}
		i++;
	} while (*(buffer + i) != '\0');
}
int IsNumOrExpression(char bufferElement)
{
	return isdigit(bufferElement);
}
int IsNotNum(_TreeStack* head, char bufferElement, char* buffer)
{
	_Tree* firstPopedElement = PopStack(head);
	_Tree* secondPopedElement = PopStack(head);
	_Tree* node = NULL;

	node = AllocationTree(node);
	node->expression = bufferElement;

	TreeLeftLinker(node, secondPopedElement);
	TreeRightLinker(node, firstPopedElement);

	PushNode(node, head, buffer);

	return 0;
}
int PushNode(_Tree* expressionNode, _TreeStack* head, char* buffer)
{
	_TreeStack* element = NULL;

	element = AllocationStack(element, buffer);
	if (element == NULL)
		return -1;

	element->expression = expressionNode;

	StackLinker(head, element);

	return 0;
}
int Push(_TreeStack* head, char bufferElement) //Return: -1 -> Allocation error; element->number -> All good
{
	_TreeStack* element = NULL;
	_Tree* node = NULL;

	element = AllocationStack(element, NULL);
	if (element == NULL)
		return -1;

	node = AllocationTree(node);
	node->expression = bufferElement;
	element->expression = node;

	StackLinker(head, element);

	return 0;
}
_TreeStack* StackLinker(_TreeStack* firstElement, _TreeStack* secondElement)
{
	secondElement->next = firstElement->next;
	firstElement->next = secondElement;

	return firstElement;
}
_Tree* PopStack(_TreeStack* head)
{
	_TreeStack* element = NULL;

	element = head->next->expression;
	head->next = head->next->next;

	return element;
}
_Tree* PrintToArray(_Tree* startPosition, char* inorderArray, int* i)
{
	if (startPosition == NULL)
		return 1;

	PrintToArray(startPosition->right, inorderArray, i);

	*i = StoreInArray(startPosition->expression, inorderArray, i);

	PrintToArray(startPosition->left, inorderArray, i);
}
int StoreInArray(char expression, char* inorderArray, int* i)
{
	int index = *i;

	inorderArray[index] = expression;
	return *i + 1;
}
int PrintToFile(char* opositeInorderArray, int i)
{
	FILE* inorderFile = fopen("inorder.txt", "w");
	int j = 0;

	if (inorderFile == NULL) {
		printf("%s", FOPENERROR);
		return -1;
	}
	
	for (j = 1; j < i + 1; j++)
		fprintf(inorderFile, "%c ", opositeInorderArray[i - j]);

	if (fclose(inorderFile) == EOF) {
		printf("%s", FCLOSEERROR);
		return -1;
	}
}
