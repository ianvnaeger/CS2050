//don't add to this list. You won't need anything else.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//for expandable use.
#define NUMHEROES 6
#define NUMCHOSENHEROES 3
#define MAXNUMSAVEFILES 5
#define MAXPLAYERNAME 20

//for locating the save file
typedef enum f_
{
	EXIST,
	DOESNOTEXIST
} FileFinder;

//MVP OF THE HOMEWORK
//Mostly self-expalanatory pieces. 
typedef struct hero_
{
	char name[40];
	int health;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
} Hero;

//Not used in this HW, just defined to prep for later HWs
typedef struct boss_
{
	char name[40];
	int health;
	int maxHealth;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
} Boss;


//THAT'S A LOT OF FUNCTIONS. GET EXCITED.
void deleteFile(int choice, char* filename);
void saveFileData(int choice, char* filename, Hero* heroes, char* playerName, int progress);
char* getPlayerName();
Hero* loadSavedData(char* filename);
Hero* loadInitialData();
Hero* pickHeroes(Hero* heroes);
void sortHeroes(Hero* heroes);
void printHeroes(Hero* heroes, int numHeroes);
//The following ones are all done for you. Just call them as instructed. 
FileFinder findSaveFile();
void loadSavedGameHandler();
void DeleteSavedGameHandler();
void loadGameStateData(char*** names, int** states, int* fileCount);
char* choiceToFile(int num);
void freeMemory(char** names, int* states);
void startNewGame();
void playGame(Hero* heroes, char* playerName, Boss* boss, int progress, int choice);
int chooseSaveFile();

int main(void)
{
	FileFinder ff = findSaveFile(); 
	int select;

	if( ff == EXIST ) 
	{ 
		printf("Welcome to the Gauntlet! \nCan you save the Kingdom?\n"); 
		printf("Select an option. \n 1) Start a New Game \n 2) Load a Saved Game \n 3) Delete a saved file \n 4) Quit \n"); 
		scanf( "%d", &select ); 

		while( select >= 5 || select <= 0 ) 
		{ 
			printf("Invalid Option. Please Try Again."); 
			fscanf( stdin, "%d", &select ); 
		} 

		if( select == 1 ) 
		{ 
			startNewGame(); 
		} 
		else if( select == 2 ) 
		{ 
			loadSavedGameHandler(); 
		} 
		else if( select == 3 ) 
		{ 
			DeleteSavedGameHandler(); 
		} 
		else if( select == 4 )
		{ 
			return 0; 
		} 
	}  

	if( ff == DOESNOTEXIST ) 
	{ 
		printf("Welcome to the Gauntlet! \nCan you save the Kingdom?\n"); 
		printf("Select an option. \n1) Start a New Game \n2) Quit \n"); 
		scanf( "%d", &select ); 

		while( select >= 3 || select <= 0 ) 
		{ 
			printf("Invalid Option. Please Try Again."); 
			fscanf( stdin, "%d", &select ); 
		} 

		if( select == 1 ) 
		{ 
			startNewGame(); 
		} 
		else if( select == 2 ) 
		{ 
			return 0; 
		} 
	} 

	return 0; 
}

void deleteFile(int choice, char* filename)
{
	int k , r; 
	char gamestate[] = "gamestat.txt"; 

	r = remove( filename );
	if( r == 0 ) 
	{ 
		printf("File Successfully Deleted");
	} 
	else 
	{ 
		printf("Error: Unable to delete file"); 
	} 

	FILE* fp = fopen( gamestate, "w"); 

	char** names; 

	for( k = 0; k < MAXNUMSAVEFILES; k++ ) 
	{ 
		*(names + k)= malloc( MAXPLAYERNAME * sizeof( char ) ); 
	} 

	int *states;

	int nf; 

	loadGameStateData( &names , &states , &nf ); 

	nf--; 
	
	*( names + (choice - 1)) = "000"; 

	states[ choice - 1 ] = 0; 

	fprintf( fp, "%d", nf ); 

	for( k = 0; k < (choice - 1); k++ ) 
	{ 
		fprintf( fp, "%s | %d\n" , *( names + k) , states[k] ); 
	} 
	
	for( k = choice; k < MAXNUMSAVEFILES; k++ ) 
	{ 
		fprintf( fp, "%s | %d\n" , *( names + k) , states[k] ); 
	} 

}

