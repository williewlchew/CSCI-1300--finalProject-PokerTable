#ifndef DEALER_H
#define DEALER_H
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Player.h"


using namespace std;

class Dealer
{
    private:
        //Game basics
        int pot;
        vector<Card> flop;
        Deck deck;

        //Players
        Player players[2];
        int bigBlind; //goes last
        int ante;
        int roundWinner;


    public:
        Dealer(); //Constructs the game; prompt the menu
        ~Dealer();
        void startGame(); //
        void loadGame();
        void exitGame();
        //testing
        void testTestCases();


    private:
        //Utilities

        //Pre-Flop
        void startRound(); //move blinds and deal cards
        void moveBlinds();
        void dealCard(Player&);

        //Flop
        void midRound();
        void processMidRound();
        void processMenu();
        void processHelp();
        void turnCard();
        void turnCard(int);

        //Finish Round
        void endRound(); //Compilation of functions to compare cards to decide on a winner and gives money to winner
        int findWinner(); //Test cases to find the winning hand amoung the non folded players
        bool testHighCard(int&);
        bool testPair(int&);
        bool testTwoPair(int&);
        bool testTrips(int&); //tests for matching values
        bool testStraight(int&);
        bool testFlush(int&);
        bool testFullHouse(int&);
        bool testFours(int&);
        bool testStraightFlush(int&);
        bool testRoyalFlush(int&);
        //Test case helpers
        bool testSuit(Card[], int&);
        bool testStraight(Card[], int&);
        bool testMatch(Card[], int, int&);
        void fillTestSelection(Card[], int);
};

#endif // DEALER_H
