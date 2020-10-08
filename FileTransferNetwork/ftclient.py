"""*********************************************************************************************************************
*   PROGRAM:        ftclient.py
*   AUTHOR:         Russell Eck
*   LAST MODIFIED:  2/25/2019
*	DESCRIPTION:	This is the client portion of the file transfer system. This program starts with valid command line
*					arguments which specify host, port numbers, and the command of -l or -g for listing directory or 
*					getting a file from the server. Once connected the client will set up a second TCP socket to recv
*					the data from the server which will either be a directory listing on the server or the requested
*					file specified in the command line.
*	SOURCES:		splitline function information - geeksforgeeks.org/python-string-splitlines/
*					command line argument information - tutorialspoint.com/python3/python_command_line_arguments.htm
*					TCP socket setup information from Week 4 lectures			
*********************************************************************************************************************"""

import sys
from socket import *
import os.path
from os import path

"""*******************************************************************************************
*										startUp()
*	Description:	This function checks the number and values of the command line arguments.
*					It validates all pieces of the command line ensuring a valid input is used
*					before attempting to even connect to the server.
*	Pre Cond:		Correct number of command line arguments and format
*	Post Cond:		Client can proceed to connect to server
*******************************************************************************************"""
def startUp():
	
	# First check to make sure the correct number of command line args were used. If not notify user and exit
	if len(sys.argv) < 5 or len(sys.argv) > 6:
		print("\n----------------------------------------------------------------------------------------")
		print("Error: Incorrect number of command line arguments. You provided", len(sys.argv))
		print("Valid format 1 <ServerAddress> <ServerConnectionPort> <-l> <ServerDataPort>")
		print("Valid format 2 <ServerAddress> <ServerConnectionPort> <-g> <FileName> <ServerDataPort>")
		print("----------------------------------------------------------------------------------------\n")
		sys.exit(1)

	# Check to make sure a valid port number range was picked for connectin port. If not notify error and exit
	if (int(sys.argv[2]) < 20000) or (int(sys.argv[2]) > 60000):
		print("\n----------------------------------------------------------------------------------------")
		print("Error: Valid server port will be in range 20,000-60,000")
		print("----------------------------------------------------------------------------------------\n")
		sys.exit(1)
	
	# Check to make sure a valid port number range was picked for Data Port. If not notify error and exit
	# If -l format was used...
	if len(sys.argv) == 5:
		if (int(sys.argv[4]) < 20000) or (int(sys.argv[4]) > 60000):
			print("\n----------------------------------------------------------------------------------------")
			print("Error: Valid server port will be in range 20,000-60,000")
			print("----------------------------------------------------------------------------------------\n")
			sys.exit(1)

		# Make sure the connection and data ports provided are not the same
		if int(sys.argv[2]) == int(sys.argv[4]):
			print("\n----------------------------------------------------------------------------------------")
			print("Error: The connection and data ports cannot be the same")
			print("----------------------------------------------------------------------------------------\n")
			sys.exit(1)
			

		# Make sure -l is used, otherwise our server does not support this command
		if sys.argv[3] != "-l":
			print("\n----------------------------------------------------------------------------------------")
			print("Error: The server only supports -l commands in the following format")
			print("Valid format <ServerAddress> <ServerConnectionPort> <-l> <ServerDataPort>")
			print("----------------------------------------------------------------------------------------\n")
			sys.exit(1)
			

	# Else -g format was used...
	else:
		if (int(sys.argv[5]) < 20000) or (int(sys.argv[5]) > 60000):
			print("\n----------------------------------------------------------------------------------------")
			print("Error: Valid server port will be in range 20,000-60,000")
			print("----------------------------------------------------------------------------------------\n")
			sys.exit(1)
		
		# Make sure the connection and data ports provided are not the same
		if int(sys.argv[2]) == int(sys.argv[5]):
			print("\n----------------------------------------------------------------------------------------")
			print("Error: The connection and data ports cannot be the same")
			print("----------------------------------------------------------------------------------------\n")
			sys.exit(1)
		
		# Make sure -g is used, otherwise our server does not support this command
		if sys.argv[3] != "-g":
			print("\n----------------------------------------------------------------------------------------")
			print("Error: The server only supports -g commands in the following format")
			print("Valid format <ServerAddress> <ServerConnectionPort> <-g> <FileName> <ServerDataPort>")
			print("----------------------------------------------------------------------------------------\n")
			sys.exit(1)
		


"""*******************************************************************************************
*										sendCommandMessage()
*	Description:	Gets input from the server user and sends message to client
*	Pre Cond:		Established connection with a client
*	Post Cond:		Sends message to client and returns the message to main to be checked for 
*					\quit message
*******************************************************************************************"""
def sendCommandMessage(clientSocket):

	# Emptry string to construct command line
	commandLine = ""

	# Loop through command line args and apend to string
	for command in sys.argv[1:]:	
		commandLine = commandLine + command + " "

	# Get the host name and append to the string
	commandLine = commandLine + gethostname()	
	
	# Send the formatted information to the server
	clientSocket.send(commandLine.encode())