void saveFileData(int choice, char* filename, Hero* heroes, char* playerName, int progress)
{
	FILE* gsfp = fopen( "gamestate.txt" , "r+" ); 
	int k , x;
	char** names = (char**)malloc( sizeof(char)* MAXNUMSAVEFILES*MAXPLAYERNAME); 

	for( k = 0; k < MAXNUMSAVEFILES; k++) 
	{ 
		names[k] = malloc( MAXPLAYERNAME * sizeof( char ) );
	} 

	int *states = (int*)malloc(sizeof(int) * MAXNUMSAVEFILES);  
	
	int nf; 

	fscanf( gsfp , "%d", &nf); 

	printf("bebug 1\n");

//	loadGameStateData( &names , &states , &nf );
	for( x = 0; x < MAXNUMSAVEFILES; x++ )
	{ 
		fscanf( gsfp , "%s | %d", names[x], &states[x]); 
	} 
	fseek( gsfp , 0 , SEEK_SET); 

	if( progress == 1 ) 
	{ 
			nf++; 

			*(names + (choice - 1)) = playerName; 

			states[ choice - 1 ] = progress; 

			fprintf( gsfp, "%d", nf );

			for( x = 0; x < MAXNUMSAVEFILES; x++ )
			{
				fprintf( gsfp , "%s | %d", names[x], states[x] ); 
			} 	

/*			for( k = 0; k < (choice - 1); k++ ) 
			{ 
				fprintf( gsfp, "%s | %d\n" ,  names[k] , states[k] ); 
			} 

			for( k = choice; k < MAXNUMSAVEFILES; k++ ) 
			{ 
				fprintf( gsfp, "%s | %d\n" , names[k] , states[k] ); 
			} 
*/
	}

	else if ( progress == 2 ) 
	{ 

		for( k = 0; k < MAXNUMSAVEFILES; k++ ) 
		{ 
			if( strcmp( playerName , *( names + k ) ) == 0 ) 
			{ 
				*(names + k) = playerName;

				states[ k ] = progress; 

				for( x = 0; x < MAXNUMSAVEFILES; x++ ) 
				{ 
					fprintf( gsfp , "%s | %d", names[x], states[x] ); 
				} 

			} 
		}	
		
		FILE* fnp = fopen( filename , "w" ); 
		for( k =0; k < NUMHEROES; k++) 
		{ 
			fprintf( fnp , "%s | %d | %d | %d | %d", heroes[k].name , heroes[k].health , heroes[k].baseDefense , heroes[k].baseAttack , heroes[k].baseSpeed );
		} 
	}

}

char* getPlayerName()
{
	char* PlayerName = malloc( MAXPLAYERNAME*sizeof( char ) ); 
	
	printf("Please enter your player name: \n"); 
	scanf("%s", PlayerName); 

	return PlayerName; 
}

Hero* loadSavedData(char* filename)
{ 
	FILE* fp = fopen( filename , "r" ); 

	int k; 

	Hero* heroes = malloc( NUMCHOSENHEROES*sizeof( Hero )  ); 

	for( k = 0; k < NUMCHOSENHEROES; k++ ) 
	{ 
		fscanf( fp, "%s %d %d %d %d" , heroes[k].name , &heroes[k].health , &heroes[k].baseDefense , &heroes[k].baseAttack , &heroes[k].baseSpeed ); 
	} 

	return heroes;
}

Hero* loadInitialData()
{	
	FILE* fp = fopen( "Heroes.txt" , "r" ); 

	int k; 

	Hero* heroes = malloc( NUMHEROES*sizeof( Hero )  ); 
	
	for( k = 0; k < NUMHEROES; k++ ) 
	{ 
		fscanf( fp, "%s | %d | %d | %d | %d" , heroes[k].name , &heroes[k].health , &heroes[k].baseDefense , &heroes[k].baseAttack , &heroes[k].baseSpeed ); 
	} 

	return heroes; 
}

