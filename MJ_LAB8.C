#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SHELL_COMMANDS_MEANING "md->make directory,cd->enters a directory,dir->displays information about direcories andd subdirecotires,cd dir->enters a directory/subdirectory"
#define MEMORY_ALLOCATION_ERROR "Failure while allocating memory"
#define FGETS_ERROR "Failure while saving directory name to string"
#define EMPTY_STACK_ERROR "Warning,stack is empty"
#define DIR_OR_SUBDDIR_NOT_FOUND_WARNING "Warning,requested directory/subdirectory doesn't exist"
#define SCANF_ERROR "Error while reading from stdin"
#define SHELL_COMMAND_ERROR "You have eneterd a wrong number"

typedef struct Root* pointer;
struct Root {
	int ordinal_number;
	pointer brother;
	pointer child;
};
typedef struct Stack* ptr;
struct Stack {
	pointer element_from_tree;
	ptr next;
};

void ShellCommands(pointer,ptr,int); //If third argument==0->user has entered a command(number) for exit
void SwitchCase(int, pointer,ptr);
void DirectoryOrSubdirectory(pointer,ptr);
void MakeDirectory(pointer,ptr);
void SetPointersAndValues(pointer,pointer,int);
pointer Malloc();
void MallocCheck(pointer);
void DirectoryOrSubdirectoryName(int*); //All names will be with ordinal numbers instead of words
void MakeSubdirectory(pointer,ptr);
pointer FindDirectoryOrSubdirectory(pointer,ptr,int);
void BrotherOfNewDirectory(pointer,ptr);
void Push(pointer, ptr);
void StackPointersAndValues(pointer,ptr,ptr);
ptr StackMalloc();
pointer Pop(ptr);
int IsStackEmpty(ptr); //Returns 1 if stack isn't empty,otherwise returns 0
void LastElementInOut(ptr);
void LinkTwoBrothers(pointer, pointer);
void LinkParentAndChild(pointer, pointer);
void LowerToUpper(char*);
void ChangeDirectoryOrSubdirectory(pointer,ptr);
void NameChange(pointer);
int DirectorySubdirectoryStructure(pointer, ptr,int);
void DisplayInformationAboutDirOrSubdir(pointer, ptr,int); //If third argument==0->size of dir won't be displayed
															//If third argument == 1->size of dir will be displayed
void FoundOrNot(pointer,pointer,ptr);                     
void SizeOfDirSubdir(pointer);
void ScanfCheck(int); //Return -1 when error while saving occurs
void SetPosition(int);

int main() {
	struct Root root;
	struct Stack head;
	root.brother = NULL;
	root.child = NULL;
	head.next = NULL;
	ShellCommands(&root, &head,1);

	return 0;
}

void ShellCommands(pointer root,ptr head,int end_or_not)
{
	int shell_command = 0;
	int check = 0;
	printf("Enter one of the following numbers which represent shell commands:\n");
	printf("1(md),2(cd dir),3(cd...),4(dir),5(exit): \n");
	printf("\n");
	printf("%s\n", SHELL_COMMANDS_MEANING);
	check=scanf(" %d", &shell_command);
	ScanfCheck(check);
	if (end_or_not == 1 && check!=0)
		SwitchCase(shell_command, root, head);
}

void SwitchCase(int shell_command, pointer root,ptr head) {
	char decision;
	switch (shell_command) {
	case 1:
		DirectoryOrSubdirectory(root, head);
		ShellCommands(root,head,1);
	case 2:
		ChangeDirectoryOrSubdirectory(root, head);
		ShellCommands(root, head,1);
	case 3:
		 DisplayInformationAboutDirOrSubdir(root, head,0);
		 ShellCommands(root, head,1);
	case 4:
		DisplayInformationAboutDirOrSubdir(root, head, 1);
		ShellCommands(root, head,1);
	case 5:
		ShellCommands(root, head, 0);
	default:
		printf("%s", SHELL_COMMAND_ERROR);
		ShellCommands(root, head,1);
	}
}

void DirectoryOrSubdirectory(pointer root,ptr head) {
	char decision;
	int check = 0;
	printf("Directory or subdirectory(D for directory,S for subdirectory):");
	check=scanf(" %c", &decision);
	ScanfCheck(check);
	LowerToUpper(&decision);
	if (decision == 'D')
		MakeDirectory(root,head);
	else if (decision == 'S')
		MakeSubdirectory(root,head);
}

