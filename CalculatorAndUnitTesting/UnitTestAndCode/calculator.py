"""*********************************************************************************************************************
*   Program:        calculator.py
*   Date:           2/24/2020
*   Authors:        Russell Eck, Morgan Eck, Michael Payne
*   Description:    This is a calculator program. It contains 9 functions... Multiplication, Division, Square Root,
*                   X Squared, Reciprocal, Factorial, Absolute Value, Sine, and Cosine. The program prompts the user
*                   for input then performs the correct function required. The program has error checking to ensure
*                   valid input is used during calculations.
*********************************************************************************************************************"""

import math

"""*********************************************************************************************************************
*                                           Multiplication(num1, num2)
*   
*       Description:    This function returns the product of the two numbers passed in as arguments.
*********************************************************************************************************************"""
def Multiplication(num1, num2):

    # Return the product of the two numbers
    return num1 * num2



"""*********************************************************************************************************************
*                                           Division(num1, num2)
*   
*       Description:    This function returns the division of the two numbers passed in as arguments. If the 2nd
*                       number is zero (denominator) then division cannot be performed and an error message is returned.
*********************************************************************************************************************"""
def Division(num1, num2):

    # If the denominator is zero division cannot be performed
    if num2 == 0:
        return "Cannot divide by zero"

    # Otherwise perform the division
    else:
        return num1 / num2



"""*********************************************************************************************************************
*                                           SquareRoot(num1)
*   
*       Description:    This function returns the square root of the pass in argument. If the number is not greater
*                       than or equal to zero it issues an error to the user instead of performing the operation.
*********************************************************************************************************************"""
def SquareRoot(num1):

    # A valid number, perform operation and return value
    if num1 >= 0:
        return math.sqrt(num1)

    # Not valid, return error message
    else:
        return "Cannot get square root of negative numbers"



"""*********************************************************************************************************************
*                                           XSquared(num1)
*   
*       Description:    This function returns the square of the value passed in as an argument.
*********************************************************************************************************************"""
def XSquared(num1):

    # Return the number multiplied by itself
    return num1 * num1



"""*********************************************************************************************************************
*                                           Reciprocal(num1)
*   
*       Description:    This function returns the reciprocal of the value passed in as an argument. If the argument
*                       is zero then an error message is return to the user instead since we cannot divide by zero.
*********************************************************************************************************************"""
def Reciprocal(num1):

    # If the number is zero, division cannot be performed
    if num1 == 0:
        return "Cannot divide by zero"

    # Otherwise perform the reciprocal
    else:
        return 1 / num1



"""*********************************************************************************************************************
*                                           Factorial(num1)
*   
*       Description:    This function returns the factorial of the number pass in as an argument. The value must
*                       be a whole number integer greater than zero, otherwise the function sends back and error 
*                       message.
*********************************************************************************************************************"""
def Factorial(num1):

    # If number is negative return error message
    if num1 < 0:
        return "Cannot get factorial of negative numbers"

    # Check if the float is an integer, i.e. 100.0 == 100
    elif num1.is_integer():
        return math.factorial(num1)

    # Otherwise it isn't so return error message to main
    else:
        return math.gamma(num1 + 1)



"""*********************************************************************************************************************
*                                           AbsoluteValue(num1)
*   
*       Description:    This function returns the absolute value of the number passed in as an argument.
*********************************************************************************************************************"""
def AbsoluteValue(num1):

    # Return the absolute value of passed number
    return abs(num1)



"""*********************************************************************************************************************
*                                           Sine(num1)
*   
*       Description:    This function returns the sine of the value passed in as an argument.
*********************************************************************************************************************"""
def Sine(num1):

    # Return the sin of the passed in number
    return math.sin(num1)



"""*********************************************************************************************************************
*                                           Cosine(num1)
*   
*       Description:    This function returns the cosine of the value passed in as an argument.
*********************************************************************************************************************"""
def Cosine(num1):

    # Return the cosine of the passed in number
    return math.cos(num1)



"""*********************************************************************************************************************
*                                           displayMainMenu()
*   
*       Description:    This function displays the menu options that the user can choose to perform the specified math
*                       operation or exit the program.
*********************************************************************************************************************"""
def displayMainMenu():

    #Display the main menu and the calculator options
    print("")
    print("******************************************")
    print("             SELECT AN OPTION             ")
    print("******************************************")
    print("1. Multiplication      6. Factorial       ")
    print("2. Division            7. Absolute Value  ")
    print("3. Square Root         8. Sine            ")
    print("4. X Squared           9. Cosine          ")
    print("5. Reciprocal          10. Exit           ")
    print("******************************************")
    print("")



