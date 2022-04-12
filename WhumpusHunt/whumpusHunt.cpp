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
#include "whumpusHunt.h"


//function definitions
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
void play_whumpus_hunt(void)
{
	//set initial play state
	int isPlaying = 1;
	char playerAction = '\0';
	string playerName;
	//get user name
	cout << "Enter Player Name:\n";
	//set username
	cin >> playerName;

	do
	{

		//get player name for new player
		if (playerAction == 'n' || playerAction == 'N')
		{
			cout << "Enter Player Name:\n";
			cin >> playerName;
		}
		//set up game
		GameWorld g1(playerName);

		int gameStatus = 0;
		int isAlive = 1;
		do
		{
			//clear screen
			system("CLS");
			//show options
			display_menu();
			//only shows player 'U'
			g1.display_player_world();
			//grabs input
			cin >> playerAction;
			//input decisions
			switch (playerAction)
			{
			case 'I':
			case 'i':
				g1.move_up();
				break;
			case 'K':
			case 'k':
				g1.move_down();
				break;
			case 'j':
			case 'J':
				g1.move_left();
				break;
			case 'L':
			case 'l':
				g1.move_right();
				break;
				//restart with same player
			case 'r':
			case 'R':
				gameStatus = 1;
				break;
				//restart with new player
			case 'n':
			case 'N':
				gameStatus = 1;
				break;
				//quit
			case 'q':
			case 'Q':
				gameStatus = 1;
				isPlaying = 0;
				break;
			case 'c':
			case 'C':
				system("CLS");
				g1.display_entire_world();
				break;
			case 'v':
			case 'V':
				g1.display_visible_world();
				system("pause");
				break;
			default:
				cout << "Input not recognized as valid: ";
				system("pause");
				break;

			}
			//checks if user is restarting game
			if (playerAction == 'r' || playerAction == 'R' || playerAction == 'n' || playerAction == 'N')
			{
				cout << "Restarting Game!" << endl;
			}
			//update current game state
			else
			{
				gameStatus = g1.have_I_won();
				isAlive = g1.am_I_alive();
			}
		} while (gameStatus != 1 && isAlive == 1 && playerAction != 'q');
		//display user name
		g1.print_name();
		//display user fate (death by pit/whumpus/found gold)
		g1.print_end_state();
		//calculate and set score
		g1.set_score();
		//display score on screen
		cout << "You earned " << g1.get_score() << " points." <<endl;
		//wait for user to continue
		system("pause");
		//open outfile
		ofstream outfile;
		outfile.open("GameScores.txt");
		//print username and score to outfile using overloaded operator
		outfile << g1;
		outfile.close();

	} while (isPlaying);
}
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
void GameWorld::display_entire_world(void)
{
	
	cout << " ---------------------" << endl;
	for (int index = 0; index < ROW; index++)
	{
		for (int colIndex = 0; colIndex < COL; colIndex++)
		{

			cout << " | " << gameBoard[index][colIndex];
		}
		cout << " |" << endl;
		cout << " ---------------------" << endl;
	}
	fullDisplays += 1;
	system("pause");

}
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
void GameWorld::generate_pit(int numberPit)
{
	//port this function to generate player, gold, and whumpus position. 
	do
	{
		pits[numberPit].row = rand() % 5;
		pits[numberPit].col = rand() % 5;
	} while (gameBoard[pits[numberPit].row][pits[numberPit].col] != ' ');

	gameBoard[pits[numberPit].row][pits[numberPit].col] = 'P';
}
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
int GameWorld::move_up(void)
{
	if (player.row != 0)
	{
		moves += 1;
		gameBoard[player.row][player.col] = ' ';
		player.row -= 1;
		if (gameBoard[player.row][player.col] == 'P' || gameBoard[player.row][player.col] == 'W')
		{
			cout << playerName <<" died!\n";
			return -1;
		}
		gameBoard[player.row][player.col] = 'U';
		return 1;
	}
	else
	{
		cout << "Error: At the top of map\n";
		system("pause");
		return 0;
	}
}
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
int GameWorld::move_down(void)
{
	if (player.row != 4)
	{
		moves += 1;
		gameBoard[player.row][player.col] = ' ';
		player.row += 1;
		if (gameBoard[player.row][player.col] == 'P' || gameBoard[player.row][player.col] == 'W')
		{
			cout << playerName << " died!\n";
			return -1;
		}
		gameBoard[player.row][player.col] = 'U';
		return 1;
	}
	else
	{
		cout << "Error: At the bottom of map\n";
		system("pause");
		return 0;
	}
}
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
int GameWorld::move_left(void)
{
	if (player.col != 0)
	{
		moves += 1;
		gameBoard[player.row][player.col] = ' ';
		player.col -= 1;
		if (gameBoard[player.row][player.col] == 'P' || gameBoard[player.row][player.col] == 'W')
		{
			cout << playerName <<" died!\n";
			return -1;
		}
		gameBoard[player.row][player.col] = 'U';
		return 1;
	}
	else
	{
		cout << "Error: At the Left Side of map\n";
		system("pause");
		return 0;
	}
}
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
int GameWorld::move_right(void)
{
	moves += 1;

	if (player.col != 4)
	{
		moves += 1;
		gameBoard[player.row][player.col] = ' ';
		player.col += 1;
		if (gameBoard[player.row][player.col] == 'P' || gameBoard[player.row][player.col] == 'W')
		{
			cout << playerName <<" died!\n";
			return -1;
		}
		gameBoard[player.row][player.col] = 'U';
		return 1;
	}
	else
	{
		cout << "Error: At the Right Side of map\n";
		system("pause");
		return 0;
	}
}
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
int GameWorld::have_I_won(void)
{
	if (player.row == gold.row && player.col == gold.col)
	{
		endedBy = " found the pot of Gold!\n";
		return 1;
	}
	else
		return 0;
}
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
int GameWorld::am_I_alive(void)
{
	if (gameBoard[player.row][player.col] == 'W')
	{
		endedBy = "was eaten by The Whumpus";
		return 0;
	}
	else if (gameBoard[player.row][player.col] == 'P')
	{
		endedBy = "fell in a Pit";
		return 0;
	}
	else
		return 1;
}
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
void GameWorld::display_player_world(void)
{


	cout << " ---------------------" << endl;
	for (int index = 0; index < ROW; index++)
	{
		for (int colIndex = 0; colIndex < COL; colIndex++)
		{

			cout << " | ";
			if (gameBoard[index][colIndex] == 'U')
			{
				cout << gameBoard[index][colIndex];
			}
			else
			{
				cout << " ";
			}
			
		}
		cout << " |" << endl;
		cout << " ---------------------" << endl;
	}

	

	
}
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
void display_menu(void)
{
	cout << "i: Move Up\t" << "k: Move Down\n" << "j: Move Left\t" << "l: Move Right\n";
	cout << "v: Display Visible World-Shows adjacent caves(-2 pts)\n";
	cout << "c: Display Entire World (-5 pts)\n";
	cout << "r: Restart game as same character\t" << "n: Restart game as new character\n";
	cout << "q: Quit Game\n";
}
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
void GameWorld::print_name(void)
{
	cout << playerName << " ";
}
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
void GameWorld::print_end_state(void)
{
	cout << endedBy << endl;
}
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
void GameWorld::display_visible_world(void)
{
	partialDisplays += 1;

	cout << " ---------------------" << endl;
	for (int index = 0; index < ROW; index++)
	{
		for (int colIndex = 0; colIndex < COL; colIndex++)
		{

			cout << " | ";
			//checks if address of cell is same as address of adjacent cells to player. Displays them when they are.
			if (gameBoard[index][colIndex] == 'U' || &gameBoard[index][colIndex] == &gameBoard[player.row + 1][player.col] || &gameBoard[index][colIndex] == &gameBoard[player.row - 1][player.col]
				|| &gameBoard[index][colIndex] == &gameBoard[player.row][player.col + 1] || &gameBoard[index][colIndex] == &gameBoard[player.row][player.col - 1] || &gameBoard[index][colIndex] == &gameBoard[player.row + 1][player.col + 1]
				|| &gameBoard[index][colIndex] == &gameBoard[player.row + 1][player.col - 1] || &gameBoard[index][colIndex] == &gameBoard[player.row - 1][player.col + 1] || &gameBoard[index][colIndex] == &gameBoard[player.row - 1][player.col - 1])
			{
				cout << gameBoard[index][colIndex];
			}
			else
			{
				cout << " ";
			}

		}
		cout << " |" << endl;
		cout << " ---------------------" << endl;
	}




}
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
void GameWorld::set_score(void)
{
	
	score += (5 * moves);
	score -= (2 * partialDisplays);
	score -= (5 * fullDisplays);
}
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
int GameWorld::get_score(void)
{
	return score;
}
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
ofstream& operator<<(ofstream& outfile, GameWorld& g1)
{
	outfile << g1.playerName  << " earned " << g1.score << " points." << endl;
	return outfile;
}
