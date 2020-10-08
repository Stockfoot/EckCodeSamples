TITLE Designing low-level I/O procedures     (EckRussellProgram6A.asm)

;// Author:Russell Eck
;// Last Modified : 6/1/2019
;// Project Number : Low Level IO                   Due Date : 6/9/2019
;// Description:	This program utilizes macros for getting strings and
;//				displaying strings. The procedures convert integers into
;//				strings and strings into integers before calling or reading
;//				them in. The test part of the program gets 10 strings of
;//				numbers from the user. It converts these strings into actual
;//				integers and stores them in an array. The sum and average of the
;//				array is then calculated. The array, sum, and average are
;//				displayed by converting the integers back into strings.

INCLUDE Irvine32.inc

;//Max numbers of 10 constant
MAX_NUMS = 10

;//**********************************************************************
;//						getString MACRO
;//Description: Recieves the offset and size of userString variable
;//			 and calls ReadString to fill variable
;//**********************************************************************
getString MACRO prompt, inputString, inputLength
	displayString prompt
	push		ecx
	push		edx
	mov		edx, inputString
	mov		ecx, inputLength
	call		ReadString
	pop		edx
	pop		ecx

ENDM



;//************************************************************************
;//						displayString MACRO
;//Description: Moves the address of the passed string into EDX then calls
;//			 Irvines WriteString to display to console. Protects EDX
;//************************************************************************
displayString MACRO stringToDisplay
	;//Move address and display passed string.
	push		edx
	mov		edx, stringToDisplay
	call		WriteString
	pop		edx

ENDM



.data

;//Program title, programmer, and description
programTitle		BYTE		"Project 6A - Designing low-level I/O procedures", 0
programmerName		BYTE		"Programmer - Russell Eck", 0
titleDivider		BYTE		"-------------------------------------------------------------------------------", 0
progDescription1	BYTE		"Please provide 10 unsigned decimal integers.", 0
progDescription2	BYTE		"Each number needs to be small enough to fit inside a 32 bit register.", 0
progDescription3	BYTE		"At the end the program will display a list of the integers, their sum, and their average value.", 0

;//Getting user data
promptNumber		BYTE		"Please enter an unsigned number: ", 0
userString		BYTE		32 DUP(0)
errorMessage		BYTE		"ERROR: You did not enter an unsigned number or your number was too big.", 10, 13, 0

;//Sum of the converted string to integer
sumInt			DWORD	0

;//Uninitialied array for user's 10 numbers
intArray			DWORD	MAX_NUMS DUP(?)

;//Holds sum and average of array
arraySum			DWORD	0
arrayAverage		DWORD	0

;//Display prompts
enteredNumbers		BYTE		"You entered the following numbers: ", 0
sumOfNumbers		BYTE		"The sum of these numbers is: ", 0
averageOfNumbers	BYTE		"The average of these numbers is: ", 0
comma			BYTE		", ", 0
programEnding		BYTE		"Thanks for playing!", 0

.code
main PROC

;//*************************************************
;//DISPLAY PROGRAM NAME, PROGRAMMER AND DESCRIPTION
;//*************************************************
	;//Push strings by reference and move to introduction procedure
	push		OFFSET progDescription3
	push		OFFSET progDescription2
	push		OFFSET progDescription1
	push		OFFSET titleDivider
	push		OFFSET programmerName
	push		OFFSET programTitle
	call		introduction

;//******************************************************************
;//GET USER'S NUMBERS TO FILL ARRAY OF 10 WITH READVAL, TEST PROGRAM
;//******************************************************************
	;//Set the loop counter to 10 to fill the array and point to beginning of array
	mov		ecx, MAX_NUMS
	mov		edi, OFFSET intArray

fillArrayLoop:

	push		OFFSET sumInt
	push		OFFSET userString
	push		(SIZEOF userString) - 1
	push		OFFSET promptNumber
	push		OFFSET errorMessage

	call		readVal

	;//Add the validated number to the array
	mov		eax, sumInt
	mov		[edi], eax
	mov		eax, [edi]

	;//Move to next position of the array
	add		edi, 4

	loop		fillArrayLoop

;//*****************************************************
;//CALCULATE THE SUM OF THE NUMBERS, TEST PROGRAM
;//*****************************************************
	;//Push array that has 10 numbers to get the sum
	push		OFFSET intArray
	push		OFFSET arraySum

	call		calculateSum

