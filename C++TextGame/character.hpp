/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Character Class.
*******************************************************************************/

#ifndef CHARACTERCLASS_HPP
#define CHARACTERCLASS_HPP

#include "space.hpp"

using std::string;

class Character
{
    private:
    
        Space *currentSpace;
        int healthPoints;
        bool alive;
        string characterName;
        
        
    public:
    
        Character();
        Character(Space* currentSpace, int healthPoints, string name);
        ~Character();
        
        void setCharacterSpace(Space* currentSpace);
        Space* getCharacterSpace();
        
        int nessAttackDiceRoll();
        int paulaAttackDiceRoll();
        int jeffAttackDiceRoll();
        int pooAttackDiceRoll();
        int giygasAttackDiceRoll();
        void defenseFunction(int incomingDamage);
        int defenseDiceRoll();
        
        std::string getCharacterName();
        int getCharacterHealthPoints();
        bool getCharacterAlive();
        void setCharacterHealthPoints(int healthPoints);
        
        
};

#endif