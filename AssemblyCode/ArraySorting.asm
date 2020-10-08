TITLE Generate Random Numbers and Sorting Arrays		(EckRussellProgram5.asm)

;// Author:Russell Eck
;// Last Modified : 5/16/2019
;// Project Number : Array Sorting                   Due Date : 5/26/2019
;// Description:	This program prompts the user to enter the number of random integers that
;//				they want to put into an array. Random numbers are then generated between
;//				100 and 999 and placed into the array. The unsorted array is displayed and
;//				then sorted in descending order. The median of the array is calculated and
;//				displayed followed by the sorted array being displayed.
;// Sources:		Assembly Language x86, Bubble Sort, Page 375 used in listSort PROC

INCLUDE Irvine32.inc

USER_MIN = 10				;//Lowest number of integers user can generate
USER_MAX = 200				;//Greatest number of integers user can generate
LO = 100					;//Lowest value the random integer generator can create
HI = 999					;//Greatest value the random integer generator can create

.data

;//Program title and programmers name
programTitle		BYTE		"Project 5 - Generating Random Numbers and Sorting Arrays", 0
programmerName		BYTE		"Programmer - Russell Eck", 0
titleDivider		BYTE		"-------------------------------------------------------------------------------", 0
progDescription1	BYTE		"This program generates a set of random integers [100-999] based on user choice.", 0
progDescription2	BYTE		"It then display the unsorted array, the median of the array, and the sorted array.", 0

;//Get user choice
promptEnterData	BYTE		"Enter the number of random integers you want to generate [10-200] : ", 0
promptTooLow		BYTE		"That number is too low. Please re-enter your number.", 0
promptTooHigh		BYTE		"That number is too high. Please re-enter your number.", 0

;//Create and fill array with random numbers
theArray			DWORD	USER_MAX DUP(?)
arrayCount		DWORD	?

;//Display unsorted array, sorted array, and median
unsortedDisplay	BYTE		"Here are your unsorted numbers.", 0
sortedDisplay		BYTE		"Here are your sorted numbers.", 0
medianDisplay		BYTE		"The median of your numbers is: ", 0
fiveSpaces		BYTE		"     ", 0
printedTen		DWORD	0

.code
main PROC

;//******************************************
;//DISPLAY PROGRAM NAME AND PROGRAMMER
;//******************************************
	;//Set up the random generator
	call		Randomize

	;//Push strings by reference and move to introduction procedure
	push		OFFSET progDescription2
	push		OFFSET progDescription1
	push		OFFSET titleDivider
	push		OFFSET programmerName
	push		OFFSET programTitle
	call		introduction

;//****************************************************
;//GET NUMBER OF RANDOM INTEGERS TO GENERATE FROM USER
;//****************************************************
	;//Push strings by reference for user input prompting
	push		OFFSET promptEnterData
	push		OFFSET arrayCount
	push		OFFSET promptTooLow
	push		OFFSET promptTooHigh
	call		getData

;//*************************************
;//FILL ARRAY WITH RANDOM NUMBER VALUES
;//*************************************
	;//Push array and the user's number of numbers to create
	push		OFFSET theArray
	push		arrayCount
	call		fillArray

;//*************************************
;//DISPLAY THE UNSORTED ARRAY
;//*************************************
	;//Push the unsorted array, message, and count
	push		printedTen
	push		OFFSET fiveSpaces
	push		OFFSET titleDivider
	push		OFFSET unsortedDisplay
	push		OFFSET theArray
	push		arrayCount
	call		displayList

;//**************************************
;//SORT THE ARRAY WITH SEQUENTIAL SEARCH
;//**************************************
	;//Push the array to sort and the count of the array
	push		OFFSET theArray
	push		arrayCount
	call		sortList

;//*************************************
;//CALCULATE AND DISPLAY THE MEDIAN
;//*************************************
	;//Push the array to sort and the count of the array
	push		OFFSET medianDisplay
	push		OFFSET theArray
	push		arrayCount
	call		displayMedian

;//*************************************
;//DISPLAY THE FINAL SORTED ARRAY
;//*************************************
;//Push the unsorted array, message, and count
	push		printedTen
	push		OFFSET fiveSpaces
	push		OFFSET titleDivider
	push		OFFSET sortedDisplay
	push		OFFSET theArray
	push		arrayCount
	call		displayList


	exit	; exit to operating system
main ENDP


