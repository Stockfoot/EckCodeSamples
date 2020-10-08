/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the specification file for Menu Class.
***********************************************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

#ifndef MENUCLASS_HPP
#define MENUCLASS_HPP

class Menu
{

    private:

        int menuChoice;

    public:

        Menu();
        ~Menu();
        int getMenuChoice();
        int integerValidation();
        void displayIntro();
        int onettMenuOptions();
        int twosonMenuOptions();
        int wintersMenuOptions();
        int dalaamMenuOptions();
        int saturnValleyMenuOptions();

};

#endif
