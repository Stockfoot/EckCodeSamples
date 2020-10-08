/************************************************************************************************************
*	PROGRAM:		smallsh.c
*	AUTHOR:			Russell Eck
*	DATE:			11/12/2019
*	DESCRIPTION:	This program functions as a basic shell. It has 3 built in commands, status, exit, and cd.
*					It handles blank lines as well as comment lines beginning with a '#' character. The program
*					handles foreground and background processes as well as fork/exec of non built in commands.
*					The shell handles the CTRL-C and CTRL-Z signals. CTRL-C sends SIGINT signal and CTRL-Z
*					sends SIGTSTP signal which toggles between foreground and background mode. 
************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_INPUT_LENGTH 2048
#define MAX_ARG_LENGTH 512

//Function Definitions
void getUserInput(char *inputArgs[], char inputFileName[], char outputFileName[], int *backgroundProcess);
void displayExitStatus(int *childExitMethod);
void commandExecution(char *inputArgs[], char inputFileName[], char outputFileName[], int *backgroundProcess, int *childExitMethod, struct sigaction SIGINT_child);
void toggleSIGTSTP(int);

//Global variable since signal functions can't be passed variables
//Set to true initially
int TOGGLE_BACKGROUND = 1;

/************************************************************************************************************
*										BEGIN MAIN
************************************************************************************************************/
int main()
{
	/*************************************************************
	* VARIABLE DECLARATION AND INTIALIZATION
	*************************************************************/

	//SIGINT handler
	//Sets the default action to ignore CTRL C
	struct sigaction SIGINT_ignore = {0};
	SIGINT_ignore.sa_handler = SIG_IGN;
	sigfillset(&SIGINT_ignore.sa_mask);
	SIGINT_ignore.sa_flags = 0;
	sigaction(SIGINT, &SIGINT_ignore, NULL);

	//SIGTSTP handler
	//Sets action to go to toggleSIGTSTP function for CTRL Z
	struct sigaction SIGTSTP_toggle = {0};
	SIGTSTP_toggle.sa_handler = toggleSIGTSTP;
	sigfillset(&SIGTSTP_toggle.sa_mask);
	SIGTSTP_toggle.sa_flags = 0;
	sigaction(SIGTSTP, &SIGTSTP_toggle, NULL);
	
	//Loop Counters
	int i = 0;
	int j = 0;
	int childExitMethod = -5;
		
	//Bools
	int exitShell = 0;
	int compareResult = 0;
	int backgroundProcess = 0;
	
	//Character Argument Buffers
	char *inputArgs[MAX_ARG_LENGTH];
	char inputFileName[100];
	char outputFileName[100];
	
	//Default Arg Array Pointers to Null
	for (i = 0; i < 512; i++)
	{
		inputArgs[i] = NULL;
	}
	
	//Clear input and output file name arrays
	memset(inputFileName, '\0', sizeof(inputFileName));
	memset(outputFileName, '\0', sizeof(outputFileName));

	/*************************************************************
	* BEGIN MAIN SHELL LOOP
	*************************************************************/
	
	do
	{
		/****************************************
		* GET USER INPUT
		****************************************/
		getUserInput(inputArgs, inputFileName, outputFileName, &backgroundProcess);
		
		/**********************************************
		* CHECK IF USER ENTERED A COMMENT OR BLANK LINE
		**********************************************/
		
		//If line is a comment ignore and loop again
		if (inputArgs[0][0] == '#')
		{
			exitShell = 0;
		}
		
		//If line is a empty line ignore and loop again
		else if (inputArgs[0][0] == '\0')
		{
			exitShell = 0;
		}
		
		/**********************************************
		* CHECK IF USER ENTERED CD, STATUS, OR EXIT
		**********************************************/
		
		/**********
		* EXIT
		**********/
		else if (!strcmp(inputArgs[0], "exit"))
		{
			exitShell = 1;
		}

		/**********
		* CD
		**********/
		else if(!strcmp(inputArgs[0], "cd"))
		{
			//The user entered cd with no argument so change to home directory
			if (inputArgs[1] == NULL)
			{
				chdir(getenv("HOME"));
				printf("Changing to %s\n", getenv("HOME"));
				fflush(stdout);
			}

			//The user passed a folder with cd, change directory
			else
			{
				compareResult = chdir(inputArgs[1]);
				
				//If chdir did not return zero, the change was unsuccessful
				if (compareResult != 0)
				{
					printf("Error: Directory was not found or does not exists\n");
					fflush(stdout);
				}
			}
		}
		
		/**********
		* STATUS
		**********/
		else if (!strcmp(inputArgs[0], "status"))
		{
			displayExitStatus(&childExitMethod);
		}

		/**********************************************
		* USER ENTERED COMMAND TO EXECUTE
		**********************************************/
		else
		{
			commandExecution(inputArgs, inputFileName, outputFileName, &backgroundProcess, &childExitMethod, SIGINT_ignore);	
		}

		/****************************************
		* RESET VARIABLES FOR NEXT LOOP
		****************************************/
		backgroundProcess = 0;

		for (i = 0; i < 512; i++)
		{
			inputArgs[i] = NULL;
		}
		
		memset(inputFileName, '\0', sizeof(inputFileName));
		memset(outputFileName, '\0', sizeof(outputFileName));
			
	}
	while (exitShell == 0);


	return 0;
}



