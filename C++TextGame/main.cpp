/******************************************************************************
* Program Name: Project 5 (Final Project)
* Author:       Russell Eck
* Date:         11/21/2018
* Description:  This is the text based game based on the Super Nintendo game Earthbound.
*               The player plays as Ness and goes from town to town acquiring new Party
*               members, new weapons, and defeating local bosses to acquire sound stone
*               melodies which will aid Ness in the final battle against the Evil Giygas.
*               
*               Source for ASCII Art: https://www.asciiart.eu
*******************************************************************************/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <memory>
#include <ctime>
#include <stack>

#include "menuClass.hpp"
#include "character.hpp"
#include "onett.hpp"
#include "twoson.hpp"
#include "winters.hpp"
#include "dalaam.hpp"
#include "saturn.hpp"
#include "giygas.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::shared_ptr;
using std::stack;

int main()
{
    Menu menus;
    srand(time(0));
    int actionPoints = 10;
    int roundCounter = 0;
    int damage = 0;
    bool prayerAcquired = false;
    bool homerunBatAcquired = false;
    bool swordOfKingsAcquired = false;
    
    //Menu choices
    bool option1Chosen = false;
    bool option2Chosen = false;
    bool option3Chosen = false;
    bool paulaInParty = false;
    bool jeffInParty = false;
    bool pooInParty = false;
    int onettMenuChoice = 1;
    int twosonMenuChoice = 1;
    int wintersMenuChoice = 1;
    int dalaamMenuChoice = 1;
    int saturnValleyMenuChoice = 1;
    int giygasLairMenuChoice = 1;
    
    //Item containers
    stack<int> soundStonesItems;
    //Can only hold 2 of the 3 weapons. Homerun Bat, Prayer Ability, and Sword of Kings.
    stack<int> weaponItems; 
    int weaponLimit = 2;
    
    /******************************************
    * Game Setup of Spaces.
    ******************************************/
    //Create all space pointers.
    Space *onett = new Onett();
    Space *twoson = new Twoson();
    Space *winters = new Winters();
    Space *dalaam = new Dalaam();
    Space *saturnValley = new SaturnValley();
    Space *giygasLair = new GiygasLair();
    
    //Link all spaces setting pointers.
    onett->setUpPointer(twoson);
    twoson->setDownPointer(onett);
    twoson->setUpPointer(winters);
    winters->setDownPointer(twoson);
    winters->setUpPointer(dalaam);
    dalaam->setDownPointer(winters);
    dalaam->setUpPointer(saturnValley);
    saturnValley->setDownPointer(dalaam);
    saturnValley->setUpPointer(giygasLair);
    giygasLair->setDownPointer(saturnValley);
    
    //Create characters.
    Character ness(onett, 50, "Ness");
    Character giygas(giygasLair, 500, "Giygas");
    
    
    /******************************************
    * Display intro menu and begin game.
    ******************************************/
    menus.displayIntro();
   
    /********************************************************
    * Ness start on Onett space. Loop and perform actions.
    ********************************************************/
    while (onettMenuChoice == 1 || onettMenuChoice == 2)
    {
        /******************************************
        * Display Onett Menu and choices
        ******************************************/
        cout << "Current Space: " << ness.getCharacterSpace() -> getSpaceName() << endl;
        cout << "Current Party: " << "Ness" << endl;
        cout << "Sound Stone Melodies: " << soundStonesItems.size() << endl;
        cout << "Weapons Held: " << weaponItems.size() << "/" << weaponLimit << " ";
        if (homerunBatAcquired == true)
        {
            cout << " (Homerun Bat) ";
        }
        cout << endl;
        cout << "Action Points: " << actionPoints << endl;
        cout << "===============================" << endl << endl;
        onett->displaySpace();
        cout << "Ness is awoken by a loud crash. A meteor has hit the hill near his house and evil has spilled across the land." << endl;
        cout << "He is tasked with visiting the locations around the world and defeating the Sanctuary Bosses as well as gathering " << endl;
        cout << "his allies Paula in Twoson, Jeff in Winters, and Poo in Dalaam." << endl << endl;
        
        onettMenuChoice = menus.onettMenuOptions();
        
        /**********************************************
        * User chooses option 1 to get the Homerun bat.
        **********************************************/
        if (onettMenuChoice == 1 && option1Chosen == false)
        {
            cout << "Ness goes to his sisters bedroom and pulls the Homerun Bat out of the present." << endl;
            cout << "Ness's attack power increases by 30!" << endl;
            weaponItems.push(1);
            option1Chosen = true;
            homerunBatAcquired = true;
            actionPoints--;
        }
        
        //Option 1 has already been chosen.
        else if (onettMenuChoice == 1 && option1Chosen == true)
        {
            cout << "Ness has already gotten the Homerun bat." << endl;
            cout << "Choose another option or move on to Twoson." << endl;
        }
        
        /**********************************************************************
        * User chooses option 2 to defeat Giant Ant and get sound stone melody.
        ***********************************************************************/
        if (onettMenuChoice == 2 && option2Chosen == false)
        {
            cout << "Ness makes his way to the Giant Step. He defeats the Giant Ant boss and records the melody to the Sound Stone!" << endl;
            option2Chosen = true;
            actionPoints--;
            soundStonesItems.push(5);
        }
        
        //Option 2 has already been chosen.
        else if (onettMenuChoice == 2 && option2Chosen == true)
        {
            cout << "Ness has already defeated the Giant Ant and recorded the melody to the Sound Stone." << endl;
            cout << "Choose another option or move on to Twoson." << endl;
        }
        
        /*************************************************************
        * User choose option 3 to move on to the town of Twoson.
        *************************************************************/
        if (onettMenuChoice == 3)
        {
            cout << "Ness defeats the local sharks removing the road block to Twoson." << endl;
            cout << "He then heads south to the town of Twoson where Paula lives." << endl;
            actionPoints--;
            ness.setCharacterSpace(twoson);
        }
        
        //Press enter to continue and clear console.
        cout << endl << "PRESS ENTER TO CONTINUE" << endl;
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        system("clear");
        
    }
    
    //Reset menu bool between each space.
    option1Chosen = false;
    option2Chosen = false;
    option3Chosen = false;
    
    /********************************************************
    * Ness moves to Twoson space. Loop and perform actions.
    ********************************************************/
    while (twosonMenuChoice == 1 || twosonMenuChoice == 2 || twosonMenuChoice == 3)
    {
        /******************************************
        * Display Twoson Menu and choices
        ******************************************/
        cout << "Current Space: " << ness.getCharacterSpace() -> getSpaceName() << endl;
        cout << "Current Party: " << "Ness";
        if (paulaInParty == true)
        {
            cout << ", Paula";
        }
        cout << endl;
        cout << "Sound Stone Melodies: " << soundStonesItems.size() << endl;
        cout << "Weapons Held: " << weaponItems.size() << "/" << weaponLimit << " ";
        
        if (homerunBatAcquired == true)
        {
            cout << " (Homerun Bat) ";
        }
        
        if (prayerAcquired == true)
        {
            cout << " (Prayer) ";
        }
        
        cout << endl;
        cout << "Action Points: " << actionPoints << endl;
        cout << "===============================" << endl << endl;
        twoson->displaySpace();
        cout << "Ness reaches the town of Twoson. Twoson is the town where Paula lives but she has gone missing." << endl;
        cout << "Ness goes through the nearby caves to Happy Happy Village, a town full of cultists. He defeats the leader" << endl;
        cout << "and frees Paula from their imprisonment."  << endl << endl;
        
        twosonMenuChoice = menus.twosonMenuOptions();
        
        /*****************************************************
        * User chooses option 1 to recruit Paula to the party
        *****************************************************/
        if (twosonMenuChoice == 1 && option1Chosen == false)
        {
            cout << "After rescuing Paula from the Happy Happy Cultists, Ness recruits Paual to the party. Paula joins the party!" << endl;
            option1Chosen = true;
            paulaInParty = true;
            actionPoints--;
        }
        
        //Option 1 has already been chosen.
        else if (twosonMenuChoice == 1 && option1Chosen == true)
        {
            cout << "Paula has already joined the party." << endl;
            cout << "Choose another option or move on to Winters." << endl;
        }
        
        /*******************************************************
        * User chooses option 2 and defeats the Giant Mole boss.
        *******************************************************/
        if (twosonMenuChoice == 2 && option2Chosen == false)
        {
            cout << "The Giant Mole boss is defeated in the caves next to Twoson. The melody is recorded to the Sound Stone!" << endl;
            option2Chosen = true;
            actionPoints--;
            soundStonesItems.push(5);
        }
        
        //Option 2 has already been chosen.
        else if (twosonMenuChoice == 2 && option2Chosen == true)
        {
            cout << "The Giant Mole boss has already been defeated and the melody recorded to the Sound Stone." << endl;
            cout << "Choose another option or move on to Winters." << endl;
        }
        
        /**************************************************************************************
        * User chooses option 3 to have paula acquire prayer ability. Must have Paula in party.
        **************************************************************************************/
        if (twosonMenuChoice == 3 && option3Chosen == false && paulaInParty == true)
        {
            cout << "Paula acquires the Prayer ability! This ability could be very usuful in the final battle...." << endl;
            weaponItems.push(1);
            option3Chosen = true;
            actionPoints--;
            prayerAcquired = true;
        }
        
        //User choose option 3 but does not have Paula in the party.
        else if (twosonMenuChoice == 3 && option3Chosen == false && paulaInParty == false)
        {
            cout << "You must recruit Paula to your party before she can learn the Prayer ability." << endl;
            cout << "Choose another option or move on to Winters." << endl;
        }
        
        //Option 3 has already been chosen.
        else if (twosonMenuChoice == 3 && option3Chosen == true)
        {
            cout << "Paula has already acquired the Prayer ability." << endl;
            cout << "Choose another option or move on to Winters." << endl;
        }
        
        /***********************************************************
        * User choose option 4 and moves on to the town of Winters.
        ***********************************************************/
        if (twosonMenuChoice == 4)
        {
            cout << "Ness helps the Runaway Five band with their debts and frees them of their contract." << endl;
            cout << "He then heads north to the town of Winters where Jeff lives." << endl;
            actionPoints--;
            ness.setCharacterSpace(winters);
        }
        
        //Press enter to continue and clear console.
        cout << endl << "PRESS ENTER TO CONTINUE" << endl;
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        system("clear");
    }

    //Reset menu bool between each space.
    option1Chosen = false;
    option2Chosen = false;
    option3Chosen = false;
    
    /********************************************************
    * Ness moves to Winters space. Loop and perform actions.
    ********************************************************/
    while (wintersMenuChoice == 1 || wintersMenuChoice == 2)
    {
        /******************************************
        * Display Winters Menu and choices
        ******************************************/
        cout << "Current Space: " << ness.getCharacterSpace() -> getSpaceName() << endl;
        cout << "Current Party: " << "Ness";
        
        if (paulaInParty == true)
        {
            cout << ", Paula";
        }
        
        if (jeffInParty == true)
        {
            cout << ", Jeff";
        }
        
        cout << endl;
        cout << "Sound Stone Melodies: " << soundStonesItems.size() << endl;
        cout << "Weapons Held: " << weaponItems.size() << "/" << weaponLimit << " ";
        
        if (homerunBatAcquired == true)
        {
            cout << " (Homerun Bat) ";
        }
        
        if (prayerAcquired == true)
        {
            cout << " (Prayer) ";
        }
        
        cout << endl;
        cout << "Action Points: " << actionPoints << endl;
        cout << "===============================" << endl << endl;
        winters->displaySpace();
        cout << "Ness reaches the town of Winters. A snowy village up north where Jeff lives and his genius" << endl;
        cout << "inventor father Dr. Andonuts. Other colorful characters live here such as the Bubble Monkey" << endl;
        cout << "and the elusive Tessie monster." << endl << endl;
        
        wintersMenuChoice = menus.wintersMenuOptions();
        
        /*****************************************************
        * User chooses option 1 to recruit Jeff.
        *****************************************************/
        if (wintersMenuChoice == 1 && option1Chosen == false)
        {
            cout << "Jeff leaves the boarding school he is living at and meets up with Ness." << endl;
            cout << "Jeff joins the party!" << endl;
            actionPoints--;
            jeffInParty = true;
            option1Chosen = true;
        }
        
        //Option 1 has already been chosen.
        else if (wintersMenuChoice == 1 && option1Chosen == true)
        {
            cout << "Jeff has already joined the party." << endl;
            cout << "Choose another option or move on to Dalaam." << endl;
        }
        
        /*****************************************************
        * User chooses option 2 to activate Bubble Monkey ride.
        *****************************************************/
        if (wintersMenuChoice == 2 && option2Chosen == false)
        {
            cout << "Ness pulls out a piece of gum and give it to Bubble Monkey. Bubble Monkey blows a bubble" << endl;
            cout << "and floats over the nearby water. The Tessie monster rises from the water and the party" << endl;
            cout << "takes a ride." << endl;
            actionPoints--;
            option2Chosen = true;
        }
        
        //Option 2 has already been chosen.
        else if (wintersMenuChoice == 2 && option2Chosen == true)
        {
            cout << "Ness doesn't have any more gum for Bubble Monkey." << endl;
            cout << "Choose another option or move on to Dalaam." << endl;
        }
        
        /***********************************************************
        * User choose option 3 to move on to Dalaam.
        ***********************************************************/
        if (wintersMenuChoice == 3)
        {
            cout << "Ness defeats the boss at the nearby Stone Henge and boards Dr. Andonuts flying ship." << endl;
            cout << "He then heads to the asian village of Dalaam where Poo lives." << endl;
            actionPoints--;
            ness.setCharacterSpace(dalaam);
        }
        
        //Press enter to continue and clear console.
        cout << endl << "PRESS ENTER TO CONTINUE" << endl;
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        system("clear");
    
    }
    
    //Reset menu bool between each space.
    option1Chosen = false;
    option2Chosen = false;
    option3Chosen = false;
    
    /********************************************************
    * Ness moves to Dalaam space. Loop and perform actions.
    ********************************************************/
    while (dalaamMenuChoice == 1 || dalaamMenuChoice == 2)
    {
        //Check action points and end game if zero.
        if (actionPoints <= 0)
        {
            cout << "You have run out of action points!" << endl;
            cout << "            GAME OVER             " << endl;
            return 0;
        }
        
        /******************************************
        * Display Dalaam Menu and choices
        ******************************************/
        cout << "Current Space: " << ness.getCharacterSpace() -> getSpaceName() << endl;
        cout << "Current Party: " << "Ness";
        
        if (paulaInParty == true)
        {
            cout << ", Paula";
        }
        
        if (jeffInParty == true)
        {
            cout << ", Jeff";
        }
        
        if (pooInParty == true)
        {
            cout << ", Poo";
        }
        
        cout << endl;
        cout << "Sound Stone Melodies: " << soundStonesItems.size() << endl;
        cout << "Weapons Held: " << weaponItems.size() << "/" << weaponLimit << " ";
        
        if (homerunBatAcquired == true)
        {
            cout << " (Homerun Bat) ";
        }
        
        if (prayerAcquired == true)
        {
            cout << " (Prayer) ";
        }
        
        cout << endl;
        cout << "Action Points: " << actionPoints << endl;
        cout << "===============================" << endl << endl;
        dalaam->displaySpace();
        cout << "Ness reaches the town of Dalaam. This is a town in the far East where Poo the prince lives." << endl;
        cout << "It is a spiritual place where the residents utilize PSI powers." << endl << endl;
        
        dalaamMenuChoice = menus.dalaamMenuOptions();
        
        /*****************************************************
        * User chooses option 1 to recruit Poo to party.
        *****************************************************/
        if (dalaamMenuChoice == 1 && option1Chosen == false)
        {
            cout << "Ness goes to the palace of Dalaam and meets with the prince Poo." << endl;
            cout << "Poo joins the party!" << endl;
            actionPoints--;
            option1Chosen = true;
            pooInParty = true;
        }
        
        else if (dalaamMenuChoice == 1 && option1Chosen == true)
        {
            cout << "Poo is already in the party." << endl;
            cout << "Choose another option or move on to Saturn Valley." << endl;
        }
        
        /*****************************************************
        * User chooses option 2 to defeat Electro Specter.
        *****************************************************/
        if (dalaamMenuChoice == 2 && option2Chosen == false)
        {
            cout << "Ness heads out and defeats Electro Specter and records the melody to the Sound Stone!" << endl;
            actionPoints--;
            option2Chosen = true;
            soundStonesItems.push(5);
        }
        
        else if (dalaamMenuChoice == 2 && option2Chosen == true)
        {
            cout << "Ness has already defeated Electro Specter and recorded the melody to the Sound Stone." << endl;
            cout << "Choose another option or move on to Saturn Valley." << endl;
        }
        
        /*****************************************************
        * User chooses option 3 to move on to Saturn Valley.
        *****************************************************/
        if (dalaamMenuChoice == 3)
        {
            cout << "Ness heads to the final location of the village of Saturn Valley to prepare for the final battle against Giygas." << endl;
            actionPoints--;
            ness.setCharacterSpace(saturnValley);
        }
        
        //Press enter to continue and clear console.
        cout << endl << "PRESS ENTER TO CONTINUE" << endl;
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        system("clear");
    
    }
    
    //Reset menu bool between each space.
    option1Chosen = false;
    option2Chosen = false;
    option3Chosen = false;

    /********************************************************
    * Ness moves to Saturn Valley space. Loop and perform actions.
    ********************************************************/
    while (saturnValleyMenuChoice == 1 || saturnValleyMenuChoice == 2)
    {
        //Check action points and end game if zero.
        if (actionPoints <= 0)
        {
            cout << "You have run out of action points!" << endl;
            cout << "            GAME OVER             " << endl;
            return 0;
        }
        
        /******************************************
        * Display Saturn Valley Menu and choices
        ******************************************/
        cout << "Current Space: " << ness.getCharacterSpace() -> getSpaceName() << endl;
        cout << "Current Party: " << "Ness";
        
        if (paulaInParty == true)
        {
            cout << ", Paula";
        }
        
        if (jeffInParty == true)
        {
            cout << ", Jeff";
        }
        
        if (pooInParty == true)
        {
            cout << ", Poo";
        }
        
        cout << endl;
        cout << "Sound Stone Melodies: " << soundStonesItems.size() << endl;
        cout << "Weapons Held: " << weaponItems.size() << "/" << weaponLimit << " ";
        
        if (homerunBatAcquired == true)
        {
            cout << " (Homerun Bat) ";
        }
        
        if (prayerAcquired == true)
        {
            cout << " (Prayer) ";
        }
        
        if (swordOfKingsAcquired == true)
        {
            cout << " (Sword of Kings) ";
        }
        
        cout << endl;
        cout << "Action Points: " << actionPoints << endl;
        cout << "===============================" << endl << endl;
        saturnValley->displaySpace();
        cout << "Ness reaches the town of Saturn Valley. Everyone has gathered to see the party off to the final battle" << endl;
        cout << "against the evil Giygas." << endl;
        
        saturnValleyMenuChoice = menus.saturnValleyMenuOptions();
        
        /*****************************************************
        * User chooses option 1 to acquire Sword of Kings.
        *****************************************************/
        if (saturnValleyMenuChoice == 1 && option1Chosen == false && weaponItems.size() == weaponLimit)
        {
            cout << "Cannot acquire the Sword of Kings. Weapon limit of 2 is reached with the Homerun Bat and Prayer ability." << endl;
        }
        
        else if (saturnValleyMenuChoice == 1 && option1Chosen == false && pooInParty == true)
        {
            cout << "Poo acquires the extremely powerful Sword of Kings!" << endl;
            cout << "Poo's attack power increases by 40!" << endl;
            swordOfKingsAcquired = true;
            actionPoints--;
            option1Chosen = true;
        }
        
        else if (saturnValleyMenuChoice == 1 && option1Chosen == false && pooInParty == false)
        {
            cout << "Poo is not in the party and cannot acquire the Sword of Kings!" << endl;
        }
        
        else if (saturnValleyMenuChoice == 1 && option1Chosen == true)
        {
            cout << "Poo has already acquired the Sword of Kings." << endl;
            cout << "Choose another option or move on to Giygas's Lair." << endl;
        }

        /*****************************************************
        * User chooses option 2 to defeat Guardian General.
        *****************************************************/
        if (saturnValleyMenuChoice == 2 && option2Chosen == false)
        {
            cout << "Ness defeats the Guardian General and records the melody to the Sound Stone!" << endl;
            actionPoints--;
            option2Chosen = true;
            soundStonesItems.push(5);
        }
        
        else if(saturnValleyMenuChoice ==2 && option2Chosen == true)
        {
            cout << "Ness has already defeated the Guardian General." << endl;
            cout << "Choose another option or move on to Giygas's Lair." << endl;
        }

        /*****************************************************
        * User chooses option 3 to move on to Saturn Valley.
        *****************************************************/
        if (saturnValleyMenuChoice == 3)
        {
            cout << "Ness heads to the final battle against Giygas! Good Luck!" << endl;
            actionPoints--;
            ness.setCharacterSpace(giygasLair);
        }
        
        //Press enter to continue and clear console.
        cout << endl << "PRESS ENTER TO CONTINUE" << endl;
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        system("clear");
    
    }
    
    //Reset menu bool between each space.
    option1Chosen = false;
    option2Chosen = false;
    option3Chosen = false;
    
    
    /********************************************************
    * Ness moves to the final battle against Giygas.
    ********************************************************/
    //If user didn't recruit Paula and her Prayer Ability, the user automatically fails.
    if (prayerAcquired == false)
    {
        cout << "  Without Paula and her Prayer ability there is no hope in defeating Giygas. " << endl;
        cout << "Ness and his party are defeated and the world is overcome by the Evil Giygas." << endl;
        cout << "                                  GAME OVER                                  " << endl;
        
        return 0;
    }
    
    /******************************************
    * Display Giygas Lair
    ******************************************/
    cout << "Current Space: " << ness.getCharacterSpace() -> getSpaceName() << endl;
    cout << "Current Party: " << "Ness";
        
    if (paulaInParty == true)
    {
        cout << ", Paula";
    }
        
    if (jeffInParty == true)
    {
        cout << ", Jeff";
    }
        
    if (pooInParty == true)
    {
        cout << ", Poo";
    }
        
    cout << endl;
    cout << "Sound Stone Melodies: " << soundStonesItems.size() << endl;
    cout << "Weapons Held: " << weaponItems.size() << "/" << weaponLimit << " ";
        
    if (homerunBatAcquired == true)
    {
        cout << " (Homerun Bat) ";
    }
        
    if (prayerAcquired == true)
    {
        cout << " (Prayer) ";
    }
        
    if (swordOfKingsAcquired == true)
    {
        cout << " (Sword of Kings) ";
    }
        
    cout << endl;
    cout << "Action Points: " << actionPoints << endl;
    cout << "===============================" << endl << endl;
    giygasLair->displaySpace();
    cout << "Ness reaches Giygas's Lair!" << endl;
    
    
    //Reduce Giygas max health based on number of melodies acquired.
    int giygasHealthReduction = (20 * soundStonesItems.size());
    cout << "Giygas current max health points = " << giygas.getCharacterHealthPoints() << endl;
    cout << "Sound Stone melodies reduce Giygas max health Points by " << giygasHealthReduction << endl;
    giygas.setCharacterHealthPoints(giygas.getCharacterHealthPoints() - giygasHealthReduction);
    cout << "Giygas new max health points = " << giygas.getCharacterHealthPoints() << endl;
    cout << "BATTLE BEGINS!" << endl;
    
    //Press enter to continue and clear console.
    cout << endl << "PRESS ENTER TO CONTINUE" << endl;
    cin.ignore(std::numeric_limits<int>::max(),'\n');
    system("clear");
    
    
    /**********************************
    * Battle against Giygas begins.
    **********************************/
    while (ness.getCharacterAlive() && giygas.getCharacterAlive())
        {
            //Round display
            roundCounter++;
            cout << "Round " << roundCounter << "... FIGHT!" << endl;
            cout << "-------------------" << endl;
        
            //Ness attacks, Giygas defends.
            damage = 0;
            cout << "Attacker is " << ness.getCharacterName() << endl; 
            cout << "Health Points = " << ness.getCharacterHealthPoints() <<endl;
            damage = ness.nessAttackDiceRoll();
            
            //Add more damage if Ness has Homerun Bat.
            if (homerunBatAcquired == true)
            {
                cout << "Damage increased by 30 with Homerun Bat!" << endl;
                damage = damage + 30;
            }
            
            //Jeff attacks if in party.
            if (jeffInParty == true)
            {
                damage = damage + ness.jeffAttackDiceRoll();
            }
            
            //Poo attacks if in party.
            if (pooInParty == true)
            {
                damage = damage + ness.pooAttackDiceRoll();
            }
            
            //Add more damage if Poo has Sword of Kings.
            if (swordOfKingsAcquired == true)
            {
                cout << "Damage increased by 40 with Sword of Kings!" << endl;
                damage = damage + 40;
            }
            
            //Paula attacks if in party.
            if (paulaInParty == true)
            {
                damage = damage + ness.paulaAttackDiceRoll();
            }
            
            cout << "Paula prays with all her might. Giygas is now vulnerable." << endl;
            
            cout << "------------------------------------------------------------------------" << endl;
            cout << "Defender is " << giygas.getCharacterName() << endl;
            cout << "Health Points = " << giygas.getCharacterHealthPoints() << endl;
            giygas.defenseFunction(damage);
            cout << endl << "========================================================================" << endl << endl;
        
            //If Giygas has died, don't allow next part of round to proceed and break loop.
            if (giygas.getCharacterAlive() == false)
            {
                cout << "THE EVIL GIYGAS HAS BEEN DEFEATED!" << endl;
                cout << "PEACE HAS BEEN BROUGHT TO EARTH, YOU WIN!" << endl;
                break;
            }
        
            //Giygas attacks, Ness defends.
            damage = 0;
            cout << "Attacker is " << giygas.getCharacterName() << endl;
            cout << "Health Points = " << giygas.getCharacterHealthPoints() << endl;
            damage = giygas.giygasAttackDiceRoll();
            cout << "------------------------------------------------------------------------" << endl;
            cout << "Defender is " << ness.getCharacterName() << endl;
            cout << "Health Points = " << ness.getCharacterHealthPoints() << endl;
            ness.defenseFunction(damage);
            cout << "========================================================================" << endl;
        
            //Ness has died, don't allow next part of round to proceed and break loop.
            if (ness.getCharacterAlive() == false)
            {
                cout << "   NESS AND HIS FRIENDS HAVE DIED!   " << endl;
                cout << "THE EVIL GIYGAS TAKES OVER THE WORLD!" << endl;
                cout << "             GAME OVER!              " << endl;
                break;
            }
        
            //Press enter to go to next round and clear console.
            cout << endl << "PRESS ENTER FOR NEXT ROUND" << endl;
            cin.ignore(std::numeric_limits<int>::max(),'\n');
            system("clear");
        }
        
        //Delete dynamic memory.
        delete onett;
        delete twoson;
        delete winters;
        delete dalaam;
        delete saturnValley;
        delete giygasLair;
        
    return 0;
    
}
