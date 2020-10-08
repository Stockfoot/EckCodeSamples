/************************************************************************************************************
*	PROGRAM:		Deccryption Server (otp_dec_d.c)
*	AUTHOR:			Russell Eck
*	DATE:			12/1/2019
*	DESCRIPTION:	This is the server portion of decryption. This program loops infinitely and can handle
*					up to 5 incoming connections. The program forks off a child after accepting connection
*					and receives cipher text and key text from the client. It then converts both of these texts
*					to integers between 0-26. It then decrypts the message performing modulus addition. It
*					then converts the integers back to characters and sends the plain text to the client.
************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_SIZE 100000

void convertCharsToInts(char inputCharArray[], int outputIntArray[], int sizeOfInput);
void convertIntsToChars(int inputIntArray[], char outputCharArray[], int sizeOfInput);
void decrypt(int intPlainTextArray[], int intKeyTextArray[], int intCipherTextArray[], int sizeOfInput);

/************************************************************************************************************
*										BEGIN MAIN
************************************************************************************************************/
int main(int argc, char *argv[])
{
	/********************************************************
	* VARIABLE DECLARATION AND INITIALIZATION
	********************************************************/
	int listenSocketFD;
	int establishedConnectionFD;
	int portNumber;
	int charsRead;
	int i = 0;
	int child_exit_status;
	socklen_t sizeOfClientInfo;
	char plainTextBuffer[MAX_SIZE];
	char keyTextBuffer[MAX_SIZE];
	char cipherTextBuffer[MAX_SIZE];
	char receiveTextBuffer[MAX_SIZE];
	int intPlainText[MAX_SIZE];
	int intKeyText[MAX_SIZE];
	int intCipherText[MAX_SIZE];
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	pid_t spawnPID;

	//Clear character buffers
	memset(plainTextBuffer, '\0', sizeof(plainTextBuffer));
	memset(keyTextBuffer, '\0', sizeof(keyTextBuffer));
	memset(cipherTextBuffer, '\0', sizeof(cipherTextBuffer));
	memset(receiveTextBuffer, '\0', sizeof(receiveTextBuffer));

	//Set -1 default values in int arrays
	for (i = 0; i < MAX_SIZE; i++)
	{
		intPlainText[i] = -1;
		intKeyText[i] = -1;
		intCipherText[i] = 1;
	}

	//Check usage and arguments
	if (argc < 2)
	{ 
		fprintf(stderr,"USAGE: %s port\n", argv[0]);
		exit(1);
	}

	/*******************************************
	* SET UP ADDRESS STRUCT FOR THIS SERVER
	*******************************************/
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	/**********************
	* CREATE SOCKET
	**********************/
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);

	//If the file descriptor is < 0 the socket failed
	if (listenSocketFD < 0)
	{
		fprintf(stderr, "ERROR opening socket\n");
		exit(1);
	}

	/**********************************
	* BEGIN LISTENING ON SOCKET
	**********************************/
	//Connect socket to port
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		fprintf(stderr, "ERROR on binding\n");
		exit(1);
	}

	//Turn socket on - It can receive up to 5 connections
	listen(listenSocketFD, 5);

	while (1)
	{
		/************************************************************************
		* ACCEPT A CONNECTION, BLOCK IF ONE IS NOT AVAILABLE UNTIL ONE CONNECTS
		************************************************************************/
		//Get the size of the address for the client that will connect
		sizeOfClientInfo = sizeof(clientAddress);
	
		//Accept the connection from listen queue or block here until a connection request arrives
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo);
		
		//If connection fails error and exit
		if (establishedConnectionFD < 0)
		{
			fprintf(stderr, "ERROR on accept\n");
		}
	
		/********************************
		* SPAWN A NEW PROCESS
		********************************/
		spawnPID = fork();
	
		if (spawnPID < 0)
		{
			//New process failed to creat, error and break
			fprintf(stderr, "ERROR on creating a new fork\n");
		}
			
		/***************************************
		* CHILD PROCESS GETS TEXTS AND DECRYPTS
		***************************************/		 
		else if (spawnPID == 0)
		{			
			close(listenSocketFD);
				
			/********************************
			* SEND SERVER NAME TO CLIENT
			********************************/
			charsRead = send(establishedConnectionFD, "otp_dec_d", 9, 0);
			if (charsRead < 0)
			{
				fprintf(stderr, "ERROR sending server name\n");
			}
				
			/********************************
			* GET CIPHER TEXT FROM OTP_DEC
			********************************/
			//Loop until we have found the delimiter at the end of the received text
			while (strstr(cipherTextBuffer, "@") == NULL)
			{
				//Clear receiving buffer
				memset(receiveTextBuffer, '\0', sizeof(receiveTextBuffer));

				//Get the next chunk of text being sent
				charsRead = recv(establishedConnectionFD, receiveTextBuffer, (sizeof(receiveTextBuffer) - 1), 0);
					
				//Concatenate the received text into the final cipher text buffer
				strcat(cipherTextBuffer, receiveTextBuffer);
				
				//Break loop if there is an error receiving the data
				if (charsRead < 0)
				{
					fprintf(stderr, "ERROR reading from socket\n");
					break;
				}
			}
				
			//Replace delimiter with null terminator
			cipherTextBuffer[strstr(cipherTextBuffer, "@") - cipherTextBuffer] = '\0';
	
			/********************************
			* SEND CONFIRMATION TO CLIENT
			********************************/
			charsRead = send(establishedConnectionFD, "Success", 7, 0);
			if (charsRead < 0)
			{
				fprintf(stderr, "ERROR sending confirmation\n");
			}
	
			/********************************
			* GET KEY TEXT FROM OTP_DEC
			********************************/
			//Loop until we have found the delimiter at the end of the received text
			while (strstr(keyTextBuffer, "@") == NULL)
			{
				//Clear receiving buffer
				memset(receiveTextBuffer, '\0', sizeof(receiveTextBuffer));

				//Get the next chunk of text being sent
				charsRead = recv(establishedConnectionFD, receiveTextBuffer, (sizeof(receiveTextBuffer) - 1), 0);
				
				//Concatenate the received text into the final key text buffer
				strcat(keyTextBuffer, receiveTextBuffer);
			
				//Break loop if there is an error receiving the data
				if (charsRead < 0)
					{
					fprintf(stderr, "ERROR reading from socket\n");
					break;
				}
			}
				
			//Replace delimiter with null terminator
			keyTextBuffer[strstr(keyTextBuffer, "@") - keyTextBuffer] = '\0';
			
			/*****************************************
			* CONVERT CIPHER TEXT AND KEY TO INTEGERS
			*****************************************/
			convertCharsToInts(cipherTextBuffer, intCipherText, strlen(cipherTextBuffer));
			convertCharsToInts(keyTextBuffer, intKeyText, strlen(cipherTextBuffer));			
				
			/*******************************
			* DECRYPT THE CIPHER INTEGERS
			*******************************/
			decrypt(intPlainText, intKeyText, intCipherText, strlen(cipherTextBuffer));
				
			/********************************************
			* CONVERT THE PLAIN TEXT INTS TO CHARS
			********************************************/
			convertIntsToChars(intPlainText, plainTextBuffer, strlen(cipherTextBuffer));
				
			/********************************************
			* ADD DELIMITER TO PLAIN TEXT BEFORE SENDING
			********************************************/
			plainTextBuffer[strlen(plainTextBuffer)] = '@';

			/********************************
			* SEND PLAIN TEXT TO CLIENT
			********************************/
			charsRead = send(establishedConnectionFD, plainTextBuffer, strlen(plainTextBuffer), 0);
			if (charsRead < 0)
			{
				fprintf(stderr, "ERROR sending plain text to client\n");
			}
	
			//Close existing socket which is connected to the client
			close(establishedConnectionFD);
			exit(0);
		}
		
		else
		{
			//Close existing socket which is connected to the client
			close(establishedConnectionFD);

			do
			{
				spawnPID = waitpid(-1, &child_exit_status, WNOHANG);
			}
			while (spawnPID > 0);
		}


	}

	close(listenSocketFD); // Close the listening socket

	return 0; 
}


