

/*

Created By: Andrew Lefors
Created On: 4/27/2020
Project: Poker
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
#include "poker.h"

/* shuffle cards in deck */

void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck and draw from deck  */
int deal(const int wDeck[][13], int *wDrawn[][13], const char* wFace[], const char* wSuit[], Hand userHand[], int card, int cardsToDraw)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int cardPos = card;
	int index = 0;
	int counter = 0;
	/* deal each of the 52 cards */
	for (card = 1; card <= cardsToDraw && (cardPos + (card - 1)) <= 52; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if ((cardPos + (card - 1)) < 11 || cardsToDraw == 5)
				{
					if (wDeck[row][column] == (cardPos + card) && index < cardsToDraw && wDrawn[row][column] != 1)
					{
						/*printf("%5s of %-8s%c",
							wFace[column], wSuit[row],
							card % 2 == 0 ? '\n' : '\t');*/
						userHand[index].playerHand->faceValueIndex = column;
						userHand[index].playerHand->suitIndex = row;
						userHand[index].cardsToKeep[index] = 1;
						/*printf("Face Value Index: %d\nSuit Value Index: %d\n", userHand[index].playerHand->faceValueIndex, userHand[index].playerHand->suitIndex);*/
						
						wDrawn[row][column] = 1;
						index++;
					}
				}
				else if (wDeck[row][column] == (cardPos + card) && index < cardsToDraw && wDrawn[row][column] != 1)
				
				{
					
						if (userHand[index].cardsToKeep[index] == 0)
						{
							userHand[index].playerHand->faceValueIndex = column;
							userHand[index].playerHand->suitIndex = row;
							index++;
						}
						else
						{
							
							card = card - 1;
							index++;

						}
					
				}
			
			}
		}
	}
	return (cardPos + (card - 1));
}

void display_hand(Hand userHand[], const char *wFace[], const char *wSuit[])
{
	int index = 0;
	
	for (; index < 5; index++)
	{
		printf("Card %d: %s of %s\n", (index + 1), wFace[userHand[index].playerHand->faceValueIndex], wSuit[userHand[index].playerHand->suitIndex]);
	}
}

void init_drawn_cards(int* drawn[][13])
{
	int row = 0, col = 0;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 14; col++)
		{
			drawn[row][col] = 0;
		}
	}
}

