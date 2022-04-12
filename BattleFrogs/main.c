/*

Created By: Andrew Lefors
Created On: 3/27/2020
Assignment: PA-6 'Battleship!'
Created For: Dr. O'Fallon CPTS_121 Spring 2020
File Version: 0.3.27.20

Description: This is the Game of BattleFrogs. To win, you must sink all of the Computers ships. If the Computer sinks all of your ships, you lose. You begin by selecting to place your ships manually or at random.              
	         Ships are placed in order from largest to smallest: Carrier, Battleship, Crusier, Submarine, and Destroyer. You will be asked for the direction to place your ship, and the position for the front of the ship.      
	         Ships placed vertically will occupy the spaces BELOW the initial point based on ship length. Ships placed horizontally will occupy the spaces to the RIGHT of the initial point based on ship length.                
	         Statistics are recorded and placed into a log file 'battleship.log' at the end of the match, along with each move made during the game.


			NOTE: clear screen function: Learned how to do this from StackOverflow: https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c/42500322



*/
#include "battleShip.h"

int main(void)
{
	int isGameActive = 0;
	srand((unsigned int)time(NULL));

	
	while (isGameActive == 0)
	{
		//Enter Menu Loop, repeat unless user selects quit
		isGameActive = menu_loop();

	}
	
	
	return 0;
}