Hero* pickHeroes(Hero* heroes)
{

	int h1, h2, h3;
	Hero* Party = malloc( NUMCHOSENHEROES*sizeof( Hero ) ); 

	sortHeroes( heroes ); 

	printHeroes( heroes , NUMHEROES ); 


	printf("Please pick your First Hero:\n"); 
	scanf("%d", &h1); 
	while( h1 < 0 || h1 > 6 ) 
	{ 
		printf("Invalid Hero choice! Please pick a valid Hero option:\n"); 
		scanf("%d", &h1); 
	} 
	printf("The Kingdom is in good hands! Hero saved!\n"); 

	printf("Please pick your Second Hero:\n"); 
	scanf("%d", &h2); 
	while( h2 < 0 || h2 > 6 || h2 == h1) 
	{ 
		printf("Invalid Hero choice! Please pick a valid Hero option:\n"); 
		scanf("%d", &h2); 
	} 
	printf("The King will be proud! Hero saved!\n"); 

	printf("Please pick your Third Hero:\n"); 
	scanf("%d", &h3); 
	while( h3 < 0 || h3 > 6 || h3 == h1 || h3 == h2 ) 
	{ 
		printf("Invalid Hero choice! Please pick a valid Hero option:\n"); 
		scanf("%d", &h3); 
	} 
	printf("Go save the Kingdom! Hero saved!\n"); 
 
	Party[0] = heroes[h1]; 
	Party[1] = heroes[h2]; 
	Party[2] = heroes[h3]; 
	
	return Party; 
}

void sortHeroes(Hero* heroes)
{ 
	int k,j; 
	Hero Swap; 

	for( k = 1; k <= 0; k++ )
	{ 
		j = k; 

		while( j >0 && strcmp( heroes[j].name , heroes[j - 1].name ) > 0 ) 
		{ 
			Swap = heroes[j]; 
			heroes[j] = heroes[j - 1]; 
			heroes[j - 1] = Swap; 

			j--; 
		} 
	} 
}

void printHeroes(Hero* heroes, int numHeroes)
{ 
	int	k; 

	for( k = 0; k < numHeroes; k++ ) 
	{ 
		printf("%d) %s\n 		Health: %d\n 		Defense: %d\n 		Attack: %d\n 		Speed: %d\n", k , heroes[k].name , heroes[k].health , heroes[k].baseDefense, heroes[k].baseAttack, heroes[k].baseSpeed );
	} 
}



/***************************************START OF FUNCTIONS GIVEN TO YOU*********************************************************************/

FileFinder findSaveFile()
{
	printf("Checking save file...\n\n");
	//This should exist. Make sure the file is with your HW. 
	FILE* fp = fopen("gamestate.txt", "r");
	if(!fp)
	{
		//You will have to debug this...it could be for a variety of reasons. 
		perror("gamestate.txt read error");
		exit(1);
	}

	int numFiles;

	//read the number of save file slots that are taken up, and 
	//interpret accordingly. 
	if(fscanf(fp, "%d", &numFiles) < 1)
	{
		printf("gamestate.txt: failed to read number of save files. Check input file.\n");
		exit(1);
	}

	FileFinder f;
	if (numFiles == 0) 
	{ 
		
		f = DOESNOTEXIST;
	}
	else 
	{ 
		f = EXIST; 
	}
	
	fclose(fp);
	
	printf("Check complete.\n\n");
	return f;
}

void loadSavedGameHandler()
{
	//initial load of all data that might be needed. 
	char** names;
	int* states;
	int numFiles;
	int choice;

	loadGameStateData(&names, &states, &numFiles);

	while(1)
	{
		printf("\nChoose a file you would like to load: \n");
		printf("(-1 to return to main menu)\n");
		printf(">");
		scanf("%d", &choice);
		while((choice < 1 || choice > MAXNUMSAVEFILES) && choice != -1)
		{
			printf("Invalid choice. Please choose a different option:\n ");
			printf(">");
			scanf("%d", &choice);
	
		}
	
		if(choice == -1)
		{
			freeMemory(names, states);
			return;
		}
	
		if(states[choice-1] == 0)
		{
			printf("There is no saved file present in this slot.\n");
		}
		else
		{
			//From here, a valid saved file has been selected, so we need to interpret where
			//the save file is in terms of game progression. This way we know what data to load

			//the state value will never be anything other than 0, 1, or 2. 
			if(states[choice-1] == 1)
			{
				//Heroes have not been selected yet.
				playGame(loadInitialData(), names[choice-1], NULL, states[choice-1], choice);
			}
			else
			{
				//Heroes have already been selected. 
				Hero* heroes = loadSavedData(choiceToFile(choice-1));
				if(!heroes)
				{
					printf("Failed to load heroes. Exiting...\n");
					freeMemory(names, states);
					exit(1);
				}
				playGame(heroes, names[choice-1], NULL, states[choice-1], choice);
			}
	
			freeMemory(names, states);
			return;
		}
	}
}

