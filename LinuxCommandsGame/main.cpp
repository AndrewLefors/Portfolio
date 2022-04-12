/*******************************************************************************************************************************************
 * Author: Andrew J. Lefors                                                                                                                *
 * Project: Linux Command Matching                                                                                                         *
 * Created On: 2/01/2021                                                                                                                   *
 * Last Updated: 2/09/2021                                                                                                                 *
 * Description:                                                                                                                            *
 *                                                                                                                                         *
 *                                                                                                                                         *
 *                                                                                                                                         *
 * NOTES: ADVANTAGE OF LINKED LIST-Enables Rapid insertion of new nodes.                                                                   *
 *        DISADVANTAGE OF LINKED LIST- Must iterate to delete a node/find a node.                                                          *
 *                                                                                                                                         *
 *        ADVANTAGE OF ARRAY- Can rapidly (in constant time) remove any profile.                                                           *
 *        DISADVANTAGE OF ARRAY - must create new array with size n+1 and copy old array over for insertion at front.                      *
 *                                                                                                                                         *
 * *****************************************************************************************************************************************/


#include "data.hpp"
#include "node.hpp"
#include "list.hpp"
#include "functions.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


int main(void)
{
    List<Data> newList;
    //gets contents from file and places in singly linked list
    loadData("commands.csv", &newList);
    
   
    //Gets line count from profiles !Required to load profiles!
    int count = getLines("profiles.csv");
    //Gets saved user profiles and loads them into array of objects
    //Returns reference to dynamically allocated array.  
    Profiles *users = loadProfiles("profiles.csv", count);
    int option = -1;
    int isActive = 0;
    do
    {
    
    
    option = displayMenu();

    switch(option)
    {
        case 1: displayRules();
        break;

        case 2: std::system("clear");
                playGame(&newList, users);
        break;

        case 3: std::system("clear");
                loadGame(users);
                playGame(&newList, users);
        break;

        case 4: std::system("clear");
                addNewCommand(&newList);
        break;

        case 5: std::system("clear");
                removeCommand(&newList);
        break;

        case 6: isActive = exitGame(&newList, users);
        break;

        default: std::system("clear");
                 std::cout << "Error: Input not valid. Try again." << std::endl;
                 break;
    }
  
    } while(isActive != 1);
    return 0;
}
