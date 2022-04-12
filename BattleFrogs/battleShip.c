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


			



*/

#include "battleShip.h"



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
int menu_loop(void)
{

	int isGameActive = 0, menuOption = 0;
	while (isGameActive == 0)
	{
		menuOption = display_menu_options();
		switch (menuOption)
		{
			//Handle exiting of game on escape, 0, and clicking x in upper right corner of window
		case 0:
			printf("Goodbye!\n");
			isGameActive = 1;
			break;
			//Displays game rules when user inputs 1
		case 1:
			display_game_rules();
			//print game rules function
			isGameActive = 0;
			break;

			//Starts Game Loop when user inputs 2
		case 2:
			isGameActive = 0;
			play_battleship();
			break;
		}

	}
	return isGameActive;
}

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
int display_menu_options(void)
{
	//frog menu display
	int option = 0, c = 0;
	do
	{
		printf("          ____________________________________________________________________\n");
		printf("         /                        Welcome To BattleFrogs!                     \\ \n");
		printf("        /                         0 = Quit Game                                \\ \n");
		printf("       /                          1 = View Game Rules                           \\ \n");
		printf("       \\                         2 = Play Battle Frogs!                         /\n");
		printf("        \\  ____________________________________________________________________/\n");
		printf("         \\/ \n");
		printf("          ~  ~\n");//Spent more time on this frog than I'd like to admit. 
		printf("          @..@\n");//Worth it.
		printf("         (-----)\n");//inb4 'What frog?'
		printf("        { )_J_( }\n");
		printf("      <^>|>   <|<^>\n");
		printf(" -------------------------\n");//It's a log, I promise.
		printf("(      BattleFrogs!       )\n");
		printf(" -------------------------\n");
		scanf("%d", &option);
	} while ((c = getchar()) != '\n' && option >= 0 && option < 3);
	return option;
}

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
void display_game_rules(void)
{
	//REPLACE WITH BATTLESHIP GAME RULES
	printf("************************************************************************************************************************************************************************************************************************\n");
	printf("* This is the Game of BattleFrogs. To win, you must sink all of the Computers ships. If the Computer sinks all of your ships, you lose. You begin by selecting to place your ships manually or at random.              *\n");
	printf("* Ships are placed in order from largest to smallest: Carrier, Battleship, Crusier, Submarine, and Destroyer. You will be asked for the direction to place your ship, and the position for the front of the ship.      *\n");
	printf("* Ships placed vertically will occupy the spaces BELOW the initial point based on ship length. Ships placed horizontally will occupy the spaces to the RIGHT of the initial point based on ship length.                *\n");
	printf("* Statistics are recorded and placed into a log file at the end of the match, along with each move made during the game.                                                                                               *\n");
	printf("************************************************************************************************************************************************************************************************************************\n");
}

