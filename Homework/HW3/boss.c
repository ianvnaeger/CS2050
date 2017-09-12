#include "game.h"

//Knock yourself out boys and girls. 

Boss* loadBoss()
{
	FILE* fp = fopen("Boss.txt","r");
	if( fp == NULL )
	{
		printf("could not open the boss file\n");
		return NULL;
	} //Load file and error checks it

	Boss* boss = malloc( sizeof(Boss) );
	boss->root = NULL;
	fscanf(fp, "%s | %d | %d | %d | %d", boss->name, &boss->maxHealth, &boss->baseDefense, &boss->baseAttack, &boss->baseSpeed);
	boss->health = boss->maxHealth; 
	//makes boss, then loads it with proper characteristics
	
	while( feof(fp) == 0 )
	{
		DecisionTreeNode* newD = malloc( sizeof(DecisionTreeNode) );
		newD->left = NULL;
		newD->right = NULL;
		newD->FirstAction = NULL;
		ActionNode* front = newD->FirstAction;
		//Makes new decision

		int len, i;
		fscanf(fp, "%d | %d | %d", &newD->healthFloor, &newD->healthCeiling, &len);
		//fills new decision with info
		for( i = 0; i < len; i++ )
		{
			int dec;
			ActionNode* newA = malloc( sizeof(ActionNode) );
			newA->next = NULL;
			fscanf(fp, "%d", &dec);
			switch( dec )
			{
				case 0:
					newA->decision = 0;
					break;
				case 1:
					newA->decision = 1;
					break;
				case 2:
					newA->decision = 2;
					break;
			}//Had to use switch because enums were being dumb...

			front = addActionToList( front, newA );

		}//Makes new decision and adds it to action list
			newD->FirstAction = front; 
			boss->root = addNodeToTree( boss->root, newD );
	}

		fclose(fp);
		return boss;		
}

ActionNode* addActionToList( ActionNode* front, ActionNode* newAction )
{
	ActionNode* currentPtr = front; 
	if( currentPtr == NULL )
	{
			front = newAction; 
		 	return front;
	}
	else
	{
		while( currentPtr->next != NULL )
		{
			currentPtr = currentPtr->next;
		}
	}
	newAction->next = NULL;
	currentPtr->next = newAction;

	return front;
} // Finds the end of the Action lists and puts the action on the end

DecisionTreeNode* addNodeToTree( DecisionTreeNode* root, DecisionTreeNode* newNode )
{
	if( root == NULL )
	{
		return newNode;
	}
	else if( newNode->healthCeiling < root->healthFloor ) 
	{
		root->left = addNodeToTree( root->left, newNode );
	}
	else if( newNode->healthFloor > root->healthCeiling )
	{
		root->right = addNodeToTree( root->right, newNode );
	}

	return root;
}// Looks for a place to put decision on the tree and puts it there

ActionNode* fetchNewList( Boss* boss, DecisionTreeNode* root )
{
	ActionNode* act = malloc( sizeof(ActionNode) ); 

	if(root == NULL || boss == NULL)
	{
		return NULL; 
	}
	if(boss->health <= root->healthCeiling && boss->health >= root->healthFloor)
	{
		act = root->FirstAction; 
	}
	else if(boss->health > root->healthCeiling)
	{
		act = fetchNewList(boss, root->right);
	}
	else if(boss->health < root->healthFloor)
	{
		act =  fetchNewList(boss, root->left);
	}

	return act;
}// Searches tree for appropriate action list, then returns that

void freeBossTree(DecisionTreeNode* root)
{
	if(root != NULL)
	{
		freeBossTree(root->left); 
		freeBossTree(root->right); 
		freeActionListInNode(root->FirstAction); 
		free(root); 
	}
}// Deletes all of the boss tree via Recusion

void freeActionListInNode(ActionNode* head)
{
	ActionNode* prev;

	while(head != NULL && head->next != NULL)
	{
		prev = head;
		head = head->next;
		free(prev);
	}

	free(head); 
}// Walks through the Valley of Dead Actions and torches them on the way out

