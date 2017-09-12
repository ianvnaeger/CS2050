//Lab Code: It's Cold
//Lab Section: B
//PawPrint: IVNQM2
//Ian Naeger
//Lab 3

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
Student* getClass( const char* , const char* , int* ); 
void bubbleSort( Student* , int ); 
void storeClass( const char* , Student* , int ); 
void printClass( Student* , int ); 

int main(int argc, char* argv[] ) 
{ 
	if( argc != 4 ) 
	{ 
		printf("\n Incorrect Usage\n ./a.out <class file> <students file> <output file> \n"); 
		return 0; 
	} 

	char *file1; 
	file1 = malloc( strlen( argv[1] )*sizeof( char ) ); 
	file1 = argv[1]; 

//	FILE* fp1 = fopen( file1, "r" ); 

	if( file1 == NULL ) 
	{ 
		printf("\n Invalid Class File\n");  
		return 0; 
	} 

	char *file2; 
	file2 = malloc( strlen( argv[2] )*sizeof( char ) ); 
	file2 = argv[2]; 

//	FILE* fp2 = fopen( file2, "rb" ); 

	if( file2 == NULL ) 
	{ 
		printf("\n Invalid Students File\n");  
		return 0; 
	} 

	char *file3; 
	file3 = malloc( strlen( argv[3] )*sizeof( char ) ); 
	file3 = argv[3]; 

//	FILE* fp3 = fopen( file3, "wb" ); 

	if( file3 == NULL ) 
	{ 
		printf("\n Invalid Output File\n");  
		return 0; 
	} 

	int len;  
	Student *Class; 
	
	Class = getClass( file1 , file2 , &len ); 
	storeClass( file3, Class , len ); 
//	bubbleSort( Class , len ); 
	printClass( Class , len ); 


/*	fclose( fp1 );
	free( file1 ); 
	fclose( fp2 );
	free( file2 ); 	
	fclose( fp3 );
	free( file3 ); */
	return 0; 

} 

Student* getClass( const char* classFile, const char* studentFile, int* len )
{  
	int num , k; 
	FILE* cfp = fopen( classFile, "r" );
	FILE* sfp = fopen( studentFile, "rb" );
	//	Student bob; 

	fscanf( cfp , "%d" , &num); 

	int ID[num]; 
	Student* Class = malloc( num*sizeof( Student ) ); 
	*len = num*sizeof( Student );

	for( k = 0; k < num; k++) 
	{ 
		fscanf( cfp, "%d" , &ID[k] );
	} 

	for( k = 0; k < num; k++ ) 
	{ 	
		*(Class + k) = findStudent( sfp , ID[k] );
	//	FILE* fp = &bob;
	//	fscanf( fp , "%d %s %f" , &(Class + k)->id , (Class + k)->name , &(Class + k)->gpa ); 
	} 

	return Class; 
	
} 
/*
void bubbleSort( Student* students , int len ) 
{ 
 	int k , c; 
	Student *Swap = malloc( sizeof( Student ));


	for( k = 0; k < len; k++) 
	{ 
		for( c = 0; c < len; c++ ) 
		{ 
			if( (students + k)->gpa < (students + c)->gpa ) 
			{ 
				Swap = (students + k); 
				(students + k) = (students + c); 
				(students + c) = Swap; 
			}

		} 


	} 


} */

void storeClass( const char* filename, Student* students, int len ) 
{ 
	FILE* fp = fopen( filename, "wb" ); 
	fwrite( students , 1 , len , fp ); 
}

void printClass( Student* students, int len )
{ 
	int k; 

	for( k = 0; k < len; k++ ) 
	{ 
		printf("%d %s %f \n", (students + k)->id , (students + k)->name , (students + k)->gpa ); 
	} 

	printf("\n"); 
} 

Student findStudent( FILE* fp , int studentId )
{
	FILE* sPtr = fp;
	fseek( fp , sizeof(studentId) , SEEK_SET ); 
	Student bob;
	fread( &bob , sizeof(Student) , 1 , fp); 
	fp = sPtr;
	return bob; 
} 
