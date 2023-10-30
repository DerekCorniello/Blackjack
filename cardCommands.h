#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <vector> //the vector file allows us to have a changing length of a list, easier to operate with in this case
#include <ctime>
#include <string>

// Define the deck of cards globally
std::vector<class card> deckOfCards = {}; // a vector of all of the cards in the future

// Define the types for the special characters globally
const char* hearts = "\x03";  //♥
const char* diamond = "\x04";  //♦
const char* clubs = "\x05";  //♣
const char* spades = "\x06";  //♠
/*
*
* Here we define a class called card in order to
* store some information on cards, like it's type
* value, and if it is an ace
*
* Also defined in this class is a method for printing
* the card in plain text.
*
*/

class card
{
	const char* type{};
	std::string number{};
	int value{};
	bool isAce{};

	public:

	card(const char* type, std::string number, int value, bool isAce)
	{
		card::type = type;
		card::number = number;
		card::value = value;
		card::isAce = isAce;
	}

	std::string const printCard()
	{
		return number + type;
	}

	int getValue() const { return value; }
	bool getIsAce() const { return isAce; }
};

/*
*
* Uses the initialized deckOfCards vector to create a new deck of cards
* after every round. We do not have to worry about shuffling them
* because they are picked at random.
*
* Return Type: void/null
* Parameters: none
*
*/

void ShuffleDeck()
{
	//initialize a list of all cards
	deckOfCards.clear();

	for (int i = 0; i < 4; i++) //start by changing the suit of card
	{
		const char* type;
		switch (i) // the case will check if 
		{
		case(0):
			type = hearts;
			break;
		case(1):
			type = diamond;
			break;
		case(2):
			type = clubs;
			break;
		default:
			type = spades;
			break;
		}

		for (int j = 1; j < 14; ++j) //will count up from 1 until 13. 1 = A, 11 = J, 12 = Q and 13 = K, identified by a switch case
		{
			switch (j)
			{
			case (1): // Ace Case
				deckOfCards.push_back(card{ type, "A", 11, true });
				break;
			case (11): // Jack Case
				deckOfCards.push_back(card{ type, "J", 10, false });
				break;
			case (12): // Queen Case
				deckOfCards.push_back(card{ type, "Q", 10, false });
				break;
			case (13): // King Case	
				deckOfCards.push_back(card{ type, "K", 10, false });
				break;
			default: // 2-10 Case
				char str[12];
				int num = j;
				sprintf_s(str, "%d", j); // convert string to int
				deckOfCards.push_back(card{ type, str, j, false });
				break;
			}
		}
	}
}

