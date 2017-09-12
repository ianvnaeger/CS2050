//Ian Naeger
//Prelab 6

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define assert_with_msg(expression, msg) { \
		if (!(expression)) { \
					printf("\x1b[31m%s", msg);\
					assert(expression);\
				}\
}

typedef struct node_ {
		int data;
		struct node_* next;
} Node;

/* Parameters: 
 *   * filename - The name of an input file
 *    *
 *     * Return: The head of a linked list
 *      *
 *       * This function will build a linked list
 *        * from the numbers in the input file. 
 *         * Unlike previous weeks, the length of
 *          * this file is UNKNOWN. Every number 
 *           * in the file should be included in 
 *            * the linked list. 
 *             */
Node* build_list(const char* filename);
void print_List(Node* head);

/*
 *  * Because this is your first exposure to
 *   * linked lists, test code has been provided. 
 *    * After implementing build_list, simply run
 *     * ./a.out and if you can get the message at 
 *      * the bottom to print you are finished. 
 *       */
int main(void) 
{
	int i;
	//Generates an input file for you to use
	//	//with the numbers [1, 5)
	const char* filename = "prelab6_input_file.txt";
	FILE* fp = fopen(filename, "w");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "%d\n", i);
	}
	fclose(fp);
			
	//Calls your build_list function
	Node* head = build_list(filename);
		
	int y;	
	fopen(filename, "r");
	printf("Correct order: \n");
	for(i=0; i<5; i++)
	{
		fscanf(fp, "%d", &y);
		printf("%d\n", y);
	}
	print_List(head); 
	fclose(fp); 									
	
	//This code tests your linked list
	//for correctness. It will check
	//that each node has the correct 
	//value and free your memory as
	//it goes along. If the boolean 
	//condition in one of the assert
	//statements is false then it will
	//crash your program. 
	for (i = 4; i >= 0; i--) {
		char msg[100];
		sprintf(msg, "linked list is to short\ns %d nodes but should be 4\n", 4 - i);
		assert_with_msg(head != NULL, msg);
		sprintf(msg, "linked list nodes are not in correct order\nexpected current node to be %d but was actually %d\n", i, head->data);
		sprintf(msg, "linked list nodes are not in correct order\nexpected current node to be %d but was actually %d\n", i, head->data);
		assert_with_msg(head->data == i, msg);
		Node* prev = head;
		head = head->next;
		free(prev);
	}
	printf("Congratulations! You finished the prelab!\n");
	return 0;
}

Node* build_list( const char* filename ) 
{ 
	FILE* fp = fopen( filename, "r" ); 
	if( fp == NULL ) 
	{ 
		printf("Unable to open input!\n");
		return NULL;
	} 

	Node* StartPtr = NULL;
	Node* CurrentPtr = NULL;
//	Node* NextPtr = NULL; 
//	Node* PreviousPtr = NULL; 
	int num;

	while( !(feof(fp)))
	{
		Node* New = malloc( sizeof(Node) );

		fscanf( fp , "%d" , &num);

		if( StartPtr == NULL)
	   	{ 
			StartPtr = New;
			StartPtr->data = num; 
			StartPtr->next = NULL;
		    CurrentPtr = StartPtr;
		} 
		else 
		{ 
			StartPtr = New; 
			StartPtr->next = CurrentPtr; 
			StartPtr->data = num;
			CurrentPtr = StartPtr;
		} 
	}
	fclose(fp); 
	return StartPtr->next;

}

void print_List( Node* head ) 
{ 
	if( head == NULL ) 
	{ 
		printf("Couldn't print. Link-List is NULL\n");
		return;
	} 
	Node* ptr = head->next; 
	printf("Node 1: %d\n", head->data);
	int p = 2; 
	while( ptr != NULL ) 
	{ 
		printf("Node %d: %d\n", p, ptr->data); 
		ptr = ptr->next; 
		p++; 
	} 
} 
