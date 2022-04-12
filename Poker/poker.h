/*

Created By: Andrew Lefors
Created On: 4/27/2020
Assignment: PA-7 'Poker!'
Created For: Dr. O'Fallon CPTS_121 Spring 2020
File Version: 0.4.27.20

Description: In poker, players form sets of five playing cards, called hands, according to the rules of the game.Each hand has a rank, which is compared against the ranks of other hands participating in the showdown to
	decide who wins the pot. In high games, like Texas hold 'em and seven-card stud, the highest-ranking hands win. In low games, like razz, the lowest-ranking hands win. In high-low split games, both the highest-ranking
	and lowest-ranking hands win, though different rules are used to rank the high and low hands. Each hand belongs to a category determined by the patterns formed by its cards.A hand in a higher
	- ranking category always ranks higher than a hand in a lower - ranking category.A hand is ranked within its category using the ranks of its cards. Individual cards are ranked, from highest to lowest :
	A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3 and 2.[6] However, aces have the lowest rank under ace - to - five low or ace - to - six low rules, or under high rules as part of a five - high straight or straight flush.
	Suits are not ranked, so hands that differ by suit alone are of equal rank.
			 Whomp-whomp.

			NOTE: RULES WERE OBTAINED FROM WIKIPEDIA
			NOTE: After successful hand completion, error around variable stack 'drawn' occurs when trying to quit to menu.
			NOTE: clear screen function: Learned how to do this from StackOverflow: https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c/42500322



*/

#pragma once


#define _CRT_SECURE_NO_WARNINGS // necessary to ignore scanf_s () warnings (Must come first)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>





typedef struct card
{
	int faceValueIndex;
	int suitIndex;
} Card;

typedef struct hand
{
	Card playerHand[5];
	int cardsToKeep[5];

} Hand;

void shuffle(int wDeck[][13]);

int deal(const int wDeck[][13], int wDrawn[][13], const char* wFace[], const char* wSuit[], Hand userHand[], int card, int cardsToDraw);

void display_hand(Hand userHand[], const char* wFace[], const char* wSuit[]);

void init_drawn_cards(int* drawn[][13]);

void evaluate_user_hands(int userFaceFreqArray[], int userSuitFreqArray[], int *handsArray[]);

void get_user_hand_freq(Hand userHand[], int faceFreqArray[], int suitFreqArray[]);

void display_freqs(int faceFreqArray[], int suitFreqArray[]);

void init_freq_arrays(int* faceFreqArray[], int* suitFreqArray[]);

int compare_hands(int playerHandArray[], int computerHandArray[]);

void init_hands_array(int* handsArray[]);

void display_winner(int isVictory);

void clear_screen(void);

void press_key_to_continue(void);

int computer_evalute_cards_to_draw(int computerHandsArray[], Hand computerHand[], int compFreqArray[]);

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

void play_frog_poker(void);