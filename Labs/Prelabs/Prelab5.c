//Ian Naeger
//Prelab 5 

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<math.h> 

typedef enum { 
	PENNY = 1,
	NICKEL = 5, 
	DIME = 10,
	QUARTER = 25, 
} Denomination; 

typedef struct { 
	Denomination denomination; 
	int quantity; 
} Coin; 

typedef Coin* PiggyBank; 

PiggyBank loadBank( const char* filename, int* lenPtr);
int totalMoney( PiggyBank bank , int length ); 

int main( int argc , char* argv[] ) 
{ 
	if( argc != 2 ) 
	{ 
		printf("\n Insufficient Arguments! \n");
		return 0; 
	} 

	char *file; 
	file = malloc( strlen( argv[1] )*sizeof( char ) );
	file = argv[1]; 

	int len , total;
   	PiggyBank Bank;
	Bank = loadBank( file , &len ); 
	total = totalMoney( Bank , len ); 

	printf("You have %d cents!\n" , total); 

	return 0; 
}

PiggyBank loadBank( const char* filename, int* lenPtr ) 
{ 
	int k;
	FILE* fp = fopen( filename, "r" ); 
	if( fp == NULL ) 
	{ 
		printf("\n Invalid File\n"); 
		return NULL; 
	} 

	fscanf(fp , "%d" , lenPtr); 

	PiggyBank Bank = malloc( *lenPtr * sizeof( Coin ) ); 

	for( k = 0; k < *lenPtr; k++) 
	{ 
		fscanf( fp, "%d %d" , (int*)&(Bank+k)->denomination , &(Bank+k)->quantity ); 
	} 

	return Bank; 
} 

int totalMoney( PiggyBank bank , int length ) 
{ 
	int k , i ,total; 
	total = 0;
	
	for( k = 0; k < length; k++ ) 
	{ 
		i = (bank+k)->denomination * (bank+k)->quantity;
	   	total = total + i; 
	} 

	return total; 
} 






