// Lab Code: Winter is Coming 
// Lab Section: B 
// Name: Ian Naeger
// Pawprint: IVNQM2 
// Lab 2 

#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<math.h> 

#define MAXNAMESIZE 20

typedef struct song { 
	char* name; 
	int rating; 
	int numTimesPlayed;
} Song; 

Song* readAlbum( const char* , int* );
void printAlbum( Song* , int );
int changeRating( char* , int , Song* , int ); 
int listenToSong( char* , Song* , int ); 
//void bubble_sort( Song* , int ); 

int main( int argc , char* argv[] ) 
{ 
	if( argc != 2 ) 
	{ 
		printf("\n Insufficient Arguments! \n"); 
		return 0; 
	} 

	char *file; 
	file = malloc( strlen( argv[1] )*sizeof(char) ); 
	file = argv[1];

	int length; 

	struct song *Album; 
    Album = readAlbum( file , &length ); 

	printAlbum( Album , length );  

	int select , index , rating;
   	char *title = malloc( MAXNAMESIZE*sizeof(char)); 	
	int loop = 1;


	while( loop == 1 )
	{
		printf(" Enter 1 to listen to a song \n Enter 2 to change a rating \n Enter 0 to quit \n"); 
		scanf("%d", &select); 

		if( select == 1 ) 
		{	 
			printf("Enter a song:"); 
			scanf("%s", title); 
			index = listenToSong( title , Album , length ); 
				if( index == -1 ) 
				{ 
					printf("Unable to find %s \n", title );  
				} 
				else 
				{ 
					printf("%s %d %d \n", (Album + index)->name, (Album + index)->rating , (Album + index)->numTimesPlayed); 
				} 

		} 
		else if( select == 2 ) 
		{ 
			printf("Enter a song:"); 
			scanf("%s", title); 
		   	printf("Enter a new rating:"); 
			scanf("%d", &rating); 	
			index = changeRating( title , rating , Album , length ); 
				if( index == -1 ) 
				{ 
					printf("Unable to find %s \n", title );  
				} 
				else 
				{ 
					printf("%s %d %d \n", (Album + index)->name, (Album + index)->rating , (Album + index)->numTimesPlayed); 
				} 
		} 
		else if( select == 0 ) 
		{
			loop = 0; 
		}	 
	} 

/*	bubble_sort( Album , length ); 

	int j; 

	for( j = 0; j < length; j++)  
	{ 
		printf("%s %d %d \n", (Album + j )->name, (Album + j )->rating , (Album + j )->numTimesPlayed);
	} 
*/
	free( Album ); 
	return 0; 
	
} 

Song* readAlbum( const char* filename, int* lenPtr ) 
{ 
	FILE* file = fopen( filename, "r" ); 

	if( file == NULL ) 
	{ 
		return NULL;  
	}
	
	int x;
	int k;

	fscanf( file, "%d" , &x ); 

	*lenPtr = x; 
	struct song *array = malloc( (*lenPtr)*sizeof(struct song) ); 

	for( k = 0; k < (*lenPtr); k++ ) 
	{ 
		(array+k)->name = malloc( MAXNAMESIZE*sizeof( char ));
	}


	for( k = 0; k < (*lenPtr); k++ ) 
	{ 
		fscanf( file, "%s %d %d" , (array + k)->name, &(array + k)->rating , &(array +k)->numTimesPlayed); 
	} 
 
	fclose( file ); 

	return array; 
} 

void printAlbum( Song* album, int len ) 
{ 
	int k; 

	for( k = 0; k < len; k++ ) 
	{ 
		printf("%s %d %d \n", (album + k)->name, (album + k)->rating, (album + k)->numTimesPlayed );
	} 

	printf("\n"); 
} 

int changeRating( char* title, int rating , Song* album , int len ) 
{ 
	int k;

	for( k = 0; k < len; k++ ) 
	{ 
		if( strcmp((album + k)->name , title ) == 0 )  
		{
			(album + k)->rating = rating;
			return k;
		} 
	}

	return -1; 
} 

int listenToSong( char* title, Song* album , int len ) 
{ 
	int k; 

	for( k = 0; k < len; k++ ) 
	{ 
		if( strcmp((album + k)->name , title ) == 0 )  
		{
			(album + k)->numTimesPlayed++;
			return k;
		} 
	}
	
	return -1; 
} 

/* void bubble_sort( Song* album , int len ) 
{ 
	int k , c; 
	Song *swap = malloc( sizeof(struct song)); 

	for( k = 0; k < len; k++ ) 
	{ 
		for( c = 0; c < len; c++ ) 
		{ 
			if( (album + k)->numTimesPlayed < (album + (k+1))->numTimesPlayed ) 
			{ 
				*swap = *(album + k); 
			   	*(album + k) = 	*(album + (k+1)); 
				*(album + (k+1)) = *swap; 
			} 
	
		} 
	} 
}
*/ 



