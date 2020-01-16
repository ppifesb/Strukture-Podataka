#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ALLOCATION_ERROR "\n\n***Allocation error***\n\n"
#define TAB "\t"


typedef struct Tree {
	int num;
	struct Tree* left;
	struct Tree* right;
}_Tree;

_Tree* AllocationTree(_Tree* element);
_Tree* AddElement(_Tree* root);
_Tree* NewElementEntry(_Tree* newElement);
_Tree* TreeLeftLinker(_Tree* firstElement, _Tree* secondElement);
_Tree* TreeRightLinker(_Tree* firstElement, _Tree* secondElement); 
_Tree* PositionFinder(_Tree* startPosition, int num);
_Tree* FindMin(_Tree* startPosition);
_Tree* Print(_Tree* startPosition, int numOfTabs);
_Tree* PositionChecker(_Tree* pointToElement, int num);
int RootErase(_Tree* root);
int EraseElement(_Tree* root, int num);
int LRCheck(_Tree* pointToElement);
int EraseMode(_Tree* root, _Tree* pointToPrevElement, _Tree* pointToElement, int childNum, int numForErase);
int ZeroErase(_Tree* pointToPrevElement, _Tree* pointToElement, int numForErase);
int OneErase(_Tree* pointToPrevElement, int numForErase);
int TwoErase(_Tree* root, _Tree* pointToPrevElement, _Tree* pointToElement, int numForErase);
int RootErase(_Tree* root);

