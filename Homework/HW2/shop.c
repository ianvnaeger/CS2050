#include "game.h"

Shop* loadShop()
{

	FILE* fp = fopen("Items.txt", "r"); 
	if(fp == NULL) 
	{
		printf("Unable to load items\n");
		return NULL;
	}
// Error Checking
	
	int k;
	Shield *head=NULL, *prev, *new; 
	for(k = 0; k < NUMSHIELDS; k++)
	{
		new = (Shield*)malloc(sizeof(Shield)); 
		if(head==NULL)
		{
			head = new;  
			new->nextShield = NULL; 
			new->prevShield = NULL;
		}
		else
		{
			new->nextShield = NULL; 
			new->prevShield = prev;
			prev->nextShield = new; 
		}
		fscanf(fp, "%s | %d | %d", (new->name), &(new->cost), &(new->defense));
		prev = new;
	}
// Get Sheild Nodes with name price and defense	

	Sword *headS=NULL, *prevS, *newS;
	for(k = 0; k<NUMSWORDS; k++)
	{
		newS = (Sword*)malloc(sizeof(Sword)); 
		if(headS==NULL)
	 	{
			headS = newS;  
			newS->nextSword = NULL; 
			newS->prevSword = NULL;
		}
		else
		{
			newS->nextSword = NULL; 
			newS->prevSword = prevS;
			prevS->nextSword = newS;
		}
		fscanf(fp, "%s | %d | %d", (newS->name), &(newS->cost), &(newS->attack));
		prevS = newS;
	}
// Get Sword nodes with name price and attack

	fclose(fp);						
		
	Shop* y = malloc(sizeof(Shop));					
	y->headSword = headS;
	y->headShield = head; 
	y->headShield = head; 

	printf(" \n\n\nBONUS!!!\n\nNodes contain both next and previous pointers!\n\n\n");
	
	return y; 													
// Give shop the heads of the sheild and sword nodes											
}

void destroyShop(Shop* shop)
{
	Shield* shldCurrent = shop->headShield;
	Shield* shldHolder = NULL; 
	Sword* swrdCurrent = shop->headSword;
	Sword* swrdHolder = NULL; 

	while( shldCurrent != NULL ) 
	{ 
		shldHolder = shldCurrent->nextShield;
		free( shldCurrent );
		shldCurrent = shldHolder;
	} 
// Destroy the Sheild nodes

	while( swrdCurrent != NULL ) 
	{ 
		swrdHolder = swrdCurrent->nextSword;
		free( swrdCurrent );
		swrdCurrent = swrdHolder;
	} 
// Destroy the Sword nodes	

	free( shop );
// Gives the shop a sock ( Harry Potter Reference for freeing it)
}

void sortShields(Shield** shields)
{
	if(*shields == NULL)
	{
		printf("Unable to sort because list is NULL\n");
		return;
	}
// Error Checking

	int i=0, k;
	Shield* cur = (*shields), *head = (*shields), *comp, *swap, *temp, *prev; 
	while( cur != NULL && cur->nextShield != NULL )
	{
		prev = cur;
		comp = cur->nextShield; 
														
		while( prev != NULL )
		{
			if( comp->cost < prev->cost )
			{	
				temp = comp;
				swap = comp->prevShield;
				if( temp->nextShield != NULL ) 
				{
					(temp->nextShield)->prevShield = swap;
				}
				if( swap->prevShield !=NULL )
				{
					(swap->prevShield)->nextShield = temp;
				}
				swap->nextShield = temp->nextShield; 
				temp->prevShield = swap->prevShield;
				temp->nextShield = swap; 
				swap->prevShield = temp;
				prev = comp->prevShield;
				continue;
			}

			comp = prev;
			prev = prev->prevShield;
		}

		while( head->prevShield != NULL )
		{
			head = head->prevShield; 
		}	if( *shields == NULL )

		cur = head;
		
		for( k = i; k >= 0; k--)
		{
			cur = cur->nextShield;
		}
	
		i++;
	}
// Takes your sheild nodes and sorts them by rearranging the nodes
}

