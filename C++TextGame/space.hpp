/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Space Class.
*******************************************************************************/

#ifndef SPACECLASS_HPP
#define SPACECLASS_HPP

class Space
{
    private:
    
    protected:
    
        Space *upPointer;
        Space *downPointer;
        Space *leftPointer;
        Space *rightPointer;
        
    public:
    
        Space();
        virtual ~Space();
        
        Space* getUpPointer();
        Space*  getDownPointer();
        Space*  getLeftPointer();
        Space*  getRightPointer();
        
        void setUpPointer(Space*  upPointer);
        void setDownPointer(Space*  downPointer);
        void setLeftPointer(Space*  leftPointer);
        void setRightPointer(Space*  rightPointer);
        
        virtual std::string getSpaceName() = 0;
        virtual void displaySpace() = 0;
        
        
};

#endif