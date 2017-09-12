// Lab Code: Bad Wolf 
// IVNQM2
// 1/26/16
// Section B
// Lab 1
// Ian Naeger

#include<math.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
// Included Libraries

double* read_file( char* , int );
double find_min( double* , int );
double find_max( double* , int );
double find_avg( double* , int ); 
void write_to_file( char* , double* , int ); 
// Prototypes

int main( int argc , char* argv[] ) 
{ 
	if( argc != 4 ) 
	{ 
		printf("\n Insufficient Arguments! \n"); 
		return 0; 
	} 
	// Ensures correct ammount of Command Line Arguments

	int size = atoi( argv[1] ); 
	// Gets length of file from command line
	char *input; 
	char *output; 
	double min , max , avg;
	// variables
   	
	input = malloc( strlen( argv[2] )*sizeof(char) );
	input = argv[2];
    // make input array	

	output = malloc( strlen( argv[3] )*sizeof(char) ); 
	output = argv[3];
	// make output array 

	double *array= malloc( size*sizeof(double) ); 

	array = read_file( input , size ); 
	// make array and populate it with info from input 
	
	min = find_min( array , size ); 
	max = find_max( array , size );
	avg = find_avg( array , size ); 
	// Find min, max, and average of the array 
	write_to_file( output , array , size ); 
	// write array to output file

	printf(" Minimum: %lf \n Maximum: %lf \n Average: %lf \n", min , max , avg ); 
	
	free( array ); 	

	return 0;
} 

double* read_file( char* filename , int length ) 
{ 
	FILE* file = fopen( filename, "r"); 

	if( file == NULL) 
	{
		return NULL; 
	}

	int k;
	double *array;

	array = malloc( length*sizeof(double) ); 

	for( k = 0; k < length; k++ )
	{ 
		fscanf( file, "%lf" , (array + k) ); 
	} 

	fclose(file); 

	return array; 

} 

double find_min( double* array , int length )
{ 
	int k; 
	double min = 1000000000;

	for( k = 0; k < length; k++)
	{ 
		if( *(array + k) < min )
		{ 
			min = *(array + k);
		} 
	} 

	return min; 
}

double find_max( double* array , int length )
{ 
	int k; 
	double max = 0;

	for( k = 0; k < length; k++)
	{ 
		if( *(array + k) > max )
		{ 
			max = *(array + k);
		} 
	} 

	return max; 
}

double find_avg( double* array , int length )
{ 
	int k; 
	double avg = 0;

	for( k = 0; k < length; k++)
	{ 
		avg = avg + *(array + k); 
	} 

	avg = avg / k; 

	return avg; 
}

void write_to_file( char* filename , double* array , int length ) 
{ 
	int k; 
	FILE* file = fopen( filename , "w");
	
	for( k = 1; k < length; k++ ) 
	{ 
		fprintf( file , "%lf \n", ( array[length - k] ) ); 
	} 

	fclose( file );

} 