void sortSwords(Sword** swords)
{

	if( *swords == NULL)
	{
		printf("Unable to sort because list is NULL\n");
		return;
	}
//Error Checking

	int i=0, k;
	Sword* cur = (*swords), *head = (*swords), *comp, *swap, *temp, *prev; 
	while(cur != NULL && cur->nextSword != NULL)
	{
		prev = cur;
		comp = cur->nextSword; 
														
		while( prev != NULL )
		{
			if( comp->cost < prev->cost )
			{	
				temp = comp;
				swap = comp->prevSword;
				if( temp->nextSword != NULL ) 
				{
					(temp->nextSword)->prevSword = swap;
				}
				if( swap->prevSword !=NULL )
				{
					(swap->prevSword)->nextSword = temp;
				}
				swap->nextSword = temp->nextSword; 
				temp->prevSword = swap->prevSword;
				temp->nextSword = swap; 
				swap->prevSword = temp;
				prev = comp->prevSword;
				continue;
			}

			comp = prev;
			prev = prev->prevSword;
		}

		while(head->prevSword != NULL)
		{
			head = head->prevSword; 
		}
		
		cur = head;
		
		for(k = i; k>=0; k--)
		{
			cur = cur->nextSword;
		}
	
		i++;
	}
// Takes your sword nodes and rearranges them by moving what pointers point to what nodes
}

void printShields(Shield* shields)
{
	int k = 1; 
	Shield* Current = shields; 

	while( Current != NULL )
	{ 
		printf("%d - %s \n\t\tCost: %d \n\t\tDefense: %d\n", k , Current->name , Current->cost , Current->defense );
	Current = Current->nextShield;
		k++; 
	} 
// Prints off the different shields and their info from a linked list
}

void printSwords(Sword* swords)
{
	int k = 1;
   	Sword* Current = swords;	

	while( Current != NULL )
	{ 
		printf("%d - %s \n\t\tCost: %d \n\t\tAttack: %d\n", k , Current->name , Current->cost , Current->attack );
		Current = Current->nextSword;
		k++;
	} 
// Prints off the different swords and their info from a linked list
}

Sword* removeSwordFromList(Sword** swords, int choice)
{
	Sword* Current = (*swords); 
	Sword* Next = NULL;
	Sword* Previous = NULL;
	int k;

	for( k = 1; k <= (choice-1); k++ )
	{ 
		Current = Current->nextSword; 
	} 
	// Goes through the linked list to find the chosen sword

	Previous = Current->prevSword;
	Next = Current->nextSword; 
	Previous->nextSword = Next;
	Next->prevSword = Previous; 

	return Current;   
	// Rearranges linked list to remove the chosen node and then returns it
}

Shield* removeShieldFromList(Shield** shields, int choice)
{
	Shield* Current = (*shields); 
	Shield* Next = NULL;
	Shield* Previous = NULL;
	int k;

	for( k = 1; k <= (choice-1); k++ )
	{ 
		Current = Current->nextShield; 
	} 

	Previous = Current->prevShield;
	Next = Current->nextShield; 
	Previous->nextShield = Next;
	Next->prevShield = Previous; 

	return Current;   
// Rearranges linked list to remove the chosen node and then returns it
}

/***************************START OF FUNCTIONS GIVEN TO YOU**********************************/

void freeHeroesAndItems(Hero* heroes)
{
	int i;
	for(i = 0; i < NUMCHOSENHEROES; i++)
	{
		if(heroes[i].heroSword != NULL)
		{
			free(heroes[i].heroSword);
		}
		if(heroes[i].heroShield != NULL)
		{
			free(heroes[i].heroShield);
		}
	}
	free(heroes);
}

