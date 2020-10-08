/************************************************************************************************************
*	PROGRAM:		Keygen (keygen.c)
*	AUTHOR:			Russell Eck
*	DATE:			12/1/2019
*	DESCRIPTION:	This program generates a random key using all of the capital letters of the alphabet plus
*					the space character. On execution of the program the user specifies how many random
*					characters they would like to generate. The default execution displays the key to stdout
*					but is generally redirected to a file upon execution.
************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>


/************************************************************************************************************
*										BEGIN MAIN
************************************************************************************************************/
int main(int argc, char *argv[])
{
	//Make sure user passed a number of keys to generate
	if (argc != 2)
	{ 
		fprintf(stderr, "ERROR You must provide the number of characters to generate\n");
	}

	/********************************************************
	* VARIABLE DECLARATION AND INITIALIZATION
	********************************************************/
	srand(time(NULL));
	int numberOfKeys = atoi(argv[1]);
	int i = 0;
	char keyBuffer[100000];
	char keygenCharacters[27] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
								'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
								'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ' }; 

	//Clear the keyBuffer before generating random characters
	memset(keyBuffer, '\0', sizeof(keyBuffer));

	/********************************************************
	* GENERATE THE NUMBER OF RANDOM CHARACTERS SPECIFIED
	********************************************************/
	for (i = 0; i < numberOfKeys; i++)
	{
		keyBuffer[i] = keygenCharacters[rand() % 27];
	}
	
	//Output to stdout with a new line character
	//This is redirected to a file upon execution (keygen 20 > myKeyFile)
	printf("%s\n", keyBuffer);

	return 0; 
}



