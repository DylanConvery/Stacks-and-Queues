#include <stdio.h>
#include <stdlib.h>

//FIFO data structure
typedef struct Queue {
	unsigned pid;      
	struct Queue *next_node;
} Queue;

//forward declarations
int enqueue(Queue** head, Queue** tail, unsigned pid);
int dequeue(Queue** head, Queue** tail);
int isEmpty(Queue* head);
void printQueue(Queue* head);
void menu(Queue** head, Queue** tail);

int main() {
    //head of queue
	Queue* head = NULL; 
    //tail of queue
	Queue* tail = NULL; 
    //start queue
    menu(&head, &tail);
    return 0;
}

// insert a node at queue tail
int enqueue(Queue** head, Queue** tail, unsigned pid) {
    //allocate memory for new process
	Queue* newPtr = malloc(sizeof(Queue));
    //check to make sure we had sufficient memory
	if (newPtr != NULL) {
        //set up new node with relevent data
		newPtr->pid = pid;
		newPtr->next_node = NULL;
		// if queue is empty, insert node at head
		if (isEmpty(*head)) {
			*head = newPtr;
		} else {
            //set last node in queue to point to the new last node 
            //i.e - 0->1->2->3->NULL
			(*tail)->next_node = newPtr;
		}
        //set tail to now point at the new last node
		*tail = newPtr;
        return 0;
	}
    //indicte failure
    return -1;
}

// remove node from queue head
int dequeue(Queue** head, Queue** tail) {
    //check if queue is empty so we don't dereference a null pointer
    if (!isEmpty(*head)) {
        //store first node in queue
        Queue* tempPtr = *head;
        //move head forward in the queue
        *head = (*head)->next_node;
        //check if queue is now empty
        if (isEmpty(*head)) {
            //reset tail so we don't end up trying to access freed memory
            *tail = NULL;
        }
        //deallocate the first node
        free(tempPtr);
        return 0;
    }
    //indicte failure
    return -1;
}

//check if queue is empty
int isEmpty(Queue* head) {
    //if head is NULL, return true, otherwise return false
    return head == NULL;
}

// print the queue
void printQueue(Queue* head) {
    //check if queue is empty so we don't dereference a null pointer
	if (isEmpty(head)) {
		printf("Queue is empty.\n");
	} else {
		printf("The queue is: ");
        //walkthrough stack until we hit the end
		while (head != NULL) {
			printf("PID(%u) --> ", head->pid);
			head = head->next_node;
		}
		printf("NULL\n");
	}
}

//menu for queue operation
void menu(Queue** head, Queue** tail) {
	static unsigned pid = 1;
	unsigned choice;
    //print menu instructions
    printf(
        "***QUEUE MENU***\n"
		"1. Add Process\n"
		"2. Remove Process\n"
		"3. Exit\n"
        ": "
    );
    //get the users choice
	scanf("%u", &choice);
	//execute user choice
	while (choice != 3) {
		switch (choice) {
		//enqueue process
		case 1:
			if(enqueue(head, tail, pid) == 0) {
                printf("Process added sucessfully.\n");
                pid++;
            } else {
	        	fprintf(stderr, "Process not added. No memory available.\n");
            }
			printQueue(*head);
			break;
        //dequeue process
		case 2:
			if(dequeue(head, tail) == 0) {
                printf("Process removed sucessfully\n");                
            } else {
                fprintf(stderr, "Removal failed.\n");
            }
			printQueue(*head);
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