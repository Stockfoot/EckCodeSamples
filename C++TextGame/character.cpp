/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the implementation file for Character Class. The Character
*               class contains a current space holder, name, alive, and health points.
*               It has getter and setters for private variables as well. It has
*               random die roll generators for each type of character in the game as well
*               as a random defend generator and a whole defense function for the final battle.
*******************************************************************************/

#include <iostream>

#include "character.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


/******************************************************************************
*                           Character::Character()
*
*    Description: Default constructor for Character class.
*******************************************************************************/
Character::Character()
{
    currentSpace = nullptr;
    healthPoints = 50;
    alive = true;
    characterName = "";
}



/******************************************************************************
*                           Character::Character()
*
*    Description: Overloaded constructor for Character class.
*******************************************************************************/
Character::Character(Space* currentSpace, int healthPoints, string characterName)
{
    this -> currentSpace = currentSpace;
    this -> healthPoints = healthPoints;
    alive = true;
    this -> characterName = characterName;
}



/******************************************************************************
*                           Character::~Character()
*
*    Description: Deconstructor for Character class.
*******************************************************************************/
Character::~Character()
{
    
}



/******************************************************************************
*               void setCharacterSpace(shared_ptr<Space> currentSpace)
*
*    Description: Setter for currentSpace.
*******************************************************************************/
void Character::setCharacterSpace(Space* currentSpace)
{
    this -> currentSpace = currentSpace;
}



/******************************************************************************
*                   shared_ptr<Space> getCharacterSpace()
*
*    Description: getter for currentSpace.
*******************************************************************************/
Space* Character::getCharacterSpace()
{
    return currentSpace;
}



/******************************************************************************
*                       int Character::attackDiceRoll()
* 
*    Description: This function generates a random integer based on the restrictions
*                 of the given character type. It then displays the die number and 
*                 returns the integer back to the attack function.
*******************************************************************************/
int Character::nessAttackDiceRoll()
{
    int numRolled = rand() % (20 - 5 + 1) + 5;
    cout << "Attackin Ness rolled a " << numRolled << endl;
    return numRolled;
}



/******************************************************************************
*                       int Character::attackDiceRoll()
* 
*    Description: This function generates a random integer based on the restrictions
*                 of the given character type. It then displays the die number and 
*                 returns the integer back to the attack function.
*******************************************************************************/
int Character::giygasAttackDiceRoll()
{
    int numRolled = rand() % (9 - 1 + 1) + 1;
    cout << "Attacking Giygas rolled a " << numRolled << endl;
    return numRolled;
}



/******************************************************************************
*                       int Character::paulaAttackDiceRoll()
* 
*    Description: This function generates a random integer based on the restrictions
*                 of the given character type. It then displays the die number and 
*                 returns the integer back to the attack function.
*******************************************************************************/
int Character::paulaAttackDiceRoll()
{
    int numRolled = rand() % (10 - 3 + 1) + 3;
    cout << "Attacking Paula rolled a " << numRolled << endl;
    return numRolled;
}



/******************************************************************************
*                       int Character::jeffAttackDiceRoll()
* 
*    Description: This function generates a random integer based on the restrictions
*                 of the given character type. It then displays the die number and 
*                 returns the integer back to the attack function.
*******************************************************************************/
int Character::jeffAttackDiceRoll()
{
    int numRolled = rand() % (15 - 3 + 1) + 3;
    cout << "Attacking Jeff rolled a " << numRolled << endl;
    return numRolled;
}



/******************************************************************************
*                       int Character::pooAttackDiceRoll()
* 
*    Description: This function generates a random integer based on the restrictions
*                 of the given character type. It then displays the die number and 
*                 returns the integer back to the attack function.
*******************************************************************************/
int Character::pooAttackDiceRoll()
{
    int numRolled = rand() % (25 - 5 + 1) + 5;
    cout << "Attacking Poo rolled a " << numRolled << endl;
    return numRolled;
}



/******************************************************************************
*                       void Character::defenseFunction()
* 
*    Description: This is the character defense function. It is passed the integer
*                 that was rolled from the attacks dice. This function does not return
*                 anything and instead does all display and calulations within the function.
*                 If total damage is less or equal to zero no damage is displayed. If damage
*                 is greater than 100 we know that Medusas gaze attack was passed into 
*                 the defense function and that the player should be set to 0 health.
*                 Otherwise we calculate and display normal damge. At the end we check
*                 if the strength points are less than zero, if they are the player is 
*                 dead and this is returned to main. 
*                 Unique to Vampire class is the charm function.
*******************************************************************************/
void Character::defenseFunction(int incomingDamage)
{
    
    
    
        //Roll defense dice, calculate and display damage.
        int defense = defenseDiceRoll();
        int totalDamage = incomingDamage - defense;
        cout << "Damage = Attacker's Roll " << incomingDamage << " - Defender's Roll " << defense << endl;
        cout << "Total damage done " << totalDamage << endl;
        cout << "Health Points before damage was " << healthPoints << endl;
        
        //If damage is zero or negative number no damage was done. Do not change strength points.
        if (totalDamage <= 0)
        {
            cout << "No damage was done." << endl;
            cout << "Health Points after no damage is " << healthPoints << endl;
        }
        
        
        //Damage was done so change strength points accordingly.
        else
        {
            healthPoints = healthPoints - totalDamage;
            cout << "New Health Points after damage is " << healthPoints << endl;
        }
    
    
    //Check to see if player is dead and change bool if dead.
    if (healthPoints <= 0)
    {
        cout << "The character has died!" << endl;
        alive = false;
    }
}



/******************************************************************************
*                       int Character::defenseDiceRoll()
* 
*    Description: This function generates a random integer based on the restrictions
*                 of the given character type. It then displays the die number and 
*                 returns the integer back to the attack function.
*******************************************************************************/
int Character::defenseDiceRoll()
{
    int numRolled = rand() % (4 - 1 + 1) + 1;
    cout << "Defender rolled a " << numRolled << endl;
    return numRolled;
}



/******************************************************************************
*                       std::string Character::getCharacterName()
* 
*    Description: Getter function for characterName protected variable.
*******************************************************************************/
std::string Character::getCharacterName()
{
    return characterName;
}



/******************************************************************************
*                       int Character::getCharacterHealthPoints()
* 
*    Description: Getter function for healthPoints protected variable.
*******************************************************************************/
int Character::getCharacterHealthPoints()
{
    return healthPoints;
}



/******************************************************************************
*                       bool Character::getCharacterAlive()
* 
*    Description: Getter function for alive protected variable.
*******************************************************************************/
bool Character::getCharacterAlive()
{
    return alive;
}



/******************************************************************************
*                       void setCharacterHealthPoints(int healthPoints)
* 
*    Description: Setter function for healthPoints protected variable.
*******************************************************************************/
void Character::setCharacterHealthPoints(int healthPoints)
{
    this -> healthPoints = healthPoints;
}