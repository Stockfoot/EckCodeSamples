/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Onett Class.
*******************************************************************************/

#ifndef ONETTCLASS_HPP
#define ONETTCLASS_HPP

#include "space.hpp"

class Onett : public Space
{
    private:
    
    protected:
    
        std::string currentSpaceName;
    
    public:
    
        Onett();
        virtual ~Onett();
        
        std::string getSpaceName();
        void displaySpace();
        
};

#endif