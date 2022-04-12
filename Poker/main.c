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

int main(void)
{
	int isMenuActive = 0;
	/* seed random-number generator */
	srand((unsigned)time(NULL)); 
	do
	{
		isMenuActive = menu_loop();
	} while (isMenuActive = 0);
	return 0;
}