void MakeDirectory(pointer root,ptr head) {
	if (root->child == NULL)
		SetPointersAndValues(root,NULL,2);
	else
		BrotherOfNewDirectory(root,head);
}

void SetPointersAndValues(pointer root,pointer undefined,int recognition) { //Second argument is undefined as it can be brother or parent of newly allocated element
	pointer allocated = Malloc();
	if (root->child == NULL)
		root->child = allocated;                                            //If recognition==1->second argument is brother of newly allocated element
	allocated->child = NULL;                                                //If recognition==0->second argument is parent of newly allocated element
	allocated->brother = NULL;                                              //If recognition==2->second argument is NULL->function is called when there is no elements
	DirectoryOrSubdirectoryName(&(allocated->ordinal_number));
	if (recognition == 1)
		LinkTwoBrothers(undefined, allocated);
	else if (recognition == 0)
		LinkParentAndChild(undefined, allocated);
	else
		;
}

pointer Malloc() {
	pointer allocated = (pointer)malloc(sizeof(struct Root));
	MallocCheck(allocated);
	return allocated;
}

void MallocCheck(pointer to_be_checked) {
	if (to_be_checked == NULL) {
		printf("%s", MEMORY_ALLOCATION_ERROR);
		return - 1;
	}
}

void DirectoryOrSubdirectoryName(int* pointer_to_ordinal_number) {
	int check = 0;
	int number = 0;
	printf("Enter the ordinal number(name) of directory/subdirectory:");
	check=scanf("%d",&number);
	ScanfCheck(check);
	*pointer_to_ordinal_number = number;
}

void MakeSubdirectory(pointer root,ptr head) {
	int parent_ordinal_number=0;
	int check = 0;
	pointer parent;
	if(root->child==NULL)
		SetPointersAndValues(root->child,NULL,2);
	printf("Enter the ordinal number of directory whose child the new directory will be: ");
	check=scanf(" %d", &parent_ordinal_number);
	ScanfCheck(check);
	parent = FindDirectoryOrSubdirectory(root, head, parent_ordinal_number);
	SetPointersAndValues(root, parent, 0); //Third argument is 1 when second argument is parent
}

pointer FindDirectoryOrSubdirectory(pointer root,ptr head,int to_be_found){ 
	pointer stoping_variable;
	pointer break_variable;
	if (root == NULL && IsStackEmpty(head) == 1) {
		break_variable = FindDirectoryOrSubdirectory(Pop(head)->brother, head, to_be_found);
		if (break_variable->ordinal_number == NULL)
			return NULL;
		if (break_variable->ordinal_number == to_be_found)
			return break_variable;
	}
	else if(root==NULL && IsStackEmpty(head)==0)
		return NULL;
	if (root->ordinal_number == to_be_found) 
		return root;
	while (root != NULL) {
		if (root->brother != NULL)
			Push(root,head);
	    stoping_variable=FindDirectoryOrSubdirectory(root->child, head, to_be_found);
		if (stoping_variable == NULL)
			return NULL;
		if (stoping_variable->ordinal_number == to_be_found)
			return stoping_variable;
	}
}

void BrotherOfNewDirectory(pointer root,ptr head) {
	int brother_ordinal_number=0;
	int check = 0;
	pointer brother;
	printf("Enter the ordinal number of directory whose brother the new directory will be: ");
	check = scanf("%d", &brother_ordinal_number);
	ScanfCheck(check);
	brother = FindDirectoryOrSubdirectory(root, head, brother_ordinal_number);
	SetPointersAndValues(root,brother,1); //third argument is 0 when second argument is brother
}

void Push(pointer root, ptr head)
{
	ptr allocated = StackMalloc();
	MallocCheck(allocated);
	StackPointersAndValues(root,allocated,head);
}

void StackPointersAndValues(pointer root,ptr allocated,ptr head)
{
	allocated->next = head->next;
	head->next = allocated;
	allocated->element_from_tree = root;
}

ptr StackMalloc() {
	ptr allocated = (ptr)malloc(sizeof(struct Stack));
	MallocCheck(allocated);
	return allocated;
}

