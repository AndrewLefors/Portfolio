/*

Created By: Andrew Lefors
Created On: 3/27/2020
Project: BattleFrogs (BattleShip)
File Version: 0.3.27.20

Description: This is the Game of BattleFrogs. To win, you must sink all of the Computers ships. If the Computer sinks all of your ships, you lose. You begin by selecting to place your ships manually or at random.
			 Ships are placed in order from largest to smallest: Carrier, Battleship, Crusier, Submarine, and Destroyer. You will be asked for the direction to place your ship, and the position for the front of the ship.
			 Ships placed vertically will occupy the spaces BELOW the initial point based on ship length. Ships placed horizontally will occupy the spaces to the RIGHT of the initial point based on ship length.
			 Statistics are recorded and placed into a log file 'battleship.log' at the end of the match, along with each move made during the game.


			NOTE: clear screen function: Learned how to do this from StackOverflow: https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c/42500322



*/

#ifndef PA6_BATTLESHIP_H
#define PA6_BATTLESHIP_H
#define _CRT_SECURE_NO_WARNINGS // necessary to ignore scanf_s () warnings (Must come first)
#define BOARD_SIZE 10
#define ROWS 10
#define COLUMNS 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct ships
{
	char* shipName;
	int shipLength;
	int position[5][2];
	int health;
	int isAlive;


}Ships;

typedef struct stats
{
	char *playerName;
	int shipsRemain;
	int target[2];
	char* shipSunk;
	int shots;
	int hits;
	int misses;
	double hitPercent;
	char *hitMiss;

}Stats;

/************************************************************
* Function: menu_loop ()                                    *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  loop through menu and prompt user for input.*
*			    if 0 quit, 1 display rules, 2 play game     *
* Input parameters:                                         *
* Returns: isGameActive                                     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int menu_loop(void);

/************************************************************
* Function: display_menu_options ()                         *
* Date Created: 3/15/2020                                   *
* Date Last Modified: 3/15/2020                             *
* Description:  print menu options to screen                *
* Input parameters:                                         *
* Returns: integer, 0: quit, 1:view rules, 2: play          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int display_menu_options(void);

/************************************************************
* Function: display_game_rules ()                           *
* Date Created: 3/15/2020                                   *
* Date Last Modified: 3/15/2020                             *
* Description:  print game rules to screen                  *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void display_game_rules(void);

/************************************************************
* Function: play_battleship ()                              *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  Run game battleship                         *
* Input parameters:                                         *
* Returns: integer isGameActive                             *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void play_battleship(void);

/************************************************************
* Function: init_board ()                                   *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  initilize empty game board of N x M size    *
* Input parameters: int number of rows, columns             *
* Returns:                                                  *
* Preconditions: num_rows & num_cols must be <= BOARD_SIZE  *
* Postconditions: Board array populated with '~'            *
*************************************************************/
void init_board(char board[][BOARD_SIZE], int num_rows,
	int num_cols);

/************************************************************
* Function: print_board ()                                  *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  displays game board on screen               *
* Input parameters: int number rows, columns                *
* Returns:                                                  *
* Preconditions: board is initilized                        *
* Postconditions:                                           *
*************************************************************/
void print_board(char board[][10], int num_rows,
	int num_cols);

/************************************************************
* Function: select_random_player ()                         *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  randomly generates int 0 or 1               *
* Input parameters:			                                *
* Returns: integer 0: user(player1) 1:computer(player2)     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int select_random_player(void);


/************************************************************
* Function: manually_assign_ships_on_board ()               *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  randomly generates int 0 or 1               *
* Input parameters:			                                *
* Returns: integer 0: user(player1) 1:computer(player2)     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void manually_assign_ships_on_board(char playerBoard[][BOARD_SIZE], Ships battleShips[],
	int* row_ptr, int* col_ptr);

/************************************************************
* Function: clear_screen ()                                 *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  clears the screen of all output             *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void clear_screen(void);

int get_random_or_manual();

void init_ship_struct(Ships battleShips[]);

char get_ship_token(int index);

void randomly_assign_ships_on_board(char playerBoard[][BOARD_SIZE], Ships battleShips[],
	int* row_ptr, int* col_ptr, int playerTurn);


/************************************************************
* Function: press_key_to_contine ()                         *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Enter any key to continue progressing       *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void press_key_to_continue(void);

void init_stat_struct(Stats playerStats[], char* playerNames[]);

int check_shot(char playerBoard[][BOARD_SIZE], Ships battleShips[], Stats playerStats[], int playerTurn, int row, int col);

/************************************************************
* Function: display_winner ()                               *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  display to screen  who won                  *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void display_winner(int isVictory);

#endif
