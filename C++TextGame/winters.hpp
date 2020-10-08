/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Winters Class.
*******************************************************************************/

#ifndef WINTERSCLASS_HPP
#define WINTERSCLASS_HPP

#include "space.hpp"

class Winters : public Space
{
    private:
    
    protected:
    
        std::string currentSpaceName;
    
    public:
    
        Winters();
        virtual ~Winters();
        
        std::string getSpaceName();
        void displaySpace();
        
};

#endif