;//**********************************************************************
;//						introduction PROC
;//Description:	Displays the program and programmer name.
;//Receives:		OFFSET of introduction strings
;//Returns:		Nothing
;//PreConditions:	
;//Regs Changed:	EDX
;//**********************************************************************
introduction PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Display the program and programmer name
	mov		edx, [ebp + 16]
	call		WriteString
	call		CrLf
	mov		edx, [ebp + 8]
	call		WriteString
	call		CrLf
	mov		edx, [ebp + 12]
	call		WriteString
	call		CrLf
	mov		edx, [ebp + 16]
	call		WriteString
	call		CrLf
	call		CrLf
	mov		edx, [ebp + 20]
	call		WriteString
	call		CrLf
	mov		edx, [ebp + 24]
	call		WriteString
	call		CrLf
	call		CrLf
	call		CrLf

	pop		ebp
	ret		20					;//5 variables were used

introduction ENDP




;//**********************************************************************
;//						getData PROC
;//Description:	Prompts user to enter number between [10-200]. Validates
;//				choice and assigns to arrayCount variable
;//Receives:		OFFSET of prompt string and OFFSET of userChoice
;//Returns:		User's value gets assigned to userChoice memory
;//PreConditions:	
;//Regs Changed:	EAX, EBX, EDX
;//**********************************************************************
getData PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

enterData:
	;//Prompt user to enter data and get user's number
	mov		edx, [ebp + 20]
	call		WriteString
	call		ReadInt

	;//Check if number is too low
	cmp		eax, USER_MIN
	jl		numTooLow
	
	;//Check if number is too high
	cmp		eax, USER_MAX
	jg		numTooHigh

	;//Number is in range, skip to validNumber
	jmp		validNumber

numTooLow:
	;//If number is too low notify user and reprompt
	mov		edx, [ebp + 12]
	call		WriteString
	call		CrLf
	jmp		enterData

numTooHigh:
	;//If number is too high notify user and reprompt
	mov		edx, [ebp + 8]
	call		WriteString
	call		CrLf
	jmp		enterData

validNumber:
	;//Place the value of eax into the addresss of arrayCount
	mov		ebx, [ebp + 16]		;//Put address of arrayCount into ebx
	mov		[ebx], eax			;//Place validated int into arrayCount variable
	call		CrLf
	call		CrLf

	pop		ebp
	ret		16					;//4 variables were used

getData ENDP



;//**********************************************************************
;//						fillArray PROC
;//Description:	Fills the passed array with random numbers generated by
;//				randomRange using constants LO and HI.
;//Receives:		Offset of the array to fill and size of the array
;//Returns:		An array filled with random integers
;//PreConditions:	
;//Regs Changed:	EAX, ECX, EDI
;//**********************************************************************
fillArray PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Set up array in EDI and ecx with the arrayCount
	mov		edi, [ebp + 12]		;//Address of theArray
	mov		ecx, [ebp + 8]			;//ecx is loop control

randomNumberLoop:
	;//Calculate a random number based on LO and HI. Range = (HI - LO + 1) + LO
	mov		eax, HI
	sub		eax, LO
	add		eax, 1
	call		RandomRange
	add		eax, LO

	;//Place random value in the current array element and loop for size of array
	mov		[edi], eax
	add		edi, 4
	loop		randomNumberLoop

	pop		ebp
	ret		8					;//2 variables were used

fillArray ENDP



;//**********************************************************************
;//						sortList PROC
;//Description:	Bubble sort the array in descending order
;//Receives:		OFFSET of the array and the count of the array
;//Source:		Assembly Language x86, Bubble Sort, Page 375
;//Returns:		Array sorted in descending order
;//PreConditions:	
;//Regs Changed:	EAX, ECX, ESI
;//**********************************************************************
sortList PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Set up ecx counter based on number of array elements
	mov		ecx, [ebp + 8]			;//ecx is loop control

	;//Bubble sort requires decrement to stay in bounds
	dec		ecx					;//Decrement count by 1
	
	;//Loop through and swap in descending order using bubble sort
L1: 
	push		ecx					;//Save outer loop count
	mov		esi, [ebp+12]			;//Address of theArray first element
L2: 
	mov		eax, [esi]			;//Get array value
	cmp		[esi + 4], eax			;//Compare a pair of values
	jle		L3					;//If [ESI] >= [ESI+4], no exchange
	xchg		eax, [esi + 4]			;//Exchange the pair
	mov		[esi], eax
L3: 
	add		esi, 4				;//Move both pointers forward
	loop		L2					;//Inner loop
	pop		ecx					;//Retrieve outer loop count
	loop		L1					;//Else repeat outer loop

L4:
	;//Sorting complete, return to main with sorted array
	pop		ebp
	ret		8					;//2 variables were used

sortList ENDP



