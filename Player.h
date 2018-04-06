#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Card.h"
#include <iostream>

using namespace std;

class Player
{
    //Attributes
    public:
        int money;
        int inPot;
        int blind;
        Card hand[2];

    private:
        //Standard Information
        bool user;
        string name;
        bool folded;
        bool justBet;

        //Testing for Win
        vector<int> winningHands;
        /** Hand Index (Does not account for high cards)
            0 - None
            1 - Pair
        */

        //Computer controlled attributes
        int handValue;
        int baseBet;

    //Methods
    public:
        Player();
        ~Player();
        bool isFolded();
        void resetForRound();
        void dealt(Card[]);
        void putInMoney(int);

        //Saving and loading
        void savePlayer(int);
        void loadPlayer(int);

        //if the player is a user
        bool isUser(); //returns true if its a user
        void promptPlayer(int); //promts the player to make his move

        //if the player is computer controlled
        void setStats(bool, string);//isUser, name
        void getBestPlay(int,  vector<Card>); //calculate the next best play for the computer

    private:
        //Basic Poker Moves
        void check();
        void bet();
        void bet(int);
        void call(int);
        void fold();

        //Methods for the computer controlled player
        int calculateHandValue(); //used to calculate the computer's best play
        void executeNextPlay(int, int); //chooses what to do based on calculation and stats
        int checkMatching(vector<Card>);
        int checkStraightRange(vector<Card>);
        int checkFlush(vector<Card>);
        int checkWinningHand(vector<Card>);
        bool haveSuit(vector<Card>);
        bool haveStraight(vector<Card>);
};

#endif // PLAYER_H
