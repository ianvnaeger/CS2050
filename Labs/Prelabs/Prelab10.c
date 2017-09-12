#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

/*
 ** Parameters:
 ** token - A string
 **
 ** Return:
 * 1 if the string is a valid phone number,
 ** 0 otherwise
 **
 ** A valid phone number takes the form
 ** (XXX)XXX-XXXX where X is a digit 0-9. 
 */
int isPhoneNumber(char* token);

int main(void) {
//This is a valid phone number
	assert(isPhoneNumber("(123)456-7890") == 1);
//These are not valid phone numbers
	assert(isPhoneNumber("123-456-7890")    == 0);
	assert(isPhoneNumber("1234567890")      == 0);
	assert(isPhoneNumber("(123) 456-7890") == 0);
	assert(isPhoneNumber("Hello World")     == 0);
	assert(isPhoneNumber("")				== 0);
	printf("Congratulations! You finsihed the prelab!");
	return 0;
}

int isPhoneNumber(char* token) {
	if(token == NULL || (*token) == '\0')
			return 0; 
	int x =0; 
	while(*(token+x) != '\0')
	{
			switch(x)
			{
				case 0: 
					if(*(token+0) != '(')
						return 0; 
					break;
				case 4:
					if(*(token+4) != ')')
						return 0; 
					break;
				case 8: 
					if(*(token+8) != '-')
						return 0; 
					break; 
				default:
					if(isdigit(*(token+x)) == 0)
						return 0;
					break; 
			}
			x++;
	}
	return 1;
}
