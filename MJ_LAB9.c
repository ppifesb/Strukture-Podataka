#include<stdio.h>
#include<stdlib.h>
#define SCANF_ERROR "Error while reading from stdin"
#define MALLOC_ERROR "Error while allocating memory"
#define USER_INPUT_ERROR "You have entered a wrong letter"

typedef struct binary_search_tree* pointer;
struct binary_search_tree{
	int value;
	pointer left_child;
	pointer right_child;
};

typedef struct stack* ptr;
struct stack {
	pointer element_from_tree;
	ptr next;
};

pointer AddNewElementToTree(pointer,int);
void ScanfCheck(int);
void LowerToUpper(char *);
pointer Malloc();
void MallocCheck(pointer);
void SetValuesAndPointers(pointer,int);
pointer TreeStructure(pointer);
void InitializePointersToNull(pointer, ptr);
void PushElementToStack(pointer, ptr);
ptr StackMalloc();
void StackElementPointersAndValues(ptr,ptr,pointer);
pointer Pop(ptr);
void LastInFirstOut(ptr);
int IsStackEmpty(ptr);
void SwitchCase(pointer, ptr);
MainRootValue(pointer);
void CaseN(pointer);
void ToContinueOrNot(char*);
pointer SearchElementFromTree(pointer, int);
void CaseS(pointer);
void ElementFoundOrNot(pointer);
void DecisionCheck(char*);
void Delete(pointer);
int ValueToBeDeleted();
void ConnectChildrenAndParent(pointer,pointer);
int NumberOfChildren(pointer);
void CaseWithoutChildren(pointer, pointer);
pointer SearchForParent(pointer, pointer);
int main() {

	struct binary_search_tree root;
	struct stack head;
	InitializePointersToNull(&root, &head);
	MainRootValue(&root);
	SwitchCase(&root, &head);

	return 0;
}

pointer AddNewElementToTree(pointer root,int value_to_be_entered){
	if (root == NULL) {
		root = Malloc();
		SetValuesAndPointers(root, value_to_be_entered);
	}
	if (value_to_be_entered > root->value)
		root->right_child=AddNewElementToTree(root->right_child, value_to_be_entered);
	if(value_to_be_entered < root->value)
		root->left_child=AddNewElementToTree(root->left_child, value_to_be_entered);
	return root;
}

void ScanfCheck(int to_be_checked) {
	if (to_be_checked != 1 || to_be_checked == EOF) {
		printf("%s", SCANF_ERROR);
		return -1;
	}
}

void LowerToUpper(char* to_be_changed) {
	if (islower(*to_be_changed))
		*to_be_changed = (char)toupper(*to_be_changed);
}

pointer Malloc() {
	pointer allocated_root = NULL;
	allocated_root = (pointer)malloc(sizeof(struct binary_search_tree));
	MallocCheck(allocated_root);
	return allocated_root;
}

void MallocCheck(pointer to_be_checked) {
	if (to_be_checked == NULL) {
		printf("%s", MALLOC_ERROR);
		return -1;
	}
}

void SetValuesAndPointers(pointer allocated_root, int value_to_be_entered) {
	allocated_root->value = value_to_be_entered;
	allocated_root->right_child = NULL;
	allocated_root->left_child = NULL;
}

pointer TreeStructure(pointer root) {
	if (root == NULL)
		return NULL;
	printf("%d\n", root->value);
	TreeStructure(root->left_child);
	TreeStructure(root->right_child);
	//if (IsStackEmpty(head) == 1)
		//TreeStructure(Pop(head), head);
}

void InitializePointersToNull(pointer root, ptr head) {
	root->left_child = NULL;
	root->right_child = NULL;
	head->next = NULL;
}

void PushElementToStack(pointer tree_element, ptr head) {
	ptr stack_element = StackMalloc();
	StackElementPointersAndValues(stack_element, head, tree_element);
}

ptr StackMalloc() {
	ptr allocated = NULL;
	allocated = (ptr)malloc(sizeof(struct stack));
	MallocCheck(allocated);
	return allocated;
}

void StackElementPointersAndValues(ptr allocated,ptr head,pointer tree_element) {
	allocated->element_from_tree = tree_element;
	allocated->next = head->next;
	head->next = allocated;
}

pointer Pop(ptr head) {
	pointer to_be_poped = head->next->element_from_tree;
	LastInFirstOut(head);
	return to_be_poped;
}

void LastInFirstOut(ptr head) {
	ptr to_be_poped = head->next;
	head->next = head->next->next;
	free(to_be_poped);
}

