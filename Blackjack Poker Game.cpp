#include <iostream>
#include <iomanip>
#include <random>
#include <vector> //the vector file allows us to have a changing length of a list, easier to operate with in this case
#include <ctime>
#include <string>
#include <cmath>

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
* Defines a function that returns an uppercase of the entered string
* as C++ does not have an inherent string method to change a string
* to all upper or lowercase.
* 
* Return Type: std::string
* Parameters: None
* 
*/

std::string To_Upper() 
{
	std::string input{};
	std::cin >> input;
	//uses the std::transform to make it uppercase
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	return input;
}

/*
* 
* Defines a function that takes the values of the player and dealer's 
* cards and adds the best values to the list, returning the best value
* of the hand If the value is above 22, the player/dealer busts,
* so this value is deleted.
* 
* Return Type: int
* Parameters: vector of the values of a hand
* 
*/

int bestValue(std::vector<int> &values)
{
	int highestVal = 0;
	for (int i = 0; i < values.size(); i++)	{

		//if the value is 22 or higher, we don't want it there
		if (values[i] >= 22)
		{
			values[i] = 0;	
		}
		//otherwise let's increase the value of highestVal
		else if (values[i] > highestVal)
		{
			highestVal = values[i];
		}
		
	}
	return highestVal;
}

/*
* 
* Defines a function to print a hand using the .printCard() method defined
* in the card class. Uses vector of the hand as well as 
* two boolean inputs to check if the function should only print out one
* card (for the dealer at the beginning) or if it should print two,
* and if it is the dealer's hand.
* 
* Return Type: void/null
* Parameters: vector of the cards, two booleans
* 
*/

void printHand(std::vector<class card> hand, bool printOneCard, bool isDealerHand)
{
	if (!printOneCard && !isDealerHand) // This is the player's hand
	{
		for (int i = 0; i < hand.size(); i++) //Go through the players hand...
		{
			std::cout << hand[i].printCard() << " " << std::flush;//... and print each card.
		}
		std::cout << "is your hand! \n" << std::flush;
	}
	else if(!printOneCard && isDealerHand) // This is the dealer's hand, with two cards
	{
		for (int i = 0; i < hand.size(); i++) //Go through the dealer's hand...
		{
			std::cout << hand[i].printCard() << " " << std::flush; // ... and print each card.
		}
		std::cout << "is the dealer's hand! \n" << std::flush;
	}
	else // This is the dealer's hand on the deal
	{
		std::cout << "The dealer has " << hand[0].printCard() << " and one other card. Dealer must hit on 16 and stand on 17. \n" << std::flush;
	}
}

/*
* 
* Defines a function that uses the card that is added to the hand,
* as well as the set of values already for the hand, and a 
* boolean to check if it is the deal when we are adding values,
* and will add the possible values to the values list
* 
* Return Type: void/null
* Parameters: a card, a set of values for the hand, and a boolean
* 
*/

void addValues(class card card, std::vector <int> &values, bool isDeal)
{
	if (!isDeal) // make sure it is not the deal first, because these are added first.
	{
		std::vector <int> replacementValues{ values }; // we'll use this as a placeholder vector
		values.clear(); // and clear the rest of the values

		//add the new values to the old ones from the placeholder
		if (card.getIsAce()) // if it is an ace...
		{
			for (int i = 0; i < replacementValues.size(); i++) // this will add two values
			{
				values.push_back(replacementValues[i] + 1);
				values.push_back(replacementValues[i] + 11);
			}
		}
		else
		{
			for (int i = 0; i < replacementValues.size(); i++) // just one if its not
			{
				values.push_back(replacementValues[i] + card.getValue());
			}
		}
	}
}

/*
* 
* Definition of a function that takes a random card from the deck
* using a random seed from the computer's time, and 
* uses the modulus operator to get a random value within
* the deck, add it to the hand it is being called to, and 
* deletes the card from the deck so it cannot be added to another hand.
* 
* Return Type: void/null
* Parameters: a hand, the values of the hand, and a boolean to check if it is the deal
* 
*/

