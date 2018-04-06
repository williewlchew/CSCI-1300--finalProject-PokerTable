#include "Card.h"
#include <iostream>

//constructor
Card::Card()
{
    value = 0;
    suit = 0;
}

Card::Card(int suitInput, int valueInput)
{
    suit = suitInput;
    value = valueInput;
}

Card::~Card()
{

}

void Card::setValue(int valueInput)
{
    value = valueInput;
}

void Card::setSuit(int suitInput)
{
    suit = suitInput;
}

int Card::getValue()
{
    return value;
}

int Card::getSuit()
{
    return suit;
}

string Card::displayCard()
{
    string suitOutput = "";
    string valueOutput = "";
    if (suit == 0)
        suitOutput = "Clubs";
    else if(suit == 1)
        suitOutput = "Daimonds";
    else if(suit == 2)
        suitOutput = "Hearts";
    else if(suit == 3)
        suitOutput = "Spade";
    if (value >= 1 && value <= 9)
        valueOutput = to_string(value + 1);
    else if(value == 10)
        valueOutput = "J";
    else if(value == 11)
        valueOutput = "Q";
    else if(value == 12)
        valueOutput = "K";
    else if(value == 13)
        valueOutput = "A";
    return (" |" + suitOutput + "-" + valueOutput) + "| ";
}