void evaluate_user_hands(int userFaceFreqArray[], int userSuitFreqArray[], int *handsArray[])
{
	int index = 0, counter = 0, matchingFace = 0, matchingSuit = 0, straightFlush = 0, flush = 0, straight = 0, sequentialFace = 0,
		fourOfAKind = 0, pair = 0, twoPair = 0, twoPairMarker = 0, threeOfAKind = 0, fullHouse = 0, highCard = -1;
	//check for Straight flush and flush
	//outer loop for card suit
	for (index = 0; index < 4; index++)
	{
		//checking if all same suit
		if (userSuitFreqArray[index] == 4)
		{
			matchingSuit = 1;
			
		}
		//evalute card face values
		if (matchingSuit == 1)
		{
			//inner loop for card face value
			for (counter = 0; counter < 13; counter++)
			{
				//checking if cards in hand are sequential in order, i.e., 3, 4 ,5.
				//increment sequentialFace for each consecutive card, reset when out if gap.
				if (userFaceFreqArray[counter] == 1)
				{
					sequentialFace += 1;
					//Check if straight flush
					if (sequentialFace > 4)
					{
						//set straightFlush to highest face value for comparison if both users have it. (Not likely) 
						straightFlush = counter;
					}
				}
				else
				{
					
					sequentialFace = 0;
					//set value of flush to highest face card in hand.
					if (userFaceFreqArray[counter] > 0)
					{
						flush = counter;
					}
				}
			}
		}

	}
	//END CHECK STRAIGHT FLUSH

	//check for four of a kind
			//loop for card face value
			for (counter = 0; counter < 13; counter++)
			{
				//checking if cards are all the same face value
				//set value of fourOfAKind to position for comparison.
				if (userFaceFreqArray[counter] == 4)
				{
					fourOfAKind = counter;
					
				}
				else
				{
					fourOfAKind = 0;
				}
			}
	//END CHECK FOUR OF KIND

	//check for Full House, pair, three of a kind.
			for (counter = 0; counter < 13; counter++)
			{
				if (userFaceFreqArray[counter] == 2)
				{
					pair = counter;
					
				}
				if (userFaceFreqArray[counter] == 3)
				{
					threeOfAKind = counter;
				}
				if (pair > 0 && threeOfAKind > 0)
				{
					fullHouse = threeOfAKind;
				}
			}
	//END CHECK FULL HOUSE, TWO PAIR, THREE PAIR
	
	//check for straight
			//reset sequntial face
			sequentialFace = 0;
			//inner loop for card face value
			for (counter = 0; counter < 13; counter++)
			{
				//checking if cards in hand are sequential in order, i.e., 3, 4 ,5.
				//increment sequentialFace for each consecutive card, reset when out if gap.
				if (userFaceFreqArray[counter] == 1)
				{
					sequentialFace += 1;
					//Check if straight flush
					if (sequentialFace > 4)
					{
						//set straight to highest face value for comparison if both users have it. (Not likely) 
						straight = counter;
					}
				}
				else
				{
					sequentialFace = 0;
				}
			}
	//END CHECK STRAIGHT
	
	//check for two pair
			for (index = 0; index < 13; index++)
			{
				if (userFaceFreqArray[index] > 1)
				{
					twoPairMarker += 1;
				}
				if (twoPairMarker > 1)
				{
					twoPair = index;
				}
			}
	//END CHECK TWO PAIR

	//check high card
			for (index = 0; index < 13; index++)
			{
				if (userFaceFreqArray[index] == 1)
				{
					highCard = index;
				}
			}

			//Set evaluted hands into hands array
			handsArray[0] = straightFlush;
			handsArray[1] = fourOfAKind;
			handsArray[2] = fullHouse;
			handsArray[3] = flush;
			handsArray[4] = straight;
			handsArray[5] = threeOfAKind;
			handsArray[6] = twoPair;
			handsArray[7] = pair;
			handsArray[8] = highCard;
			
}

void get_user_hand_freq(Hand userHand[], int faceFreqArray[], int suitFreqArray[])
{
	int index = 0, counter = 0;
	for (index = 0; index < 5; index++)
	{
		for (counter = 0; counter < 13; counter++)
		{
			if (userHand[index].playerHand->faceValueIndex == counter)
			{
				faceFreqArray[counter] = faceFreqArray[counter] + 1;
			}
			
		}
		for (counter = 0; counter < 4; counter++)
		{
			if (userHand[index].playerHand->suitIndex == counter)
			{
				suitFreqArray[counter] = suitFreqArray[counter] + 1;
			}
		}
	}
}

void display_freqs(int faceFreqArray[], int suitFreqArray[])
{
	int index = 0;
	for (; index < 13; index++)
	{
		printf("Frequency of %d: %d\n", index, faceFreqArray[index]);
	}
	for (index = 0; index < 4; index++)
	{
		printf("Frequency of %d: %d\n", index, suitFreqArray[index]);
	}
}

void init_freq_arrays(int *faceFreqArray[], int *suitFreqArray[])
{
	int index = 0;
	for (; index < 13; index++)
	{
		faceFreqArray[index] = 0;
	}
	for (index = 0; index < 4; index++)
	{
		suitFreqArray[index] = 0;
	}
}

void init_hands_array(int* handsArray[])
{
	int index = 0;
	for (index = 0; index < 9; index++)
	{
		handsArray[index] = 0;
	}
}

int compare_hands(int playerHandArray[], int computerHandArray[])
{
	int index = 0, leader = -1;
	for (index = 0; index < 9; index++)
	{
		if (playerHandArray[index] > computerHandArray[index])
		{
			return 0;
		}
		else if (playerHandArray[index] < computerHandArray[index])
		{
			return 1;
		}
		
	}
	return leader;
}


