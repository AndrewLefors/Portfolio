/*

Created By: Andrew Lefors
Created On: 2/24/2020
Project: Game of Chance - Craps
File Version: 0.2.30.20

Description: This is the game of Craps, where the user will be prompted for a bank balance from which wagers can be made.
				The user will place bets and roll the die, being mocked along the way by an ugly toad. No files are saved.




*/
#define _CRT_SECURE_NO_WARNINGS // necessary to ignore scanf_s () warnings (Must come first)
#pragma once
//import standard libraries
#include <stdio.h> //standard in/out lib
#include <math.h> //math lib for functions sqrt (), ceil (), etc
#include <stdlib.h> //Library for srand() and rand() 
#include <time.h> //
//Constant macros
#define penaltyValue 100
//function prototypes


/************************************************************
* Function: start_game ()                                   *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description: Begins the game of Crappy Craps              *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void start_game();


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
void print_game_rules(void);


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
double get_bank_balance(void);

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
int is_valid_balance(double bankBalance);


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
double get_wager_amount(double bankBalance);


/************************************************************
* Function: check_wager_amount ()                           *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Checks to see if the wager is within the    *
*               limits of the player's available balance.   *
*				If the wager exceeds the player's allowable *
*				balance, then 0 is returned; otherwise 1    *
*				is returned.                                *
* Input parameters:                                         *
* Returns:                                                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int check_wager_amount(double wager, double balance);


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
int roll_die(void);


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
void press_enter_to_continue(void);


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
int calculate_sum_dice(int die1_value, int die2_value);


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
int is_win_loss_or_point(int sum_dice);


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
int is_point_loss_or_neither(int sum_dice, int *pointValuePtr);


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
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);


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
void chatter_messages(int winLossPoint, int rollCount, double* initialBankBalancePtr, double currentBankBalance);

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
int valid_or_not(int isValidWager, double wagerAmount, double *bankBalancePtr, int cheatAttempt);

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
int negative_wager(int cheatAttempt, double *bankBalancePtr);

/************************************************************
* Function: frog_menu ()                                    *
* Date Created: 2/21/2020                                   *
* Date Last Modified: 2/21/2020                             *
* Description:  Displays game menu with ASCII frog          *
* Returns: option 0, 1 or 2                                 *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
int frog_menu(void);


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
int dice_rolls(double rollCount, int* pointValuePtr, double* initialBankBalance, double currentBankBalance);

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
int is_game_active(double bankBalance);
