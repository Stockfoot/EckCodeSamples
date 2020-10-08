/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Twoson Class.
*******************************************************************************/

#ifndef TWOSONCLASS_HPP
#define TWOSONCLASS_HPP

#include "space.hpp"

class Twoson : public Space
{
    private:
    
    protected:
    
        std::string currentSpaceName;
    
    public:
    
        Twoson();
        virtual ~Twoson();
        
        std::string getSpaceName();
        void displaySpace();
        
};

#endif