#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct node_ { 
		int data;
			struct node_* next;
} Node;

/*
 *  * Parameters: 
 *   * head - The current head of the queue
 *    * data - The data to be enqueued
 *     *
 *      * Return: 
 *       * The new head of the queue
 *        *
 *         * The function will take in the head of
 *          * a queue and a new piece of data
 *           * and enqueue (insert at the end)
 *            * that data into the queue
 *             */
Node* enqueue(Node* head, int data);

int main(void) 
{
	Node* queue = NULL;
	int i;
	for (i = 0; i < 4; i++) 
	{
		queue = enqueue(queue, i);
	}

	for (i = 0; i < 4; i++) 
	{
		if (queue == NULL) 
			{
			printf(ANSI_COLOR_RED "The queue is to short!\n" ANSI_COLOR_RESET);
			return 1;
			}
		if (queue->data != i) 
			{
			printf(ANSI_COLOR_RED "The queue is out of order!\n" ANSI_COLOR_RESET);
			return 2;
			}
		Node* prev = queue;
		queue = queue->next;
		free(prev);
	}

	printf(ANSI_COLOR_GREEN "You have completed the prelab!\n" ANSI_COLOR_RESET);
	return 0;
}

Node* enqueue(Node* head, int data) 
{
	Node* current = head, *new; 
	new = (Node*)malloc(sizeof(Node));
	if(head==NULL)
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
