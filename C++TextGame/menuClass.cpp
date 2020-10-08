/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the implementation file for menu class. This class
*               displays the intro menu of the program and contains integer
*               validation for user choice inputs.
***********************************************************************/

#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>

#include "menuClass.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           Menu::Menu()
*
*    Description: Default constructor for Menu class
*******************************************************************************/
Menu::Menu()
{
    menuChoice = -1;
}



/******************************************************************************
*                           Menu::~Menu()
*
*    Description: Destructor for Menu class
*******************************************************************************/
Menu::~Menu()
{

}



/******************************************************************************
*                           int Menu::getMenuChoice()
*
*    Description: Getter function for private variable menuChoice.
*******************************************************************************/
int Menu::getMenuChoice()
{
    return menuChoice;
}



/******************************************************************************
*                       int Menu::integerValidation()
*
*    Description: This function prompts the user to enter a choice and then checks
*                 if the input is an integer or not. It is looped until the user
*                 enters a valid integer type and then returns it.
*******************************************************************************/
int Menu::integerValidation()
{
    string userInput;
    bool integerCheck = true;

    do
    {
        //Reset flag and count every time loop iterates.
        integerCheck = true;

        //Get first input to test.
        cout << "Enter your choice: ";
        getline(cin, userInput);
        
        //If user didn't enter anything loop until they do.
        while (userInput.empty())
        {
            cout << "You entered nothing." << endl;
            cout << "Enter your choice: ";
            getline(cin, userInput);
        }

        //Checks each character in the user input.
        //If a single one isn't an integer set flag to false.
        for (int i = 0; i < userInput.length(); i++)
        {
            //This accounts for a negative integer.
            if (userInput[i] == '-')
            {
                i++;
            }
            
            if(!(isdigit(userInput[i])))
            {
                integerCheck = false;
            }
        }

        //If flag is false ask them to enter again.
        if(!integerCheck)
        {
            cout << "That is not an integer." << endl;
            cout << "Please try again." << endl;
        }
    }

    while(!integerCheck);

    return std::stoi (userInput);
}



/******************************************************************************
*                           void Menu::displayIntro()
*
*    Description: Displays ascii character intro screen at beginning of program.
*******************************************************************************/
void Menu::displayIntro()
{
    cout << "=================================================================" << endl;
    cout << "    o               .     ___---___                    .     " << endl;       
    cout << "       .              .--\\        --.     .     .         . " << endl;
    cout << "                    ./.;_.\\     __/~ \\.                    " << endl;
    cout << "                   /;  / `-'  __\\    . \\                   " << endl;
    cout << " .        .       / ,--'     / .   .;   \\        |          " << endl;
    cout << "                 | .|       /       __   |      -O-       .  " << endl;
    cout << "                |__/    __ |  . ;   \\ | . |      |          " << endl;
    cout << "                |      /  \\_    . ;| \\___|                 " << endl;
    cout << "   .    o       |      \\  .~\\___,--'     |           .     " << endl;
    cout << "                 |     | . ; ~~~~\\_    __|                  " << endl;
    cout << "    |             \\    \\   .  .  ; \\  /_/   .             " << endl;
    cout << "   -O-        .    \\   /         . |  ~/                  . " << endl;
    cout << "    |    .          ~\\ \\   .      /  /~          o         " << endl;
    cout << "  .                   ~--___ ; ___--~                        " << endl;
    cout << "                 .          ---         .                    " << endl;
    cout << "=================================================================" << endl;
    cout << "                           EARTHBOUND                           " << endl;
    cout << "=================================================================" << endl;
    cout << "The goal of Earthbound is to move your character Ness through"  << endl;
    cout << "the different locations getting items and the characters Jeff," << endl;
    cout << "Paula, and Poo to help you fight the last battle. The last    " << endl;
    cout << "battle takes place when you move to the Giygas Lair space.    " << endl;
    cout << "There are 6 locations in the game but you are only allowed 10  " << endl;
    cout << "action points. So make sure you dont waste them!               " << endl;
    cout << "Each person you recruit helps you kill Giygas faster.       "  << endl;
    cout << "Each Sound Stone melody you have knocks 20 health off Giygas." << endl;
    cout << "Each weapon you have increases damage done to Giygas.          " << endl;
    cout << "You lose the game if you run out of action points, dont have a" << endl;
    cout << "special ability for the final battle, or die in the final battle." << endl;
    cout << "=================================================================" << endl;
    
    //Press enter to continue and clear console.
    cout << endl << "PRESS ENTER TO BEGIN" << endl;
    cin.ignore(std::numeric_limits<int>::max(),'\n');
    system("clear");
}



