//Lab Code: Spring?
//PawPrint: IVNQM2
//Name: Ian Naeger
//Section: B
//Lab 9
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

Node* buildBalancedTree(int array[], int low, int high);
void quicksort(int array[] , int low , int high ); 
int partition( int array[] , int low , int high ); 
void preorder( Node* root ); 
void inorder( Node* root );
void postorder( Node* root );
void freeTree( Node* root ); 
int height( Node* root );
void printTree(Node* root, int depth);
void padding(int depth);
void printEveryPath( Node* root , int* path , int depth ); 

int main(int argc, char* argv[]) 
{
	srand(time(NULL));
	int array[10]; 
	int k , min , max; 	
	max = 0;
	min = 1000;
	for( k = 0; k < 10; k++ ) 
	{ 
		array[k] = ( rand() % 100 ) + 1;
	} 
	
	quicksort( array , 0  , 9 ); 
	Node* root = buildBalancedTree(array, 0 , 9);
	
	int H; 
	H = height( root ); 
	printf("The height of the tree is: %d \n", H ); 

	printf("PRE-ORDER: ");
	preorder( root ); 
	printf("\n");

	printf("IN-ORDER: ");
	inorder( root ); 
	printf("\n");

	printf("POST-ORDER: ");
	postorder( root ); 
	printf("\n");



	printf("\n\n\nBONUS!!!\n"); 
	printEveryPath( root , NULL , H );
	printf("\n"); 

	freeTree( root ); 
	return 0; 
}

Node* buildBalancedTree(int array[], int low, int high)
{
	if(low > high)
	{		
		return NULL; 
	}
	else
	{
		Node* head = malloc(sizeof(Node)); 
		int  top= (low+high)/2;
		head->data = array[top]; 
		head->left = buildBalancedTree(array, low, top-1); 
		head->right = buildBalancedTree(array, top+1, high);
		return head;
	}
	return NULL;
}

void quicksort( int array[], int low , int high )
{ 
	int piv; 
	if( high > low ) 
	{ 
		piv = partition( array , low , high );
		quicksort( array , low , piv-1 ); 
		quicksort( array , piv+1 , high ); 
	} 
} 

int partition( int array[] , int low , int high ) 
{ 
	int left , right; 
	int item , swap;
	left = low; 
	item = array[low];
	right = high; 
	while( left < right) 
	{ 
		while( array[left] <= item ) 
		{ 
			left++; 
		} 
		while( array[right] > item ) 
		{
			right--; 
		} 
		if( left < right ) 
		{ 
			swap = array[left]; 
			array[left] = array[right]; 
			array[right] = swap; 
		}
	}	
		array[low] = array[right]; 
		array[right] = item; 
		return right; 
} 
		
void preorder( Node* root )
{ 
	if( root == NULL ) 
	{ 
		return; 
	} 
	
	printf("%d " , root->data); 

	preorder( root->left ); 
	preorder( root->right ); 

} 

void inorder( Node* root ) 
{ 	
	if( root == NULL ) 
	{ 
		return; 
	} 

	inorder( root->left ); 

	printf("%d ", root->data ); 

	inorder( root->right ); 

} 

void postorder( Node* root ) 
{ 
	if( root == NULL ) 
	{ 
		return; 
	} 

	postorder( root->left ); 

	postorder( root->right ); 

	printf("%d ", root->data ); 

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

} 

int height( Node* root ) 
{ 
	if( root == NULL ) 
	{ 
		return 0; 
	} 
	else
	{ 
		int LH = height( root->left );
		int RH = height( root->right );

		if( LH > RH ) 
		{ 
			return (LH+1); 
		} 
		else 
		{ 
			return (RH+1); 
		} 
 	} 
} 	

void printTree(Node* root, int depth) {
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	} else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d\n", root->data);
		printTree(root->left, depth + 1);
	}
}

void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
}

void printEveryPath( Node* root , int* path , int depth ) 
{ 
	if( root->right == NULL && root->left == NULL ) 
	{ 
		printf("%d \n", root->data);
		return;
	}
	if( root->left != NULL ) 
	{ 
		printf("%d ", root->data); 
		printEveryPath( root->left, NULL, depth ); 
	} 
	if( root->right != NULL ) 
	{ 
		printf("%d ", root->data); 
		printEveryPath( root->right, NULL , depth ); 
	} 

}
