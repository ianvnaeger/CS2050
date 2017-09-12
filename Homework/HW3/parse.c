#include "game.h"

//If you haven't knocked yourself out in boss.c, do it here.
//Otherwise, knock yourself out again. 

void ParseShieldInfo( Shield* s, FILE* fp )
{
	if( fp == NULL )
	{
		return; 
	}// Error checks the file, because I don't trust any one, not anymore...
	
	char* line = (char*)malloc( sizeof(char) * MAXFILELINELENGTH ); 
	if( fgets( line, MAXFILELINELENGTH, fp ) == NULL )
	{
		return; 
	}// Checks to see if line has anything, because I don't even trust myself...

	strcpy( s->name, strtok( line, "|" ) );
	s->cost = atoi( strtok( NULL, "|" ) ); 
	s->defense = atoi( strtok( NULL, "|" ) ); 
	strcpy( s->description, strtok( NULL, "|") );  
	s->description[strlen(s->description)-1] = '\0';
	// Fills the appropriate shield characteristics with things learned from that sneaky little line
}

void ParseSwordInfo( Sword* s, FILE* fp )
{

	if( fp == NULL )
	{
		return; 
	}// Error checks the file, because Momma didn't raise no fool
	
	char* line = (char*)malloc( sizeof(char) * MAXFILELINELENGTH ); 
	if( fgets( line, MAXFILELINELENGTH, fp ) == NULL )
	{
		return; 
	}// Error checks line, because you can't trust line for nothing, just like my ex

	strcpy( s->name, strtok( line, "|" ) );
	s->cost = atoi( strtok( NULL, "|" ) ); 
	s->attack = atoi( strtok( NULL, "|" ) ); 
	strcpy( s->description, strtok( NULL, "|" ) );  
	s->description[strlen(s->description)-1] = '\0'; 
	// Fills the different appropriate sword characteristics with things given by line, because like my ex, line likes to give stuff to lots of people
}