int main(){
	_Tree* root = NULL;
	_Stack* head = NULL;
	_Tree* test;

	root = AllocationTree(root);
	head = AllocationStack(head);

	NewElementEntry(root);
	
	
	AddElement(root);
	AddElement(root);
	AddElement(root);
	AddElement(root);
	AddElement(root);
	AddElement(root);
	AddElement(root);
	AddElement(root);
	/*AddElement(root);*/

	Print(root, 0);
	printf("\n\n\n");
	EraseElement(root, 9);
	printf("-----------------------------------------------------------\n\n\n");
	Print(root, 0);
	printf("\n\n\n");
	EraseElement(root, 6);


	printf("\n\n\n");
	Print(root, 0);
	return 0;

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
	element->num = 0;

	return element;
}
_Tree* NewElementEntry(_Tree* newElement)
{
	printf("Unesite broj: ");
	scanf("%d", &newElement->num);

	return newElement->num;
}
_Tree* TreeLeftLinker(_Tree* firstElement, _Tree* secondElement)
{
	secondElement->left = firstElement->left;
	firstElement->left = secondElement;

	return firstElement;
}
_Tree* TreeRightLinker(_Tree* firstElement, _Tree* secondElement)
{
	secondElement->right = firstElement->right;
	firstElement->right = secondElement;

	return firstElement;
}
_Tree* PositionFinder(_Tree* startPosition, int num)
{
	_Tree* pointToElement = startPosition;

	if (num < startPosition->num && startPosition->left != NULL) {
		pointToElement = pointToElement->left;
		pointToElement = PositionFinder(pointToElement, num);
	}
	if (num > startPosition->num && startPosition->right != NULL){
		pointToElement = pointToElement->right;
		pointToElement = PositionFinder(pointToElement, num);
	}
	return pointToElement;
}
_Tree* PrevPositionFinder(_Tree* startPosition, int num)
{
	_Tree* pointToElement = startPosition;

	if (num < startPosition->num && startPosition->left != NULL) {
		if (PositionChecker(pointToElement, num))
			return pointToElement;
		pointToElement = pointToElement->left;
		pointToElement = PrevPositionFinder(pointToElement, num);
	}
	if (num > startPosition->num && startPosition->right != NULL) {
		if (PositionChecker(pointToElement, num))
			return pointToElement;
		pointToElement = pointToElement->right;
		pointToElement = PrevPositionFinder(pointToElement, num);
	}
	return pointToElement;
}
_Tree* PositionChecker(_Tree* pointToElement, int num)
{
	if (pointToElement->right != NULL)
		if (pointToElement->right->num == num)
			return 1;
	if (pointToElement->left != NULL)
		if (pointToElement->left->num == num)
			return 1;

	return 0;
	
}
_Tree* AddElement(_Tree* root)
{
	_Tree* newElement = NULL;
	_Tree* addingPosition = NULL;
	int num = 0;

	newElement = AllocationTree(newElement);
	num = NewElementEntry(newElement);
	addingPosition = PositionFinder(root, num);

	if (num > addingPosition->num) {
		TreeRightLinker(addingPosition, newElement);
	}
	else if(num < addingPosition->num) {
		TreeLeftLinker(addingPosition, newElement);
	}
}
int EraseElement(_Tree* root, int num)
{
	_Tree* pointToElement = PositionFinder(root, num);
	_Tree* pointToPrevElement = PrevPositionFinder(root, num);
	int childNum = LRCheck(pointToElement);

	if (pointToElement == pointToPrevElement) {
		RootErase(root);
		return 0;
	}

	EraseMode(root, pointToPrevElement, pointToElement, childNum, num);


}
int LRCheck(_Tree* pointToElement)
{
	if (pointToElement->left == NULL && pointToElement->right == NULL) {
		return 0;
	}
	if (pointToElement->left == NULL || pointToElement->right == NULL) {
		return 1;
	}
	if (pointToElement->left != NULL && pointToElement->right != NULL) {
		return 2;
	}
}
int EraseMode(_Tree* root, _Tree* pointToPrevElement, _Tree* pointToElement, int childNum, int numForErase)
{
	if (childNum == 0) {
		ZeroErase(pointToPrevElement, pointToElement, numForErase);
	}
	if (childNum == 1) {
		OneErase(pointToPrevElement, numForErase);
	}
	if (childNum == 2) {
		TwoErase(root, pointToPrevElement, pointToElement, numForErase);
	}
}
int ZeroErase(_Tree* pointToPrevElement, _Tree* pointToElement, int numForErase)
{
	if (pointToPrevElement->left->num == numForErase) {
		free(pointToElement);
		pointToPrevElement->left = NULL;
		return 0;
	}
	if (pointToPrevElement->right->num == numForErase) {
		free(pointToElement);
		pointToPrevElement->right = NULL;
		return 0;
	}
}
int OneErase(_Tree* pointToPrevElement, int numForErase)
{
	_Tree* pointToElement = NULL;

	if (pointToPrevElement->left != NULL && pointToPrevElement->left->num == numForErase) {
		pointToElement = pointToPrevElement->left;
		if (pointToElement->left != NULL) {
			pointToPrevElement->left = pointToElement->left;
		}
		else if (pointToElement->right != NULL) {
			pointToPrevElement->left = pointToElement->right;
		}
		free(pointToElement);
	}
	if (pointToPrevElement->right != NULL && pointToPrevElement->right->num == numForErase) {
		pointToElement = pointToPrevElement->right;
		if (pointToElement->left != NULL) {
			pointToPrevElement->right = pointToElement->left;
		}
		else if (pointToElement->right != NULL) {
			pointToPrevElement->right = pointToElement->right;
		}
		free(pointToElement);
	}
}
int TwoErase(_Tree* root, _Tree* pointToPrevElement, _Tree* pointToElement, int numForErase)
{
	_Tree* minElement = FindMin(pointToElement);
	pointToPrevElement = PrevPositionFinder(root, minElement->num);
	
	pointToElement->num = minElement->num;
	OneErase(pointToPrevElement, minElement->num);
}
int RootErase(_Tree* root)
{
	_Tree* minElement = FindMin(root);
	_Tree* prevElementPosition = PrevPositionFinder(root, minElement->num);

	root->num = minElement->num;
	if (prevElementPosition == minElement)
		root->right = NULL;
	else
		EraseElement(prevElementPosition, minElement->num);
}
_Tree* FindMin(_Tree* startPosition)
{
	int min = startPosition->right->num;
	startPosition = startPosition->right;

	while (startPosition->left != NULL) {
		startPosition = startPosition->left;
	}

	return startPosition;
}
_Tree* Print(_Tree* startPosition, int numOfTabs)
{
	int i = 0;

	if (startPosition == NULL)
		return 1;

	Print(startPosition->right, numOfTabs + 1);
	for (i = 0; i < numOfTabs; i++)
		printf(TAB);

	printf("%d\n\n", startPosition->num);

	Print(startPosition->left, numOfTabs + 1);
}
