/************************************************************************************************************
*   PROGRAM:        chatclient.cpp
*   AUTHOR:         Russell Eck
*	LAST MODIFIED:	2/2/2020
*   DESCRIPTION:    This is the client portion of a networked chat program. The server must be running. The
*   				client is then ran with the server name and server port as command line arguments. The user
*   				is provides a chat name and then gets connected to the server. The user can then chat back
*   				and forth between the server. If the user or the server types "\quit" then the chat ends
*   				and the client program ends. The server will remain open to be connected to again.
*   SOURCES:		The majority of this code was reused and modified from my Network Encyption/Decryption program
*   				from CS344.
************************************************************************************************************/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

//Function Headers
string userHandleInput();
void sendMessage(int &socketFD, char *sendBuffer, int bufferSize, const char *userHandle);
void receiveMessage(int &socketFD, char *recvBuffer, int bufferSize, const char *userHandle);
void initiateContact(int &socketFD, const char *userHandle, char *serverHandle, int userHandleSize, int serverHandleSize);

/************************************************************************************************************
*                                       BEGIN MAIN
************************************************************************************************************/
int main(int argc, char *argv[])
{
    /**********************************************
    * VARIABLE DECLARATION AND INITIALIZATION
    **********************************************/
    string userHandleChoice;
    int socketFD;
    int portNumber;
    int charsWritten;
    int charsRead;
	bool quitChat = false;
	char sendBuffer[501];
	char recvBuffer[501];
	char serverHandle[11];
	char userHandle[11];
    struct sockaddr_in serverAddress;
    struct hostent* serverHostInfo;

	//Clear character buffers
	memset(sendBuffer, '\0', sizeof(sendBuffer));
	memset(recvBuffer, '\0', sizeof(recvBuffer));
	memset(serverHandle, '\0', sizeof(serverHandle));
	memset(userHandle, '\0', sizeof(userHandle));

    //Check # of arguments from command line
    if (argc != 3)
    {
        cerr << "Error: Incorrect number of command line arguments. Host name and port number required, try again." << endl;
        exit(1);
    }

	/******************************
	* GET USER HANDLE
	******************************/
    userHandleChoice = userHandleInput();
	strcpy(userHandle, userHandleChoice.c_str());

    /********************************************************
    * SET UP ADDRESS STRUCT FOR THIS CLIENT
    ********************************************************/
    memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
    portNumber = atoi(argv[2]); // Get the port number, convert to an integer from a string
    serverAddress.sin_family = AF_INET; // Create a network-capable socket
    serverAddress.sin_port = htons(portNumber); // Store the port number
    serverHostInfo = gethostbyname(argv[1]); // Convert the machine name into a special form of address
    
	//Issue error and exit if server hostname is wrong or does not exist
    if (serverHostInfo == NULL)
    {
        cerr << "CLIENT: ERROR, no such host" << endl;
        exit(1);
    }

    //Copy in the address to the structure
    memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length);

    /*********************
    * CREATE SOCKET
    *********************/
    socketFD = socket(AF_INET, SOCK_STREAM, 0); 
    
	//If socket creation was unsuccessful error and exit.
    if (socketFD < 0)
    {
        cerr << "CLIENT: ERROR opening socket" << endl;
		exit(1);
    }

    /****************************
    * CONNECT TO SERVER
    ****************************/
    //Display prompts
	cout << endl << endl;
    cout << "-------------------------------------------" << endl;	
	cout << "Connecting to server..." << endl;
	cout << "Hostname: " << argv[1] << endl;
	cout << "Port: " << argv[2] << endl;

	//Create initial connection, error if unsuccsful and exit 1.
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "CLIENT: ERROR connecting to server" << endl;
        exit(1);
    }

	//Display successful connection prompt
	cout << "Successfully connected to server" << endl;
    cout << "-------------------------------------------" << endl << endl;    

    /**************************************
    * INITIATE CONTACT AND EXCHANGE NAMES
    **************************************/
	initiateContact(socketFD, userHandle, serverHandle, 11, 11);
	
	/*************************************************
    * LOOP SEND/RECV CHAT UNTIL A USER TYPES "\quit"
    *************************************************/
	while(quitChat == false)
	{
    	/**********************************
    	* RECEIVE FROM CHAT CLIENT 
    	**********************************/
		receiveMessage(socketFD, recvBuffer, 501, userHandle);

		//If the server sent a quit message, set bool to true and end loop
		if (!strcmp(recvBuffer, "\\quit"))
		{
			quitChat = true;
		}
		
		//Otherwise it was a normal chat message, proceed with chatting
		else
		{
			//Print message from server to display
			printf("%s> %s\n", serverHandle, recvBuffer);

    		/**************************************
    		* SEND TO CHAT CLIENT
    		**************************************/
			sendMessage(socketFD, sendBuffer, 501, userHandle);

			//If the message was "\quit", set bool to true to end loop and connection
			if (!strcmp(sendBuffer, "\\quit\n"))
			{
				quitChat = true;
			}
   		} 
	}

    //Close Socket before ending
    close(socketFD);
   
	//Display connection closed to user
	printf("\n***********************************************\n");
	printf("Chat disconnected with %s\n", serverHandle);
	printf("***********************************************\n\n");
	

    return 0;
}



