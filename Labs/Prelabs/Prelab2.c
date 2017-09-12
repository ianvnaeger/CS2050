// Ian Naeger
// IVNQM2 
// Prelab2

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

	int *length; 

printf("hfgh\n"); 

	struct song *Album; 
    Album = readAlbum( file , length ); 

printf("hjk;lio\n"); 	

	printAlbum( Album , *length ); 

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

	Song aSong; 
	Song bSong; 
	Song cSong; 

	aSong.name = malloc( MAXNAMESIZE*sizeof(char) ); 	
	bSong.name = malloc( MAXNAMESIZE*sizeof(char) ); 
	cSong.name = malloc( MAXNAMESIZE*sizeof(char) ); 

	fscanf( file, "%d" , x ); 

	*lenPtr = x; 
	struct song *array = malloc( (*lenPtr)*sizeof(struct song) ); 

	array[0] = aSong; 
	array[1] = bSong;
	array[2] = cSong; 	

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
		printf("%d", (*(album + k)) );
	} 

	printf("\n"); 
} 





