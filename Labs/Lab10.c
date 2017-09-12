// Lab Code" Cucumber
// Par Print: IVNQM2
// Name: Ian Naeger 
// Section: B 
// Lab: 10

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int isDate( char* token ); 
int isEmail(char* token ); 
int isPhoneNumber( char* token );
int nullCheck( char* token ); 

int main( int argc , char* argv[] ) 
{
	if( argc != 2 ) 
	{ 
		printf("\nINSUFFICENT ARGUMENTS!!! \n");
		return 0; 
	}

	char* filename = malloc( strlen( argv[1] )*sizeof(char) );
	filename = argv[1]; 

	FILE* fp = fopen( filename , "r" ); 

//	char d[] = "\n"," ","\t"; 
	char* token;
	char* Date;
	char* Number;
	char* Email; 
	int k;
	char line[250];

	while( fgets( line , 250 , fp ) != NULL ) 
	{ 

		token = strtok( line , "\t\n " );  

		while( token != NULL ) 
		{ 
			k = nullCheck( token ); 

			if( *(token + (k - 1)) == '.' || *(token + (k - 1)) == '!' || *(token + (k - 1)) == '?' ) 
				*(token + ( k - 1)) = '\0'; 
	
			if( isDate( token ) == 1 ) 
				Date = token; 
			
			if( isPhoneNumber( token ) == 1 ) 
				Number = token; 
	
			if( isEmail( token ) == 1 ) 
				Email = token; 

			token = strtok( NULL , "\t\n " ); 
		}

	} 
	printf("\n Phone Number: %s \n Date: %s \n Email: %s \n", Number , Date , Email ); 

	return 0;
}

int isPhoneNumber(char* token) {
	if(token == NULL || (*token) == '\0')
	{
		return 0; 
	}

	int x =0; 
	while(*(token + x) != '\0')
	{
			switch(x)
			{
				case 0: 
					if(*(token + 0) != '(')
						return 0; 
					break;
				case 4:
					if(*(token + 4) != ')')
						return 0; 
					break;
				case 8: 
					if(*(token + 8) != '-')
						return 0; 
					break; 
				default:
					if(isdigit(*(token + x)) == 0)
						return 0;
					break; 
			}
			x++;
	}
	return 1;
}

int isDate( char* token ) 
{ 
	if(token == NULL || (*token) == '\0')
		return 0; 

	int x =0; 
	while(*(token + x) != '\0')
	{
			switch(x)
			{
				case 2: 
					if(*(token + 2) != '/')
						return 0; 
					break;
				case 5:
					if(*(token + 5) != '/')
						return 0; 
					break;
				default:
					if(isdigit(*(token + x)) == 0)
						return 0;
					break; 
			}
			x++;
	}

	int a , b , c , d , e , f , g , h , i , j , k; 

	a = *(token); 
	b = *(token + 1); 
	a = a * 10; 
	c = a + b; 
	if( c < 1 || c > 12 ) 
		return 0; 

	d = *(token + 3); 
	e = *(token + 4);
	d = d * 10; 
	f = d + e;
	if( c == 1 || c == 3 || c == 5 || c == 7 ||	c == 8 || c == 10 || c == 12 ) 
	{ 
		if( f < 1 || f > 31 ) 
			return 0; 
	} 
	else if( c == 4 || c == 6 || c == 9 || c == 11 ) 
	{ 
		if( f < 1 || f > 30 ) 
			return 0; 
	} 
	else if( c == 2 ) 
	{ 
		if( f < 1 || f > 28 ) 
			return 0; 
	} 

	g = *(token + 6); 
	h = *(token + 7); 
	i = *(token + 8); 
	j = *(token + 9);
	g = g * 1000;
	h = h * 100; 
	i = i * 10; 
	k = g + h+ i + j; 

	if( k < 2000 ) 
		return 0; 

	return 1;
}

int isEmail( char* token ) 
{ 
	if(token == NULL || (*token) == '\0')
			return 0; 

	int k; 
	k = nullCheck( token ); 
	if( k == 0 ) 
		return 0; 

	if( *(token + (k - 1)) != 'm' ) 
		return 0;

	if( *(token + (k - 2)) != 'o' ) 
		return 0;

	if( *(token + (k - 3)) != 'c' ) 
		return 0;

	if( *(token + (k - 4)) != '.' ) 
		return 0;

	int x = 1; 
	while(*(token + x) != '\0')
	{ 
		if( *(token + x) ==	'@' )
			return 1;
		
		x++; 
	} 
	return 0; 
}

int nullCheck( char* token ) 
{ 
	int k; 

	for( k = 0; k < 100; k++ ) 
	{ 
		if( *(token + k) == '\0' ) 
		{ 
			return k;
		} 
	} 
	return 0; 
} 


