/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for SaturnValley Class.
*******************************************************************************/

#ifndef SATURNVALLEYCLASS_HPP
#define SATURNVALLEYCLASS_HPP

#include "space.hpp"

class SaturnValley : public Space
{
    private:
    
    protected:
    
        std::string currentSpaceName;
    
    public:
    
        SaturnValley();
        virtual ~SaturnValley();
        
        std::string getSpaceName();
        void displaySpace();
};

#endif