void play_battleship(void)
{
	int playerTurn = -1, placementOption = -1, dir = -1, isVictory = -1, playerHit = -1, turns = 0, round = 0, row = -1, col = -1, index = 0, c = 0;;
	char player1Board[BOARD_SIZE][BOARD_SIZE], player2Board[BOARD_SIZE][BOARD_SIZE];
	Ships battleShips1[5], battleShips2[5];
	Stats playerStats[2];
	char* shipNames[5] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" }, * playerNames[2] = {"Player 1", "Computer"};
	int shipLengths[5] = { 5, 4, 3, 3, 2 };
	int* row_ptr = -1, * col_ptr = -1;
	FILE* battleLog = NULL;
	char* string = "\0";

	battleLog = fopen("battleship.log", "w");

	//initilize user board
	init_board(player1Board, ROWS, COLUMNS);
	//initilize computer board
	init_board(player2Board, ROWS, COLUMNS);
	//initilize player 1 ship struct
	init_ship_struct(battleShips1, shipNames, shipLengths);
	//init player 2 ship struct
	init_ship_struct(battleShips2, shipNames, shipLengths);
	//init player 1 stat struct
	init_stat_struct(playerStats, playerNames);
	//'randomly' select first player
	playerTurn = select_random_player();
	//ask user if they want to place ships or have them placed at random
	placementOption = get_random_or_manual();
	switch (placementOption)
	{
	case 0:
		manually_assign_ships_on_board(player1Board, battleShips1, row_ptr, col_ptr);
		randomly_assign_ships_on_board(player2Board, battleShips2, row_ptr, col_ptr, 1);
		
		break;
	case 1:
		randomly_assign_ships_on_board(player1Board, battleShips1, row_ptr, col_ptr, 0);
		randomly_assign_ships_on_board(player2Board, battleShips2, row_ptr, col_ptr, 1);
		
		break;
	}

	

	do
	{
		if (round % 2 == 0)
		{
			clear_screen();
		}
		turns += 1;
		round = turns / 2;
		//display user board
		if (playerTurn == 0)
		{
			print_board(player2Board, ROWS, COLUMNS, playerTurn+1);
			do
			{
				printf("Target, Captain?!\n");
				printf("Enter Target as: Row Column\n");
				scanf("%d %d", &row, &col);

			} while ((c = getchar()) != '\n' && player2Board[row][col] == '*' || player2Board[row][col] == 'm');

			playerHit = check_shot(player2Board, battleShips2, playerStats, playerTurn, row, col);
			fprintf(battleLog, "%s: %d,%d %s\n", playerStats[playerTurn].playerName, playerStats[playerTurn].target[0],
				playerStats[playerTurn].target[1], playerStats[playerTurn].shipSunk);
			press_key_to_continue();
			if (playerStats[1].shipsRemain < 1)
			{
				isVictory = 0;
				fprintf(battleLog, "%s Wins, %s Loses\n", playerStats[0].playerName, playerStats[1].playerName);
			}
			playerTurn = 1;
		}
		else if (playerTurn == 1)
		{
			
			do
			{
				row = rand() % 10;
				col = rand() % 10;

			} while (player1Board[row][col] == '*' || player1Board[row][col] == 'm');

			playerHit = check_shot(player1Board, battleShips1, playerStats, playerTurn, row, col);
			print_board(player1Board, ROWS, COLUMNS, playerTurn - 1);

			if (playerStats[playerTurn].shipSunk != "\0")
			{
				string = "Sunk!";
			}
			else
			{
				string = "\0";
			}

			fprintf(battleLog, "%s: %d,%d %s %s\n", playerStats[playerTurn].playerName, playerStats[playerTurn].target[0],
				playerStats[playerTurn].target[1], playerStats[playerTurn].shipSunk, *string);
			if (playerStats[0].shipsRemain < 1)
			{
				isVictory = 1;
				fprintf(battleLog, "%s Wins, %s Loses\n", playerStats[1].playerName, playerStats[0].playerName);

			}
			playerTurn = 0;
		}

		

	} while (round < 10);

	for (index = 0; index < 2; index++)
	{
		
		playerStats[index].hitPercent = ((double)playerStats[index].hits) / playerStats[index].misses;
		fprintf(battleLog, "\n***%s Stats***\nNumber Hits: %d\nNumber Misses: %d\nTotal Shots: %d\nHit/Miss Ratio: %lf\n", playerStats[index].playerName, playerStats[index].hits,
			playerStats[index].misses, playerStats[index].shots, playerStats[index].hitPercent);
	}

	
	display_winner(isVictory);
	press_key_to_continue();
	fclose(battleLog);
	clear_screen();
	
	
}

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
	int num_cols)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols;
			++col_index)
		{
			board[row_index][col_index] = '~';
		}
	}
}

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
	int num_cols, int playerTurn)
{
	int row_index = 0, col_index = 0;

	//display current scores
	printf("    ****************                  \n");
	printf("    *Player %d Board*                  \n", playerTurn+1);
	printf("    ****************                  \n");

	printf("  0 1 2 3 4 5 6 7 8 9\n"); //adjusted spacing to match column index with column elements when dipalyed
	switch (playerTurn)
	{
	case 0:
		for (; row_index < num_rows; ++row_index)
		{
			printf("%d ", row_index);
			for (col_index = 0; col_index < num_cols;
				++col_index)
			{
				printf("%c ", board[row_index][col_index]);
			}

			putchar('\n');
		}
		break;
	case 1:
		for (; row_index < num_rows; ++row_index)
		{
			printf("%d ", row_index);
			for (col_index = 0; col_index < num_cols;
				++col_index)
			{
				if (board[row_index][col_index] == '*')
				{
					printf("%c ", board[row_index][col_index]);
				}
				else if (board[row_index][col_index] == 'm')
				{
					printf("%c ", board[row_index][col_index]);
				}
				else
				{
					printf("- ");
				}
				
			}

			putchar('\n');
		}
		break;
	}
}

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
int select_random_player(void)
{
	return (rand() % 2);
}

