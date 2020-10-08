/************************************************************************************************************
*	PROGRAM:		ftserver (ftserver.cpp)
*	AUTHOR:			Russell Eck
*	DATE:			2/25/2020
*	DESCRIPTION:	This is the server portion of a file transfer system. The server starts on a specific port
*					specified in the command line at launch. It then waits for the client to connect. It handles
*					a directory listing function that goes through the current working directory of the server and
*					sends back the name of all the files and folder to the client. It also has a get file function.
*					This function checks if the requested file exists, if it doesn't it sends back and error message
*					to the client. If it does exist it sends the file to the client. If the client already has a 
*					file with the send name then it appens "copy" to the front of the file. Both functions use a second
*					TCP socket to send the data.
*	SOURCES:		Parse out string to vector reference www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++
*					Majority of server info and error handling reused from my final project in CS344 Operating Systems
*					File name extraction in current working directory taken from my Project 2 in CS344 Operating Systems
************************************************************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

#define MAX_SIZE 2000

void startUp(int argc, int portNumber, char *hostName, int hostNameSize);
void getCommandInfo(char *commandInfo, int sizeOfCommandInfo, char *sendRecvBuffer, int sizeOfSendRecvBuffer, int establishedConnectionFD, vector<string> &splitCommandInfo);	
void listCommand(vector<string> &splitCommandInfo, int establishedConnnectionFD);
void getCommand(vector<string> &splitCommandInfo, int establishedConnectionFD);

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
	socklen_t sizeOfClientInfo;
	char hostName[50];
	char commandInfo[MAX_SIZE];
	char sendRecvBuffer[MAX_SIZE];
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	vector<string> splitCommandInfo;

	//Clear character buffers
	memset(hostName, '\0', sizeof(hostName));
	memset(commandInfo, '\0', sizeof(commandInfo));
	memset(sendRecvBuffer, '\0', sizeof(sendRecvBuffer));

	/******************************************************************
	* SET UP ADDRESS STRUCT FOR THIS SERVER AND CALL STARTUP FUNCTION
	******************************************************************/
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process
	startUp(argc, portNumber, hostName, sizeof(hostName)); // Check args and port ranges

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
	* BIND SOCKET WITH SERVER INFO
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

		//Display notification to screen
		cout << endl;
		cout << "*************************************" << endl;
		cout << "Server is waiting for a connection..." << endl;
		cout << "*************************************" << endl << endl;

		//Accept the connection from listen queue or block here until a connection request arrives
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo);
		
		//If connection fails error and exit
		if (establishedConnectionFD < 0)
		{
			fprintf(stderr, "ERROR on accept\n");
		}

		/************************************************************************
		* GET THE COMMAND FROM THE CLIENT, SEND ERROR BACK IF INVALID COMMAND
		************************************************************************/	
		getCommandInfo(commandInfo, sizeof(commandInfo), sendRecvBuffer, sizeof(sendRecvBuffer), establishedConnectionFD, splitCommandInfo);

		/********************************
		* PERFORM -l COMMAND
		********************************/
		if (splitCommandInfo.size() == 5)
		{
			listCommand(splitCommandInfo, establishedConnectionFD);
		}
		
		/********************************
		* PERFORM -g COMMAND
		********************************/
		else 
		{
			getCommand(splitCommandInfo, establishedConnectionFD);
		}

		
		close(establishedConnectionFD);

	}

	close(listenSocketFD); // Close the listening socket

	return 0; 
}


/************************************************************************************************************
* 										void startUp()
*							
*	Description:	This function is responsible for the initial startup of the server. It checks the number
*					of command line arguments as well as a valid port range. If not valid an error is issued
*					and the program exits, otherwise it displays the port number.
*	Pre Cond:		Startup of server with comand line arguments provided.
*	Post Cond:		Startup is validated and server displays port number
************************************************************************************************************/
void startUp(int argc, int portNumber, char *hostName, int hostNameSize)
{
	//Check usage and arguments
	if (argc != 2)
	{ 
		fprintf(stderr,"Error: Only one command line argument may be used to set up the server port\n");
		exit(1);
	}

	//Check for valid port range number
	if (portNumber < 20000 || portNumber > 60000)
	{
		fprintf(stderr, "Error: Restart the server with a valid port range from 20,000-60,000\n");
		exit(1);
	}

	//Get the host name and place in buffer
	gethostname(hostName, hostNameSize);

	//We passed the error checking, display server port number and host name
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "SERVER OPEN ON PORT:  " << portNumber << endl;
	cout << "SERVER HOST NAME IS:  " << hostName << endl;
	cout << "-------------------------------------------------" << endl << endl;

}