void display_winner(int isVictory)
{
	//display game winner

	if (isVictory == 0)
	{
		printf("**********************************************************************\n");
		printf("*         111111 1          1   1   1  1111 111111      1            *\n");
		printf("*         1    1 1         1 1   1 1   1    1    1     11            *\n");
		printf("*         111111 1        1   1   1    111  111111    1 1            *\n");
		printf("*         1      1       1  1  1  1    1    1    1      1            *\n");
		printf("*         1      1 1 1  1       1 1    1111 1     1     1            *\n");
		printf("*                                                    1111111         *\n");

	}
	else if (isVictory == 1)
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

int computer_evalute_cards_to_draw(int computerHandsArray[], Hand computerHand[], int compFreqArray[])
{
	int index = 0, counter = 0, onePair = 0, twoPair = 0;
	//check if hand contains striaghtflush through straight, if so return 0 for cards to draw
	for (index = 0; index < 5; index++)
	{
		if (computerHandsArray[index] > 0)
		{
			return 0;
		}
	}
		//draw 2 cards if three of a kind
		if (computerHandsArray[5] > 0)
		{
			for (index = 0; index < 13; index++)
			{
				if (compFreqArray[index] > 2)
				{
					for (counter = 0; counter < 5; counter++)
					{
						if (computerHand[counter].playerHand->faceValueIndex == index)
						{
							computerHand[counter].cardsToKeep[counter] = 1;
						}
						else
						{
							computerHand[counter].cardsToKeep[counter] = 0;
						}
					}
				}
			}
				return 2;
		}
		//draw 1 card if two pairs
		else if (computerHandsArray[6] > 0)
		{
			for (index = 0; index < 13; index++)
			{
				if (compFreqArray[index] > 1)
				{
					
					
						for (counter = 0; counter < 5; counter++)
						{
							if (computerHand[counter].playerHand->faceValueIndex == index)
							{
								computerHand[counter].cardsToKeep[counter] = 1;
							}
							else
							{
								computerHand[counter].cardsToKeep[counter] = 0;
							}
						}
					
					
				}
			}
			return 1;
		}
		//draw 3 cards if one pair
		else if (computerHandsArray[7] > 0)
		{
			for (index = 0; index < 13; index++)
			{
				if (compFreqArray[index] > 0)
				{


					for (counter = 0; counter < 5; counter++)
					{
						if (computerHand[counter].playerHand->faceValueIndex == index)
						{
							computerHand[counter].cardsToKeep[counter] = 1;
						}
						else
						{
							computerHand[counter].cardsToKeep[counter] = 0;
						}
					}


				}
			}

			return 3;
		}
		else
		{
			return rand() % 4;
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
			play_frog_poker();
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
		printf("         /                        Welcome To Frog Poker !                     \\ \n");
		printf("        /                         0 = Quit Game                                \\ \n");
		printf("       /                          1 = View Game Rules                           \\ \n");
		printf("       \\                         2 = Play Frog Poker  !                         /\n");
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
	//REPLACE WITH Poker GAME RULES
	printf("************************************************************************************************************************************************************************************************************************\n");
	printf("* In poker, players form sets of five playing cards, called hands, according to the rules of the game.Each hand has a rank, which is compared against the ranks of other hands participating in the showdown to        *\n"); 
	printf("* decide who wins the pot. In high games, like Texas hold 'em and seven-card stud, the highest-ranking hands win. In low games, like razz, the lowest-ranking hands win. In high-low split games, both the highest-ranking*\n"); 
	printf("* and lowest-ranking hands win, though different rules are used to rank the high and low hands. Each hand belongs to a category determined by the patterns formed by its cards.A hand in a higher                      *\n");
	printf("* - ranking category always ranks higher than a hand in a lower - ranking category.A hand is ranked within its category using the ranks of its cards.[5] Individual cards are ranked, from highest to lowest :         *\n");
	printf("* A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3 and 2.[6] However, aces have the lowest rank under ace - to - five low or ace - to - six low rules, or under high rules as part of a five - high straight or straight flush.     *\n");
	printf("* Suits are not ranked, so hands that differ by suit alone are of equal rank.                                                                                                                                          *\n");
	printf("************************************************************************************************************************************************************************************************************************\n");
}

void play_frog_poker(void)
{

	Hand userHand[5] = { -1, -1, -1, -1, -1 };
	Hand computerHand[5] = { -1, -1, -1, -1, -1 };
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	int isGameActive = -1;
	do
	{
		/* initalize deck array and drawn array */
		int deck[4][13] = { 0 };
		int drawn[4][13] = { 0 };
		int playerFaceFreqArray[13] = { 0 }, playerSuitFreqArray[4] = { 0 };
		int compFaceFreqArray[13], compSuitFreqArray[4];
		int* playerHandsArray[9], compHandsArray[9];
		int winLose = -1, dummyVar = 0;
		//reset cards drawn array
		init_drawn_cards(drawn);
		int card = 1, cardsToDraw = 5;
		int index = 0, stayOrDraw = -1, drawCount = 0;
		//initilize and reset hands array
		init_hands_array(playerHandsArray);
		init_hands_array(compHandsArray);
		//Shuffle the deck
		shuffle(deck);


		do
		{
			//FIRST HAND OF NEW DECK
		//Deal player hand, update card position in deck
			card = deal(deck, drawn, face, suit, userHand, card, cardsToDraw);
			//init face value frequency array
			init_freq_arrays(playerFaceFreqArray, playerSuitFreqArray);
			//get user face & suit value frequencies
			get_user_hand_freq(userHand, playerFaceFreqArray, playerSuitFreqArray);
			//display user cards
			display_hand(userHand, face, suit);
			//display user frequencies
			/*display_freqs(playerFaceFreqArray, playerSuitFreqArray);*/

			//deal computer hand, update card position in deck
			card = deal(deck, drawn, face, suit, computerHand, card, cardsToDraw);
			//init computer frequncy arrays
			init_freq_arrays(compFaceFreqArray, compSuitFreqArray);
			//get computer face & suit frequncies 
			get_user_hand_freq(computerHand, compFaceFreqArray, compSuitFreqArray);
			//get computers current hand
			evaluate_user_hands(compFaceFreqArray, compSuitFreqArray, compHandsArray);
			//END FIRST HAND OF NEW DECK


			//Computer checks hand and draws appropriate number of cards
			cardsToDraw = computer_evalute_cards_to_draw(compHandsArray, computerHand, compFaceFreqArray);
			card = deal(deck, drawn, face, suit, computerHand, card, cardsToDraw);
			init_freq_arrays(compFaceFreqArray, compSuitFreqArray);
			get_user_hand_freq(computerHand, compFaceFreqArray, compSuitFreqArray);
			evaluate_user_hands(compFaceFreqArray, compSuitFreqArray, compHandsArray);
			//Check if player wants to replace cards in hand
			printf("Stay or Draw cards?\n0: Stay\t1: Draw\n");
			scanf("%d", &stayOrDraw);
			if (stayOrDraw == 1 && drawCount < 3)
			{
				clear_screen();
				display_hand(userHand, face, suit);
				cardsToDraw = 0;
				for (index = 0; index < 5; index++)
				{
					printf("0: Discard\t1: Keep\n");
					printf("Discard %s of %s?\n", face[userHand[index].playerHand->faceValueIndex], suit[userHand[index].playerHand->suitIndex]);
					scanf("%d", &userHand[index].cardsToKeep[index]);
					if (userHand[index].cardsToKeep[index] == 0)
					{
						cardsToDraw += 1;
					}
				}
				/*card = deal(deck, drawn, face, suit, userHand, card, cardsToDraw);
				init_freq_arrays(playerFaceFreqArray, playerSuitFreqArray);
				get_user_hand_freq(userHand, playerFaceFreqArray, playerSuitFreqArray);
				display_hand(userHand, face, suit);*/
				drawCount++;

				press_key_to_continue();
				/*clear_screen();*/
			}
			else
			{

				clear_screen();
				//evaluate players hand
				evaluate_user_hands(playerFaceFreqArray, playerSuitFreqArray, playerHandsArray);
				//evalute computers hand
				evaluate_user_hands(compFaceFreqArray, compSuitFreqArray, compHandsArray);

				winLose = compare_hands(playerHandsArray, compHandsArray);
				printf("Your Cards:\n");
				display_hand(userHand, face, suit);
				printf("----------------------------\n");
				printf("Computers Cards:\n");
				display_hand(computerHand, face, suit);
				display_winner(winLose);

				press_key_to_continue();
				clear_screen();
				printf("Continue Playing?\n1: Keep Playing\t2: Quit to Menu\n");
				scanf("%d", &isGameActive);
				
			
			}
		} while (card < 52 && isGameActive == 1);
		init_drawn_cards(drawn);
	} while (isGameActive == 1);
	
}