void addRandomCard(std::vector<class card>& Hand, std::vector <int> &values, bool isDeal)
{
	//use the random number and modulus to have a number between 0-51
	int rand1 = rand() % deckOfCards.size();
	//grab the card from the deck
	class card card1 = deckOfCards[rand1];
	//delete it from the deck...
	deckOfCards.erase(deckOfCards.begin() + rand1);
	//and put it in the respective hand
	Hand.push_back(card1);
	addValues(card1, values, false);
}

/*
* Defines the gameplay for the user to hit the deck or stand
*			   **MAJOR GAMEPLAY FRAMEWORK**
* 
* Return Type: void/null
* Parameters: the player's hand, a boolean to keep hitting, and the values of the hand
*/

void hitFunction(std::vector<class card>& playerHand, bool keepHitting, std::vector <int> values)
{
	//initial question
	std::cout << "\n\nWould you like to hit? (Type 'Hit' or 'Stand') " << std::flush;
	std::string hitResponse = To_Upper(); //use this to generalize the response
	while (hitResponse != "NO" && hitResponse != "STAND" && bestValue(values) != 21)
	{
		if (bestValue(values) == 21)
		{			
			std::cout << "\nYou hit Blackjack! An even 21!\n" << std::endl << std::flush;
			return;															
		}

		//make sure it is a valid input
		while (hitResponse != "HIT" && hitResponse != "STAND"  )
		{
			std::cout << "Invalid Input: " << std::flush;
			hitResponse = To_Upper();
		}
		//if the player wants to hit...
		if (hitResponse == "HIT")
		{
			system("CLS");
			std::cout << "You decided to hit!" << std::endl << std::flush;
			//...give them a card...
			addRandomCard(playerHand, values, false);
			//...and print them a hand to let them know what they drew
			printHand(playerHand, false, false);

			if (bestValue(values) == 0)
			{
				return; //bust! get out of this and skip straight to the end.
			}
			if (bestValue(values) == 21)
			{
				std::cout << "\nYou hit Blackjack! An even 21!\n" << std::endl << std::flush;
				return;
			}
			std::cout << "Would you like to hit again? (Type 'Yes' or 'No') " << std::flush;
			hitResponse = To_Upper();
			//same as first quesion
			while (hitResponse != "YES" && hitResponse != "NO")
			{
				std::cout << "Invalid Input: " << std::flush;
				hitResponse = To_Upper();
			}

			if (hitResponse == "NO")
			{
				keepHitting = false;
				system("CLS");
			}
			else 
			{
				hitResponse = "HIT";
			}
		}

		else if (hitResponse == "STAND")
		{
			std::cout << "You decided to stand!" << std::endl << std::flush;
			system("CLS");
			keepHitting = false; //leave the while loop
			return;
		}

		else
		{
			std::cout << "Invalid input, Please enter 'Yes' or 'No': " << std::flush;
		}
	}

	if (bestValue(values) == 21)
	{
		std::cout << "\nYou hit Blackjack! An even 21!\n" << std::endl << std::flush;
		return;
	}
}

/*
* 
* This is the function that defines the behavior for the computer dealer
* Dealer hits on 16 and stands on 17
* 
* Return Type: void/null
* Parameters: the hand and the set of values with it
* 
*/

void dealerHitFunction(std::vector<class card> &dealerHand, std::vector <int> &values)
{
	int best = bestValue(values);
	while (best < 17) //dealer must stand on 17, so don't let them hit
	{
		if (best == 0) // if they have a 0, they busted on all values!
		{
			return;
		}
		addRandomCard(dealerHand, values, true); // add another card
		best = bestValue(values); //check the best value again
	}
}

/*
* 
* Defines a function that will check if there are any aces in the deal
* and adjust the hand's values accordingly
* 
* Return Type: void/null
* Parameters: the hand and the values associated with it
* 
*/

