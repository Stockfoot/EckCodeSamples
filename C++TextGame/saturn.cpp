/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for SaturnValley Class. This class contains
*               a string for the space as well as a display for related ASCII art.
*******************************************************************************/

#include <iostream>

#include "saturn.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           SaturnValley::SaturnValley() : Space()
*
*    Description: Default constructor for SaturnValley class.
*******************************************************************************/
SaturnValley::SaturnValley() : Space()
{
    currentSpaceName = "Saturn Valley";
}



/******************************************************************************
*                           SaturnValley::~SaturnValley()
* 
*    Description: Desctructor for SaturnValley class.
*******************************************************************************/
SaturnValley::~SaturnValley()
{
    
}



/******************************************************************************
*                   std::string SaturnValley::getSpaceName();
* 
*    Description: Getter for current space name.
*******************************************************************************/
std::string SaturnValley::getSpaceName()
{
    return currentSpaceName;
}



/******************************************************************************
*                           void displaySpace()
* 
*    Description: Display the image and information of current space.
*******************************************************************************/
void SaturnValley::displaySpace()
{
    cout << "                   \\  |  /         ___________                  " << endl;
    cout << "    ____________  \\ \\_# /         |  ___      |       _________    " << endl;
    cout << "   |            |  \\  #/          | |   |     |      | = = = = |   " << endl;
    cout << "   | |   |   |  |   \\\\#           | |`v'|     |      |         |   " << endl;
    cout << "   |            |    \\#  //       |  --- ___  |      | |  || | |   " << endl;
    cout << "   | |   |   |  |     #_//        |     |   | |      |         |   " << endl;
    cout << "   |            |  \\\\ #_/_______  |     |   | |      | |  || | |   " << endl;
    cout << "   | |   |   |  |   \\\\# /_____/ \\ |      ---  |      |         |   " << endl;
    cout << "   |            |    \\# |+ ++|  | |  |^^^^^^| |      | |  || | |   " << endl;
    cout << "   |            |    \\# |+ ++|  | |  |^^^^^^| |      | |  || | |   " << endl;
    cout << "^^^|    (^^^^^) |^^^^^#^| H  |_ |^|  | |||| | |^^^^^^|         |   " << endl;
    cout << "   |    ( ||| ) |     # ^^^^^^    |  | |||| | |      | ||||||| |   " << endl;
    cout << "   ^^^^^^^^^^^^^________/  /_____ |  | |||| | |      | ||||||| |   " << endl;
    cout << "        `v'-                      ^^^^^^^^^^^^^      | ||||||| |   " << endl;
    cout << "         || |`.      (__)    (__)                          ( )     " << endl;
    cout << "                     (oo)    (oo)                       /---V      " << endl;
    cout << "              /-------\\/      \\/ --------\\             * |  |      " << endl;
    cout << "             / |     ||        ||_______| \\                        " << endl;
    cout << "            *  ||W---||        ||      ||  *                       " << endl;
    cout << "               ^^    ^^        ^^      ^^                          " << endl;
}