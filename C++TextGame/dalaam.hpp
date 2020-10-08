/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Dalaam Class.
*******************************************************************************/

#ifndef DALAAMCLASS_HPP
#define DALAAMCLASS_HPP

#include "space.hpp"

class Dalaam : public Space
{
    private:
    
    protected:
    
        std::string currentSpaceName;
    
    public:
    
        Dalaam();
        virtual ~Dalaam();
        
        std::string getSpaceName();
        void displaySpace();
        
};

#endif