pointer Pop(ptr head) {
	IsStackEmpty(head);
	pointer to_be_poped = head->next->element_from_tree;
	LastElementInOut(head);
	return to_be_poped;
}

int IsStackEmpty(ptr head){
	if (head->next == NULL) {
		printf("%s", EMPTY_STACK_ERROR);
		return 0;
	}
	else
		return 1;
}

void LastElementInOut(ptr head) {
	ptr to_be_removed = head->next;
	head->next = to_be_removed->next;
	free(to_be_removed);
}

void LinkTwoBrothers(pointer first_brother, pointer second_brother ) {
	second_brother->brother = first_brother->brother;
	first_brother->brother = second_brother;
}

void LinkParentAndChild(pointer parent, pointer child) {
	child->child = parent->child;
	parent->child = child;
}

void LowerToUpper(char* pointer_to_lowercase_char) {
	if (islower(*pointer_to_lowercase_char))
		*pointer_to_lowercase_char=toupper(*pointer_to_lowercase_char);
	*pointer_to_lowercase_char = (char)*pointer_to_lowercase_char;
}

void ChangeDirectoryOrSubdirectory(pointer root,ptr head) {
	int to_be_found=0;
	int check = 0;
	printf("Enter the ordinal number of directory/subdirectory you want to change:");
	check = scanf("%d", &to_be_found);
	ScanfCheck(check);
	pointer dir_subdir_to_be_found = FindDirectoryOrSubdirectory(root, head, to_be_found);
	NameChange(dir_subdir_to_be_found);
}

void NameChange(pointer to_be_changed) {
	int new_ordinal_number = 0;
	int check = 0;
	printf("Enter the new name(ordinal number): ");
	check=scanf("%d", &new_ordinal_number);
	ScanfCheck(check);
	to_be_changed->ordinal_number = new_ordinal_number;
}

int DirectorySubdirectoryStructure(pointer root, ptr head, int position) { //For command dir, first argument is dummy element if we want to see the whole structure of tree 
	int stoping_var = 0;
	int breaking_var = 0;
	if (root == NULL && IsStackEmpty(head) == 0)             //IsStackEmpty returns 0 if stack is empty,otherwise it returns 1
		return 0;
	if (root == NULL && IsStackEmpty(head) == 1) {
		position--;
		breaking_var=DirectorySubdirectoryStructure(Pop(head)->brother, head, position);
		if (breaking_var == 0)
			return 0;
	}
	if (position == 0)
		printf("%d\n", root->ordinal_number);
	else if (position != 0) {
		SetPosition(position);
		printf("%d\n", root->ordinal_number);
	}
	while (root != NULL) {
		if (root->brother != NULL)
			Push(root, head);
		position++;
		stoping_var=DirectorySubdirectoryStructure(root->child, head, position);
		if (stoping_var == 0)
			return 0;
	}
}

void DisplayInformationAboutDirOrSubdir(pointer root, ptr head,int recognition) {
	int dir_subdir_number = 0;
	int check = 0;
	pointer to_be_displayed;
	DirectorySubdirectoryStructure(root->child, head, 0);
	printf("Enter the name of directory/subdirectory whose information you want to see:");
	check=scanf("%d", &dir_subdir_number);
	ScanfCheck(check);
	to_be_displayed = FindDirectoryOrSubdirectory(root, head, dir_subdir_number);
	FoundOrNot(root,to_be_displayed,head);
	if(recognition!=0)
		SizeOfDirSubdir(to_be_displayed);
	DirectorySubdirectoryStructure(to_be_displayed, head,0);
}

void FoundOrNot(pointer root,pointer found_dir_subdir,pointer head) {
	if (found_dir_subdir == NULL) {
		printf("%s", DIR_OR_SUBDDIR_NOT_FOUND_WARNING);
		ShellCommands(root, head,1);
	}
}

void SizeOfDirSubdir(pointer to_be_displayed) {
	printf("Size of directory/subdirectory you wanted to display is %d", sizeof(to_be_displayed));
}

void ScanfCheck(int to_be_checked) {
	if (to_be_checked != 1 || to_be_checked == EOF) {
		printf("%s", SCANF_ERROR);
		return -1;
	}
}

void SetPosition(int position) {
	int i = 0;
	for (i = 0; i < position; i++)
		printf("  ");
}