void aceCheckForValues(std::vector<class card> hand, std::vector <int>& values)
{
	if (hand[0].getIsAce() && hand[1].getIsAce()) //both aces yield 3 values
	{
		values.push_back(2);
		values.push_back(12);
		values.push_back(20);
	}
	else if (hand[0].getIsAce()) // add 1 and 11 to the other card
	{
		values.push_back(hand[1].getValue() + 1);
		values.push_back(hand[1].getValue() + 11);
	}
	else if (hand[1].getIsAce()) // add 1 and 11 to the other card
	{
		values.push_back(hand[0].getValue() + 1);
		values.push_back(hand[0].getValue() + 11);
	}
	else // this will just be the sum of the two cards
	{
		values.push_back(hand[0].getValue() + hand[1].getValue());
	}
}

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
					deckOfCards.push_back(card { type, "A", 11, true });
					break;
				case (11): // Jack Case
					deckOfCards.push_back(card { type, "J", 10, false });
					break;
				case (12): // Queen Case
					deckOfCards.push_back(card { type, "Q", 10, false });
					break;
				case (13): // King Case	
					deckOfCards.push_back(card { type, "K", 10, false });
					break;
				default: // 2-10 Case
					char str[12];
					int num = j;
					sprintf_s(str, "%d", j); // convert string to int
					deckOfCards.push_back(card { type, str, j, false });
					break;
			}
		}
	}
}

/*
* 
* This is a function to check the winner of the game
* by comparing the best value of all each hand
* 
* Return Type: void/null
* Parameters: Both values, the wager and money as ints
* 
*/

void determineWinner(std::vector <int> playerValues, std::vector <int> dealerValues, double wager, double& money, bool OnDeal = false)
{
	if (OnDeal && bestValue(playerValues) == 21) //blackjack on the deal for the player
	{
		wager = wager + ceil(1.5 * wager);
		std::cout << "You beat the dealer on a perfect 21! You win $" << wager << ". Your current winnings are $" << money << "." << std::flush; //output
	}
	else if (bestValue(dealerValues) == 21) //blackjack on the deal for the dealer
	{
		money -= wager;
		std::cout << "\nThe dealer had a perfect 21 on the deal! \n" << std::flush;
		std::cout <<"You lost to the dealer! You lost $" << wager << ". Your current winnings are $" << money << "." << std::flush; //output
	}
	else if (bestValue(playerValues) == 21) //blackjack for the dealer
	{
		money += wager;
		std::cout << "\nYou had a perfect 21! \n" << std::flush;
		std::cout << "You beat the dealer! You won $" << wager << ". Your current winnings are $" << money << "." << std::flush; //output
	}
	else if (bestValue(playerValues) > bestValue(dealerValues)) //blackjack for the player
	{
		money += wager; 
		
		if (bestValue(dealerValues) == 0 || dealerValues.size() == 0) // the dealer busts here
		{
			std::cout << "The dealer busted!" << std::endl;
		}
		std::cout << "You beat the dealer! You win $" << wager << ". Your current winnings are $" << money << "." << std::flush; //output
	}
	else if (bestValue(playerValues) < bestValue(dealerValues))
	{
		money -= wager; //change the total money through the wager
		if (bestValue(playerValues) == 0 || playerValues.size() == 0)// the player busts here
		{
			std::cout << "You busted!" << std::endl;
		}
		std::cout << "You lost to the dealer! You lost $" << wager << ". Your current winnings are $" << money << "." << std::flush; //output
	}
	else //if there is no other case, they must have tied
	{
		std::cout << "You pushed, you get your $" << wager << " back!" << " Your current winnings are $" << money << "." << std::flush; //output
	}
}