/******************************************************************************
*                           int Menu::onettMenuOptions()
*
*    Description: Displays the options to perfom while on Onett space.
*******************************************************************************/
int Menu::onettMenuOptions()
{
    cout << "Please choose an option to perform at Onett." << endl;
    cout << "Note: Each option uses an action point." << endl;
    cout << "============================================" << endl;
    cout << "1. Grab the Homerun Bat for Ness." << endl;
    cout << "2. Defeat Giant Ant and record melody to sound stone." << endl;
    cout << "3. Move on to the town of Twoson." << endl;
    
    menuChoice = integerValidation();
    
    while ((menuChoice != 1) && (menuChoice != 2) && (menuChoice != 3))
    {
        cout << "You must enter a 1, 2, or 3." << endl;
        menuChoice = integerValidation();
    }
    
    system("clear");
    
    return menuChoice;
    
}



/******************************************************************************
*                           int Menu::twosonMenuOptions()
*
*    Description: Displays the options to perfom while on Twoson space.
*******************************************************************************/
int Menu::twosonMenuOptions()
{
    cout << "Please choose an option to perform at Twoson." << endl;
    cout << "Note: Each option uses an action point." << endl;
    cout << "=============================================" << endl;
    cout << "1. Recruit Paula to your party." << endl;
    cout << "2. Defeat Giant Mole and record melody to sound stone." << endl;
    cout << "3. Acquire prayer ability for Paula." << endl;
    cout << "4. Move on to town of Winters" << endl;
    
    menuChoice = integerValidation();
    
    while ((menuChoice != 1) && (menuChoice != 2) && (menuChoice != 3) && (menuChoice != 4))
    {
        cout << "You must enter a 1, 2, 3, or 4." << endl;
        menuChoice = integerValidation();
    }
    
    system("clear");
    
    return menuChoice;
    
}



/******************************************************************************
*                           int Menu::wintersMenuOptions()
*
*    Description: Displays the options to perfom while on Winters space.
*******************************************************************************/
int Menu::wintersMenuOptions()
{
    cout << "Please choose an option to perform at Winters." << endl;
    cout << "Note: Each option uses an action point." << endl;
    cout << "==============================================" << endl;
    cout << "1. Recruit Jeff to your party." << endl;
    cout << "2. Use Bubble Monkey and take a ride with Tessie." << endl;
    cout << "3. Move on to town of Dalaam." << endl;
    
    menuChoice = integerValidation();
    
    while ((menuChoice != 1) && (menuChoice != 2) && (menuChoice != 3))
    {
        cout << "You must enter a 1, 2, or 3." << endl;
        menuChoice = integerValidation();
    }
    
    system("clear");
    
    return menuChoice;
    
}



/******************************************************************************
*                           int Menu::dalaamMenuOptions()
*
*    Description: Displays the options to perfom while on Dalaam space.
*******************************************************************************/
int Menu::dalaamMenuOptions()
{
    cout << "Please choose an option to perform at Dalaam." << endl;
    cout << "Note: Each option uses an action point." << endl;
    cout << "=============================================" << endl;
    cout << "1. Recruit Poo to your party." << endl;
    cout << "2. Defeat Electro Specter and record melody to sound stone." << endl;
    cout << "3. Move on to town of Saturn Valley." << endl;
    
    menuChoice = integerValidation();
    
    while ((menuChoice != 1) && (menuChoice != 2) && (menuChoice != 3))
    {
        cout << "You must enter a 1, 2, or 3." << endl;
        menuChoice = integerValidation();
    }
    
    system("clear");
    
    return menuChoice;
    
}



/******************************************************************************
*                           int Menu::saturnValleyMenuOptions()
*
*    Description: Displays the options to perfom while on Saturn Valley space.
*******************************************************************************/
int Menu::saturnValleyMenuOptions()
{
    cout << "Please choose an option to perform at Saturn Valley." << endl;
    cout << "Note: Each option uses an action point." << endl;
    cout << "====================================================" << endl;
    cout << "1. Get Sword of Kings for Poo." << endl;
    cout << "2. Defeat Guardian General and record melody to sound stone." << endl;
    cout << "3. Move on to final battle at Giygas Lair." << endl;
    
    menuChoice = integerValidation();
    
    while ((menuChoice != 1) && (menuChoice != 2) && (menuChoice != 3))
    {
        cout << "You must enter a 1, 2, or 3." << endl;
        menuChoice = integerValidation();
    }
    
    system("clear");
    
    return menuChoice;
    
}