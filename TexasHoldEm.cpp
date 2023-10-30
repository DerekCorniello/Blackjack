#include <iostream>
#include "cardCommands.h"
#include <string>

/*
*
* Determines the ranking of the hand based on the following:
* 
* Royal Flush: A, K, Q, J, 10 of the same suit.
* Straight Flush: Five consecutive cards of the same suit.
* Four of a Kind: Four cards of the same rank.
* Full House: Three cards of one rank and two cards of another rank.
* Flush: Five cards of the same suit, not in sequence.
* Straight: Five consecutive cards of any suit.
* Three of a Kind: Three cards of the same rank.
* Two Pair: Two cards of one rank and two cards of another rank.
* One Pair: Two cards of the same rank.
* High Card: When no other hand is made, the highest card in your hand is your "high card."
* 
*/


std::string handVal(std::vector<class card> hand)
{
	std::vector<std::string> values = {};
	std::vector<int> cardIndex_straight = {};
	std::vector<int> cardIndex_flush = {};

	for (card c:hand)
	{
		
	}
}


int main()
{

}
