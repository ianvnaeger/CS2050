// Lab Code: Chicago
// Pawprint: IVNQM2
// Name: Ian Naeger
// Section: B
// Lab 8

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_ {
		int data;
		struct node_* left;
		struct node_* right;
} Node;

void printTree(Node* root, int depth);
Node* insert(Node* root, int data);
Node* buildTree( char* filename ); 
int min( Node* root ); 
Node* delete( Node* root , int data); 
void freeTree( Node* root );
Node* flipTree( Node* root ); 
// Prototypes, structs, and library defining

int main( int argc , char* argv[] ) 
{
	if( argc != 2 )
	{ 
		printf("\n INSUFFICENT ARGUMENTS!!! \n");
		return 0; 
	} 

	char* filename = malloc( strlen( argv[1] )*sizeof(char) );
	filename = argv[1]; 
// Filename retreval 
	Node* root = NULL;
	int del;

	root =	buildTree( filename ); 
	printf(" Initial Tree: \n "); 
	printTree( root , 0 ); 
// Builds the tree from the input and prints it

	printf(" Enter a number to delete: \n"); 
	scanf("%d", &del); 

	root = delete( root , del ); 
	printf(" Tree without %d: \n", del );
	printTree( root , 0 ); 
// Gets number to delete, deletes it in the tree, and prints the new tree

	/* BONUS!!! */
	printf("\n\n BONUS!!!!! \n\n"); 
	root = flipTree( root ); 
	printTree( root , 0 ); 

	freeTree( root ); 
// Flips the tree, prints it, and then frees it

	return 0;
}

Node* insert(Node* root, int data) 
{
	if(root == NULL)
	{
		Node* new = malloc(sizeof(Node)); 
		new->data = data; 
		new->left = NULL;
		new->right = NULL; 
		return new; 
	}

// Starts a new tree
	if(data < root->data)
	{
		root->left = insert(root->left, data); 
		return root;
	}
	else if(data > root->data)
	{
		root->right = insert(root->right, data); 
		return root; 
	}
	return root;
// Orders nodes so that if you go left it is less than and if you go right it is greater than
}

Node* buildTree( char* filename ) 
{ 
	FILE* fp = fopen( filename , "r" ); 
	if( fp == NULL ) 
	{ 
		printf("Unable to open input!\n"); 
		return NULL; 
	} 

	int num; 

	Node* root = malloc( sizeof(Node) );
	root = NULL; 

	while( !(feof(fp)) ) 
	{ 
		fscanf( fp , "%d", &num); 

		root = insert( root , num ); 
	} 

	fclose(fp); 
	return root;
// Takes an input file, scans it for values, then puts the values into a tree in order
} 

int min( Node* root ) 
{ 
	if( root == NULL ) 
	{ 
		return 0;
	} 

	Node* Current = root;

	while( Current->left != NULL )
	{ 
		Current = Current->left; 
	} 
	return Current->data; 
// Finds the minimum value in a tree
} 

Node* delete( Node* root , int data ) 
{ 
	Node* move;
	Node* prev; 
	Node* hold; 

	if( root == NULL ) 
	{ 
		printf("\n Empty Tree\n"); 
		return root;
	} 
	else
	{ 
		move = root;
		prev = move; 

		while( move->data != data ) 
		{ 
			prev = move; 
			if( data < move->data ) 
			{ 
				move = move->left; 
			}
			else
			{ 
				move = move->right;
			} 
		} 

		if( move->left != NULL && move->right != NULL ) 
		{ 
			hold = move->right; 
			while( hold->left != NULL ) 
			{ 
				prev = hold; 
				hold = hold->left;
			} 
			move->data = hold->data;
			hold->data = '\0';
			move = hold;
		   	return root;	
		} 
		if( move->left == NULL && move->right == NULL )
		{ 
			if( prev->right == move) 
			{ 
				prev->right = NULL; 
			} 
			else 
			{ 
				prev->left = NULL; 
			} 
			free(move); 
			return root; 
		} 
		if(  move->left == NULL && move->right != NULL )
		{ 
			if( prev->left == move ) 
			{ 
				prev->left = move->right; 
			} 
			else 
			{ 
				prev->right = move->right; 
			} 
			free(move); 
			return root; 
		} 
		if( move->left != NULL && move->right == NULL )
		{ 
			if( prev->left == move ) 
			{ 
				prev->left = move->left; 
			} 
			else 
			{ 
				prev->right = move->left; 
			} 
			free(move); 
			return root;
		}
	   	return root;	
	}
// Finds a value and deletes it in the tree without destroying the tree
} 

void freeTree( Node* root ) 
{ 
	if( root == NULL ) 
	{ 
		return; 
	} 

	freeTree( root->left ); 
	freeTree( root->right ); 

	free( root ); 
// Frees the memory taken up by the tree in a logical order, as to not create memory leaks
} 

Node* flipTree( Node* root ) 
{ 
	if( root == NULL ) 
	{ 
		return NULL; 
	} 
	else 
	{ 
		Node* new = malloc( sizeof(Node) ); 

		new->data = root->data;
		new->left = flipTree(root->right);
	    new->right = flipTree(root->left);

		return new;
	}	
// Takes a tree and makes it into its mirror
} 

void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
// Given Function
}

void printTree(Node* root, int depth) {
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	} else if( (root->data) == '\0' ){ 
		padding(depth); 
		printf("~\n"); 
	} else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d\n", root->data);
		printTree(root->left, depth + 1);
	}
// Given Function, with modification to print deleted tree correctly
}	

