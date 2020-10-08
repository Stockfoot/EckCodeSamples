/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Twoson Class. Twoson class contains
*               a string for the space as well as a display for related ASCII art.
*******************************************************************************/

#include <iostream>

#include "twoson.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           Twoson::Twoson() : Space()
*
*    Description: Default constructor for Twoson class.
*******************************************************************************/
Twoson::Twoson() : Space()
{
    currentSpaceName = "Twoson";
}



/******************************************************************************
*                           Twoson::~Twoson()
* 
*    Description: Desctructor for Twoson class.
*******************************************************************************/
Twoson::~Twoson()
{
    
}


/******************************************************************************
*                   std::string Twoson::getSpaceName();
* 
*    Description: Getter for current space name.
*******************************************************************************/
std::string Twoson::getSpaceName()
{
    return currentSpaceName;
}



/******************************************************************************
*                           void displaySpace()
* 
*    Description: Display the image and information of current space.
*******************************************************************************/
void Twoson::displaySpace()
{
    cout << "                             (   )                             " << endl;
    cout << "                          (    )                               " << endl;
    cout << "                           (    )                              " << endl;
    cout << "                         (    )                                " << endl;
    cout << "                            )  )                               " << endl;
    cout << "                           (  (                  /\\            " << endl;
    cout << "                            (_)                 /  \\  /\\       " << endl;
    cout << "                    ________[_]________      /\\/    \\/  \\      " << endl;
    cout << "           /\\      /\\        ______    \\    /   /\\/\\  /\\/\\     " << endl;
    cout << "          /  \\    //_\\       \\    /\\    \\  /\\/\\/    \\/    \\    " << endl;
    cout << "   /\\    / /\\/\\  //___\\       \\__/  \\    \\/                    " << endl;
    cout << "  /  \\  /\\/    \\//_____\\       \\ |[]|     \\                    " << endl;
    cout << " /\\/\\/\\/       //_______\\       \\|__|      \\                   " << endl;
    cout << "/      \\      /XXXXXXXXXX\\                  \\                  " << endl;
    cout << "        \\    /_I_II  I__I_\\__________________\\                 " << endl;
    cout << "               I_I|  I__I_____[]_|_[]_____I                    " << endl;
    cout << "               I_II  I__I_____[]_|_[]_____I                    " << endl;
    cout << "               I II__I  I     XXXXXXX     I                    " << endl;
    cout << "            ~~~~~'   '~~~~~~~~~~~~~~~~~~~~~~~~                 " << endl;
}