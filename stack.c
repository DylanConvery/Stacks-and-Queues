#include <stdio.h>
#include <stdlib.h>

//LIFO data structure
typedef struct Stack {
    unsigned pid;
    struct Stack* next_node;
} Stack;

//forward declarations
int push(Stack** head, unsigned pid);
int pop(Stack** head);
int isEmpty(Stack* head);
void printStack(Stack* head);
void menu(Stack** head);

int main() {
    //head of stack 
    Stack* head = NULL;
    //start stack
    menu(&head);
    return 0;
}

//push node to stack
int push(Stack** head, unsigned pid) {
    //allocate memory for new process
	Stack* newPtr = malloc(sizeof(Stack));
    //check to make sure we had sufficient memory
	if (newPtr != NULL) {
        //set up new node with relevent data
        newPtr->pid = pid;
		newPtr->next_node = *head;
		*head = newPtr;
        return 0;
	}
    //indicte failure
    return -1;
}

//pop node from stack
int pop(Stack** head) {
    //check if stack is empty so we don't dereference a null pointer
    if (!isEmpty(*head)) {
        //store first node in stack
        Stack* tempPtr = *head;
        //move head forward in the stack
        *head = (*head)->next_node;
        //deallocate the first node
        free(tempPtr);
        return 0;
    }
    //indicte failure
    return -1;
}

//check if stack is empty
int isEmpty(Stack* head) {
    //if head is NULL, return true, otherwise return false
	return head == NULL;
}

//print out stack in an understandable format
void printStack(Stack* head) {
    //check if stack is empty so we don't dereference a null pointer
	if (isEmpty(head)) {
        printf("Stack is empty.\n");
    } else {
		printf("The stack is: ");
        //walkthrough stack until we hit the end
		while (head != NULL) {
			printf("PID(%u) --> ", head->pid);
			head = head->next_node;
		}
		printf("NULL\n");
	}
}

//menu for stack operation
void menu(Stack** head) {
    static unsigned pid = 1;
    unsigned choice;
    //print menu instructions
    printf(
        "***STACK MENU***\n"
        "1. Add process\n"
        "2. Remove process\n"
        "3. Exit\n"
        ": "
    );
    //get the users choice
    scanf("%u", &choice);
    //execute users choice
    while(choice != 3){
        switch(choice){
        //push process
        case 1:
			if(push(head, pid) == 0) {
                printf("Process added sucessfully.\n");
                pid++;                 
            } else {
	        	fprintf(stderr, "Process not added. No memory available.\n");
            }
			printStack(*head);
			break;
        //pop process
		case 2:
            if (pop(head) == 0) {
                printf("Process removed sucessfully\n");
            } else {
                fprintf(stderr, "Removal failed.\n");
            }
			printStack(*head);
			break;
        //error
		default:
			printf("Invalid choice.\n");
			break;
        }
        printf(": ");
		scanf("%u", &choice);
    }
    printf("Quitting...\n");
}


