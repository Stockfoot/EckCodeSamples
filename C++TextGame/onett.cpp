/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Onett Class. Onett class contains
*               a string for the space as well as a display for related ASCII art.
*******************************************************************************/

#include <iostream>

#include "onett.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           Onett::Onett() : Space()
*
*    Description: Default constructor for Onett class.
*******************************************************************************/
Onett::Onett() : Space()
{
    currentSpaceName = "Onett";
}



/******************************************************************************
*                           Onett::~Onett()
* 
*    Description: Desctructor for Onett class.
*******************************************************************************/
Onett::~Onett()
{
    
}



/******************************************************************************
*                   std::string Onett::getSpaceName();
* 
*    Description: Getter for current space name.
*******************************************************************************/
std::string Onett::getSpaceName()
{
    return currentSpaceName;
}



/******************************************************************************
*                           void displaySpace()
* 
*    Description: Display the image and information of current space.
*******************************************************************************/
void Onett::displaySpace()
{
    cout << "            `'::.                  " << endl;
    cout << "    _________H ,%%&%,              " << endl;
    cout << "   /\\     _   \\%&&%%&%           " << endl;
    cout << "  /  \\___/^\\___\\%&%%&&          " << endl;
    cout << "  |  | []   [] |%\\Y&%'            " << endl;
    cout << "  |  |   .-.   | ||                " << endl;
    cout << "~~@._|@@_|||_@@|~||~~~~~~~~~~~~~   " << endl;
    cout << "     `'''| |'''`                   " << endl;
}