"""*********************************************************************************************************************
*                                           getMenuChoice()
*   
*       Description:    This function gets the user's input choice for the menu. The function will loop infinitely
*                       until a valid input between 1-10 is entered. Once valid it returns the choice back to the main
*                       function which is then used to move on to the appropriate match function.
*********************************************************************************************************************"""
def getMenuChoice():

    while True:
        # Get user input
        userChoice = input("Enter your choice: ")

        # Check if the input is only numbers
        if userChoice.isdigit() == False:
            print("")
            print("You must enter a number, try again...")
            print("")

        # Check that the number is in valid range
        elif int(userChoice) < 1 or int(userChoice) > 10:
            print("")
            print("You must enter between 1 and 10, try again...")
            print("")

        # Return valid number cast as integer
        else:
            return int(userChoice)



"""*********************************************************************************************************************
*                                           getOneNumber()
*   
*       Description:    This function prompts the user to enter a number. The function accepts both float and integer
*                       values. It contains error checking and re-prompting if the user doesn't enter a valid type. The
*                       function then returns the valid number back to main where it will be used in the appropriate
*                       math function.
*********************************************************************************************************************"""
def getOneNumber():

    while True:
        # Get user input
        try:
            userNumberOne = float(input("Enter number: "))

        # Check if the input is only numbers
        except ValueError:
            print("")
            print("You must enter a valid number, try again...")
            print("")

        # Return the valid number
        else:
            return userNumberOne



"""*********************************************************************************************************************
*                                           getTwoNumbers()
*   
*       Description:    This function prompts the user to enter two numbers. The function accepts both float and integer
*                       values. It contains error checking and re-prompting if the user doesn't enter a valid type. The
*                       function then appends both numbers to a list which is returned to main to call on the next math
*                       function.  
*********************************************************************************************************************"""
def getTwoNumbers():

    while True:
        # Get user input
        try:
            userNumberOne = float(input("Enter first number: "))
            userNumberTwo = float(input("Enter second number: "))

        # Check if the input is only numbers
        except ValueError:
            print("")
            print("You must enter a valid number, try again...")
            print("")

        # Return the valid numbers in a list
        else:
            userNums = []
            userNums.append(userNumberOne)
            userNums.append(userNumberTwo)
            return userNums



"""*********************************************************************************************************************
*       MAIN FUNCTION
*********************************************************************************************************************"""
def main():

    # Bool to break loop and end program
    exitCalculator = False

    # Loop until user chooses to exit
    while exitCalculator == False:

        # Display main menu and user choices
        displayMainMenu()

        # Get the user's menu choice
        userInput = getMenuChoice()

        # Call Multiplication and get two number inputs
        if userInput == 1:
            numbers = getTwoNumbers()
            print(numbers[0], "*", numbers[1], "=", Multiplication(numbers[0], numbers [1]))
            input("Press Enter to continue...")

        # Call Division and get two number inputs
        elif userInput == 2:
            numbers = getTwoNumbers()
            print(numbers[0], "/", numbers[1], "=", Division(numbers[0], numbers[1]))
            input("Press Enter to continue...")

        # Call Square Root and get number input
        elif userInput == 3:
            print("Square Root = ", SquareRoot(getOneNumber()))
            input("Press Enter to continue...")

        # Call X Squared and get number input
        elif userInput == 4:
            print("X Squared = ", XSquared(getOneNumber()))
            input("Press Enter to continue...")

        # Call Reciprocal and get number input
        elif userInput == 5:
            print("1/x = ", Reciprocal(getOneNumber()))
            input("Press Enter to continue...")

        # Call Factorial and get number input
        elif userInput == 6:
            print("Factorial = ", Factorial(getOneNumber()))
            input("Press Enter to continue...")

        # Call Absolute Value and get number input
        elif userInput == 7:
            print("Absolute Value = ", AbsoluteValue(getOneNumber()))
            input("Press Enter to continue...")

        # Call Sine and get number input
        elif userInput == 8:
            print("Sine = ", Sine(getOneNumber()))
            input("Press Enter to continue...")

        # Call Cosine and get number input
        elif userInput == 9:
            print("Cosine = ",Cosine(getOneNumber()))
            input("Press Enter to continue...")

        # User chose to exit program, end loop
        else:
            exitCalculator = True



"""*********************************************************************************************************************
*       BEGIN SCRIPT
*********************************************************************************************************************"""
main()