/************************************************************************************************************
* 										void getUserInput()
*							
*	Description:	This function gets the user input and acts as the prompt. It receives the inputFile and
*					outputFile buffer and backgroundProcess form the main. These variables will be modified
*					if the user enters an input, output, or & for a background process. If the user enters
*					a black line or comment then  we return to main, otherwise all of the user's input is parsed
*					into the inputArgs array using strtok.
*
************************************************************************************************************/
void getUserInput(char *inputArgs[], char inputFileName[], char outputFileName[], int *backgroundProcess)
{
	/*************************************************************
	* FUNCTION VARIABLES
	*************************************************************/
	int i = 0;
	int findNewLine = 0;
	int compareResult = 0;
	char inputBuffer[MAX_INPUT_LENGTH];
	memset(inputBuffer, '\0', sizeof(inputBuffer));
	pid_t pid = getpid();

	/*************************************************************
	* DISPLAY PROMPT AND GET USER INPUT
	*************************************************************/
	
	//Display prompt, flush, and get input
	printf(": ");
	fflush(stdout);
	fgets(inputBuffer, MAX_INPUT_LENGTH, stdin);

	//fgets places a trailing newline character, loop through and replace with '\0'
	while (findNewLine != 1)
	{
		if (inputBuffer[i] == '\n')
		{
			inputBuffer[i] = '\0';
			findNewLine = 1;
		}
		i++;
	}
	
	/*************************************************************
	* CHECK IF INPUT IS A COMMENT OR BLANK LINE AND RETURN
	*************************************************************/

	//Check if input is a comment, set arg array to # and return
	if (inputBuffer[0] == '#')
	{
		inputArgs[0] = "#";
		return;
	}
	
	//Check if input is a blank line, set arg array to "" and return
	else if (!strcmp(inputBuffer, ""))
	{
		inputArgs[0] = "";
		return;
	}
	
	/*************************************************************
	* USER ENTERED A COMMAND, PARSE DATA INTO ARGUMENT ARRAY
	*************************************************************/

	//Token to find space delimeters
	char *token = strtok(inputBuffer, " ");
	
	//Loop through the string the user entered and place each piece separated by a space
	//into individual character arrays inside the *inputArgs[]
	i = 0;
	while (token != NULL)
	{
		//If we encounter input "<", skip the character by calling strtok again
		//Place the next word into intputFileName to use in main
		if (!strcmp(token, "<"))
		{
			token = strtok(NULL, " ");
			strcpy(inputFileName, token);		
		}

		//If we encounter output ">", skip the character by calling strtok again
		//Place the next word into outputFileName to use in main
		else if (!strcmp(token, ">"))
		{
			token = strtok(NULL, " ");
			strcpy(outputFileName, token);
		}
		
		//If we encounter background flag "&", set flag to true to use in main
		else if (!strcmp(token, "&"))
		{
			*backgroundProcess = 1;
		}

		//Else it is a normal command, extract and place into inputArgs[]
		else
		{
			inputArgs[i] = strdup(token);
		}
		
		//Increment variables for next loop
		i++;
		token = strtok(NULL, " ");

	}
	
	/*************************************************************
	* CHECK IF ANY ARGS ARE "$$", REPLACE WITH PID IF TRUE
	*************************************************************/
	i = 0;
	//Loop through the argument array, if we find "$$" replace with PID
	while (inputArgs[i] != NULL)
	{
		if (!strcmp(inputArgs[i], "$$"))
		{
			sprintf(inputArgs[i], "%d", pid);
		}

		i++;
	}
}



