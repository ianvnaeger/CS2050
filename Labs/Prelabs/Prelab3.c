//Ian Naeger
//IVNQM2
//Prelab 3

#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<math.h> 

typedef struct { 
	int id; 
	char name[20]; 
	float gpa; 
} Student; 

Student findStudent(FILE* , int ); 

int main(int argc, char* argv[] ) 
{ 
	if( agrc != 2 ) 
	{ 
		printf("\n Insufficient Arguments! \n"); 
		return 0; 
	} 

	char *file; 
	file = malloc( strlen( argv[1] )*sizeof( char ) ); 
	file = argv[1]; 

	FILE* fp = fopen( file, "rb" ); 

	if( file == NULL ) 
	{ 
		printf("\nInvalid File\n");  
		return NULL; 
	} 

	int UserSelect;

	printf("Enter Student ID to find desired student:"); 
	scanf("%d", &UserSelect); 

	Student Stud; 
	int k; 

	for( k = 0; k < 5; k++ )
	{ 
		Stud = findStudent( fp , ( UserSelect + k ) ); 
		printf("%s", Stud); 
	} 

	fclose( fp );
	free( file ); 
	
	return 0; 

} 



Student findStudent(FILE* fp , int StudentID )
{

	fseek( fp , SEEK_SET , 0 ); 
	fread( ptr , 1 , asdf , fp); 
} 
