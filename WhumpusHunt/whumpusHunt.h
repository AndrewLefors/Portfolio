/***************************************************************************************************************************
*                                                                                                                          *
* Created By: Andrew Lefors                                                                                                *
* Created On: 6/01/2020                                                                                                    *
* Project: Hunt The Whumpus                                                                                                *
* File Version: 0.6.02.20                                                                                                  *
* File Description: This program simulates the game "Hunt The Whumpus" by Gregory Yob, Originally Developed in 1972.       *
*                   User is asked to input their name, at which time the game world is generated. Input commands are       *
*                   displayed with the map for the user to navigate the game-space. User loses if they fall into a pit or  *
*		    run into the Whumpus. User wins if they find the gold. Scores are tabulated at the end, with each      *
*		    successful turn earning the player 5 points. Each Partial or Full display has a negative impact on your*
*		    score of -2 and -5, respectively. The method you ended the game by is displayed on screen, and the user*
*		    name and score are written to an outfile "GameScores.txt".                                             *
*		    Happy Hunting!                                                                                         *
*                                                                                                                          *
*           ~  ~                                                                                                           *
*           @..@                                                                                                           *
*	   (-----)                                                                                                         *
*	  { )_J_( }                                                                                                        *
*	<^>|>   <|<^>                                                                                                      *
****************************************************************************************************************************/
#ifndef WHUMPUSHUNT_H
#define WHUMPUSHUNT_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#define ROW 5
#define COL 5
#define MIN_PITS 5
using namespace std;


struct Position
{
	int row;
	int col;
};

class GameWorld
{
private:

