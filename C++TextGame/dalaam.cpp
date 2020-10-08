/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Dalaam Class. Dalaam class contains
*               a string for the space as well as a display for related ASCII art.
*******************************************************************************/

#include <iostream>

#include "dalaam.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           Dalaam::Dalaam() : Space()
*
*    Description: Default constructor for Dalaam class.
*******************************************************************************/
Dalaam::Dalaam() : Space()
{
    currentSpaceName = "Dalaam";
}



/******************************************************************************
*                           Dalaam::~Dalaam()
* 
*    Description: Desctructor for Dalaam class.
*******************************************************************************/
Dalaam::~Dalaam()
{
    
}



/******************************************************************************
*                   std::string Dalaam::getSpaceName();
* 
*    Description: Getter for current space name.
*******************************************************************************/
std::string Dalaam::getSpaceName()
{
    return currentSpaceName;
}


/******************************************************************************
*                           void displaySpace()
* 
*    Description: Display the image and information of current space.
*******************************************************************************/
void Dalaam::displaySpace()
{
    cout << "                                      /\\                                       " << endl;
    cout << "                                      /\\                                      " << endl;
    cout << "                                      /\\                                       " << endl;
    cout << "                                      /\\                                       " << endl;
    cout << "                                    _`=='_                                     " << endl;
    cout << "                                 _-~......~-_                                  " << endl;
    cout << "                             _--~............~--_                              " << endl;
    cout << "                       __--~~....................~~--__                        " << endl;
    cout << "           .___..---~~~................................~~~---..___,            " << endl;
    cout << "            `=.________________________________________________,='             " << endl;
    cout << "               @^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^@                " << endl;
    cout << "                        |  |  I   I   II   I   I  |  |                         " << endl;
    cout << "                        |  |__I___I___II___I___I__|  |                         " << endl;
    cout << "                        | /___I_  I   II   I  _I___\\ |                         " << endl;
    cout << "                        |'_     ~~~~~~~~~~~~~~     _`|                         " << endl;
    cout << "                    __-~...~~~~~--------------~~~~~...~-__                     " << endl;   
    cout << "            ___---~~......................................~~---___             " << endl;
    cout << ".___..---~~~......................................................~~~---..___, " << endl;
    cout << " `=.______________________________________________________________________,='  " << endl;
    cout << "    @^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^@     " << endl;
    cout << "              |   |    | |    |  |    ||    |  |    | |    |   |               " << endl;
    cout << "              |   |____| |____|  |    ||    |  |____| |____|   |               " << endl;
    cout << "              |__________________|____||____|__________________|               " << endl;
    cout << "            _-|_____|_____|_____|__|------|__|_____|_____|_____|-_             " << endl;
}