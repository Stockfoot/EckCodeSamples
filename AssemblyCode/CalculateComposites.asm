TITLE Calculate Composite Numbers  		(EckRussellProgram4.asm)

;// Author:Russell Eck
;// Last Modified : 4/30/2019
;// Project Number : Calculate Composites                  Due Date : 5/12/2019
;// Description:	This program calculates composite numbers. First, the user is instructed to enter 
;//				the number of composites to be displayed, and is prompted to enter an integer in 
;//				the range [1 .. 400]. The user enters a number, n, and the program verifies that 
;//				1 <= n <= 400. If n is out of range, the user is re-prompted until s/he enters a 
;//				value in the specified range. The program then calculates and displays all of the 
;//				composite numbers up to and including the nth composite. The results should be 
;//				displayed 10 composites per line with at least 3 spaces between the numbers.
;//				EC1: Allign output columns.

INCLUDE Irvine32.inc

LOW_LIMIT = 1			;//Constant for lowest acceptable user input
HIGH_LIMIT = 400		;//Constant for highest acceptable user input

.data

;//Program title and programmers name
programTitle		BYTE		"Project 4 - Calculate Composite Numbers", 0
programmerName		BYTE		"Programmer - Russell Eck", 0
titleDivider		BYTE		"---------------------------------------------", 0
extraCred1		BYTE		"EC1: Allign output columns", 0

;//Instructions for program
instructions1		BYTE		"Enter the number of composites to be displayed", 0
instructions2		BYTE		"Enter an integer in the range [1 .. 400]", 0
instructions3		BYTE		"Enter your number: ", 0
instructions4		BYTE		"Out of range, try again!", 0
userNumber		DWORD	0

;//Finding and printing composite numbers
currentNum		DWORD	2
compositesPrinted	DWORD	0
boolFound			DWORD	0
printedPerLine		DWORD	0
threeSpaces		BYTE		"   ",9 ,0

;//Parting message and program end
thankYouMessage	BYTE		"Thank you for using the Calculate Composite Numbers program!", 0
goodbyeMessage		BYTE		"Goodbye!", 0

.code
main PROC

;//******************************************
;//DISPLAY PROGRAM NAME AND PROGRAMMER
;//******************************************
	mov		eax, OFFSET programTitle
	mov		ebx, OFFSET programmerName
	mov		ecx, OFFSET titleDivider
	call		introduction

;//******************************************
;//DISPLAY INSTRUCTIONS AND GET USER DATA
;//******************************************
	mov		eax, OFFSET instructions1
	mov		ebx, OFFSET instructions2
	mov		ecx, OFFSET instructions3
	mov		esi, OFFSET instructions4
	call		getUserData
	mov		userNumber, eax			;//Valid number returned in EAX

;//******************************************
;//DISPLAY COMPOSITES
;//******************************************
	call		showComposites
	

;//******************************************
;//SAY GOODBYE AND END PROGRAM
;//******************************************
	mov		eax, OFFSET thankYouMessage
	mov		ebx, OFFSET goodbyeMessage
	call		goodbye

	exit	; exit to operating system
main ENDP



;//--------------------------------------------------------------------------------
;//------------------------     PROCEDURES     ------------------------------------
;//--------------------------------------------------------------------------------



;//**********************************************************************
;//						introduction PROC
;//Description:	Displays the program and programmer name.
;//Receives:		EAX, EBX, and ECX which contain 3 intro strings
;//Returns:		Nothing
;//PreConditions:	
;//Regs Changed:	
;//**********************************************************************
introduction PROC
	;//Display intro strings
	mov		edx, ecx
	call		WriteString
	call		CrLf
	mov		edx, eax
	call		WriteString
	call		CrLf
	mov		edx, ebx
	call		WriteString
	call		CrLf
	mov		edx, ecx
	call		WriteString
	call		CrLf
	call		CrLf
	mov		edx,	OFFSET extraCred1
	call		WriteString
	call		CrLf
	call		CrLf
	call		CrLf

	ret
introduction ENDP



;//**********************************************************************
;//						getUserData PROC
;//Description:	Gets user's number and determines if it is valid and in
;//				range.
;//Receives:		EAX, EBX, ECX, and ESI which contain instruction strings
;//Returns:		User's valid number in EAX
;//PreConditions:	
;//Regs Changed:	
;//**********************************************************************
getUserData PROC
	;//Display instructions to user
	mov		edx, eax
	call		WriteString
	call		CrLf
	mov		edx, ebx
	call		WriteString
	call		CrLf
	call		CrLf
	call		CrLf

userInput:
	;//Prompt user to enter number and put their number into EAX
	mov		edx, ecx
	call		WriteString
	call		ReadInt

	;//Call sub procedure validateData passing it user's number in EAX
	;//Once valid, sub procedure will return here and then return EAX back to main
	call		validateData
		 
	ret
getUserData ENDP