/************************************************************
* Function: manually_assign_ships_on_board ()               *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  prompts user for starting location          *
*               and direction for ship to be placed         *
* Input parameters:			                                *
* Returns: integer 0: user(player1) 1:computer(player2)     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void manually_assign_ships_on_board(char playerBoard[][BOARD_SIZE], Ships battleShips[],
	int* row_ptr, int* col_ptr)
{
	int option = -1, c = 0;
	int index = 0, row = -1, col = -1;
	char shipToken = '\0';
	int playerTurn = 0;
	printf("Ships in battleFrogs are placed in the Following Order:\n");
	printf("1-Carrier\t2-Battleship\t3-Submarine\n4-Crusier\t5-Destroyer");
	printf("Ships in BattleFrogs are placed based on their orientation (Horizontal/Verticle), and starting position (Row, Column)\n");
	printf("Ships oriented vertically will have their front placed at the starting position and the rear below it based on ship length.\n");
	printf("Ships oriented horizontally will have their front placed at the starting postion and the rear to the right based on ship length of starting position.\n");
	for (index = 0; index < 5; index++)
	{

		shipToken = get_ship_token(index);
		do
		{
			clear_screen();
			print_board(playerBoard, ROWS, COLUMNS, playerTurn);
			printf("Now Placing: %s\n", battleShips[index].shipName);
			printf("Which direction will the ship be placed?\n");
			printf("0 = Verticle\t1 = Horizontal\n");
			scanf("%d", &option);

		} while ((c = getchar()) != '\n' && option != 0 && option != 1);

		switch (option)
		{
		case 0:
			do
			{
				clear_screen();
				printf("NOTE: If the coordinates you choose make the ship fall outside the bounds of the board\n");
			    printf("or overlaps with another ship, you will be promtped for new coordinates.\n");
				printf("Enter start coordinates as an ordered pair, (Row, Column), of integers, 0-9.\n");
				print_board(playerBoard, ROWS, COLUMNS, playerTurn);
				do
				{
					scanf("%d %d", &row, &col);
				} while ((c = getchar() != '\n'));

			
				     //Checking if within boundary//               //Checking if 1st space is open//    //Check if last space open//              
			} while ((row - battleShips[index].shipLength) > 0 || playerBoard[row][col] != '~' || playerBoard[row + (battleShips[index].shipLength - 1)][col] != '~' 
						|| playerBoard[row + (battleShips[index].shipLength / 2)][col] != '~' || playerBoard[row + (battleShips[index].shipLength / 2 + (battleShips[index].shipLength % 2))][col] != '~'
				        || (playerBoard[row + 1][col]) != '~');
			int index2 = 0;
			for (index2 = 0; index2 < battleShips[index].shipLength; index2++)
			{
				
				battleShips[index].position[index2][0] = (row + index2);
				battleShips[index].position[index2][1] = col;
				playerBoard[battleShips[index].position[index2][0]][battleShips[index].position[index2][1]] = shipToken;
			}
			break;
		case 1:
			do
			{
				clear_screen();
				printf("NOTE: If the coordinates you choose make the ship fall outside the bounds of the board\n");
				printf("or overlaps with another ship, you will be promtped for new coordinates.\n");
				printf("Enter start coordinates as an ordered pair, (Row, Column), of integers, 0-9.\n");
				print_board(playerBoard, ROWS, COLUMNS, playerTurn);
				scanf("%d %d", &row, &col);
				//Checking if within boundary//               //Checking if 1st space is open//    //Check if last space open//              
			} while ((col - battleShips[index].shipLength) > 0 || playerBoard[row][col] != '~' || playerBoard[row][col + (battleShips[index].shipLength - 1)] != '~'
				|| playerBoard[row][col + (battleShips[index].shipLength / 2)] != '~' || playerBoard[row][col + (battleShips[index].shipLength / 2 + (battleShips[index].shipLength % 2))] != '~'
				|| (playerBoard[row][col + 1]) != '~');
			for (index2 = 0; index2 < battleShips[index].shipLength; index2++)
			{
				battleShips[index].position[index2][0] = row;
				battleShips[index].position[index2][1] = (col + index2);
				playerBoard[battleShips[index].position[index2][0]][battleShips[index].position[index2][1]] = shipToken;
			}

		}
	}
}


/************************************************************
* Function: manually_assign_ships_on_board ()               *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  prompts user for starting location          *
*               and direction for ship to be placed         *
* Input parameters:			                                *
* Returns: integer 0: user(player1) 1:computer(player2)     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int generate_dir(void)
{
	return rand() % 2;
}

/************************************************************
* Function: manually_assign_ships_on_board ()               *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  prompts user for starting location          *
*               and direction for ship to be placed         *
* Input parameters:			                                *
* Returns: integer 0: user(player1) 1:computer(player2)     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/


/************************************************************
* Function: manually_assign_ships_on_board ()               *
* Date Created: 3/27/2020                                   *
* Date Last Modified: 3/27/2020                             *
* Description:  prompts user for starting location          *
*               and direction for ship to be placed         *
* Input parameters:			                                *
* Returns: integer 0: user(player1) 1:computer(player2)     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void generate_start_pt(int dir, int ship_length,
	int* row_ptr, int* col_ptr)
{
	// hor = 0 = dir
	if (dir == 0)
	{
		*row_ptr = rand() % 10;
		*col_ptr = rand() % (10 - ship_length + 1);
	}
	else if (dir == 1)
	{
		*row_ptr = rand() % (10 - ship_length + 1);
		*col_ptr = rand() % 10;
	}
}

int get_random_or_manual(void)
{
	int option = -1, c = 0;
	do
	{
		printf("Do you want to manually place your ships or randomly?\n");
		printf("0: Manually assign ship locations.\t");
		printf("1: Randomly assign ship locations.\n");
		scanf("%d", &option);

	} while ((c = getchar()) != '\n' && option != 0 && option != 1);

	return option;
}

void init_ship_struct(Ships battleShips[], char *shipNames[], int shipLengths[])
{
	int index = 0;
	for (index = 0; index < 5; index++)
	{
		battleShips[index].shipName = shipNames[index];
		battleShips[index].shipLength = shipLengths[index];
		battleShips[index].health = shipLengths[index];
		battleShips[index].position[index][0] = -1;
		battleShips[index].position[index][1] = -1;
		battleShips[index].isAlive = 1;
		

	}
}

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
void clear_screen(void)
{
	//clear the screen
	system("@cls||clear"); //https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c/42500322
}

char get_ship_token(int index)
{
	char shipToken = '\0';
	switch (index)
	{
	case 0:
		shipToken = 'c';
		break;
	case 1:
		shipToken = 'b';
		break;
	case 2:
		shipToken = 'r';
		break;
	case 3:
		shipToken = 's';
		break;
	case 4:
		shipToken = 'd';
		break;
	default:
		shipToken = '-';
	}
	return shipToken;
}

void randomly_assign_ships_on_board(char playerBoard[][BOARD_SIZE], Ships battleShips[],
	int* row_ptr, int* col_ptr, int playerTurn)
{
	int option = -1, c = 0;
	int index = 0, row = -1, col = -1;
	char shipToken = '\0';
	for (index = 0; index < 5; index++)
	{

		shipToken = get_ship_token(index);
		option = generate_dir();

		switch (option)
		{
		case 0:
			do
			{
				
				

				
				
					row = rand() % 10;
					col = rand() % 10;
				


				//Checking if within boundary//               //Checking if 1st space is open//    //Check if last space open//              
			} while ((row - battleShips[index].shipLength) > 0 || playerBoard[row][col] != '~' || playerBoard[row + (battleShips[index].shipLength - 1)][col] != '~'
				|| playerBoard[row + (battleShips[index].shipLength / 2)][col] != '~' || playerBoard[row + (battleShips[index].shipLength / 2 + (battleShips[index].shipLength % 2))][col] != '~'
				|| (playerBoard[row + 1][col]) != '~');
			int index2 = 0;
			for (index2 = 0; index2 < battleShips[index].shipLength; index2++)
			{

				battleShips[index].position[index2][0] = (row + index2);
				battleShips[index].position[index2][1] = col;
				playerBoard[battleShips[index].position[index2][0]][battleShips[index].position[index2][1]] = shipToken;
			}
			break;
		case 1:
			do
			{
		
				
					row = rand() % 10;
					col = rand() % 10;
		

				//Checking if within boundary//               //Checking if 1st space is open//    //Check if last space open//              
			} while ((col - battleShips[index].shipLength) > 0 || playerBoard[row][col] != '~' || playerBoard[row][col + (battleShips[index].shipLength - 1)] != '~'
				|| playerBoard[row][col + (battleShips[index].shipLength / 2)] != '~' || playerBoard[row][col + (battleShips[index].shipLength / 2 + (battleShips[index].shipLength % 2))] != '~'
				|| (playerBoard[row][col + 1]) != '~');
			for (index2 = 0; index2 < battleShips[index].shipLength; index2++)
			{
				battleShips[index].position[index2][0] = row;
				battleShips[index].position[index2][1] = (col + index2);
				playerBoard[battleShips[index].position[index2][0]][battleShips[index].position[index2][1]] = shipToken;
			}

		}
	}
}

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
void press_key_to_continue(void)
{
	char dummyVar = '\0';
	//prompt user to input any character to continue
	printf("Press any key to continue:\n");
	scanf(" %c", &dummyVar);

}

int check_shot(char playerBoard[][BOARD_SIZE], Ships battleShips[], Stats playerStats[], int playerTurn, int row, int col)
{
	int shipHit = -1;
	char *string1 = "\0", *string2 = "\0";
	playerStats[playerTurn].target[0] = row;
	playerStats[playerTurn].target[1] = col;

	playerStats[playerTurn].shots += 1;

	if (playerBoard[row][col] == 'c' || playerBoard[row][col] == 'b' || playerBoard[row][col] == 'd'
		|| playerBoard[row][col] == 's' || playerBoard[row][col] == 'r')
	{
		
		playerStats[playerTurn].hits += 1;
		playerStats[playerTurn].hitMiss = "'Hit!'";
		

		if (playerBoard[row][col] == 'c')
		{
			shipHit = 0;
			

		}
		else if (playerBoard[row][col] == 'b')
		{
			shipHit = 1;
			
		}
		else if (playerBoard[row][col] == 'r')
		{
			shipHit = 2;
			
		}
		else if (playerBoard[row][col] == 's')
		{
			shipHit = 3;
			
		}
		else if (playerBoard[row][col] == 'd')
		{
			shipHit = 4;
			
		}
		playerBoard[row][col] = '*';

		battleShips[shipHit].health = battleShips[shipHit].health - 1;
		if (battleShips[shipHit].health == 0)
		{
			battleShips[shipHit].isAlive = 0;
		}

		if (battleShips[shipHit].isAlive == 0)
		{
			
			
			playerStats[playerTurn].shipsRemain = playerStats[playerTurn].shipsRemain - 1;
			playerStats[playerTurn].shipSunk = battleShips[shipHit].shipName;
			

			printf("%s: Sunk %s\n", playerStats[playerTurn].playerName , playerStats[playerTurn].shipSunk);
			battleShips[shipHit].isAlive = -1;
		}

	}
	else
	{
		playerBoard[row][col] = 'm';
		playerStats[playerTurn].misses += 1;
		playerStats[playerTurn].hitMiss = "'Miss!'";
		playerStats[playerTurn].shipSunk = "\0";
	}
	printf("%s: %s\n", playerStats[playerTurn].playerName, playerStats[playerTurn].hitMiss);
	return shipHit;
}

void init_stat_struct(Stats playerStats[], char* playerNames[])
{
	int index = 0;
	for (index = 0; index < 2; index++)
	{
		playerStats[index].shots = 0;
		playerStats[index].hits = 0;
		playerStats[index].misses = 0;
		playerStats[index].playerName = playerNames[index];
		playerStats[index].shipsRemain = 5;
		playerStats[index].hitPercent = 0.0;
		playerStats[index].shipSunk = "\0";
		playerStats[index].hitMiss = "\0";
		playerStats[index].target[0] = -1;
		playerStats[index].target[1] = -1;

	}
}

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
void display_winner(int isVictory)
{
	//display game winner
	
	if (isVictory == 1)
	{
		printf("**********************************************************************\n");
		printf("*         111111 1          1   1   1  1111 111111      1            *\n");
		printf("*         1    1 1         1 1   1 1   1    1    1     11            *\n");
		printf("*         111111 1        1   1   1    111  111111    1 1            *\n");
		printf("*         1      1       1  1  1  1    1    1    1      1            *\n");
		printf("*         1      1 1 1  1       1 1    1111 1     1     1            *\n");
		printf("*                                                    1111111         *\n");

	}
	else if (isVictory == 0)
	{
		printf("**********************************************************************\n");
		printf("*         222222 2          2   2   2  2222 222222    22222222       *\n");
		printf("*         2    2 2         2 2   2 2   2    2    2           2       *\n");
		printf("*         222222 2        2   2   2    222  222222    22222222       *\n");
		printf("*         2      2       2 222 2  2    2    2    2    2              *\n");
		printf("*         2      2 2 2  2       2 2    2222 2     2   22222222       *\n");
		printf("*                                                                    *\n");

	}
	else
	{
		printf("NOBODY-YOU PROBABLY QUIT");
	}

	printf("*       \\        / \\        /   ||  |\\    |    |||||||               *\n");
	printf("*        \\      /   \\      /    ||  | \\   |    |                     *\n");
	printf("*         \\    /     \\    /     ||  |  \\  |    |||||||               *\n");
	printf("*          \\  /       \\  /      ||  |   \\ |          |               *\n");
	printf("*           \\/         \\/       ||  |    \\|    |||||||               *\n");
	printf("**********************************************************************\n");
}