/************************************************************************************************************
* 										void getCommandInfo()
*							
*	Description:	This function gets the command info from the client. It then checks the command for errors
*					and notifies the client if there is. If not the function returns with a vector with the
*					command info that was sent from the client.
*	Pre Cond:		A valid connection from the client to the server and command info parsed out on client
*	Post Cond:		A vector that contains the parsed out command line info from the server
************************************************************************************************************/
void getCommandInfo(char *commandInfo, int sizeOfCommandInfo, char *sendRecvBuffer, int sizeOfSendRecvBuffer, int establishedConnectionFD, vector<string> &splitCommandInfo)
{
			
	//Clear buffers and vector
	memset(commandInfo, '\0', sizeOfCommandInfo);
	memset(sendRecvBuffer, '\0', sizeOfSendRecvBuffer);
	splitCommandInfo.clear();
	int charsRead = 0;
	int charsWritten = 0;

	//Get the data
	charsRead = recv(establishedConnectionFD, sendRecvBuffer, sizeOfSendRecvBuffer, 0);
					
	//Concatenate the received text into the commandInfo string
	strcat(commandInfo, sendRecvBuffer);
				
	//Error if problem receiving the data
	if (charsRead < 0)
	{
		fprintf(stderr, "ERROR reading from socket\n");
	}

	//Stream to break up string
	std::istringstream iss(commandInfo);
			
	//Loop through and put each word into the vector using spaces as delimeters
	for(string commandInfo; iss >> commandInfo; )
	{
		splitCommandInfo.push_back(commandInfo);
	}

	//Check command if -l was passed, send back error if incorrect
	if (splitCommandInfo.size() == 5)
	{
		//Command should be -l if a size of 4 args ws passed
		if (splitCommandInfo[2] != "-l")
		{
			//Clear buffer, place error message and send back to client
			memset(sendRecvBuffer, '\0', sizeOfSendRecvBuffer);
			sprintf(sendRecvBuffer, "Invalid command sent to server\n");
			charsWritten = send(establishedConnectionFD, sendRecvBuffer, sizeOfSendRecvBuffer, 0);
					
			//Error if problem sending data
			if (charsWritten < 0)
			{
				fprintf(stderr, "ERROR writing to socket\n");
			}

			cout << "Invalid command sent to server" << endl;
			close(establishedConnectionFD);
		}

		//Make sure the 2 port numbers are not the same
		if (splitCommandInfo[1] == splitCommandInfo[3])
		{
			//Clear buffer, place error message and send back to client
			memset(sendRecvBuffer, '\0', sizeOfSendRecvBuffer);
			sprintf(sendRecvBuffer, "Invalid command sent to server\n");
			charsWritten = send(establishedConnectionFD, sendRecvBuffer, sizeOfSendRecvBuffer, 0);
					
			//Error if problem sending data
			if (charsWritten < 0)
			{
				fprintf(stderr, "ERROR writing to socket\n");
			}
					
			cout << "Invalid command sent to server" << endl;
			close(establishedConnectionFD);
		}
	}

	//Check command if -g was passed, send back error if incorrect
	else if (splitCommandInfo.size() == 6)
	{
		//If 5 command line arguments were passed the command should be -g
		if (splitCommandInfo[2] != "-g")
		{
			//Clear buffer, place error message and send back to client
			memset(sendRecvBuffer, '\0', sizeOfSendRecvBuffer);
			sprintf(sendRecvBuffer, "Invalid command sent to server\n");
			charsWritten = send(establishedConnectionFD, sendRecvBuffer, sizeOfSendRecvBuffer, 0);
					
			//Error if problem sending data
			if (charsWritten < 0)
			{
				fprintf(stderr, "ERROR writing to socket\n");
			}

			cout << "Invalid command sent to server" << endl;	
			close(establishedConnectionFD);
		}
		
		//Send error back if port numbers are the same
		if (splitCommandInfo[1] == splitCommandInfo[4])
		{
			//Clear buffer, place error message and send back to client
			memset(sendRecvBuffer, '\0', sizeOfSendRecvBuffer);
			sprintf(sendRecvBuffer, "Invalid command sent to server\n");
			charsWritten = send(establishedConnectionFD, sendRecvBuffer, sizeOfSendRecvBuffer, 0);
					
			//Error if problem sending data
			if (charsWritten < 0)
			{
				fprintf(stderr, "ERROR writing to socket\n");
			}

			cout << "Invalid command sent to server" << endl;	
			close(establishedConnectionFD);
		}
	}

	//Send error back due to incorrect number of command line arguments
	else
	{			
		//Clear buffer, place error message and send back to client
		memset(sendRecvBuffer, '\0', sizeOfSendRecvBuffer);
		sprintf(sendRecvBuffer, "Invalid command sent to server\n");
		charsWritten = send(establishedConnectionFD, sendRecvBuffer, sizeOfSendRecvBuffer, 0);
					
		//Error if problem sending data
		if (charsWritten < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
		}

		cout << "Invalid command sent to server" << endl;
		close(establishedConnectionFD);
	}	
}