"""*******************************************************************************************
*										recvDirectoryList()
*	Description:	This function handles receiving the requested directory listing that was
*					sent as a command to the server. The client sets up a second data socket
*					and waits for an incoming connection from the server. Once connected the
*					client gets the directory listing, displays it to the screen, then disconnects
*					from the server.
*	Pre Cond:		A valid connection with the server, a valid command line
*	Post Cond:		A second TCP data connection is set up and the directory listing is received
*******************************************************************************************"""
def recvDirectoryList():
	
	# Create and set up the data TCP socket
	dataSocket = socket(AF_INET, SOCK_STREAM)
	dataSocket.bind(('', int(sys.argv[4])))
	dataSocket.listen(1)
	
	# Wait here until the server connects to secondary socket
	connectionSocket, addr = dataSocket.accept()
		
	# Notify user that directory listing is being received
	print("")
	print("Receiving directory structure from", sys.argv[1], ":", sys.argv[4])

	# Get the message back from the client
	directoryListing = connectionSocket.recv(10000).decode()

	# Return message to check if user typed \quit
	print("-------------------------------------------")
	print(directoryListing, end ="")
	print("-------------------------------------------")
	print("")

	# Close the TCP data connection
	connectionSocket.close()
	dataSocket.close()



"""*******************************************************************************************
*										recvFile()
*	Description:	This function handles receiving the requested file or file not found error
*					message. The client sets up a second data socket and waits fro an incoming
*					connection from the server. If the requested file does not exist it displays
*					the error message sent from the server. If the file does exist it writes the
*					data to the file in the current working directory. If the file is a duplicate
*					it appends "copy_" to the beginning of the file. It then disconnects from the server.
*	Pre Cond:		A valid connection with the server, a valid command line
*	Post Cond:		A second TCP data connection is set up and the error message or file is received
*******************************************************************************************"""
def recvFile():
	
	# Create and set up the data TCP socket
	dataSocket = socket(AF_INET, SOCK_STREAM)
	dataSocket.bind(('', int(sys.argv[5])))
	dataSocket.listen(1)
	
	# Wait here until the server connects to secondary socket
	connectionSocket, addr = dataSocket.accept()
		
	# Get the first message from server, send back confirmation
	received = "received"
	confirmation = ""
	confirmation = connectionSocket.recv(1000).decode()
	connectionSocket.send(received.encode())
	newMessage = confirmation.splitlines()

	# If the message from server is "file", proceed to recv new file
	if newMessage[0] == "file":
		
		# Notify user that directory listing is being received
		print("")
		print("-----------------------------------------------------")
		print("Receiving", sys.argv[4], "file from", sys.argv[1], ":", sys.argv[5])
		print("-----------------------------------------------------")
		
		# If the file already exists, create a new copy version
		if path.exists(sys.argv[4]):
				
			# Create a copy file name
			newFileName = "copy_" + sys.argv[4]

			# Create and open a new file for writing the data
			newFile = open(newFileName, "wb")

			# Loop and receive data until no more data is left
			while(True):
				dataChunk = connectionSocket.recv(1024)
				newFile.write(dataChunk)

				if not dataChunk:
					break

			# Close the newly written file
			newFile.close

		# Else the file doesn't already exist, create with original name
		else:
			
			# Create and open a new file for writing the data
			newFile = open(sys.argv[4], "wb")

			# Loop and receive data until no more data is left
			while(True):
				dataChunk = connectionSocket.recv(1024)
				newFile.write(dataChunk)
	
				if not dataChunk:
					break

			# Close the newly written file
			newFile.close
		
		# Print that the file transfer was complete
		print("Transfer Complete")
		print("-----------------------------------------------------")
		print("")

	# Else it was an error, recv error and issue to client	
	else:
		
		# Get the error message back from the client
		errorMessage = connectionSocket.recv(10000).decode()

		# Print message to client screen
		print("")
		print("-----------------------------------------------------")
		print(errorMessage)
		print("-----------------------------------------------------")
		print("")

	# Close the TCP data connection
	connectionSocket.close()
	dataSocket.close()

"""********************************************************************************************************************
*												BEGIN MAIN PROGRAM
********************************************************************************************************************"""

"""**********************************
* VERIFY COMMAND LINE ARGUMENTS
**********************************"""
startUp()

"""**********************************
* ESTABLISH CONTROL CONNECTION
**********************************"""
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((sys.argv[1], int(sys.argv[2])))

"""**********************************
* SEND COMMAND TO THE SERVER
**********************************"""
sendCommandMessage(clientSocket)

"""*************************************
* HANDLE THE DIRECTORY REQUEST/REPSONSE
*************************************"""
if len(sys.argv) == 5:
	recvDirectoryList()

else:
	recvFile()

"""*************************************
* CLOSE CONNECTION AND END CLIENT PROGRAM
*************************************"""
clientSocket.close()




