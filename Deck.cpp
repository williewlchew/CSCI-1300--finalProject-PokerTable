#include "Deck.h"
#include <vector>
#include "Number.h"
#include <iostream>

using namespace std;

Deck::Deck()
{
    for(int s = 0; s < 4; s++)  //construct suit
    {
        for(int v = 1; v < 14; v++) //construct value
        {
            Card card(s,v);
            deck.push_back(card);
        }
    }
}

Deck::~Deck()
{

}

void Deck::shuffle()
{
    //Deck Info
    int cardNum = deck.size();
    vector<Card> tempDeck(deck);
    Number num;
    for(int i = cardNum; i > 0; i--)
    {
        num.setBounds(0,i);
        int randomIndex = num.random(); //cout << randomIndex << " ";
        deck[i] = tempDeck[randomIndex];
        tempDeck.erase(tempDeck.begin()+randomIndex);
    }
}

Card Deck::takeCard()
{
    Card selected = deck.back();
    deck.pop_back();
    return selected;
}

void Deck::newDeck()
{
    deck.clear();
    for(int s = 0; s < 4; s++)  //construct suit
    {
        for(int v = 1; v < 14; v++) //construct value
        {
            Card card(s,v);
            deck.push_back(card);
        }
    }
}
