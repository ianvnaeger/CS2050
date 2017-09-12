//Lab Code: Pink Dragon 
//Pawprint: IVNQM2
//Name: Ian Naeger
//Section B
//Lab 5 

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
//struct and enum declaration

PiggyBank loadBank( const char* filename, int* lenPtr);
char* enumToString( Denomination denomination );
int totalMoney( PiggyBank bank , int length ); 
void printBankToScreen( PiggyBank bank, int length );
void sortByQuantity( PiggyBank bank, int length );
void writeToFile( const char* filename, PiggyBank bank , int length );
PiggyBank minimumChange(int amount);
//Prototype Declaration

int main( int argc , char* argv[] ) 
{ 
	if( argc != 3 ) 
	{ 
		printf("\n Insufficient Arguments! \n");
		return 0; 
	} 

	char *input; 
	input = malloc( strlen( argv[1] )*sizeof( char ) );
	input = argv[1]; 
	
	char *output; 
	output = malloc( strlen( argv[2] )*sizeof( char ) );
	output = argv[2];
//Get file names

	int len;
   	PiggyBank Bank;
	Bank = loadBank( input , &len ); 
	printBankToScreen( Bank , len );
	sortByQuantity( Bank , len ); 
	writeToFile( output , Bank , len );
//Load a bank, print it, sort it, and write it to a file

	int amount;
	printf("\nBONUS: Enter an amount of change: ");
	scanf("%d", &amount); 

	PiggyBank MinChng;
	MinChng = minimumChange( amount );
   	printBankToScreen( MinChng , 4 );
//Get an amount and find the smallest amount of change possible

	free(MinChng); 
	free(Bank);
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
		fscanf( fp, "%d %d" , (int*)&(Bank + k)->denomination , &(Bank + k)->quantity ); 
	} 

	fclose(fp);
	return Bank; 
} 

int totalMoney( PiggyBank bank , int length ) 
{ 
	int k , i ,total; 
	total = 0;
	
	for( k = 0; k < length; k++ ) 
	{ 
		i = (bank + k)->denomination * (bank + k)->quantity;
	   	total = total + i; 
	} 

	return total; 
} 

char* enumToString( Denomination denomination ) 
{ 
	char* coin;
	if(denomination == 1)
	{ 
		coin = "penny"; 
	}
	else if(denomination == 5)
	{ 
		coin = "nickel"; 
	}
	else if(denomination == 10)
	{ 
		coin = "dime"; 
	}
	else if(denomination == 25)
	{ 
		coin = "quarter"; 
	}

	return coin;

} 

void printBankToScreen( PiggyBank bank , int length ) 
{ 
	int total , k; 
	total = totalMoney( bank , length ); 

	printf("You have %d cents!\n", total); 

	char* coin; 

	for( k = 0; k < length; k++ )  
	{ 
		coin = enumToString( (bank + k)->denomination ); 
		printf(" %s: %d\n", coin, (bank + k)->quantity ); 
	} 
} 

void sortByQuantity( PiggyBank bank , int length ) 
{ 
	int k , i , sq , sd; 

	for( k = 1; k <= (length - 1); k++ )
	{ 
		i = k; 

		while( i > 0 && (bank + i)->quantity < (bank + (i-1))->quantity )
		{ 
			sq = (bank + i)->quantity;
			sd = (bank + i)->denomination;
			(bank + i)->quantity = (bank + (i-1))->quantity;
			(bank + i)->denomination = (bank + (i-1))->denomination;
		   	(bank + (i-1))->quantity = sq; 
			(bank + (i-1))->denomination = sd;
			i--;
		} 
	} 
} 	

void writeToFile( const char* filename , PiggyBank bank , int length ) 
{ 
	FILE* fp = fopen( filename , "w" ); 
	if( fp == NULL ) {
		return; 
	} 

	fprintf( fp, "%d\n", length); 

	int k; 
	for( k = 0; k < length; k++ ) 
	{ 
		fprintf( fp, "%d %d\n", (bank + k)->denomination , (bank + k)->quantity ); 
	} 

	fclose(fp);
} 

PiggyBank minimumChange( int amount ) 
{ 
	int quarters , dimes , nickels, pennies , remain; 

	quarters = amount / 25; 
	remain = amount % 25; 
	dimes = remain / 10;
	remain = remain % 10; 
	nickels = remain / 5; 
	remain = remain % 5; 
	pennies = remain; 

	PiggyBank Bank = malloc( 4*sizeof( Coin ) ); 

	//Quarters
	Bank->denomination = 25;
	Bank->quantity = quarters; 
	//Dimes
	(Bank + 1)->denomination = 10;
	(Bank + 1)->quantity = dimes; 
	//Nickels
	(Bank + 2)->denomination = 5;
	(Bank + 2)->quantity = nickels; 
	//Pennies
	(Bank + 3)->denomination = 1;
	(Bank + 3)->quantity = pennies;
   	
	return Bank; 
} 	