void goShopping(Hero* heroes, Shop* shop)
{

	printf("\n\nNow, you will select a sword and shield for your heroes.\n");

	int firstPass = 1; 

	int bank = STARTINGBANKVALUE;

	while(1)
	{
		printf("Which would you like to look at?\n");
		printf("1: Swords\n2: Shields\n3: Continue to fight\n");
		printf("> ");
		int choice; 
		scanf("%d", &choice);
		while(choice < 1 || choice > 3)
		{
			printf("Invalid choice. Select again: \n");
			printf("> ");
			scanf("%d", &choice);
		}

		if(choice == 3)
		{
			if(firstPass == 1)
			{
				printf("Are you sure you don't want to buy anything?\n");
				printf("1: yes\n2: no\n");
				printf("> ");
				scanf("%d", &choice);
				while(choice < 1 || choice > 2)
				{
					printf("Invalid choice. Select again: \n");
					printf("> ");
					scanf("%d", &choice);
				}
			}
			else
			{
				choice = 1;
			}

			if(choice == 1)
			{
				destroyShop(shop);
				return;
			}
		}
		else if(choice == 2)
		{
			printf("Do you want it sorted (1) or unsorted? (2)\n");
			printf(">");
			int sortChoice;
			scanf("%d", &sortChoice);
			while(sortChoice != 1 && sortChoice != 2)
			{
				printf("Invalid choice, choose again: ");
				printf(">");
				scanf("%d", &sortChoice);
			}

			if(sortChoice == 1)
			{
				sortShields(&(shop->headShield));
			}
			

			while(1)
			{
				printShields(shop->headShield);
				
				while(1)
				{
					printf("\nBudget: %d\n", bank);
					printf("Select a shield (-1 to go back): \n");
					printf("> ");
					scanf("%d", &choice);
	
					while((choice < 1 || choice > NUMSHIELDS) && choice != -1)
					{
						printf("Invalid choice. Select again: \n");
						printf("> ");
						scanf("%d", &choice);
					}
				
					if(choice != -1)
					{
						if(findShieldPrice(shop->headShield, choice) > bank)
						{
							printf("You don't have enough money for that!\n");
						}
						else break;
					}
					else break;
				}

				if(choice == -1)
				{
					break;
				}
				else
				{
					int heroChoice; 

					while(1)
					{
						printHeroes(heroes, NUMCHOSENHEROES);
						printf("Which hero do you want to have the item? (-1 to go back): \n");
						printf("> ");
						scanf("%d", &heroChoice);

						while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
						{
							printf("Invalid choice. Select again: \n");
							printf("> ");
							scanf("%d", &heroChoice);
						}

						if(heroChoice == -1)
						{
							break;
						}

						if(heroes[heroChoice - 1].heroShield != NULL)
						{
							printf("That hero already has a shield. Choose again.\n");
						}
						else
						{
							break;
						}

					}
					

					if(heroChoice == -1)
					{
						break;
					}
					else
					{
						Shield* item = removeShieldFromList(&(shop->headShield), choice);
						heroes[heroChoice - 1].heroShield = item;
						bank -= item->cost;
						firstPass = 0;
					}
				}
			}
		}
		else if(choice == 1)
		{
			printf("Do you want it sorted (1) or unsorted? (2)\n");
			printf(">");
			int sortChoice;
			scanf("%d", &sortChoice);
			while(sortChoice != 1 && sortChoice != 2)
			{
				printf("Invalid choice, choose again: ");
				printf(">");
				scanf("%d", &sortChoice);
			}

			if(sortChoice == 1)
			{
				sortSwords(&(shop->headSword));
			}
			
			while(1)
			{
				printSwords(shop->headSword);
				
				while(1)
				{
					printf("\nBudget: %d\n", bank);
					printf("Select a sword (-1 to go back): \n");
					printf("> ");
					scanf("%d", &choice);
	
					while((choice < 1 || choice > NUMSWORDS) && choice != -1)
					{
						printf("Invalid choice. Select again: \n");
						printf("> ");
						scanf("%d", &choice);
					}
				
					if(choice != -1)
					{
						if(findSwordPrice(shop->headSword, choice) > bank)
						{
							printf("You don't have enough money for that!\n");
						}
						else break;
					}
					else break;
				}

				if(choice == -1)
				{
					break;
				}
				else
				{
					int heroChoice; 

					while(1)
					{
						printHeroes(heroes, NUMCHOSENHEROES);
						printf("Which hero do you want to have the item? (-1 to go back): \n");
						printf("> ");
						scanf("%d", &heroChoice);

						while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
						{
							printf("Invalid choice. Select again: \n");
							printf("> ");
							scanf("%d", &heroChoice);
						}

						if(heroChoice == -1)
						{
							break;
						}

						if(heroes[heroChoice - 1].heroSword != NULL)
						{
							printf("That hero already has a sword. Choose again.\n");
						}
						else
						{
							break;
						}
					}
					if(heroChoice == -1)
					{
						break;
					}
					else
					{
						Sword* item = removeSwordFromList(&(shop->headSword), choice);
						heroes[heroChoice - 1].heroSword = item;
						bank -= item->cost;
						firstPass = 0;
					}
				}
			}
		}
	}
}

int findSwordPrice(Sword* swords, int choice)
{
	int i = 1;
	while(i < choice)
	{
		swords = swords->nextSword;
		i++;
	}
	return swords->cost;
}

int findShieldPrice(Shield* shields, int choice)
{
	int i = 1;
	while(i < choice)
	{
		shields = shields->nextShield;
		i++;
	}
	return shields->cost;
}
