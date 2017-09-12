//Lab Code: Trouble
//Pawprint: IVNQM2
//Name: Ian Naeger
//Section: B
//Lab 6

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

Node* build_list(const char* filename);
void print_list(Node* head);
void multiply_by( Node* head, int val );
void free_list( Node* head ); 
Node* reverse_list( Node* head ); 
// Prototypes and structs naming

int main( int argc , char* argv[] ) 
{
	if( argc != 2 ) 
	{ 
		printf("\n Insufficient Arguments! \n"); 
		return 0; 
	} 
	
	char* filename = malloc( strlen( argv[1] )*sizeof(char) ); 
	filename = argv[1]; 
// Error checking and file getting	

	Node* head = build_list(filename);
// Builds the linked list

	int k , j;	
	FILE* fp = fopen(filename, "r");

	printf("\nCorrect Order: \n");
	while( !(feof(fp)))
	{
		fscanf(fp, "%d", &k);
		printf("%d\n", k);
	}
// Prints the file out

	printf("\nFirst Print: \n");
	print_list( head );
// Prints the unmoddified list

	printf("\nEnter number to multiply by:"); 
	scanf("%d", &j );
	printf("\nMultiplied (By %d) Print: \n", j );
   	multiply_by( head , j ); 
	print_list( head );
// Prints the multiplied list 	

	printf("\nBonus (Reversed) Print: \n");
	head = reverse_list( head );
	print_list( head ); 
// Prints the reversed list 
	
	free_list( head ); 
	fclose(fp); 									
// Frees the list and closes the file 

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

void print_list( Node* head ) 
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

void multiply_by( Node* head , int val) 
{ 
	Node* StartPtr = head;
	Node* CurrentPtr = StartPtr;

	while( CurrentPtr != NULL) 
	{ 
		CurrentPtr->data = CurrentPtr->data * val; 
		CurrentPtr = CurrentPtr->next;
	} 
} 

void free_list( Node* head ) 
{ 
	Node* StartPtr = head; 
	Node* CurrentPtr = StartPtr; 
	Node* HolderPtr;

	while( CurrentPtr != NULL ) 
	{ 
		HolderPtr = CurrentPtr->next; 
		free(CurrentPtr); 
		CurrentPtr = HolderPtr; 
	} 
} 

Node* reverse_list(Node* head) 
{ 
	Node* StartPtr = head; 
	Node* CurrentPtr = StartPtr; 
	Node* PreviousPtr = NULL; 
	Node* NextPtr = NULL; 

	while( CurrentPtr != NULL ) 
	{ 
		NextPtr = CurrentPtr->next; 
		CurrentPtr->next = PreviousPtr; 
		PreviousPtr = CurrentPtr; 
		CurrentPtr = NextPtr; 
	} 
	head = PreviousPtr;
    return head;	
} 

