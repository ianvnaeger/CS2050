//Lab Code: Heating Up
//Pawprint: IVNQM2
//Name: Ian Naeger
//Section: B 
//Lab: 7
#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct node_ { 
		int data;
			struct node_* next;
} Node;

Node* enqueue(Node* head, int data);
int dequeue(Node** frontPtr); 
void printQueue(Node* front);
void freeQueue(Node* front);
Node* filterEven(Node* head); 

int main(void) 
{
	int select;
	Node* queue = NULL;
	printf(" Enter 1 to Enqueue \n Enter 2 to Dequeue \n Enter 3 to quit \n >"); 
	scanf("%d", &select); 

	while( select != 3 )
	{ 
		if( select == 1 ) 
		{ 
			int input;
			printf(" Enter a number to Enqueue:"); 
			scanf("%d", &input); 
			queue = enqueue( queue , input );
			printQueue( queue );
			printf(" >");
			scanf("%d", &select);
		} 
		else if( select == 2 ) 
		{ 
			int deq;
		    Node** queuePtr = &queue;	
			deq = dequeue( queuePtr ); 
			printf(" %d was Dequeued\n", deq);
			printQueue( queue );
			printf(" >");
			scanf("%d", &select);
		} 
	} 

	printf("BONUS!!!\n"); 
	queue = filterEven( queue ); 
	printQueue( queue ); 

	freeQueue( queue ); 
	
	return 0;	 
}

Node* enqueue(Node* head, int data) 
{
	Node* current = head, *new; 
	new = (Node*)malloc(sizeof(Node));
	if(head == NULL)
	{
		new->next = NULL;
		new->data = data;
		return new;
	}
		
	while(current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	new->next = NULL;
	new->data = data; 
	return head; 
}

int dequeue(Node** frontPtr)
{  
	Node* hold = NULL;
	int data; 
	
	data = (*frontPtr)->data; 
	hold = *frontPtr;
	*frontPtr = (*frontPtr)->next;
	free(hold); 
	
	return data; 
} 
	
void printQueue( Node* front ) 
{ 
	if( front == NULL ) 
	{ 
		printf("Couldn't Print. Queue is NULL.\n"); 
		return;
	} 
	Node* ptr = front->next;
	printf("%d -> ", front->data ); 
	while( ptr != NULL ) 
	{ 
		printf("%d -> ", ptr->data); 
		ptr = ptr->next;
	} 
	printf("NULL\n"); 

} 

void freeQueue( Node* front ) 
{ 
	Node* Current = front; 
	Node* Holder = NULL; 

	while( Current != NULL ) 
	{ 
		Holder = Current->next;
		free( Current ); 
		Current = Holder; 
	} 
} 

Node* filterEven(Node* head) 
{ 
	if( head->next == NULL ) 
	{ 
		return head; 
	} 
	else if( (head->data % 2) == 0)
	{
	   return filterEven(head->next); 
	}
	else
	{ 
		head->next = filterEven( head->next );
		return head;	
	} 
} 
