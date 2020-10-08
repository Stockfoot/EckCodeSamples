/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Winters Class. Winters class contains
*               a string for the space as well as a display for related ASCII art.
*******************************************************************************/

#include <iostream>

#include "winters.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           Winters::Winters() : Space()
*
*    Description: Default constructor for Winters class.
*******************************************************************************/
Winters::Winters() : Space()
{
    currentSpaceName = "Winters";
}



/******************************************************************************
*                           Winters::~Winters()
* 
*    Description: Desctructor for Winters class.
*******************************************************************************/
Winters::~Winters()
{
    
}



/******************************************************************************
*                   std::string Winters::getSpaceName();
* 
*    Description: Getter for current space name.
*******************************************************************************/
std::string Winters::getSpaceName()
{
    return currentSpaceName;
}



/******************************************************************************
*                           void displaySpace()
* 
*    Description: Display the image and information of current space.
*******************************************************************************/
void Winters::displaySpace()
{
    cout << "        ...        *                        *       *          " << endl;
    cout << "      ...   *         * ..   ...                        *      " << endl;
    cout << " *      ...        *           *            *                  " << endl;
    cout << "          ...               ...                          *     " << endl;
    cout << "            ..                            *                    " << endl;
    cout << "    *        ..        *                       *               " << endl;
    cout << "           __##____              *                      *      " << endl;
    cout << "  *    *  /  ##  ****                   *                      " << endl;
    cout << "         /        ****               *         *  X   *        " << endl;
    cout << "   *    /        ******     *                    XXX      *    " << endl;
    cout << "       /___________*****          *             XXXXX          " << endl;
    cout << "        |            ***               *       XXXXXXX   X     " << endl;
    cout << "    *   | ___        |                    *   XXXXXXXX  XXX    " << endl;
    cout << "  *     | | |   ___  | *       *             XXXXXXXXXXXXXXX   " << endl;
    cout << "        | |_|   | |  ****             *           X   XXXXXXX  " << endl;
    cout << "    *********** | | *******      *                X      X     " << endl;
    cout << "************************************************************   " << endl;
}