/************************************************************************************************************
* 										void listCommand()
*							
*	Description:	This function connects to the client using a second TCP connection. The server side then
*					loops through its current working directory concatenating a string that contains the
*					names of all the directories and files. It then sends this string to the client where it
*					is then displayed.
*	Pre Cond:		A valid server set up and a valid client request.
*	Post Cond:		A string containing all of the directories and files in the current working directory
*					that is returned to the client.
************************************************************************************************************/
void listCommand(vector<string> &splitCommandInfo, int establishedConnectionFD)
{
	/********************************
	* FUNCTION VARIABLES
	********************************/ 
	char currentDirectoryName[100];
	char listOfFiles[MAX_SIZE];
	DIR *directoryPointer;
	struct dirent *fileInDir;
	int charsWritten = 0;
	struct sockaddr_in dataAddress;
	struct hostent* serverHostInfo;
	int dataPortNumber = 0;
	int socketFD = 0;
	bool connectionSuccess = false;

	//Clear character buffers
	memset(currentDirectoryName, '\0', sizeof(currentDirectoryName));
	memset(listOfFiles, '\0', sizeof(listOfFiles));
		
	/********************************
	* SET UP DATA SOCKET
	********************************/ 
	
	//Convert port number and host name into useable c-strings for socket functions
	const char *portString = splitCommandInfo[3].c_str();
	const char *hostString = splitCommandInfo[4].c_str();

	//Setup connection socket
	memset((char *)&dataAddress, '\0', sizeof(dataAddress)); // Clear out the address struct
	dataPortNumber = atoi(portString); // Get the port number, convert to an integer from a string
	dataAddress.sin_family = AF_INET; // Create a network-capable socket
	dataAddress.sin_port = htons(dataPortNumber); // Store the port number
	serverHostInfo = gethostbyname(hostString); // Convert the machine name into a special form of address

	//Error if host info doesn't exist
	if (serverHostInfo == NULL)
	{
		fprintf(stderr, "ERROR: Server list directory, no such host\n");
		exit(0);
	}

	//Copy in the address
	memcpy((char*)&dataAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length);

	//Create the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0)
	{
		fprintf(stderr, "ERROR: Server list directory could not create socket\n");
	}

	//Loop until we get a successfull connection, this forces synchronization
	while (connectionSuccess == false)
	{
		//Connect to the client
		if (connect(socketFD, (struct sockaddr*)&dataAddress, sizeof(dataAddress)) >= 0)
		{
			connectionSuccess = true;
		}
	}

	
	/**********************************
	* CREATE SERVER DIRECTORY LISTING
	**********************************/ 
	
	//Display server connection info
	cout << "---------------------------------------------------------------------" << endl;
	cout << "Connection from " << splitCommandInfo[4] << endl;
	cout << "List directory requested on port " << splitCommandInfo[3] << endl;
	cout << "Sending directory contents to " << splitCommandInfo[4] << ":" << splitCommandInfo[3] << endl;
	cout << "--------------------------------------------------------------------" << endl;

	//Get the name of the current working directory
	getcwd(currentDirectoryName, sizeof(currentDirectoryName));
	
	//Open up the directory the server is running in
	directoryPointer = opendir(currentDirectoryName);

	//If directory could not be opened issue error
	if (directoryPointer == NULL)
	{
		perror("ERROR: Could not open current directory\n");
	}

	//Loop through the current working directory and extract the names, concatenate into buffer
	while ((fileInDir = readdir(directoryPointer)) != NULL)
	{
		//Add files to the directory list ignoring "." and ".."
		if (strcmp(fileInDir -> d_name, ".") != 0 && strcmp(fileInDir -> d_name, "..") != 0)
		{
			strcat(listOfFiles, fileInDir -> d_name);
			strcat(listOfFiles, "\n");	
		}
	}
	
	
	/**********************************
	* SEND THE DIRECTORY LISTING
	**********************************/ 
	
	//Send the file/directory list back to the client
	charsWritten = send(socketFD, listOfFiles, sizeof(listOfFiles), 0);
					
	//Error if problem sending data
	if (charsWritten < 0)
	{
		fprintf(stderr, "ERROR writing to socket\n");
	}

	//Close directory pointer
	closedir(directoryPointer);
	
	//Close connection with the client
	close(socketFD);

}