int IsStackEmpty(ptr head) {
	if (head->next != NULL)
		return 1;
	else
		return 0;
}

void SwitchCase(pointer main_root, ptr head) {
	char decision = ' ';
	char user_choice = ' ';
	int reading_check = 0;
	do {
		printf("N(add new element to tree),W(current look of tree),D(delete certain element from tree),S(search for certain element)");
		printf("Enter your choice:");
		reading_check = scanf(" %c",&user_choice);
		LowerToUpper(&user_choice);
		switch (user_choice) {
		case 'N':
			CaseN(main_root);
			break;
		case 'W':
			TreeStructure(main_root);
			break;
		case 'S':
			CaseS(main_root);
			break;
		case 'D':
			Delete(main_root);
			break;
		default:
			printf("%s\n", USER_INPUT_ERROR);
			break;
		}
		ToContinueOrNot(&decision);
	} while (decision == 'Y');
}

MainRootValue(pointer main_root) {
	int reading_check = 0;
	printf("Enter the value of main root:");
	reading_check=scanf(" %d",&main_root->value);
	ScanfCheck(reading_check);
}

void CaseN(pointer main_root) {
	int value_to_be_entered=0;
	int reading_check = 0;
	printf("Enter the value you want to enter:");
	reading_check = scanf("%d", &value_to_be_entered);
	AddNewElementToTree(main_root, value_to_be_entered);
}

void ToContinueOrNot(char* decision) {
	int reading_check = 0;
	printf("Do you want to continue working with tree?(Y for yes,N for no):");
	reading_check=scanf(" %c", decision);
	LowerToUpper(decision);
	ScanfCheck(reading_check);
	DecisionCheck(decision);
}

pointer SearchElementFromTree(pointer root, int to_be_searched) {
	pointer value_returned = NULL;
	if (root == NULL)
		return NULL;
	if (root->value == to_be_searched)
		return root;
	if (root->value > to_be_searched)
		value_returned=SearchElementFromTree(root->left_child, to_be_searched);
	if (root->value < to_be_searched)
		value_returned =SearchElementFromTree(root->right_child, to_be_searched);
	return value_returned;
}

void CaseS(pointer root) {
	int to_be_searched = 0;
	int reading_check = 0;
	pointer to_be_found = NULL;

	printf("Enter the element you want to search for:");
	reading_check = scanf("%d",&to_be_searched);
	to_be_found = SearchElementFromTree(root, to_be_searched);
	ElementFoundOrNot(to_be_found);
}

void ElementFoundOrNot(pointer search_function_returned) {
	if (search_function_returned != NULL) {
		printf("Requested element exists in binary search tree\n");
		TreeStructure(search_function_returned);
	}
	else
		printf("Requested element doesn't exist in binary search tree\n");
}

void DecisionCheck(char* decision) {
	if (*decision == 'Y' || *decision == 'N')
		return 0;
	else
		ToContinueOrNot(decision);
}

void Delete(pointer root) {
	pointer to_be_deleted = SearchElementFromTree(root, ValueToBeDeleted());
	if (to_be_deleted != NULL)
		ConnectChildrenAndParent(to_be_deleted, root);
}

int ValueToBeDeleted() {
	int value_to_be_deleted = 0;
	int reading_check = 0;
	printf("Which element do you want to delete?:");
	reading_check = scanf("%d", &value_to_be_deleted);
	return value_to_be_deleted;
}

void ConnectChildrenAndParent(pointer to_be_deleted,pointer root) {
	if (NumberOfChildren(to_be_deleted) == 0)
		CaseWithoutChildren(to_be_deleted, root);
}

int NumberOfChildren(pointer to_be_deleted) {
	if (to_be_deleted->right_child == NULL && to_be_deleted->left_child == NULL)
		return 0;
	if (to_be_deleted->left_child != NULL && to_be_deleted->right_child == NULL)
		return 1;
	if (to_be_deleted->left_child == NULL && to_be_deleted->right_child != NULL)
		return 1;
	if (to_be_deleted->right_child != NULL && to_be_deleted->left_child != NULL)
		return 2;
}

void CaseWithoutChildren(pointer to_be_deleted, pointer root) {
	pointer parent_of_to_be_deleted=
}

pointer SearchForParent(pointer to_be_deleted, pointer root) {
	pointer value_returned = NULL;
	if (root == NULL)
		return NULL;
	if (root->right_child == to_be_deleted || root->left_child == to_be_deleted)
		return root;

}
