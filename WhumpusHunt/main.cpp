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


int main(void)
{
	
	//set seed
	srand((unsigned int)time(NULL));
	play_whumpus_hunt();
	return 0;
}