int main()
{
	//Creates a random seed for the random numbers generated later using the OS's time
	srand((unsigned int)time(NULL));

	// Define a set amount to start with for money
	double money = 0;
	bool playAgain = true;

	//start sequence
	std::cout << "Welcome to Blackjack. " << std::endl << std::flush;
	while (money <= 0) // check that the input is a number above 0
	{
		std::cout << "How much money would you like to start with? (Enter a positive, non-zero number): " << std::flush;
		std::cin >> money;
	}

	system("CLS");
	std::cout << "Great! We'll get you started now with $" << money << ". " << std::flush; //greet the player
	system("PAUSE");
	system("CLS");

	while (playAgain) //make sure the user still wants to play after another game
	{
		ShuffleDeck(); //shuffle

		double wager = 0; // reset the wager
		while (wager <= 0) // check that the input is a number above 0
		{
			std::cout  << "You have $" << money << " available.\n" << std::flush;
			std::cout << "Please enter your wager (Enter a positive, non-zero number) for this round: " << std::flush;
			std::cin >> wager;
		}
		while (wager > money) 
		{
			std::cout << "You don't have enough money! \nPlease enter your wager (Enter a positive, non-zero number) for this round: \n" << std::flush;
			std::cin >> wager;
		}
		system("CLS");
		std::cout << "Alright, you wagered $" << wager << " on this round. I'll deal the cards when you're ready. " << std::flush;
		system("PAUSE");
		system("CLS");

		// Play the game!
		// Instantiate a list (vector) of both hands

		std::vector<class card> dealerHand = {};
		std::vector<class card> playerHand = {};

		/*  First, we need to determine the value of the hands to check and see
		 *  if either hands contain blackjack off the bat
		 *
		 *  Since Aces carry muliple values, let's initialize a list with
		 *  every possible hand value in the hand
		 *
		 *  Although this list will be mostly only one number for the
		 *  duration of the game, it will help when doing comparison
		 *  and logic later in the game.
		 */

		//instantiate a list of all of the values of the hands
		std::vector<int> dealerValues = {};
		std::vector<int> playerValues = {};

		// Start by dealing the cards, One to each first, then the second

		for (int i = 0; i < 2; i++)
		{
			addRandomCard(dealerHand, dealerValues, true);
			addRandomCard(playerHand, playerValues, true);
		}
		//add values for aces
		aceCheckForValues(dealerHand, dealerValues);
		aceCheckForValues(playerHand, playerValues);
		//print the hands so that the player can see
		printHand(playerHand, false, false);
		printHand(dealerHand, true, true);

		
		if (bestValue(dealerValues) == 21 || bestValue(playerValues) == 21) 
		{																			//someone has a blackjack
			determineWinner(playerValues, dealerValues, wager, money, true);		//no matter who it is
			continue;																//it will be handled in that function
		}
		else 
		{
			//allow the player to hit here
			hitFunction(playerHand, true, playerValues);
		}
		
		if (bestValue(playerValues) == 0 || playerValues.size() == 0) // if there is no cards in their hand or the best value is 0...
		{												 // Determine the winner as the dealer
			determineWinner({ 0 }, { 1 }, wager, money); // The zero and one here mean that there is a dealer win no matter what
			continue;									 // There is no reason for the dealer to hit 
		}
		else // let the dealer hit if they have a value of their hand
		{
			dealerHitFunction(dealerHand, dealerValues); //then the dealer
		}
		
		system("CLS");
		//print the hands when they are done
		printHand(playerHand, false, false);
		printHand(dealerHand, false, true);
		//determine the winner
		determineWinner(playerValues, dealerValues, wager, money);

		if (money <= 0) // check to make sure the person still has money to play
		{
			std::cout << "\nYou ran out of money!\nBetter Luck Next Time! \n \n";
			return 0; // Get out of the function, end game
		}

		//determine if they'd like to play again
		std::cout << "\nWould you like to play again? (Type 'yes' or 'no'): " << std::flush;

		std::string playAgainResponse{ To_Upper() }; //check to see if they want to play again
		while (playAgainResponse != "YES" && playAgainResponse != "NO") // make sure they have a correct response
		{
			std::cout << "Invalid Response, type 'yes' or 'no': " << std::flush;
			playAgainResponse = To_Upper();
		}

		if (playAgainResponse == "NO")
		{
			playAgain = false;
		}
		system("CLS");
	}

	system("CLS");
	std::cout << "You ended with $" << money << ".\n\n"; // give them a outgoing statement
}