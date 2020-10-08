/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for GiygasLair Class.
*******************************************************************************/

#ifndef GIYGASLAIRCLASS_HPP
#define GIYGASLAIRCLASS_HPP

#include "space.hpp"

class GiygasLair : public Space
{
    private:
    
    protected:
    
        std::string currentSpaceName;
    
    public:
    
        GiygasLair();
        virtual ~GiygasLair();
        
        std::string getSpaceName();
        void displaySpace();
        
};

#endif