/************************************************************************************************************
* 										void convertCharsToInts()
*							
*	Description:	This function receives an input character array, an output integer array, and the size
*					of the input array. The function then converts all the characters to integers between
*					0-26 where 26 represents a space. It achieves this using ASCII values.
************************************************************************************************************/
void convertCharsToInts(char inputCharArray[], int outputIntArray[], int sizeOfInput)
{
	int i = 0;

	//Loop through the character array converting chars to ints
	for (i = 0; i < sizeOfInput; i++)
	{
		//Subtract 65 from every character results in A=0, B=1, ..., Z=25, Space=26
		outputIntArray[i] = inputCharArray[i] - 65;
	
		//If the result is -33 then it was a space and needs to be converted to 26
		if (outputIntArray[i] == -33)
		{
			outputIntArray[i] = 26;
		}
	}
}



/************************************************************************************************************
* 										void convertIntsToChars()
*							
*	Description:	This function receives an input integer array, an output character array, and the size of
*					the input array. The function then converts all of the integers to characters between
*					A-Z and the space character. It achieves this using ASCII values.
************************************************************************************************************/
void convertIntsToChars(int inputIntArray[], char outputCharArray[], int sizeOfInput)
{
	int i = 0;

	//Loop through the integer array converting ints to chars
	for (i = 0; i < sizeOfInput; i++)
	{
		//Add 65 to every character results in ASCII values for A=65, B=66, ..., Z=90
		outputCharArray[i] = inputIntArray[i] + 65;

		//If the results is 91 then it was a space and needs to be converted
		if (outputCharArray[i] == 91)
		{
			outputCharArray[i] = ' ';
		}
	}
}


/************************************************************************************************************
* 										void decrypt()
*							
*	Description:	This function receives 3 integer arrays representing integer values from the plain text,
*					key text, and the cipher key as well as the size of the array. It decrypts the cipher
*					by performing modular addition on the cipher and key integer arrays.
************************************************************************************************************/
void decrypt(int intPlainTextArray[], int intKeyTextArray[], int intCipherTextArray[], int sizeOfInput)
{
	int i = 0;

	for (i = 0; i < sizeOfInput; i++)
	{
		intPlainTextArray[i] = (intCipherTextArray[i] - intKeyTextArray[i]);

		if (intPlainTextArray[i] < 0)
		{
			intPlainTextArray[i] = intPlainTextArray[i] + 27;
		}

	}
}