;//*****************************************************
;//CALCULATE THE AVERAGE OF THE NUMBERS, TEST PROGRAM
;//*****************************************************
	;//Quickly calculate the average the array
	mov		eax, arraySum
	mov		ebx, 10
	mov		edx, 0
	div		ebx

	;//Put average in variable
	mov		arrayAverage, eax

;//****************************************************************
;//DISPLAY ARRAY, SUM, AND AVERAGE CALLING WRITEVAL, TEST PROGRAM
;//***************************************************************
	;//Loop through and display the array
	call		CrLf
	call		CrLf
	displayString OFFSET enteredNumbers
	call		CrLf
	
	;//Set the loop counter to 10 to process and display all numbers in array
	mov		ecx, MAX_NUMS
	mov		esi, OFFSET intArray

displayArrayLoop:
	;//Loop through and display the array calling WriteVal on each element
	push		OFFSET userString
	push		esi
	call		WriteVal
	add		esi, 4

	cmp		ecx, 1
	je		skipLastComma
	displayString OFFSET comma

	loop		displayArrayLoop

skipLastComma:

	;//Display the sum
	call		CrLf
	call		CrLf
	displayString OFFSET sumOfNumbers
	push		OFFSET userString
	push		OFFSET arraySum
	call		WriteVal
	call		CrLf
	call		CrLf

	;//Display the average
	displayString OFFSET averageOfNumbers
	push		OFFSET userString
	push		OFFSET arrayAverage
	call		WriteVal
	call		CrLf
	call		CrLf

	displayString OFFSET programEnding
	call		CrLf
	call		CrLf

	exit	; exit to operating system
main ENDP


;//**********************************************************************************************************
;//BEGIN PROCEDURES
;//**********************************************************************************************************

;//**********************************************************************
;//						introduction PROC
;//Description:	Displays the program and programmer name. Uses
;//				displayString MACRO
;//Receives:		OFFSET of introduction strings
;//Returns:		Nothing
;//PreConditions:	
;//Regs Changed:	None, macro protects EDX
;//**********************************************************************
introduction PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Display the program, programmer name, and description
	displayString		[ebp + 16]
	call		CrLf
	displayString		[ebp + 8]
	call		CrLf
	displayString		[ebp + 12]
	call		CrLf
	displayString		[ebp + 16]
	call		CrLf
	call		CrLf
	displayString		[ebp + 20]
	call		CrLf
	displayString		[ebp + 24]
	call		CrLf
	displayString		[ebp + 28]
	call		CrLf
	call		CrLf
	call		CrLf

	pop		ebp
	ret		24					;//6 variables were used

introduction ENDP



;//**********************************************************************
;//						ReadVal PROC
;//Description:	Loops until a valid integer is read. Then loops to
;//				convert that string of digits to actual integer. Returns
;//				that number to main to be placed in user's array.
;//Receives:		OFFSETs of userString, prompt and error message. Size of string
;//Returns:		Places a valid converted string to integer in passed variable.
;//PreConditions:	An array or DWORD variable must be set up to recieve number.
;//Regs Changed:	EAX, EBX, ECX, EDX, ESI, EDI
;//**********************************************************************
ReadVal PROC
	LOCAL rollingSum : DWORD

	;//Protect registers
	push		edi
	push		ecx
	
validationLoop:
	
	;//EDI is the counter for how many valid numbers long the string is
	mov		edi, 0

	;//Move the string variable and length into regs
	mov		ecx, [ebp + 16]
	mov		esi, [ebp + 20]
	
	;//Call macro passing prompt message, variable, and variable size
	getString [ebp + 12], esi, ecx
	
	;//Reset forward direction before lodsb sequence
	cld

checkStringLODSB:

	;//Load byte and check if we are at end of string
	lodsb
	cmp		al, 0
	je		stringIsValid

	;//Check if current character is a digit using ASCII values, 48-57 ASCII = 0-9 numbers
	cmp		al, 48
	jb		invalidInput
	cmp		al, 57
	ja		invalidInput			
	
	;//Increment EDX which will tell how many powers of 10 we will multiply by when converting string to int
	inc		edi
	
	;//Current character was valid so move to next spot in array
	loop		checkStringLODSB
	jmp		stringIsValid

