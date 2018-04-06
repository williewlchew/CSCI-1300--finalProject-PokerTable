#ifndef CARD_H
#define CARD_H
#include <iostream>

using namespace std;

/* Project Proposal:
My project will be a text based poker game where the player plays poker against three other computer controlled
players. The goal of the project is to provide the most realistic poker experience while fulfilling the code
requirements needed for the program. The game is designed around the Dealer class calling methods from Deck and
Player to properly play the game. This makes the code easy to read and manage. The design will most likely reach
the requirement due to the amount of test cases needed to check for the winning hand of the game and the algorithm
needed to compute the computer controlled player’s next move.
*/

class Card
{
    //Attributes
    private:
        int value;
        /**Card Index:
            1 - 2
            2 - 3
            3 - 4
            4 - 5
            5 - 6
            6 - 7
            7 - 8
            8 - 9
            9 - 10
            10 - J
            11 - Q
            12 - K
            13 - A
        */
        int suit;
        /**Suit Index:
            0 - Clubs
            1 - Diamonds
            2 - Hearts
            3 - Spade
        */

    //Methods
    public:
        //Constructor
        Card();
        Card(int, int);
        //Destructor
        ~Card();
        //Getters and Manipulators
        void setValue(int);
        void setSuit(int);
        int getValue();
        int getSuit();
        string displayCard();

};

#endif // CARD_H