void DeleteSavedGameHandler()
{

	//Everything in this file is almost identical to the function above, just different ending actions.
	//Could move a lot of this to its own function, but eh
	char** names;
	int* states;
	int numFiles;
	int flag = 0;
	int choice = -1;

	while (1)
	{
		//Small optimization. If we didn't delete a file, we don't have to reload the data
		//since nothing changed. 
		if(flag == 0)
		{
			//to cover the first time the loop goes through.
			//Can't free if nothing's been loaded yet.
			if(choice != -1)
			{
				freeMemory(names, states);
			}
			loadGameStateData(&names, &states, &numFiles);
		}

		printf("\nChoose a file you would like to delete: \n");
		printf("(-1 to return to main menu)\n");
		printf(">");
		scanf("%d", &choice);
		while((choice < 1 || choice > MAXNUMSAVEFILES) && choice != -1)
		{
			printf("Invalid choice. Please choose a different option:\n ");
			printf(">");
			scanf("%d", &choice);
		}

		if(choice == -1)
		{
			//This is the only way to get out of this function. 
			freeMemory(names, states);
			return;
		}

		if(states[choice-1] == 0)
		{
			//shouldn't get here, but just in case. 
			//can't get here because the numFiles controls what's 
			//a valid value for chioce.
			printf("There is no saved file present in this slot.\n");
			flag = 1;
		}
		else
		{
			deleteFile(choice, choiceToFile(choice-1));
			flag = 0;
		}
	}
}

void loadGameStateData(char*** names, int** states, int* fileCount)
{
	printf("\n\n");
	//All memory is allocated here, and once the data is loaded 
	//The variables passed by reference into this function will be set up. 
	char** n = malloc(sizeof(char*)*MAXNUMSAVEFILES);
	int i;
	for(i = 0; i < MAXNUMSAVEFILES; i++)
	{
		n[i] = malloc(sizeof(char)*MAXPLAYERNAME);
	}

	int* s = malloc(sizeof(int)*MAXNUMSAVEFILES);

	//again, should not fail. 
	FILE* fp = fopen("gamestate.txt", "r");
	if(!fp)
	{
		perror("gamestate.txt");
		freeMemory(n, s);
		exit(1);
	}

	int numFiles;
	if(fscanf(fp, "%d", &numFiles) < 1)
	{
		printf("gamestate.txt: could not read the number of save files. Check input file.\n");
		freeMemory(n,s);
		exit(1);
	}
	//Load all the data, interpret the data, and print to the user what
	//was found in the list of save file slots. 
	for(i = 0; i < MAXNUMSAVEFILES; i++)
	{
		if(fscanf(fp, "%s | %d", n[i], &s[i]) < 2)
		{
			printf("gamestate.txt: could not read save file data #%d. Check input file.\n", i+1);
			freeMemory(n,s);
			exit(1);
		}
		//NOTE: everything shown to the user is for human readability. 
		//Stuff starts at 1, but internally stuff still starts at 0. 
		switch(s[i])
		{
			case 0: 
				printf("%d: [No File Present]\n", i+1);
				break;
			case 1: 
				printf("%d: %s - ", i+1, n[i]);
				printf("Heroes have not been selected.\n"); 
				break;
			case 2: 
				printf("%d: %s - ", i+1, n[i]);
				printf("Heroes have been selected.\n"); 
				break;
		}
	}
	
	fclose(fp);

	//complete the links after everything is loaded. 
	*names = n;
	*states = s;
	*fileCount = numFiles;
}

