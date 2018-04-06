#ifndef DECK_H
#define DECK_H
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
    //Attributes
    public:
        vector<Card> deck;

    //Method
    public:
        Deck(); //Constructs the deck
        ~Deck(); //Destructor
        Card takeCard(); //Takes a card from the top of the deck
        void shuffle(); //Shuffles the deck
        void newDeck();
};

#endif // DECK_H
