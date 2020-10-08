/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for GiygasLair Class. This class contains
*               a string for the space as well as a display for related ASCII art.
*******************************************************************************/

#include <iostream>

#include "giygas.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           GiygasLair::GiygasLair() : Space()
*
*    Description: Default constructor for GiygasLair class.
*******************************************************************************/
GiygasLair::GiygasLair() : Space()
{
    currentSpaceName = "Giygas Lair";
}



/******************************************************************************
*                           GiygasLair::~GiygasLair()
* 
*    Description: Desctructor for GiygasLair class.
*******************************************************************************/
GiygasLair::~GiygasLair()
{
    
}



/******************************************************************************
*                   std::string GiygasLair::getSpaceName();
* 
*    Description: Getter for current space name.
*******************************************************************************/
std::string GiygasLair::getSpaceName()
{
    return currentSpaceName;
}



/******************************************************************************
*                           void displaySpace()
* 
*    Description: Display the image and information of current space.
*******************************************************************************/
void GiygasLair::displaySpace()
{
    cout << "            _.------.                        .----.__      " << endl;
    cout << "           /         \\_.       ._           /---.__  \\         " << endl;
    cout << "          |  O    O   |\\\\___  //|          /       `\\ |        " << endl;
    cout << "          |  .vvvvv.  | )   `(/ |         | o     o  \\|        " << endl;
    cout << "          /  |     |  |/      \\ |  /|   ./| .vvvvv.  |\\        " << endl;
    cout << "         /   `^^^^^'  / _   _  `|_ ||  / /| |     |  | \\       " << endl;
    cout << "       ./  /|         | O)  O   ) \\|| //' | `^vvvv'  |/\\\\      " << endl;
    cout << "      /   / |         \\        /  | | ~   \\          |  \\\\     " << endl;
    cout << "      \\  /  |        / \\ Y   /'   | \\     |          |   ~     " << endl;
    cout << "       `'   |  _     |  `._/' |   |  \\     7        /          " << endl;
    cout << "         _.-'-' `-'-'|  |`-._/   /    \\ _ /    .    |          " << endl;
    cout << "    __.-'            \\  \\   .   / \\_.  \\ -|_/\\/ `--.|_         " << endl;
    cout << " --'                  \\  \\ |   /    |  |              `-       " << endl;
    cout << "                       \\uU \\UU/     |  /                       " << endl;
}