/*

Created By: Andrew Lefors
Created On: 2/24/2020
Project: Game of Chance - Craps
File Version: 0.2.30.20

Description: This is the game of Craps, where the user will be prompted for a bank balance from which wagers can be made.
				The user will place bets and roll the die, being mocked along the way by an ugly toad. No files are saved.




*/
#include "GOCraps.h"

/************************************************************
* Function: start_game ()                                   *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: Starts game by presenting Menu               *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void start_game(void)
{
	//initialize variables 
	int menuOption = 1, isGameActive = 1;
	//List of menu functions to be placed into menu function
	do
	{
			menuOption = frog_menu();
			isGameActive = play_crappy_craps(menuOption);
			
	} while (isGameActive == 1);

	return 0;
}


/************************************************************
* Function: play_crappy_craps ()                            *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: Shows rules, initiates game, or quits
				based on user input 0 quit 1 print rules
				2 play game                                 *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int play_crappy_craps(int menuOption)
{
	
	int isGameActive = 1;
	//Select to quit, view game rules, or play the game
	switch (menuOption)
	{
	default:
		printf("Input not recongized, please try again.\n");
		isGameActive = 1;
		return isGameActive;
		break;
	case 0:
		isGameActive = 0;
		return isGameActive;
		break;

	case 1:
		isGameActive = 1;
		print_game_rules();
		return isGameActive;
		break;

	case 2:
		isGameActive = game_loop();
		break;


	}
	return isGameActive;
}


/************************************************************
* Function: game_loop ()                                    *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: Loops through the game of Craps              *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int game_loop(void)
{

	int isValidBalance = 0, isValidWager = 0, cheatAttempt = 0, die1 = 0, die2 = 0, sumDie = 0, rollCount = 0, isGameActive = 0, winLossPoint = 0,
		pointValue = 0, addOrSub = 0, keepPlaying = 0, isValidOption = 0, returnMenu = 0, c = 0;
	double initialBankBalance = 0.0, bankBalance = 0.0, wagerAmount = 0.0;

	int* pointValuePtr = NULL;
	double* bankBalancePtr = NULL;

	char dummyVar = '\0';
	//validate bankBalance is > 0 and loop back if not
	do
	{
		isGameActive = 1;
		//Get initial bank value from user
		initialBankBalance = get_bank_balance();
		isValidBalance = is_valid_balance(initialBankBalance);


		//Set bankBalance from first value, return to make leaderboard scores later 
		//Use initial - current for chatter function
		if (isValidBalance != 0)
			printf("An invalid amount has been entered, please Try again:\n"); //replace with chatter function
		else
			bankBalance = initialBankBalance;

	} while (isValidBalance == 1);



	//Roll dice first time

	do
	{
		do
		{
			//Get wager amount from user
			//Validate wager is < bank balance 
			//Loop until wager < bankBalance
			//Check for negative input, apply penalty for repeated exploitation attempts
			wagerAmount = get_wager_amount(bankBalance);
			isValidWager = check_wager_amount(wagerAmount, bankBalance);
			cheatAttempt = valid_or_not(isValidWager, wagerAmount, &bankBalance, cheatAttempt);

		} while (isValidWager != 1);
		//Roll dice and determine if win loss or point value
		winLossPoint = dice_rolls(rollCount, &pointValue, &initialBankBalance, bankBalance);
		rollCount++;
		//Evaluate winLossPoint
		if (winLossPoint == 1 || winLossPoint == 0)
		{
			bankBalance = adjust_bank_balance(bankBalance, wagerAmount, winLossPoint);
			rollCount = 0;
		}
		//Keep rolling
		else if (winLossPoint == -1)
		{

			do
			{
				winLossPoint = dice_rolls(rollCount, &pointValue, &initialBankBalance, bankBalance);

				switch (winLossPoint)
				{
				case 0:
					printf("You Lose!!\n");
					bankBalance = adjust_bank_balance(bankBalance, wagerAmount, winLossPoint);
					rollCount = 0;
					break;
				case 1:
					printf("You made your point!\n");
					bankBalance = adjust_bank_balance(bankBalance, wagerAmount, winLossPoint);
					rollCount = 0;
					break;
				case -1:
					rollCount++;
					break;
				}

			} while (winLossPoint == -1);
		}

		//Check to see if user wants to play again if yes but balance <= 0, return to main menu
		keepPlaying = is_game_active(bankBalance);





	} while (keepPlaying != 0);


	do
	{
		printf("Return to Menu?\n0 = No\t1 = Yes\n");
		scanf("%d", &isGameActive);

	} while ((c = getchar()) != '\n' || isGameActive < 0 || isGameActive > 1);

	return isGameActive;
}

/************************************************************
* Function: print_game_rules ()                             *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: Prints out the rules of the game of "craps". *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void print_game_rules(void)
{
	printf("**************************************************************************************************\n");
	printf("*                          The rules of the game are straightforward:                            *\n*\n");
	printf("*                       A player rolls two dice. Each die has six faces.                         *\n*\n");
	printf("*                        These faces contain 1, 2, 3, 4, 5, and 6 spots.                         *\n*\n");
	printf("*  After the dice have come to rest, the sum of the spots on the two upward faces is calculated. *\n*\n");
	printf("*             If the sum is 7 or 11 on the first throw, the player (That's YOU!) wins.           *\n*\n");
	printf("*       If the sum is 2, 3, or 12 on the first throw (called 'craps'), the player loses.         *\n*\n");
	printf("*If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's 'point'*\n*\n");
	printf("*             To win, you must continue rolling the dice until you 'make your point.'            *\n*\n");
	printf("*                       You lose by rolling a 7 before making the point.                         *\n");
	printf("*                                                                                                *\n");
	printf("**************************************************************************************************\n");
}


/************************************************************
* Function: get_bank_balance ()                             *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Prompts the player for an initial bank      *
*               balance from which wagering will be added   *
*				or subtracted. The player entered bank      *
*				balance (in dollars, i.e. $100.00) is       *
*				returned.                                   *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
double get_bank_balance(void)
{
	double bankBalance = 0.0;
	int c = 0;
	do {

		
		printf("          ____________________________________________________________________\n");
		printf("         /                                                                    \\ \n");
		printf("        / Howdy, Partner! How much are you looking to Lose to this Toad Today? \\ \n");
		printf("       / ______________________________________________________________________/\n");
		printf("       |/ \n");
		printf("          ~  ~\n");//Spent more time on this frog than I'd like to admit. 
		printf("          @..@\n");//Worth it.
		printf("         (-----)\n");//inb4 'What frog?'
		printf("        { )_J_( }\n");
		printf("      <^>|>   <|<^>\n");
		printf(" -------------------------\n");//It's a log, I promise.
		printf("(      CrappyCraps        )\n");
		printf(" -------------------------\n");
		scanf("%lf", &bankBalance);

		//if ((c = SDLK_RETURN != 0));
		//printf("Input not recognized\n");

	} while ((c = getchar()) != '\n'); //To prevent infinite loop if user enters value like '\' 

	return bankBalance;
}

/************************************************************
* Function: get_bank_balance ()                             *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Validates bankBalance is > 0                *
* Input parameters:                                         *
* Returns:    0 if True, 1 if False                         *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int is_valid_balance(double bankBalance)
{
	if (bankBalance > 0)
		return 0;
	else
		return 1;
}


/************************************************************
* Function: get_wager_amount ()                             *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: Prompts the player for a wager on a          *
*              particular roll. The wager is returned.      *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
double get_wager_amount(double bankBalance)
{
	double wagerAmount = 0.0;
	int c = 0;
	do
	{
		printf("          ____________________________________________________________________\n");
		printf("         /                                                                    \\ \n");
		printf("        / You're up, Slick! How many Buck-A-Rooos are you putting on the Line? \\ \n");
		printf("       / ______________________________________________________________________/\n");
		printf("       |/ \n");
		printf("          ~  ~\n");//Spent more time on this frog than I'd like to admit. 
		printf("          @..@\n");//Worth it.
		printf("         (-----)\n");//inb4 'What frog?'
		printf("        { )_J_( }\n");
		printf("      <^>|>   <|<^>\n");
		printf(" ----------------------------\n");
		printf("( Remaining Balance: %.1lf)  \n", bankBalance);
		printf(" ----------------------------\n");
		scanf("%lf", &wagerAmount);
	} while ((c = getchar() != '\n'));
	return wagerAmount;
}


/************************************************************
* Function: check_wager_amount ()                           *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Checks to see if the wager is within the    *
*               limits of the player's available balance.   *
*				If the wager exceeds the player's allowable *
*				balance, then 0 is returned; otherwise 1    *
*				is returned. -1 returned if value < 0       *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int check_wager_amount(double wager, double balance)
{
	if (wager > balance)
		return 0;
	else if (wager <= 0)
		return -1;
	else
		return 1;


}


/************************************************************
* Function: roll_die ()                                     *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Rolls one die. This function randomly       *
*               generates a value between 1 and 6,          *
*				inclusively. Returns the value of the die.  *
* Input parameters:                                         *
* Returns: Value of die                                     *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int roll_die(void)
{
	int dieRoll = 0;
	
	dieRoll = (rand() % 6 + 1);
	return dieRoll;
}


/************************************************************
* Function: press_enter_to_continue ()                      *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Prompt user to press enter before continuing*
* Input parameters:     NONE                                *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void press_enter_to_continue(void)
{
	int c = 0, dummyVar = 0;
	do
	{
		printf("Press Enter to roll:\n");
		scanf("%c", &dummyVar);

	} while ((c = SDLK_RETURN) == 1);
}

/************************************************************
* Function: calculate_sum_dice ()                           *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Sums together the values of the two dice    *
*               and returns the result. Note: this result   *
*				may become the player's point in future     *
*				rolls.                                      *
* Input parameters: Two (2) die values                      *
* Returns: Sum of two die rolls                             *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int calculate_sum_dice(int die1_value, int die2_value)
{
	int sumDice = 0;
	sumDice = die1_value + die2_value;
	return sumDice;
}


/************************************************************
* Function: is_win_loss_or_point ()                         *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Determines the result of the first dice     *
*               roll. If the sum is 7 or 11 on the roll,    *
*				the player wins and 1 is returned. If the   *
*				sum is 2, 3, or 12 on the first throw       *
*				(called "craps"), the player loses          *
*				(i.e. the "house" wins) and 0 is returned.  *
*				If the sum is 4, 5, 6, 8, 9, or 10 on the   *
*				first throw, then the sum becomes the       *
*				player's "point" and -1 is returned.        *
* Input parameters: sum of die rolls                        *
* Returns: 1 if player wins, 0 if house wins, -1 if neutral *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int is_win_loss_or_point(int sum_dice)
{
	if (sum_dice == 7 || sum_dice == 11)
		return 1;
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
		return 0;
	else
		return -1;
}


/************************************************************
* Function: is_point_loss_or_neither ()                     *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Determines the result of any successive     *
*               roll after the first roll. If the sum of    *
*				the roll is the point_value, then 1 is      *
*				returned. If the sum of the roll is a 7,    *
*				then 0 is returned. Otherwise, -1 is        *
*				returned.                                   *
* Input parameters: sum of die rolls and point value        *
* Returns: 1 if player wins, 0 if house wins, -1 if neutral *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int is_point_loss_or_neither(int sum_dice, int *pointValuePtr)
{
	if (sum_dice == pointValuePtr)
		return 1;
	else if (sum_dice == 7)
		return 0;
	else
		return -1;
}


/************************************************************
* Function: adjust_bank_balance ()                          *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:   If add_or_subtract is 1, then the wager    *
*                amount is added to the bank_balance. If    *
*				 add_or_subtract is 0, then the wager       *
*				 amount is subtracted from the bank_balance.*
*				 Otherwise, the bank_balance remains the    *
*				 same. The bank_balance result is returned. *
* Input parameters: bank balance, wager amount, int         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	double adjustedBankBalance = 0.0;
	switch (add_or_subtract)
	{

	case 0:
		adjustedBankBalance = bank_balance - wager_amount;
		break;

	case 1:
		adjustedBankBalance = bank_balance + wager_amount;
		break;

	default:
		printf("Did not recognize input as valid option\n");
		break;
	}
	return adjustedBankBalance;
}


/************************************************************
* Function: chatter_messages ()                             *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Prints an appropriate message dependent on  *
*               the number of rolls taken so far by the     *
*				player, the current balance, and whether    *
*				or not the player just won his roll. The    *
*				parameter win_loss_neither indicates the    *
*				result of the previous roll.                *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void chatter_messages(int winLossPoint, int rollCount, double *initialBankBalancePtr, double currentBankBalance)
{
	if (rollCount > 6)
		printf("I'm tired of you.\n");
	else
	{
		switch (rollCount)
		{
		case 0:
			printf("Rattle Them Bones!\n");
			break;
		case 1:
			printf("You're sure to get it this time!\n");
			break;
		case 2:
			printf("I wasn't actually cheering for you, in case you were wondering\n");
			break;
		case 3:
			printf("Any day now...\n");
			break;
		case 4:
			printf("They will carve on your tomb most indecisive rolls\n");
			break;
		case 5:
			printf("I had an ASCII art frog for this, but things happened and I don't want to talk about it.\n");
			break;
		case 6:
			printf("RIDICULOUS!\n");
			break;
		}

	if (*initialBankBalancePtr > (2 * currentBankBalance))
		printf("Ooooh, son. Your Momma would not be proud. Losing all that Nectar\n");
	else if (currentBankBalance > (2 * *initialBankBalancePtr))
		printf("Drinks on you with all that extra Nectar lying around!\n");
	else
	{
		switch (rollCount)
		{
		case 0:
			if (winLossPoint == 0)
				printf("Let's designate this as the place everything started to go horrbily wrong.\n");
			else if (winLossPoint == 1)
				printf("Let's not have you make a habit of this, okay?\n");
			break;
		case 1:
			if (winLossPoint == 0)
				printf("Well fought, Good Frog, but this Toad prevails today!\n");
			else if (winLossPoint == 1)
				printf("Everybody needs a freebie to boost their confidence\n");
			break;
		case 2:
			if (winLossPoint == 0)
				printf("Ha. Hahahaha. MMhmmm, Yes, well Played, indeed.\n");
			else if (winLossPoint == 1)
				printf("This war of attrition has me hemoraghing sweet nectar\n");
			break;
		case 3:
			if (winLossPoint == 0)
				printf("I never had a doubt.\n");
			else if (winLossPoint == 1)
				printf("SURRENDER YOUR SECRETS!\n");
			break;
		}
	}
	
	}
}


/************************************************************
* Function: frog_menu ()                                    *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Displays game menu with ASCII frog          *
* Returns: option 0, 1 or 2                                 *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int frog_menu(void)
{
		int option = 0, c = 0;
		do
		{
			printf("          ____________________________________________________________________\n");
			printf("         /                        Welcome To CrappyCraps!                     \\ \n");
			printf("        /                         0 = Quit Game                                \\ \n");
			printf("       /                          1 = View Game Rules                           \\ \n");
			printf("       \\                          2 = Play Crappy Craps!                        /\n");
			printf("        \\  ____________________________________________________________________/\n");
			printf("         \\/ \n");
			printf("          ~  ~\n");//Spent more time on this frog than I'd like to admit. 
			printf("          @..@\n");//Worth it.
			printf("         (-----)\n");//inb4 'What frog?'
			printf("        { )_J_( }\n");
			printf("      <^>|>   <|<^>\n");
			printf(" -------------------------\n");//It's a log, I promise.
			printf("(      CrappyCraps        )\n");
			printf(" -------------------------\n");
			scanf("%d", &option);
		} while ((c = getchar()) != '\n');

		return option;

}



/************************************************************
* Function: dice_rolls ()                                   *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: wraps roll_dice (), sum_dice () and
			   win_loss_point/neither () and
			   enter_to_continue()                          *
* Returns:         WinLossPoint                             *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int dice_rolls(double rollCount, int *pointValuePtr, double *initialBankBalance, double currentBankBalance)
{
	int c = 0, die1 = 0, die2 = 0, sumDie = 0, winLossPoint = 0;
	char dummyVar = '\0';
	//Make user press enter to roll die
	press_enter_to_continue();

	die1 = roll_die();
	printf("Die 1: %d\n", die1);
	die2 = roll_die();
	printf("Die 2: %d\n", die2);
	sumDie = calculate_sum_dice(die1, die2);
	printf("Sum of Dice: %d\n", sumDie);
	

	//If first roll 
	if (rollCount == 0)
	{
		winLossPoint = is_win_loss_or_point(sumDie);
		*pointValuePtr = sumDie;
		chatter_messages(winLossPoint, rollCount, initialBankBalance, currentBankBalance);
		printf("PointValue: %d\n", *pointValuePtr);
	}
	//Subsequent Rolls
	else
	{
		//Need to get pointers working to use this function
		winLossPoint = is_point_loss_or_neither(sumDie, *pointValuePtr);
		chatter_messages(winLossPoint, rollCount, initialBankBalance, currentBankBalance);
		printf("PointValue: %d\n", *pointValuePtr);
	}

	return winLossPoint;
}

/************************************************************
 Function: valid_or_not ()                                  *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Checks if bet is negative, indicating an
				exploit and verifies bet is valid for bank
				balance. Calls negative_wager               *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

int valid_or_not(int isValidWager, double wagerAmount, double *bankBalancePtr, int cheatAttempt)
{

	switch (isValidWager)
	{
	case 0:
		//put error frog message here 
		printf("Sorry, your wager of %.2lf is more than your Balance of %.2lf\n", wagerAmount, *bankBalancePtr);
		break;
	case 1:
		//need to add visual dice roll that shows values of each die
		printf("Let the Games Begin!\n");

		break;
		//seperate into own function 
	case -1:
		cheatAttempt = cheatAttempt + 1;

		if (cheatAttempt == 1)
		{
			printf("You do know how money works, right?\n");
			return cheatAttempt;
			break;
		}
		else if (cheatAttempt == 2)
		{
			printf("Tryna be slick, eh?!\n Do that again and You'll be fined!\n");
			return cheatAttempt;
			break;
		}
		else if (cheatAttempt > 2)
		{
			//Take penalty and apply as own function with cheat attempt as argument
			//replace with chatter function
			negative_wager(cheatAttempt, bankBalancePtr);
			if (cheatAttempt > 4)
				cheatAttempt = 1;
			return cheatAttempt;
			break;
		}
	default:
		printf("Sorry, could not interpret input: Try Again.\n");
		break;
		
	}

}



/************************************************************
* Function: negative_wager ()                               *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Applies penalty by deducting from bank
				balance										*
* Returns:				                                    *
* Preconditions:                                            *
* Postconditions: bankBalance deducted                      *
*************************************************************/
int negative_wager(int cheatAttempt, double *bankBalancePtr)
	{
		
	
			if (cheatAttempt == 3)
				printf("Mess with the Toad, you get the BullFrog!\n");
			else if (cheatAttempt == 4)
				printf("You really don't learn, do you?\n");
			else
				printf("You're so bright your Momma calls you Sun");
			if (*bankBalancePtr > (penaltyValue * (cheatAttempt - 2)))
			{
				*bankBalancePtr = *bankBalancePtr - (penaltyValue * (cheatAttempt - 2));
			}
			else
				printf("You Bum! Get Offa My Lilly-Pad!\n");
	
		
    }


/************************************************************
* Function: is_game_active ()                               *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: checks if user wants to continue betting,
			   if they go bankrupt, if they want to return
			   to main menu or quit                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int is_game_active(double bankBalance)
{
	int isGameActive = 0, isValidOption = -1;
	do
	{
		if (bankBalance <= 0)
		{
			isGameActive = 2;
		}
		else
		{
			printf("Bet again?\n 0 = No\t1 = Yes\n");
			scanf("%d", &isGameActive);
		}

		switch (isGameActive)
		{

		case 0:
			printf("Goodbye!\n");
			isValidOption = 0;
			isGameActive = 0;
			break;
		case 1:
			printf("Remember, The House ALWAYS Wins!\n");
			isValidOption = 1;
			isGameActive = 1;
			break;

		case 2:
			printf("You're broke! I ToadYa The House ALWAYS Wins!\n");
			isGameActive = 0;
			isValidOption = 2;
			break;

		default:
			printf("Error: could not recognize input. Try Again.\n");
			isValidOption = -1;
			break;


		}


	} while (isValidOption == -1);

	return isGameActive;
}