/************************************************************************************************************
*                                       string userHandleInput()
*                           
*   Description:    This function gets the user input and acts as the prompt for getting the client handle. 
*                   It provides error checking for empty strings, strings longer than 10 characters, and
*                   strings that contain a space. Once validated the string is returned to main and used
*                   as the chat client handle.
*	Pre Cond:		No preconditions required for function.
*	Post Cond:		Returns a validated string back to main with the user handle that contains no spaces
*					and is 10 characters or less.
************************************************************************************************************/
string userHandleInput()
{
    /*************************************************************
    * FUNCTION VARIABLES
    *************************************************************/
    string userInput;
    bool validName = true;
    
    /*************************************************************
    * INITIAL PROMPT
    *************************************************************/
    cout << endl;
	cout << "----------------------------------------------------" << endl;
    cout << "Please enter a user name/handle for the chat." << endl;
    cout << "Handle must be one word and max 10 characters long." << endl;
    cout << "----------------------------------------------------" << endl << endl;

    /*************************************************************
    * LOOP AND GET USER HANDLE
    *************************************************************/
    do
    {
        //Reset flag and count every time loop iterates.
        validName = true;

        //Get first input to test.
        cout << "Enter your handle: ";
        getline(cin, userInput);
        
        //If user didn't enter anything or more than 10 characters loop until they do.
        while (userInput.empty() || userInput.length() > 10) 
        {
            cout << "You entered nothing or too many characters." << endl;
            cout << "Enter your handle: ";
            getline(cin, userInput);
        }

        //Checks each character in the user input.
        //If a single one is a space set flag to false
        for (int i = 0; i < userInput.length(); i++)
        {

            if (userInput[i] == ' ')
            {
                validName = false;
            }
            
        }

        //If flag is false ask them to enter again.
        if(!validName)
        {
            cout << "That is not a valid name." << endl;
            cout << "Please try again." << endl;
        }
    }

    while(!validName);

    return userInput;
}



/************************************************************************************************************
*						sendMessage(int &socketFD, char *sendBuffer, string userHandle)
*                           
*   Description:	This function is responsible for sending the clients message to the server. It gets the users
*   				message, then calls the send function with error checking. Message is placed in character array
*   				to later check if the \quit message was used.
*	Pre Cond:		Connection established between client and server, user handle made
*	Post Cond:		Modifies the character array directly so that it can be checkd for \quit in main
************************************************************************************************************/

void sendMessage(int &socketFD, char *sendBuffer, int bufferSize, const char *userHandle)
{
    int charsWritten = 0;
	memset(sendBuffer, '\0', bufferSize);
	
	/**************************************
    * SEND TO CHAT CLIENT
    **************************************/
	//Display prompt and get user message
    printf("%s> ", userHandle);
	fgets(sendBuffer, bufferSize, stdin);
			
	//Send the message to the server
	charsWritten = send(socketFD, sendBuffer, bufferSize, 0);
    if (charsWritten < 0)
    {
    	cerr << "CLIENT: ERROR writing to socket" << endl;
    }
    
    if (charsWritten < bufferSize)
    {
    	cerr << "CLIENT: WARNING: Not all data written to socket!" << endl;
    }
}



/************************************************************************************************************
*						receieveMessage(int &socketFD, char *receiveBuffer, string userHandle)
*                           
*   Description:    This function is responsible for receiving the servers message. It reads the message into
*   				the buffer by reference so it can later be checked for \quit message.
*	Pre Cond:		Connection established between client and server, user handle made
*	Post Cond:		Modifies the character array directly so that it can be checkd for \quit in main
************************************************************************************************************/
void receiveMessage(int &socketFD, char *recvBuffer, int bufferSize, const char *userHandle)
{
	int charsRead = 0;
	
	//Clear and reset recvBuffer
	memset(recvBuffer, '\0', bufferSize);
		
	//Receive message from server
	charsRead = recv(socketFD, recvBuffer, bufferSize, 0);
    if (charsRead < 0)
    {
    	cerr << "ERROR: Confirmation failed from server" << endl;
    }
}



/************************************************************************************************************
*						void initiateContact(int, const char, char, int, int)
*                           
*   Description:    This function is repsonsible for intitial contact betwee the client and the server. The
*   				function exchanges the client handle and the server handle and displays a successful connection
*   				to the user.
*	Pre Cond:		Connection established between client and server, user handle made
*	Post Cond:		Modifies the character array directly of the serverHandle to be used later in program
************************************************************************************************************/
void initiateContact(int &socketFD, const char *userHandle, char *serverHandle, int userHandleSize, int serverHandleSize)
{
    int charsWritten = 0;
	int charsRead = 0;
	
	/**************************************
    * SEND CLIENT CHAT NAME TO SERVER
    **************************************/
	charsWritten = send(socketFD, userHandle, userHandleSize, 0);
    if (charsWritten < 0)
    {
    	cerr << "CLIENT: ERROR writing to socket" << endl;
    }
    
    if (charsWritten < userHandleSize)
    {
        cerr << "CLIENT: WARNING: Not all data written to socket!" << endl;
    }
    
    /****************************************
    * RECEIVE SERVER CHAT NAME FROM SERVER
    ****************************************/
	charsRead = recv(socketFD, serverHandle, serverHandleSize, 0);
    if (charsRead < 0)
    {
        cerr << "ERROR: Confirmation failed from server" << endl;
    }
	
	//Display connection to user
	printf("***********************************************\n");
	printf("You are now connected with %s\n", serverHandle);
	printf("***********************************************\n\n");

}