/************************************************************************************************************
* 										void displayExitStatus()
*	
*	Description:	This function displays the child exit status from terminated processes. It receives
*					childExitMethod which is modified in waitpid() during execution. If the signal was exited
*					it displays the exit value and if it was terminated by a signal it displays the termination
*					value.
*
************************************************************************************************************/
void displayExitStatus(int *childExitMethod)
{
	int exitStatus = 0;

	//If the process was exited by a status
	if ((WIFEXITED(*childExitMethod)) != 0)
	{
		//Get exit status int and print to user
		exitStatus = WEXITSTATUS(*childExitMethod);
		printf("Exit value %d\n", exitStatus);
		fflush(stdout);
	}

	//If the process was terminated by a signal
	else if ((WIFSIGNALED(*childExitMethod)) != 0)
	{
		exitStatus = WTERMSIG(*childExitMethod);
		printf("Terminated by signal %d\n", exitStatus);
		fflush(stdout);
	}
}



/************************************************************************************************************
* 										void commandExecution()
*	
*	Description:This function receives the input array, inputFile, outputFile, backgroundProcess, sigaction
*				struct for CTRL-C, and the variable to store the childExitMethod. The function begins by
*				forking a child process. It then redirects input/output depending on the value stored in the 
*				inputFile and outputFile variables. It finally executes the command that is inside the inputArgs
*				array. If the process is a foreground process then the parent waits for the child to finish before
*				moving on. Otherwise it is executed in the background and the parent process moves forward. A loop
*				at the end checks for when a background process has completed and then displays the notification 
*				to the user once it has.
*					
************************************************************************************************************/
void commandExecution(char *inputArgs[], char inputFileName[], char outputFileName[], int *backgroundProcess, int *childExitMethod, struct sigaction SIGINT_child)
{
	/*************************************************************
	* FUNCTION VARIABLES
	*************************************************************/
	pid_t spawnPID = -5;

	int inputFileDescriptor;
	int outputFileDescriptor;
	int redirectResult;
	
	/*************************************************************
	* SPAWN CHILD - REDIRECT INPUT, OUTPUT, AND THEN EXECUTE
	*************************************************************/
	spawnPID = fork();
	switch (spawnPID)
	{
		//The fork failed, issue error and end child
		case -1:
			perror("Something went horribly wrong!\n");
			exit(1);
			break;
		
		//The fork succeeded
		//Child redirects input and output if necessary then executes command
		case 0:
			/********************************
			* SET SIGINT TO HANDLE CTRL C
			********************************/
			SIGINT_child.sa_handler = SIG_DFL;
			sigaction(SIGINT, &SIGINT_child, NULL);

			/********************************
			* INPUT REDIRECTION
			********************************/
			//Check if an input file name was passed to the function by seeing if character array is empty
			if (inputFileName[0] != '\0')
			{
				//Open the input file
				inputFileDescriptor = open(inputFileName, O_RDONLY);
				
				//Check if there was an error opening the input file
				//If there was, issue an error and exit child with status 1
				if (inputFileDescriptor == -1)
				{
					perror("Error: Could not open input file\n");
					exit(1);
				}
				
				//Redirect stdin to the input file provided in command line
				redirectResult = dup2(inputFileDescriptor, 0);
				
				//If redirection did not succeed, issue error and exit child with status 1
				if (redirectResult == -1)
				{
					perror("Error: Could not redirect input\n");
					exit(1);
				}
				
				//Close on execute
				fcntl(inputFileDescriptor, F_SETFD, FD_CLOEXEC);

			}

			/********************************
			* OUTPUT REDIRECTION
			********************************/
			//Check if an ouput file name was passed to the function by seeing if character array is empty
			if (outputFileName[0] != '\0')
			{
				//Open the output file
				outputFileDescriptor = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				
				//Check if there was an error opening the output file
				//If there was, issue an error and exit child with status 1
				if (outputFileDescriptor == -1)
				{
					perror("Error: Could not open output file\n");
					exit(1);
				}
				
				//Redirect stdout to the output file provided in command line
				redirectResult = dup2(outputFileDescriptor, 1);
				
				//If redirection did not succeed, issue error and exit child with status 1
				if (redirectResult == -1)
				{
					perror("Error: Could not redirect output\n");
					exit(1);
				}
				
				//Close on execute
				fcntl(outputFileDescriptor, F_SETFD, FD_CLOEXEC);

			}
			
			/********************************
			* EXECUTE COMMAND
			********************************/
			//Execute the command, if executing returns -1 it has failed to execute, issue error and exit child
			if (execvp(inputArgs[0], inputArgs) < 0)
			{
				printf("Error: %s is not a valid command\n", inputArgs[0]);
				fflush(stdout);
				exit(1);
			}

			break;

		
		default:
			
			//Execute in background only if ctrl Z has toggled to on and user enter the final character in command as "&"
			if ((TOGGLE_BACKGROUND == 1) && (*backgroundProcess == 1))
			{
				waitpid(spawnPID, childExitMethod, WNOHANG);
				printf("Background PID is %d\n", spawnPID);
				fflush(stdout);
			}

			//Background is not allowed or the user did not specify a background command with "&"
			else
			{
				//No ampersand required for childExitMethod since it was cast to a pointer for function
				waitpid(spawnPID, childExitMethod, 0);
			}
			
			//Loop to detect when a child background process has terminated
			//Immediately call displayExitStatus when background process terminates
			while ((spawnPID = waitpid(-1, childExitMethod, WNOHANG)) > 0)
			{
				printf("Child %d terminated\n", spawnPID);
				fflush(stdout);
				displayExitStatus(childExitMethod);
			}
			
			
	}

}



/************************************************************************************************************
* 										void toggleSIGTSTP()
*	
*	Description:	This is the signal handler function for signal SIGTSTP which gets triggered when the user
*					uses CTRL-Z at any point. It requires the use of the global variable TOGGLE_BACKGROUND.
*					This is because variable cannot be passed to signal handler functions. If the user
*					triggers the signal then it will switch the global variable and display the message to the
*					user.
*
************************************************************************************************************/
void toggleSIGTSTP(int signo)
{
	if (TOGGLE_BACKGROUND == 0)
	{
		TOGGLE_BACKGROUND = 1;
		char* exitMessage = "\nExiting foreground-only mode\n";
		write(1, exitMessage, 30);
		fflush(stdout);
	}
	
	else if (TOGGLE_BACKGROUND == 1)
	{
		TOGGLE_BACKGROUND = 0;
		char* enterMessage = "\nEntering foreground-only mode (& is now ignored)\n";
		write(1, enterMessage, 50);
		fflush(stdout);
	}
}