;//**********************************************************************
;//						displayList PROC
;//Description:	Loops through the passed array and prints 10 elements
;//				of the array per line.
;//Receives:		Offset of the array and count of the array
;//Returns:		Nothing
;//PreConditions:	
;//Regs Changed:	EAX, EBX, ECX, ESI
;//**********************************************************************
displayList PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Set up array in ESI and ecx with the arrayCount
	mov		esi, [ebp + 12]		;//Address of theArray
	mov		ecx, [ebp + 8]			;//ecx is loop control
	mov		ebx, [ebp + 28]		;//Copy printer per line counter into ebx

	;//Print string and divider
	mov		edx, [ebp + 16]
	call		WriteString
	call		CrLf
	mov		edx, [ebp + 20]
	call		WriteString
	call		CrLf
	
displayLoop:
	;//Get current array element, print to screen, then go to next array element
	mov		eax,[esi]				;//Get current element and place in EAX
	call		WriteDec				;//Print current element
	mov		edx, [ebp + 24]		;//Print 5 spaces
	call		WriteString
	inc		ebx					;//Increment printed per line counter
	add		esi, 4				;//Get the next array element
	
	;//Check if 10 ints have been printed
	cmp		ebx, 10				;//Compare printed counter to 10
	je		displayNewLine			;//If equal jump and print new line
	loop		displayLoop			;//Else loop for length of the array
	jmp		displayLoopEnd			;//Jump to end, ECX has reached 0

displayNewLine:
	;//Print a new line, 10 integers have been printed
	call		CrLf
	mov		ebx, 0
	loop		displayLoop

displayLoopEnd:
	;//Print end divider
	call		CrLf
	mov		edx, [ebp + 20]
	call		WriteString
	call		CrLf
	call		CrLf
	call		CrLf

	;//Display looping complete, return to main
	pop ebp
	ret 24

displayList ENDP




;//**********************************************************************
;//						displayMedian PROC
;//Description:	Calculates and displays the median of the sorted array.
;//				Handles both even and odd sized arrays.
;//Receives:		OFFSET of sorted array, array size, and median string
;//Returns:		Nothing
;//PreConditions:	Array must be sorted
;//Regs Changed:	EAX, EBX, ECX, EDX, ESI
;//**********************************************************************
displayMedian PROC
	;//Set up stack frame
	push		ebp
	mov		ebp, esp

	;//Set up array in EDI and ecx with the arrayCount
	mov		esi, [ebp + 12]		;//Address of theArray
	mov		ecx, [ebp + 8]			;//Size of the array

	;//First check if the array is odd or even sized
	mov		edx, 0				;//Clear remainder
	mov		eax, ecx				;//Set eax to array size
	mov		ebx, 2				;//EBX to divide array size by 2
	div		ebx

	;//Check for remainder if 0 array size is even, else it is odd
	cmp		edx, 0
	je		evenArray
	jmp		oddArray

evenArray:
	;//EAX contains index of median, we need to multiply this index by 4
	;//ESI is pointing to the beginning of the array, so add this number to ESI to get to middle index address
	mov		ebx, 4
	mul		ebx
	add		esi, eax
	
	;//Reset EAX to zero, add the first middle number of array to eax
	mov		eax, 0
	add		eax, [esi]			;//Add the value at middle index to eax
	
	;//Move the index back one to get the second middle number of array and add to eax
	sub		esi, 4
	add		eax, [esi]

	;//Divide by 2 to get the average of the 2 middle array numbers
	mov		edx, 0
	mov		ebx, 2
	div		ebx

	;//Now check for a remainder. If there was a remainder we divided by an odd number and need to round up.
	;//Ex: 17/2 = 8 remainder 1 or 8.5
	
	;//If no remainder skip to print the number, else it was odd so increment eax rounding up
	cmp		edx, 0
	je		noRemainder
	inc		eax


noRemainder:
	;//Print the value at the middle index of the array
	call		CrLf
	mov		edx, [ebp + 16]		;//Display median string
	call		WriteString
	call		WriteDec				;//Median value already in eax so print
	call		CrLf
	call		CrLf
	call		CrLf
	call		CrLf
	jmp		medianCheckEnd

oddArray:
	;//EAX contains index of median, we need to multiply this index by 4
	;//ESI is pointing to the beginning of the array, so add this number to ESI to get to middle index address
	mov		ebx, 4
	mul		ebx
	add		esi, eax

	;//Print the value at the middle index of the array
	call		CrLf
	mov		edx, [ebp + 16]		;//Display median string
	call		WriteString
	mov		eax, [esi]			;//Place value of middle index into eax
	call		WriteDec
	call		CrLf
	call		CrLf
	call		CrLf
	call		CrLf
	
medianCheckEnd:

	pop		ebp
	ret		12

displayMedian ENDP


END main