	//change to a dynamic 2d array, make set functions for player, whumpus, gold, and pit
	string playerName;
	Position player;
	Position whumpus;
	Position gold;
	Position pits[10];
	int pitCount;
	char gameBoard[ROW][COL];
	string endedBy;
	int moves;
	int partialDisplays;
    int fullDisplays;
	int score;
	

public:
	//constructor
	GameWorld(string name)
	{
		for (int rowIndex = 0; rowIndex < ROW; rowIndex++)
		{
			for (int colIndex = 0; colIndex < COL; colIndex++)
			{
				gameBoard[rowIndex][colIndex] = ' ';
			}
		}

		//set player name
		playerName = name;
		moves = 0;
		partialDisplays = 0;
		fullDisplays = 0;
		score = 0;
		//generate randome start location
		player.row = rand() % 5;
		player.col = rand() % 5;


		//create random location for whumpus, not overlapping with player
		do
		{
			whumpus.col = rand() % 5;
			whumpus.row = rand() % 5;
		} while (whumpus.col == player.col && whumpus.row == player.row);
	

		//create random location for gold, not overlapping whumpus or player
		//found better way to assign based on gameBoard values. Example in generate_pits function
		do
		{
			gold.row = rand() % 5;
			gold.col = rand() % 5;
		} while (gold.row == player.row && gold.col == player.col || gold.row == whumpus.row && gold.col == whumpus.col);

		//set game board with initial positions
		gameBoard[player.row][player.col] = 'U';
		gameBoard[whumpus.row][whumpus.col] = 'W';
		gameBoard[gold.row][gold.col] = 'G';
		//get random number of pits from 5-10
		pitCount = (MIN_PITS + (rand() % 5));
		//place pits on game board
		for (int index = 0; index < pitCount; index++)
		{
			generate_pit(index);
		}


	}
	//generic destructor
	~GameWorld()
	{

	}
	//shows entire map
/************************************************************
* Function: GameWorld::display_entire_world()               *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: Displays entire gameBoard of class GameWorld *
*              object                                       *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: fullDisplays incremented by +1            *
*************************************************************/
void display_entire_world(void);
	//shows only adjacent cells to player
/************************************************************
* Function: GameWorld::display_visible_world()              *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: Displays only player and adjacent cells on   *
*              gameBoard of class GameWorld object          *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: partialDisplays incremented by 1          *
*************************************************************/
void display_visible_world(void);
	//only displays player
/************************************************************
* Function: GameWorld::display_player_world()               *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: Displays only player on gameBoard of class   *
*              GameWorld object                             *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
void display_player_world(void);
	//creates pits on the map
/************************************************************
* Function: GameWorld::generate_pit()                       *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: Randomly creates and places pit in unoccupied*
*              gameBoard element.                           *
*                                                           *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: blank character replaced on gameBoard     *
*                 with 'P'                                  *
*************************************************************/
void generate_pit(int numberPit);
	//displays player name
/************************************************************
* Function: GameWorld::print_name()                         *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: prints user name                             *
*                                                           *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
void print_name(void);
	//displays how the player ended the game/death by pit/whumpus/found gold
/************************************************************
* Function: GameWorld::print_end_state()                    *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: prints how user ended game                   *
*                                                           *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
void print_end_state(void);
	//calculates and sets player score
/************************************************************
* Function: GameWorld::set_score()                          *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: calculates and sets player score             *
*                                                           *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: score has new value                       *
*************************************************************/
void set_score(void);
	//retrieves score
/************************************************************
* Function: GameWorld::get_score()                          *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: returns user score                           *
*                                                           *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
int get_score(void);
	//moves player up one cell
/************************************************************
* Function: GameWorld::move_up()                            *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: moves the player up one cell                 *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: Player not at top of map.                  *
* Postconditions: Player row decremented by 1               *
*************************************************************/
int move_up(void);
	//moves player down one cell
/************************************************************
* Function: GameWorld::move_down()                          *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: moves the player down one cell               *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: Player not at bottom of map.               *
* Postconditions: Player row incremented by 1               *
*************************************************************/
int move_down(void);
	//moves plarer to the left on cell
/************************************************************
* Function: GameWorld::move_left()                          *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: moves the player left one cell               *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: Player not at left border of map.          *
* Postconditions: Player column decremented by 1            *
*************************************************************/
int move_left(void);
	//moves player to the right one cell
/************************************************************
* Function: GameWorld::move_right()                         *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: moves the player right one cell              *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: Player not at right border of map.         *
* Postconditions: Player column incremented by 1            *
*************************************************************/
int move_right(void);
	//checks if user has won
/************************************************************
* Function: GameWorld::have_I_won()                         *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: checks if player position matches gold       *
* Input parameters: Void                                    *
* Returns: 1 if True, 0 if False                            *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
int have_I_won(void);
	//checks if user has lost 
/************************************************************
* Function: GameWorld::am_I_alive()                         *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: checks the players current state Alive/Dead  *
*              sets endedBy variable to cause of death      *
* Input parameters: Void                                    *
* Returns: 1 if True, 0 if False                            *
* Preconditions:                                            *
* Postconditions: endedBy contains string if False          *
*************************************************************/
int am_I_alive(void);
	//overloaded insertion operator to print user name and score to file
/************************************************************
* Function: operator<<(ofstream& outfile, GameWorld& g1)    *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: Overloads insertion operator to print user   *
*              name and scores earned to file object.       *
*                                                           *
* Input parameters: Void                                    *
* Returns: filestream                                       *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
friend ofstream& operator<<(ofstream& outfile, GameWorld& g1);

//displays user menu for input commands
/************************************************************
* Function: display_menu()                                  *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: prints user input options for game           *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
void display_menu(void);

/************************************************************
* Function: play_whumpus_hunt()                             *
* Date Created: 6/01/2020                                   *
* Date Last Modified: 6/02/2020                             *
* Description: Drives the game of Whumpus Hunt              *
* Input parameters: Void                                    *
* Returns: Void                                             *
* Preconditions: N\A                                        *
* Postconditions: N\A                                       *
*************************************************************/
void play_whumpus_hunt(void);
#endif // WHUMPUSHUNT_H