//helpful function to know what file we are loading from/saving to
char* choiceToFile(int num)
{ 
   switch(num)
   { 
		case 0: return "file1.txt"; break;
		case 1: return "file2.txt"; break;
		case 2: return "file3.txt"; break;
		case 3: return "file4.txt"; break;
		case 4: return "file5.txt"; break;
		default: 
				printf("Something happened with the save file choice. See Daniel.\n");
				exit(1); break; 
   } 
} 

void freeMemory(char** names, int* states)
{ 
	int i;
	//seg faults? Check input file/gdb. 
	for(i = 0; i < MAXNUMSAVEFILES; i++) 
	{ 
			free(names[i]); 
	} 
	free(names);
	free(states);  
} 

void startNewGame() 
{ 
	//I don't think anything else needs to be here? 
	Hero* heroes = loadInitialData(); 
	//doesn't matter what the value of choice is, since progress = 0 means get a choice value first. 
	playGame(heroes, NULL, NULL, 0, -1);
}

void playGame(Hero* heroes, char* playerName, Boss* boss, int progress, int choice)
{

	//Added flavor 
	if(progress > 0)
	{
		printf("\nWelcome back %s.\n\n", playerName);
	}

	//holds what the last thing done was.
	int initialprogress = progress;

	Hero* chosenHeroes;

	//another check for how the data is laid out. This is so we can immediately print out
	//heroes if we have already selected heroes. 
	if(progress > 1)
	{
		chosenHeroes = heroes;
	}	
	
	switch(progress)
	{
		//initial player identification
		case 0:
			playerName = getPlayerName();
			choice = chooseSaveFile();
			saveFileData(choice, choiceToFile(choice-1), NULL, playerName, 1);
		//hero selection
		case 1:
			chosenHeroes = pickHeroes(heroes);
			saveFileData(choice, choiceToFile(choice-1), chosenHeroes, playerName, 2);
			free(heroes);
		//equip heroes with items 
		case 2:
			//shop
			printHeroes(chosenHeroes, NUMCHOSENHEROES);
			free(chosenHeroes);
			//should never be past this point, so stop the pitfalling here. 
			break;
		//fight the boss (a boss? Maybe find some way to get more than one boss in there?)
		case 3: 
			//fight
			printf("Why is progree value 3? It should not be here yet.\n");
		default:
			//What?
			printf("Something fatal happened with the progress value. Check gamestate.txt.\n");
			break;
	}
	
	printf("\n\n**********Until Next Homework!*************\n\n");

	//I don't actually remember why I did this, but it works. 
	//I think because if it's a save file, it's freed elsewhere?
	if(initialprogress == 0)
	{
		free(playerName);
	}
	return;
}

int chooseSaveFile()
{
	//Initial load for data management. 
	char** names;
	int* states;
	int numFiles;
	int choice;
	int confirm = 1;

	loadGameStateData(&names, &states, &numFiles);
	
	//Get a chosen file slot to save to. The file slot must be valid, and 
	//old files can be overriden. 
	while(1)
	{
		confirm = 1;
		printf("\nChoose a file you would like to save to: \n");
		printf(">");
		scanf("%d", &choice);
		while((choice < 1 || choice > MAXNUMSAVEFILES))
		{
			printf("Invalid choice. Please choose a different option:\n ");
			printf(">");
			scanf("%d", &choice);
		}

		if(states[choice-1] != 0)
		{
			printf("There is a file here. Would you like to override it? (1 = yes, 0 = no)\n");
			printf(">");
			scanf("%d", &confirm);
			while(confirm != 1 && confirm != 0)
			{
				printf("Invalid choice. Please choose a different option:\n ");
				printf(">");
				scanf("%d", &confirm);
			}
		}

		if(confirm == 1)
		{
			//Go ahead and delete the old hero file immediately if there is one. 
			if(states[choice-1] == 2)
			{
				deleteFile(choice, choiceToFile(choice-1));
			}
			freeMemory(names, states);
			//I haven't found a bug yet with the state = 1, but there might be one somewhere. 
			return choice;
		}
	}
}