;//**********************************************************************
;//						validateData PROC
;//Description:	This procedure loops and checks user's number until
;//				it is in the range of 1 to 400, then returns to getUserData
;//Receives:		EAX which is the user's number
;//Returns:		EAX which is a validated number between 1 and 400
;//PreConditions:	
;//Regs Changed:	EAX, ECX, EDX, ESI
;//**********************************************************************
validateData PROC
	
startDataCheck:	
	;//Check if number is less then 1
	cmp		eax, LOW_LIMIT
	jl		tooLow

	;//Check if number is greater than 400
	cmp		eax, HIGH_LIMIT
	jg		tooHigh

	;//Number is valid so go to return statement and return EAX
	jmp		validNumber

tooLow:
	;//Number was less than 1, get user input again
	mov		edx, esi
	call		WriteString
	call		CrLf
	;//Prompt user to enter number and put their number into EAX, check if valid again
	mov		edx, ecx
	call		WriteString
	call		ReadInt
	jmp		startDataCheck

tooHigh:
	;//Number was greater than 400, get user input again
	mov		edx, esi
	call		WriteString
	call		CrLf
	;//Prompt user to enter number and put their number into EAX, check if valid again
	mov		edx, ecx
	call		WriteString
	call		ReadInt
	jmp		startDataCheck

validNumber:
	;//Valid number was entered, return EAX
	ret

validateData ENDP



;//**********************************************************************
;//						showComposites PROC
;//Description:	Prints 10 composite numbers per line. Calls sub
;//				procedure isComposite to find the number to print.
;//				Aligns printed data.
;//Receives:		The validated number from the user's input
;//Returns:		
;//PreConditions:	
;//Regs Changed:	EAX, EDX
;//**********************************************************************
showComposites PROC

findComposite:
	;//Set found to false and call sub proc isComposite to check current number
	mov		boolFound, 0	
	call		isComposite

	;//If current number triggered bool in sub procedure, print that number
	cmp		boolFound, 1
	je		printNum

	;//If composites printed equals userNum we are done, jump to end of procedure
	inc		currentNum
	mov		eax, compositesPrinted
	cmp		eax, userNumber
	jl		findComposite
	jmp		endOfCompositeProc

printNum:
	;//Print number and 3 spaces
	mov		eax, currentNum
	call		WriteDec
	mov		edx, OFFSET threeSpaces
	call		WriteString
	
	;//Increment currentNum, compositesPrinted, and printedPerLine variables
	inc		currentNum
	inc		compositesPrinted
	inc		printedPerLine

	;//If 10 numbers have been printed jump to make a new line
	cmp		printedPerLine, 10
	je		newLine

	;//If composites printed equals userNum we are done, jump to end of procedure
	mov		eax, compositesPrinted
	cmp		eax, userNumber
	je		endOfCompositeProc

	;//Else loop again
	jmp		findComposite

newLine:
	;//Move to next line and reset printedPerLine back to 0, then loop again
	call		CrLf
	mov		printedPerLine, 0
	mov		eax, compositesPrinted
	cmp		eax, userNumber
	je		endOfCompositeProc
	jmp		findComposite

endOfCompositeProc:

	ret

showComposites ENDP

;//**********************************************************************
;//						isComposite PROC
;//Description:	Checks if the current number is composite or not.
;//Receives:		The current number being checked for composite value.
;//Returns:		Returns true or false if the current number is composite
;//				or not.
;//PreConditions:	
;//Regs Changed:	EAX, ECX, and EDX
;//**********************************************************************
isComposite PROC
	
	;//Set up ECX for loop. Divisor needs to be N-1 otherwise remainder will always be zero.
	mov		ecx, currentNum
	dec		ecx

loopIsComposite:
		
	;//Check ECX, if it equals 1 we have decremented all the way down and found no composite nubmers.
	cmp		ecx, 1
	je		returnFalse

	;//Check if number less than currentNum that divides into a whole number with no remainder
	mov		eax, currentNum
	mov		edx, 0
	div		ecx
	
	;//If the remainder of the current number is 0 the number is composite
	cmp		edx, 0
	je		returnTrue
	
	;//No composite found, loop and check again with new ECX value
	loop		loopIsComposite

	;//If loop ends skip over returnTrue to returnFalse
	jmp		returnFalse

returnTrue:
	;//Current number is composite, return true
	mov		boolFound, 1	
	
returnFalse:

	ret

isComposite ENDP

;//**********************************************************************
;//						goodbye PROC
;//Description:	Displays the parting message and ends program.
;//Receives:		EAX and EBX containing parting message strings
;//Returns:		Nothing
;//PreConditions:	
;//Regs Changed:	
;//**********************************************************************
goodbye PROC
	;//Displays outro strings
	mov		edx, eax
	call		CrLf
	call		CrLf
	call		WriteString
	call		CrLf
	call		CrLf
	mov		edx, ebx
	call		WriteString
	call		CrLf
	call		CrLf
	call		CrLf

	ret
goodbye ENDP

END main