/************************************************************************************************************
* 										void getCommand()
*							
*	Description:	This function connects to the client with a second TCP data connection. It then looks for
*					the requested file in the servers current working directory. If the file doesn't exist
*					it sends back an error message to the client which is then displayed. Otherwise it extracts
*					all the data from the file and sends it to the client.
*	Pre Cond:		A valid server connection and client connection set up.
*	Post Cond:		The function returns an error if file doesn't exist or returns the requested file.
************************************************************************************************************/
void getCommand(vector<string> &splitCommandInfo, int establishedConnectionFD)
{
	/********************************
	* FUNCTION VARIABLES
	********************************/ 
	char currentDirectoryName[100];
	char fileNotFoundMessage[200];
	char file[] = "file\n";
	char error[] = "error";
	char buffer[1024];
	DIR *directoryPointer;
	FILE *filePointer;
	struct dirent *fileInDir;
	int charsWritten = 0;
	int charsRead = 0;
	struct sockaddr_in dataAddress;
	struct hostent* serverHostInfo;
	int dataPortNumber = 0;
	int socketFD = 0;
	bool connectionSuccess = false;

	//Clear character buffers
	memset(currentDirectoryName, '\0', sizeof(currentDirectoryName));
	memset(buffer, '\0', sizeof(buffer));
	memset(fileNotFoundMessage, '\0', sizeof(fileNotFoundMessage));
	
	//Convert port number and host name into useable c-strings for socket functions
	const char *portString = splitCommandInfo[4].c_str();
	const char *hostString = splitCommandInfo[5].c_str();
	const char *fileName = splitCommandInfo[3].c_str();
	const char *serverName = splitCommandInfo[0].c_str();
	const char *serverPort = splitCommandInfo[1].c_str();
	
	/********************************
	* SET UP DATA SOCKET
	********************************/ 
	
	//Setup connection socket
	memset((char *)&dataAddress, '\0', sizeof(dataAddress)); // Clear out the address struct
	dataPortNumber = atoi(portString); // Get the port number, convert to an integer from a string
	dataAddress.sin_family = AF_INET; // Create a network-capable socket
	dataAddress.sin_port = htons(dataPortNumber); // Store the port number
	serverHostInfo = gethostbyname(hostString); // Convert the machine name into a special form of address

	//Error if host info doesn't exist
	if (serverHostInfo == NULL)
	{
		fprintf(stderr, "ERROR: Server list directory, no such host\n");
		exit(0);
	}

	//Copy in the address
	memcpy((char*)&dataAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length);

	//Create the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0)
	{
		fprintf(stderr, "ERROR: Server list directory could not create socket\n");
	}

	//Loop until we get a successfull connection, this forces synchronization
	while (connectionSuccess == false)
	{
		//Connect to the client
		if (connect(socketFD, (struct sockaddr*)&dataAddress, sizeof(dataAddress)) >= 0)
		{
			connectionSuccess = true;
		}
	}

	/**********************************
	* CHECK IF REQUESTED FILE EXISTS
	**********************************/ 
	
	//Get the name of the current working directory
	getcwd(currentDirectoryName, sizeof(currentDirectoryName));

	//Open up the directory the server is running in
	directoryPointer = opendir(currentDirectoryName);

	//If directory could not be opened issue error
	if (directoryPointer == NULL)
	{
		perror("ERROR: Could not open current directory\n");
	}

	//Bool to check if the file exists
	bool fileExists = false;

	//Loop through the current working directory and see if the file exists
	while ((fileInDir = readdir(directoryPointer)) != NULL)
	{
		//If the file is there set bool to true
		if (strcmp(fileInDir -> d_name, fileName) == 0)
		{
			fileExists = true;
		}
	}
	

	/**********************************
	* FILE EXISTS, SEND THE FILE
	**********************************/ 
	if (fileExists == true)
	{
		//Display connection info
		cout << "-----------------------------------------------------------" << endl;
		cout << "Connection from " << splitCommandInfo[5] << endl;
		cout << "File " << splitCommandInfo[3] << " requested on port " << splitCommandInfo[4] << endl;
		cout << "Sending " << splitCommandInfo[3] << " to " << splitCommandInfo[5] << ":" << splitCommandInfo[4] << endl;
		cout << "-----------------------------------------------------------" << endl;

		//Send the error back to the client
		charsWritten = send(socketFD, file, sizeof(file), 0);
					
		//Error if problem sending data
		if (charsWritten < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
		}
		
		//Get the response
		charsRead = recv(socketFD, buffer, sizeof(buffer), 0);

		//Error is problem recv data
		if (charsRead < 0)
		{
			fprintf(stderr, "Error recv from socket\n");
		}


		/*******************************
		* EXTRACT DATA FROM FILE
		*******************************/
			
		//Open the file using the converted *fileName.c_str()
		filePointer = fopen(fileName, "r");

		//Error if file doesn't exist or could not be opened
		if (filePointer == NULL)
		{
			cout << "File opening failed" << endl;
		}

		memset(buffer, '\0', sizeof(buffer));

		//Extract everything from the file
		while (fgets(buffer, (sizeof(buffer) - 1), filePointer))
		{
			//Send extracted text to the client
			charsWritten = send(socketFD, buffer, strlen(buffer), 0);
		
			//Error if problem sending data
			if (charsWritten < 0)
			{
				fprintf(stderr, "ERROR writing file contents to client\n");
			}
		
			memset(buffer, '\0', sizeof(buffer));

		}

		//Close the file
		fclose(filePointer);

	}
	
	/***************************************************
	* FILE DOES NOT EXIST, SENT ERROR MESSAGE TO CLIENT
	***************************************************/
	else
	{
		//Send the error back to the client
		charsWritten = send(socketFD, error, sizeof(error), 0);
					
		//Error if problem sending data
		if (charsWritten < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
		}
		
		//Get the response
		charsRead = recv(socketFD, buffer, sizeof(buffer), 0);

		//Error is problem recv data
		if (charsRead < 0)
		{
			fprintf(stderr, "Error recv from socket\n");
		}
		
		//Display error message on server
		cout << "---------------------------------------------------------------" << endl;
		cout << "Error: " << splitCommandInfo[3] << " file not found" << endl;
		cout << "Sending error message to " << splitCommandInfo[5] << ":" << splitCommandInfo[4] << endl;
		cout << "---------------------------------------------------------------" << endl;
	
		//Place message into buffer
		sprintf(fileNotFoundMessage, "%s %s says FILE NOT FOUND", serverName, serverPort);

		//Send the error back to the client
		charsWritten = send(socketFD, fileNotFoundMessage, sizeof(fileNotFoundMessage), 0);
					
		//Error if problem sending data
		if (charsWritten < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
		}
	}
	
	//Close directory pointer
	closedir(directoryPointer);
	
	//Close connection with the client
	close(socketFD);

}


