/*
    Author : Willie Chew
*/
#include "Card.cpp"
#include "Deck.cpp"
#include "Player.cpp"
#include "Dealer.cpp"
#include "Number.cpp"
#include <iostream>

using namespace std;

/*** Code Planning
To do:
    Card
        -Set and get suits and values-
    Deck
        -shuffle-
        -build deck-
        -take card-
    Dealer
        turns
        initialize players
        deal cards
        move blinds
        flop and river
        decide on a winner
            test cases
    Player
        prompt player
        calculate hand value
        make a decision
        emotion
            dialouge from confidence
        find a way to make confident ai bluff

*/


void testFunction()
{
    //test random generation
    Number num;
    int dump = num.random();
    cout << num.random() << " " << num.random() << " " << num.random() << endl;

    //test deck
    Deck dec;
    dec.shuffle();
    cout << "Test Card: " << dec.deck.back().displayCard(); dec.deck.pop_back();
    cout << " Test Card: " << dec.deck.back().displayCard(); dec.deck.pop_back();
    cout << " Test Card: " << dec.deck.back().getSuit() << "-" << dec.deck.back().getValue(); dec.deck.pop_back();
    cout << " Test Card: " << dec.deck.back().getSuit() << "-" << dec.deck.back().getValue();
    //test card sorting
    Card testr[2] = {Card(0,2), Card(3,5)};
}

void testDealer()
{
    Dealer dealr;
    dealr.testTestCases();
}

int main()
{
    Dealer dealr;
    int choice = -1; string input = "";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;
    cout << "Welcome to Conrad's Poker table.";
    while(choice != 0)
    {
        cout << endl << "Input what would you like to do: start, load, exit.  " ;
        getline(cin, input);
        for(int i = 0; i < input.length(); i++)
        {
            if(input[i] == ' ')
                input = input.substr(0,i);
        }
        string temp = "";
        for(int i = 0; i < input.length(); i++)
        {
            temp += tolower(input[i]);
        }
        input = temp;

        //Process Input
        if(input == "exit")
        {
            cout << "Goodbye!";
            choice = 0;
        }

        else if(input == "start")
        {
            dealr.startGame();
        }

        else if(input == "load")
        {
            dealr.loadGame();
        }

        else if(input == "test1")
        {
            testFunction();
        }

        else if(input == "test2")
        {
            testDealer();
        }

        else
        {
            cout << endl << "Your response could not be read.";
        }
    }
    return 0;
}
