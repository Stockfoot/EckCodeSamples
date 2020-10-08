"""*********************************************************************************************************************
*   PROGRAM:        chatserve.py
*   AUTHOR:         Russell Eck
*   LAST MODIFIED:  2/2/2019
*	DESCRIPTION:	This program is the server portion of a chat client. The chat server handle is hardcoded in. The server
*					begins on execution with the port number in the command line. A valid port range is 20,000-60,000.
*					A TCP socket is setup and begins listening for a connection. A client can connect and once they do
*					the server and client can chat back and forth until either end types \quit ending the chat. The server
*					then remains on until sigint C is sent or reconnects with another client to chat.
*	SOURCES:		splitline function information - geeksforgeeks.org/python-string-splitlines/
*					command line argument information - tutorialspoint.com/python3/python_command_line_arguments.htm
*					TCP socket setup information from Week 4 lectures			
*********************************************************************************************************************"""

import sys
from socket import *

"""*******************************************************************************************
*										startUp()
*	Description:	This function checks the number and values of the command line arguments used
*					at startup. It then sets up the TCP socket and returns it to the main.
*	Pre Cond:		2 command line arguments at startup
*	Post Cond:		Server socket setup and return to main function
*******************************************************************************************"""
def startUp():
	
	# First check to make sure only 1 command line argument was entered. If not notify user and exit
	if len(sys.argv) != 2:
		print("Error: Only one command line argument may be used to set up the server port")
		print("Please restart the server with only one port number argument\n")
		sys.exit(1)

	# Check to make sure a valid port number range was picked. If not notify error and exit
	if (int(sys.argv[1]) < 20000) or (int(sys.argv[1]) > 60000):
		print("Error: Restart server with a valid port range from 20,000-60,000\n")
		sys.exit(1)
	
	# Assign the server port from the command line argument casting to an integer
	serverPort = int(sys.argv[1])
	serverChatSocket = socket(AF_INET, SOCK_STREAM)
	serverChatSocket.bind(("", serverPort))
	serverChatSocket.listen(1)
	return serverChatSocket



"""*******************************************************************************************
*										sendMessage()
*	Description:	Gets input from the server user and sends message to client
*	Pre Cond:		Established connection with a client
*	Post Cond:		Sends message to client and returns the message to main to be checked for 
*					\quit message
*******************************************************************************************"""
def sendMessage(clientSocket):
	
	validInput = False
	
	while validInput == False:
		
		# Get the message to send in the chat
		messageToSend = input("MR_ROBOTO> ")

		# The message must be less than 500 chars
		if len(messageToSend) <= 500:
			validInput = True

		else:
			print("Message must be 500 characters or less, try again")

	# Encode and send message to client
	clientSocket.send(messageToSend.encode())

	# Return message to check if user typed \quit
	return messageToSend



"""*******************************************************************************************
*										receiveMessage()
*	Description:	Receives a message from the client. It then strips off the message before
*					the new line character.
*	Pre Cond:		Established connection with a client
*	Post Cond:		Recieves message from client and returns new formatted message to main
*					to be checked for \quit message
*******************************************************************************************"""
def receiveMessage(clientSocket):
	
	# Get the message back from the client
	messageToReceive = clientSocket.recv(501).decode()

	# The message sent contains the string with a newline and 501 bytes
	# Get the message up to the newline and don't worry about the rest of the empty string
	formattedMessage = messageToReceive.splitlines()

	# Return message to check if user typed \quit
	return formattedMessage



"""*******************************************************************************************
*										displayServerInfo()
*	Description:	Displays server info to the server user.
*	Pre Cond:		Socket has been setup with hostname and port
*	Post Cond:		None
*******************************************************************************************"""
def displayServerInfo():

	# Print the host name same we know what to connect to with the client
	print()
	print("------------------------------------------------------------")
	print("Server hostname is: ", gethostname())
	print("Server port number is: ", int(sys.argv[1]))
	print("The server is ready to receive. Waiting for client response.")
	print("------------------------------------------------------------")
	print()



"""*******************************************************************************************
*										displayConnection()
*	Description:	Displays connected message to the server user.
*	Pre Cond:		Established connection with a client.
*	Post Cond:		None
*******************************************************************************************"""
def displayConnection(clientChatName):
	
	# Notify that you are connected with the client
	print()
	print("********************************************")
	print("You are now connected with ", clientChatName, sep="")
	print("********************************************")
	print()



"""*******************************************************************************************
*										displayDisconnection()
*	Description:	Displays disconnected message to the server user.
*	Pre Cond:		Established connection with a client.
*	Post Cond:		None
*******************************************************************************************"""
def displayDisconnection(clientChatName):
	# Display that you have been disconnected from client
	print()
	print("********************************************")
	print("Chat disconnected with ", clientChatName, sep="")
	print("********************************************")
	print()



"""********************************************************************************************************************
*												BEGIN MAIN PROGRAM
********************************************************************************************************************"""

"""****************************
* VARIABLES
****************************"""
serverChatName = "MR_ROBOTO"
quitChat = False

"""**********************************
* SETUP SERVER SOCKET
**********************************"""
serverChatSocket= startUp()

"""***************************************
* SERVER LOOPS INFINITELY UNTIL SIGINT C
***************************************"""
while 1:

	# Display server info to the server user
	displayServerInfo()

	# Server will wait here until a connection is received from the client
	clientSocket, address = serverChatSocket.accept()

	# Send the server handle and receive the client handle for output
	clientChatName = clientSocket.recv(11).decode()
	clientSocket.send(serverChatName.encode())

	# Display successful connection to user
	displayConnection(clientChatName)

	# Reset bool before inner chat loop
	quitChat = False

	"""*************************************************
	* LOOP CHAT UNTIL SERVER OR CLIENT ENTERS "\quit"
	*************************************************"""
	while quitChat == False:

		# Send message to client 
		messageToSend = sendMessage(clientSocket)
		
		# If server chat typed \quit, set bool to true and end chat loop
		if messageToSend == "\\quit":
			quitChat = True

		# Else it is a normal chat message, proceed
		else:
			
			# Get the message back from the client
			formattedMessage = receiveMessage(clientSocket)

			# If the message from client is "\quit", set bool to true and end chat loop
			if formattedMessage[0] == "\\quit":
				quitChat = True

			else:
				# Display message on screen
				print(clientChatName, "> ", formattedMessage[0], sep = "")

	# Notify the user that the chat is over
	displayDisconnection(clientChatName)
	
	# Close connection to the client socket, but the server socket continues to listen
	clientSocket.close()