invalidInput:
	;//Current character wasn't a digit, issue warning and start over getting user input
	displayString [ebp + 8]
	jmp		validationLoop

stringIsValid:

	;//Current string is valid, set up regs to convert string to integer
	mov		esi, [ebp + 20]

	;//Clear carry flag for checking if number is too big later on
	clc

	;//Reset forward direction and decrement EDI to be in proper power of 10 position
	cld
	mov		ecx, edi
	dec		edi
	mov		rollingSum, 0

convertStringToInt:
	;//Push length of the string, set up EAX and EBX to get the current power of ten
	push		ecx
	mov		eax, 1
	mov		ebx, 10
	mov		ecx, edi
	
	;//If ECX is zero, we are in the ones position 10^0, jump so we don't multiply the last digit by 0
	cmp		ecx, 0
	je		onesPosition

powerOfTen:
	;//Loop multiply 10x10 to get the current power of ten position
	mul		ebx
	loop		powerOfTen
	
onesPosition:	
	;//Restore ECX, the length of the valid string, decrement EDI for power of 10,
	;//and put into current power of 10 into EBX
	pop		ecx
	dec		edi
	mov		ebx, eax
	mov		eax, 0

	;//Load byte
	lodsb
	
	;//Subtract 48 to convert string to digit value and multiply by current power of 10 position
	sub		al, 48
	mul		ebx

	;//Check if the carry flag was set, this means the value is too big and invalid
	jc		invalidInput

	;//Add to rolling sum DWORD
	add		rollingSum, eax
	
	loop		convertStringToInt

returnToMain:

	;//Move the valide integer into the passed variable before returning
	mov		eax, rollingSum
	mov		edx, [ebp + 24]
	mov		[edx], eax

	pop		ecx
	pop		edi
	ret		20					;//5 variables were used

ReadVal ENDP



;//**********************************************************************
;//						WriteVal PROC
;//Description:	Converts a passed number into a string then displays
;//				that string
;//Receives:		Number to convert and string to hold converted number
;//Returns:		Nothing
;//PreConditions:	A validated unsigned integer to be passed
;//Regs Changed:	EAX, EBX, ECX, EDX, EDI
;//**********************************************************************
WriteVal PROC

	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Protect registers
	push		ecx
	push		edi

	;//Move the address then the value of the pass number into EAX
	mov		eax, [ebp + 8]		
	mov		eax, [eax]

	;//Set up our divisor and digit counter
     mov		ebx, 10   
     mov		ecx, 0  

digitCounter: 
	;//Loop through and count the number of digits in our passed DWORD variable
	mov		edx, 0
     div		ebx

	;//EDX contains the lowest power of 10 number
	;//Push so we can reverse the order when writing to string
	push		edx

	;//Increment the counter for the number of digits we have encountered
     inc		ecx
     
	;//Check to see if we are done
	test		eax, eax
     jne		digitCounter
     
	;//Move the string into EDI, set forward direction
	mov		edi, [ebp + 12]
	cld

WriteValues:
	;//Loop through pushed values, convert to ASCII and place in string
	;//ECX will loop the number of digits we pushed
	mov		eax, 0
	pop		eax
	add		eax, 48
	stosb

	loop		WriteValues

	;//Null terminate the string we just made
	mov		eax, 0
	stosb

	;//Finally call macro to write the string
	displayString	[ebp + 12]

	;//Restore regs and return
	pop		edi
	pop		ecx
	pop		ebp
	ret		8


WriteVal ENDP



;//**********************************************************************
;//						calculateSum PROC
;//Description:	Calculates the sum of the passed array and places in variable
;//Receives:		OFFSET of array and arraysum variable
;//Returns:		The sum of the array in arraySum variable
;//PreConditions:	An filled array of 10 valid integers
;//Regs Changed:	
;//**********************************************************************
calculateSum PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Move the passed array into ESI as source and set up ECX as 10, the length of the array
	mov		esi, [ebp + 12]
	mov		ecx, 10
	mov		eax, 0

calculateSumLoop:
	;//Loop through and create a rolling sum of the array
	add		eax, [esi]
	add		esi, 4
	
	loop		calculateSumLoop

	;//Move the calculated sum into the passed variable and return
	mov		edx, [ebp + 8]
	mov		[edx], eax

	pop		ebp
	ret		8					;//2 variables were used

calculateSum ENDP


END main
