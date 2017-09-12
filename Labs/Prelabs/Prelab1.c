// Ian Naeger 
// IVNQM2
// Prelab 1

#include<math.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>

int* read_file( char* , int );
void print_array( int* , int );



int main( int argc , char* argv[] ) 
{ 
	if( argc != 3 ) 
	{ 
		printf("\n Insufficient Arguments! \n"); 
		return 0; 
	} 

	int size = atoi( argv[1] ); 
	char *name; 
   	
	name = malloc( strlen( argv[2] )*sizeof(char) );
	name =  argv[2] ; 

	int* array= malloc( size*sizeof(int) ); 
	array = read_file( name , size ); 
	printf("lhkadsfhl;fad \n"); 
	print_array( array , size ); 
	
	return 0;
} 

int* read_file( char* filename , int len ) 
{ 
	FILE* file = fopen( filename, "r"); 

	if( file == NULL) 
	{
		return NULL; 
	}

	int k;
	int *array;

	array = malloc( len*sizeof(int) ); 

	for( k = 0; k < len; k++ )
	{ 
		fscanf( file, "%d" , (array + k) ); 
	} 

	fclose(file); 
	return array; 
} 

void print_array( int* array, int len ) 
{ 
	int k; 
	 
	for( k = 0; k < len; k++ ) 
	{ 
		
		printf("%d ", (*( array + k )) ); 
	} 
 
	printf("\n"); 
} 

