/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the implementation file for Space Class. Space is an object
*               that has 4 pointers that can link to other Space objects. This game
*               is linear so only the up and down space pointers are used but the 
*               class contains left and right pointers as well.
*******************************************************************************/

#include <iostream>

#include "space.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
*                           Space::Space()
*
*    Description: Default constructor for Space class.
*******************************************************************************/
Space::Space()
{
    upPointer = nullptr;
    downPointer = nullptr;
    leftPointer = nullptr;
    rightPointer = nullptr;
}



/******************************************************************************
*                           Space::~Space()
*
*    Description: Deconstructor for Space class.
*******************************************************************************/
Space::~Space()
{
    upPointer = nullptr;
    downPointer = nullptr;
    leftPointer = nullptr;
    rightPointer = nullptr;
}



/******************************************************************************
*                           Space* Space::getUpPointer()
*
*    Description: Getter for protected variable.
*******************************************************************************/
Space* Space::getUpPointer()
{
    return upPointer;
}



/******************************************************************************
*                           Space* Space::getDownPointer()
*
*    Description: Getter for protected variable.
*******************************************************************************/
Space* Space::getDownPointer()
{
    return downPointer;
}



/******************************************************************************
*                           Space* Space::getLeftPointer()
*
*    Description: Getter for protected variable.
*******************************************************************************/
Space* Space::getLeftPointer()
{
    return leftPointer;
}



/******************************************************************************
*                           Space* Space::getRightPointer()
*
*    Description: Getter for protected variable.
*******************************************************************************/
Space* Space::getRightPointer()
{
    return rightPointer;
}



/******************************************************************************
*                   void Space::setUpPointer(Space *upPointer)
*
*    Description: Setter for protected variable.
*******************************************************************************/    
void Space::setUpPointer(Space* upPointer)
{
    this -> upPointer = upPointer;
}



/******************************************************************************
*                   void Space::setDownPointer(Space *downPointer)
*
*    Description: Setter for protected variable.
*******************************************************************************/    
void Space::setDownPointer(Space* downPointer)
{
    this -> downPointer = downPointer;
}



/******************************************************************************
*                   void Space::setLeftPointer(Space *leftPointer)
*
*    Description: Setter for protected variable.
*******************************************************************************/    
void Space::setLeftPointer(Space* leftPointer)
{
    this -> leftPointer = leftPointer;
}



/******************************************************************************
*                   void Space::setRightPointer(Space *rightPointer)
*
*    Description: Setter for protected variable.
*******************************************************************************/    
void Space::setRightPointer(Space* rightPointer)
{
    this -> rightPointer = rightPointer;
}



