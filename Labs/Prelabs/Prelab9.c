#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

Node* buildBalancedTree(int array[], int low, int high);
void printTree(Node* root, int depth);
void padding(int depth);

int main(int argc, char* argv[]) {
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	Node* root = buildBalancedTree(array, 0, 6);
	printTree(root, 0);
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
