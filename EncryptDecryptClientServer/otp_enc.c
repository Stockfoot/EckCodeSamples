/************************************************************************************************************
*	PROGRAM:		Encryption Client (otp_enc.c)
*	AUTHOR:			Russell Eck
*	DATE:			12/1/2019
*	DESCRIPTION:	This is the client side program for encryption. This program extracts plain text and key
*					text from files provided as arguments upon execution. It scans both of these for invalid
*					characters before proceeding. The program then connects to the otp_enc_d server. It sends
*					the plain text and key to the server to be encrypted then receives back a cipher key which
*					it outputs to stdout which usually gets redirected to a file upon execution.
************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define MAX_SIZE 100000

/************************************************************************************************************
*										BEGIN MAIN
************************************************************************************************************/
int main(int argc, char *argv[])
{
	/********************************************************
	* VARIABLE DECLARATION AND INITIALIZATION
	********************************************************/
	int i = 0;
	int compareResult = 0;
	int socketFD;
	int portNumber;
	int charsWritten;
	int charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char cipherKey[MAX_SIZE];
	char fileReadBuffer[MAX_SIZE];
	char keyReadBuffer[MAX_SIZE];
	char receiveTextBuffer[MAX_SIZE];
	char confirmationBuffer[10];
	char localHost[] = "localhost";
	FILE *plainTextFile;
	FILE *keyFile;
	int invalidCharBool = 0;
	int plainTextCharCount = 0;
	int keyCharCount = 0;

	//Clear out buffers
	memset(fileReadBuffer, '\0', sizeof(fileReadBuffer));
	memset(keyReadBuffer, '\0', sizeof(keyReadBuffer));
	memset(confirmationBuffer, '\0', sizeof(confirmationBuffer));
	memset(cipherKey, '\0', sizeof(cipherKey));
	memset(receiveTextBuffer, '\0', sizeof(receiveTextBuffer));

    //Check usage & args
	if (argc < 4)
	{
		fprintf(stderr,"USAGE: %s hostname port\n", argv[0]);
		exit(1);
	}


	/****************************************************************
	* EXTRACT TEXT FROM PLAINTEXT AND KEY FILES AND PLACE IN BUFFERS
	****************************************************************/
	//Open the file passed as argument for reading
	plainTextFile = fopen(argv[1], "r");
	keyFile = fopen(argv[2], "r");
	
	//Issue error if plain text file not found or could not be opened
	if (plainTextFile == NULL)
	{
		fprintf(stderr, "ERROR The plain text file could not be found or open\n");
	}

	//Issue error if key file not found or could not be opened
	if (keyFile == NULL)
	{
		fprintf(stderr, "ERROR The key file could not be found or open\n");
	}

	//Extract everything from the file and place in fileReadBuffer and keyReadBuffer
	fgets(fileReadBuffer, (sizeof(fileReadBuffer) - 1), plainTextFile);
	fgets(keyReadBuffer, (sizeof(keyReadBuffer) - 1), keyFile);

	//Remove the trailing new line that fgets adds to the buffers
	fileReadBuffer[strcspn(fileReadBuffer, "\n")] = '\0';
	keyReadBuffer[strcspn(keyReadBuffer, "\n")] = '\0';

	//Close the file
	fclose(plainTextFile);
	fclose(keyFile);
	
	/****************************************************************
	* LOOP THROUGH PLAINTEXT AND VERIFY IF CHARACTERS ARE ALL VALID
	****************************************************************/
	//Loop through the plaintext and check if there are any invalid characters
	i = 0;
	while (invalidCharBool == 0 && fileReadBuffer[i] != '\0')
	{
		//If any character other than the 26 capital letters or a space is found set bool to true and exit loop
		if ((fileReadBuffer[i] < 65 && fileReadBuffer[i] != 32) || (fileReadBuffer[i] > 90))
		{
			invalidCharBool = 1;
		}

		i++;
	}

	//If the file contains any invalid characters issue error and exit(1)
	if (invalidCharBool == 1)
	{
		fprintf(stderr, "ERROR: the %s file contains invalid characters\n", argv[1]);
		exit(1);
	}
	
	/************************************************************************
	* COUNT NUMBER OF CHARACTERS IN PLAIN TEXT AND KEY. ERROR IS KEY IS LESS
	************************************************************************/
	//Count length of each buffer
	plainTextCharCount = strlen(fileReadBuffer);
	keyCharCount = strlen(keyReadBuffer);

	//If the key is shorter than the plain text issue error and exit(1)
	if (keyCharCount < plainTextCharCount)
	{
		fprintf(stderr, "ERROR: Key \'%s\' is too short\n", argv[2]);
		exit(1);
	}

	/***************************************************
	* ADD '@' CHARACTER AT END OF TEXTS AS A DELIMITER
	***************************************************/
	fileReadBuffer[plainTextCharCount] = '@';
	keyReadBuffer[plainTextCharCount] = '@';

	/********************************************************
	* SET UP ADDRESS STRUCT FOR THIS CLIENT
	********************************************************/
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname(localHost); // Convert the machine name into a special form of address
	
	if (serverHostInfo == NULL)
	{
		fprintf(stderr, "CLIENT: ERROR, no such host\n");
		exit(0);
	}

	//Copy in the address
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length);

	/*********************
	* CREATE SOCKET
	*********************/
	socketFD = socket(AF_INET, SOCK_STREAM, 0); 
	
	if (socketFD < 0)
	{
		fprintf(stderr, "CLIENT: ERROR opening socket\n");
	}

	/****************************
	* CONNECT TO SERVER
	****************************/
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
	{
		fprintf(stderr, "CLIENT: ERROR connecting\n");
		exit(2);
	}
	
	/********************************************
	* CHECK IF OTP_ENC IS CONNECTED TO OTP_ENC_D
	********************************************/
	//This will receive either "otp_enc_d" or "otp_dec_d" from the connected server
	charsRead = recv(socketFD, confirmationBuffer, (sizeof(confirmationBuffer) - 1), 0);
	if (charsRead < 0)
	{
		fprintf(stderr, "ERROR: Confirmation failed from server\n");
	}

	//Compare the received message with "otp_enc_d"
	compareResult = strcmp(confirmationBuffer, "otp_enc_d");

	//If the message from the connected server isn't "otp_enc_d" then it is the wrong server
	//Output error and exit(2)
	if (compareResult != 0)
	{
		fprintf(stderr, "ERROR: Could not contact otp_enc_d on port %d\n", portNumber);
		exit(2);
	}
	
	memset(confirmationBuffer, '\0', sizeof(confirmationBuffer));
	
	/**************************************
	* SEND PLAIN TEXT TO OTP_ENC_D SERVER
	**************************************/
	//We must send plainTextCharCount + 1 due to adding the delimiter
	charsWritten = send(socketFD, fileReadBuffer, (plainTextCharCount + 1), 0);
	if (charsWritten < 0)
	{
		fprintf(stderr, "CLIENT: ERROR writing to socket\n");
	}
	
	if (charsWritten < plainTextCharCount + 1)
	{
		fprintf(stderr, "CLIENT: WARNING: Not all data written to socket!\n");
	}
	
	/**************************************
	* RECEIVE CONFIRMATION FROM SERVER
	**************************************/
	charsRead = recv(socketFD, confirmationBuffer, (sizeof(confirmationBuffer) - 1), 0);
	if (charsRead < 0)
	{
		fprintf(stderr, "ERROR: Confirmation failed from server\n");
	}

	/**************************************
	* SEND KEY TEXT TO OTP_ENC_D SERVER
	**************************************/
	//We must send plainTextCharCount + 1 due to adding the delimiter
	charsWritten = send(socketFD, keyReadBuffer, (plainTextCharCount + 1), 0);
	if (charsWritten < 0)
	{
		fprintf(stderr, "CLIENT: ERROR writing to socket\n");
	}
	
	if (charsWritten < plainTextCharCount + 1)
	{
		fprintf(stderr, "CLIENT: WARNING: Not all data written to socket!\n");
	}

	/****************************************
	* RECEIVE FINAL CIPHER KEY FROM SERVER
	****************************************/
	while (strstr(cipherKey, "@") == NULL)
	{
		//Clear receiving buffer
		memset(receiveTextBuffer, '\0', sizeof(receiveTextBuffer));
		
		//Get the next chuck of text being sent
		charsRead = recv(socketFD, receiveTextBuffer, (sizeof(receiveTextBuffer) - 1), 0);
	
		//Concatentate the received text into the final cipher text buffer
		strcat(cipherKey, receiveTextBuffer);
		
		//Break loop if there is an error receiving the data
		if (charsRead < 0)
		{
			fprintf(stderr, "ERROR: failed to receive cipher text from server\n");
			break;
		}
	}

	//Replace the delimiter with null terminator
	cipherKey[strstr(cipherKey, "@") - cipherKey] = '\0';

	/*********************************************************
	* PRINT THE FINALIZED CIPHER KEY ADDING A NEW LINE TO END
	*********************************************************/
	printf("%s\n", cipherKey);

	//Close Socket before ending
	close(socketFD);
	
	return 0;
}




