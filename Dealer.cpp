#include "Dealer.h"
#include "Number.h"
#include "Card.h"
#include "Player.h"
#include <fstream>

Dealer::Dealer()
{
    players[0].setStats(true, "user");
    players[1].setStats(false, "Conrad");
    bigBlind = 50;
    roundWinner = -1;
}

Dealer::~Dealer()
{
    //dtor
}

//Controlling the game
void Dealer::startGame()
{
    do
    {
        startRound();
        midRound();
    }while(players[0].money > 0 && players[1].money > 0);
}


void Dealer::loadGame()//loads the previous game
{
    cout << endl << "*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;
    ifstream fin;
    fin.open("dealerSave.txt");
    if(fin.fail())
    {
        cout << endl << "Game cannot be saved/loaded at this moment. Missing an important file." << endl;
    }
    else
    {
        int part = 0;
        while(!fin.eof())
        {
            string dump = "";
            getline(fin,dump);

            if(part == 0)
            {
                if(dump == "flop")
                {
                    part++;
                }
                else
                {
                    ante = stoi(dump);
                }
            }

            else if(part == 1)
            {
                if(dump == "deck")
                {
                    part++;
                }
                else
                {
                    int s = 0;
                    int v = 0;
                    for(int i = 0; i < dump.length(); i++)
                    {
                        if(dump[i] == '-')
                        {
                            s = stoi(dump.substr(0,1));
                            v = stoi(dump.substr(i+1));
                        }
                    }
                    Card newCard(s,v);
                    flop.push_back(newCard);
                }
            }

            else if(part == 2)
            {
                int s = 0;
                int v = 0;
                for(int i = 0; i < dump.length(); i++)
                {
                    if(dump[i] == '-')
                    {
                        s = stoi(dump.substr(0,1));
                        v = stoi(dump.substr(i+1));
                    }
                }
                Card newCard(s,v);
                deck.deck.push_back(newCard);
            }
        }
        players[0].loadPlayer(0);
        players[1].loadPlayer(1);

    }
    deck.takeCard();
    //resume from last save

    if(flop.size() == 0)
    {
        do
        {
            processMidRound();
        }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));

        //flop
        if(roundWinner == -1)
        {
            turnCard(3);
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }

        if(roundWinner == -1)
        {
            turnCard();
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }

        if(roundWinner == -1)
        {
            turnCard();
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << " " << flop[4].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }
    }

    else if(flop.size() == 3)
    {
        cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << endl;
        do
        {
            processMidRound();
        }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));

        if(roundWinner == -1)
        {
            turnCard();
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }

        if(roundWinner == -1)
        {
            turnCard();
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << " " << flop[4].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }
    }

    else if(flop.size() == 4)
    {

        if(roundWinner == -1)
        {
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }

        if(roundWinner == -1)
        {
            turnCard();
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << " " << flop[4].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }
    }

    else if(flop.size() == 5)
    {
        if(roundWinner == -1)
        {
            cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << " " << flop[4].displayCard() << endl;
            do
            {
                processMidRound();
            }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
        }
    }

    Card endr(-2,-2);
    flop.push_back(endr);
    endRound();
    startGame();
}

void Dealer::exitGame() //save and exit the game
{
    //return numbers to usual
    players[0].inPot -= 800000;
    ante -= 800000;

    ofstream fout;
    fout.open("dealerSave.txt");
    if(fout.fail())
    {
        cout << endl << "Game cannot be saved/loaded at this moment. Missing an important file." << endl;
    }
    else
    {
        //save the ante, flop, and deck
        //save flop
        fout << "flop\n";
        for(int i = 0; i < flop.size(); i++)
        {
            fout << "" << flop[i].getSuit() << "-" << flop[i].getValue() << endl;
        }
        //save deck
        fout << "deck\n";
        for(int i = deck.deck.size() - 1 ; i > 0 ; i--)
        {
            fout << "" << deck.deck[i].getSuit() << "-" << deck.deck[i].getValue() << endl;
        }
        //save players
        //wipe player file
        fout.close();
        fout.open("playerSave.txt", ios::trunc);
        fout << "";
        fout.close();
        players[0].savePlayer(0);
        players[1].savePlayer(1);
    }

    exit(0);
}
//start round
void Dealer::startRound()
{
    flop.clear();
    ante = 0;
    players[0].resetForRound();
    players[1].resetForRound();
    deck.newDeck();
    deck.shuffle();
    moveBlinds();
    dealCard(players[1]);
    dealCard(players[0]);
    roundWinner = -1;
    cout << endl << "*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;
}

//mid round
void Dealer::midRound()
{
    //Output to user
    if(players[0].blind == 2)
        cout << "You are the big blind! " << endl;
    else cout << "You are the little blind. " << endl;

    //Mid Round methods
    do
    {
        processMidRound();
    }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
    //flop

    if(roundWinner == -1)
    {
        turnCard(3);
        cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << endl;
        do
        {
            processMidRound();
        }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
    }

    if(roundWinner == -1)
    {
        turnCard();
        cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << endl;
        do
        {
            if(pot > 0)
                processMidRound();
        }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
    }

    if(roundWinner == -1)
    {
        turnCard();
        cout << endl << "The cards on the table are : " << flop[0].displayCard() << " " << flop[1].displayCard() << " " << flop[2].displayCard() << " " << flop[3].displayCard() << " " << flop[4].displayCard() << endl;
        do
        {
            if(pot > 0)
                processMidRound();
        }while(!(players[0].inPot == ante && players[1].inPot == ante) && !(players[0].isFolded() || players[1].isFolded()));
    }

    Card endr(-2,-2);
    flop.push_back(endr);
    endRound();
}

//helpers for mid round
void Dealer::processMidRound()
{
    pot = players[0].inPot + players[1].inPot;
    if(players[0].blind == 1)
    {
        cout << "The pot is " << pot << ". ";
        players[0].promptPlayer(ante);
        pot = players[0].inPot + players[1].inPot; ante = players[0].inPot;
        processMenu();
        endRound();

        if(pot > 0)
        {
            players[1].getBestPlay(ante, flop);
            pot = players[0].inPot + players[1].inPot; ante = players[1].inPot;
            endRound();
        }
    }
    else
    {
        cout << "The pot is " << pot << ". ";
        players[1].getBestPlay(ante, flop);
        pot = players[0].inPot + players[1].inPot; ante = players[1].inPot;
        endRound();

        if(pot > 0)
        {
            cout << "The pot is " << pot << ". ";
            players[0].promptPlayer(ante);
            pot = players[0].inPot + players[1].inPot; ante = players[0].inPot;
            processMenu();
            endRound();
        }
    }
}

void Dealer::processMenu()
{
    if (ante > 700000 && ante < 800000)
        processHelp();
    else if(ante >= 800000)
        exitGame();
}

void Dealer::processHelp()
{
    //output helpful information
    cout << "Clubs < Diamonds < Hearts < Spades" << endl << endl;
    //return numbers to usual
    players[0].inPot -= 700000;
    ante -= 700000;
    players[0].promptPlayer(ante);

}

void Dealer::turnCard()
{
    flop.push_back(deck.takeCard());
}

void Dealer::turnCard(int amount)
{
    for(int i = 0; i < amount; i++)
    {
        flop.push_back(deck.takeCard());
    }
}

void Dealer::moveBlinds()
{
    ante = bigBlind;
    if(players[0].blind == 1 || players[0].blind == 0)
    {
        players[0].blind = 2;
        players[1].blind = 1;

        players[0].putInMoney(bigBlind);
        players[1].putInMoney(bigBlind/2);
    }

    else if(players[0].blind == 2)
    {
        players[1].blind = 2;
        players[0].blind = 1;

        players[1].putInMoney(bigBlind);
        players[0].putInMoney(bigBlind/2);
    }
}

void Dealer::dealCard(Player &p)
{
    Card dealHand[2];
    dealHand[0] = deck.takeCard();
    dealHand[1] = deck.takeCard();
    p.dealt(dealHand);
}

//End round
void Dealer::endRound()
{
    roundWinner = findWinner();

    //give money
    if(roundWinner > -1)
    {
        players[roundWinner].money += pot;
        pot = 0;
        cout << endl;
    }
}

//Helper functions for endRound
int Dealer::findWinner()
{
    int winner = -1;
    /**
        -1 no one
        0 player
        1 computer
        2 draw
    */

    if(players[0].isFolded())
    {
        winner = 1;
        cout << "Conrad wins because you folded!" << endl;
    }
    else if(players[1].isFolded())
    {
        winner = 0;
        cout << "You won because Conrad folded!" << endl;
    }
    else if(flop.size() == 6)
    {
        bool haveWinner = false;
        while(!haveWinner)
        {
            haveWinner = testRoyalFlush(winner);
            if(haveWinner)
                break;
            haveWinner = testStraightFlush(winner);
            if(haveWinner)
                break;
            haveWinner = testFours(winner);
            if(haveWinner)
                break;
            haveWinner = testFullHouse(winner);
            if(haveWinner)
                break;
            haveWinner = testFlush(winner);
            if(haveWinner)
                break;
            haveWinner = testStraight(winner);
            if(haveWinner)
                break;
            haveWinner = testTrips(winner);
            if(haveWinner)
                break;
            haveWinner = testTwoPair(winner);
            if(haveWinner)
                break;
            haveWinner = testPair(winner);
            if(haveWinner)
                break;
            haveWinner = testHighCard(winner);
        }
    }
    return winner;
}

bool Dealer::testHighCard(int &winIn)
{
    Number num;
    int playerKickers[2];

    for(int i = 0; i < 2; i++)
    {
        int hand[2];
        num.cardValToArray(players[i].hand, hand);
        playerKickers[i] = num.getLargest(hand, 2);
    }

    //get largest
    int flopVals[5] = {flop[0].getValue(), flop[1].getValue(), flop[2].getValue(), flop[3].getValue(), flop[4].getValue()};
    int largest = num.getLargest(flopVals,5);

    if(playerKickers[0] > playerKickers[1] && largest < playerKickers[0])
    {
        winIn = 0;
        cout << "You won from a high card!";
    }
    else if(playerKickers[1] > playerKickers[0] && largest < playerKickers[1])
    {
        winIn = 1;
        cout << "Conrad wins from a high card!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
    }
    else
    {
        winIn = 2;
        cout << "No one wins, split pot!";
    }
    return true;
}

bool Dealer::testPair(int &winIn)
{
    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testMatch(cards, 2, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a pair!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a pair!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testTwoPair(int &winIn)
{
    //true if test match's val.size is <= 5
    Number num;
    vector<int> val;
    vector<int> counts;
    bool retBool = false;
    int playerKickers[2];

    for(int p = 0; p < 2; p++)
    {
        Card cards[7];
        fillTestSelection(cards, p);
        num.sortCards(cards);
        //record cards[]
        for(int i = 0; i < 7; i++)
        {
            int index = -1;
            //find the value in the vectors
            for(int j = 0; j < val.size(); j++)
            {
                if(val[j] == cards[i].getValue())
                {
                    index = j;
                }
            }

            //record value
            if(index > -1)
            {
                counts[index] += 1;
            }
            else
            {
                val.push_back(cards[i].getValue());
                counts.push_back(1);
            }
        }

        //process information
        int largestVal = 0;
        for(int i = 0; i < counts.size(); i++)
        {
            if(val.size() <= 5)
            {
                if(winIn == -1)
                    winIn = p;
                else winIn = 2;

                //record kicker
                for(int k = 0; k < val.size(); k++)
                {
                    if(counts[k] == 2 && val[k] > largestVal)
                    {
                        largestVal = val[k];
                    }
                }
                retBool = true;
            }
        }

        //process kicker
        if(largestVal > playerKickers[p])
        {
            playerKickers[p] = largestVal;
        }
    }

    if(retBool)
    {
        //output and return
        if(winIn > -1)
        {
            if(winIn == 0)
            {
                cout << "You won from a two pair!";
            }
            else if(winIn == 1)
            {
                cout << "Conrad wins from a two pair!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
            }
            else
            {
                winIn = 2;
                cout << "No one wins, split pot!";
            }
            return true;
        }
    }
    else return retBool;
}

bool Dealer::testTrips(int &winIn) //tests for matching values
{

    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testMatch(cards, 3, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a three pair!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a three pair!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testStraight(int &winIn)
{
    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testStraight(cards, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a straight!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a straight!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testFlush(int &winIn)
{
    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testSuit(cards, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a flush!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a flush!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testFullHouse(int &winIn)
{

    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testMatch(cards, 3, playerKickers[i]) && testMatch(cards, 2, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a full house!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a full house!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testFours(int &winIn)
{
    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testMatch(cards, 4, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a four pair!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a four pair!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testStraightFlush(int &winIn)
{
    Number num;
    int playerKickers[2];

    //test case
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testSuit(cards, playerKickers[i]) && testStraight(cards, playerKickers[i]))
        {
            if(winIn == -1)
            {
                winIn = i;
            }
            else
            {
                winIn = 2;
            }
        }
    }

    //settle ties
    if(winIn == 2)
    {
        //compare kickers
        if(playerKickers[0] > playerKickers[1])
            winIn = 0;
        else if(playerKickers[1] > playerKickers[0])
            winIn = 1;
        else winIn = 2;
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a straight flush!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a straight flush!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }
    else return false;
}

bool Dealer::testRoyalFlush(int &winIn) //A, K, Q, J, 10, all the same suit.
{
    Number num;
    int playerKickers[2];
    bool retBool = false;
    for(int i = 0; i < 2; i++)
    {
        Card cards[7];
        fillTestSelection(cards, i);
        num.sortCards(cards);
        if(testSuit(cards, playerKickers[i]) && testStraight(cards, playerKickers[i]))
        {
            if(cards[6].getValue() == 9) //test if there is a 10 in the straight
            {
                if(winIn == -1)
                {
                    winIn = i;
                }
                else winIn = 2;
                retBool = true;
            }
        }
    }

    //output and return
    if(winIn > -1)
    {
        if(winIn == 0)
        {
            cout << "You won from a royal flush!";
        }
        else if(winIn == 1)
        {
            cout << "Conrad wins from a royal flush!" << players[1].hand[0].displayCard() << players[1].hand[1].displayCard();
        }
        else
        {
            winIn = 2;
            cout << "No one wins, split pot!";
        }
        return true;
    }

    return false;
}

bool Dealer::testMatch(Card cards[], int amount, int &kick)
{
    vector<int> val;
    vector<int> counts;

    //record cards[]
    for(int i = 0; i < 7; i++)
    {
        int index = -1;
        //find the value in the vectors
        for(int j = 0; j < val.size(); j++)
        {
            if(val[j] == cards[i].getValue())
            {
                index = j;
            }
        }

        //record value
        if(index > -1)
        {
            counts[index] += 1;
        }
        else
        {
            val.push_back(cards[i].getValue());
            counts.push_back(1);
        }
    }

    //process information
    bool retBool = false;
    int largestVal = 0;
    for(int i = 0; i < counts.size(); i++)
    {
        if(counts[i] == amount)
        {
            //record kicker
            if(val[i] > largestVal)
            {
                largestVal = val[i];
            }
            retBool = true;
        }
    }

    //process kicker
    if(largestVal > kick)
    {
        kick = largestVal;
    }
    return retBool;
}

bool Dealer::testSuit(Card cards[], int &kick)
{
    Number num;
    int c = 0; int d = 0; int h = 0; int s = 0;
    //tally suits
    for(int i = 0; i < 7; i++)
    {
        int temp = cards[i].getSuit();

        if(temp == 0)
            c++;
        else if(temp == 1)
            d++;
        else if(temp == 2)
            h++;
        else if(temp == 3)
            s++;
    }
    //process tally
    if(c >= 5 || d >= 5 || h >= 5 || s >= 5)
    {
        int cardVals[7];
        num.cardValToArray(cards, cardVals);
        kick = num.getLargest(cardVals, 7);
        return true;
    }
    else return false;
}

bool Dealer::testStraight(Card cards[], int &kick)
{
    //get the smallest three values and count up
    int lastVal;
    for(int i = 0; i < 3; i++)
    {
        lastVal = cards[i].getValue() + 1;
        for(int j = 0; j < 5; j++)
        {
            if(cards[i+j].getValue() == lastVal - 1)
            {
                lastVal--;
                if(j == 4)
                {
                    kick = cards[i].getValue();
                    return true;
                }
            }
            else break;
        }
    }
    //special case
    if(cards[0].getValue() == 13 && cards[6].getValue() == 2 && cards[5].getValue() == 3 && cards[4].getValue() == 4 && cards[3].getValue() == 5)
    {
        kick = 4;
        return true;
    }
    return false;
}

void Dealer::fillTestSelection(Card cards[], int playerIndex)
{
    //Get flop
    for(int i = 0 ; i < 5; i++)
    {
        cards[i].setSuit(flop[i].getSuit());
        cards[i].setValue(flop[i].getValue());
    }
    //Get hand
    cards[5].setSuit(players[playerIndex].hand[0].getSuit());
    cards[5].setValue(players[playerIndex].hand[0].getValue());
    cards[6].setSuit(players[playerIndex].hand[1].getSuit());
    cards[6].setValue(players[playerIndex].hand[1].getValue());
}

//testing
void  Dealer::testTestCases()
{
    Number num;
    Card testSelection[7];
    testSelection[0].setSuit(0); testSelection[0].setValue(3);
    testSelection[1].setSuit(2); testSelection[1].setValue(9);
    testSelection[2].setSuit(0); testSelection[2].setValue(10);
    testSelection[3].setSuit(2); testSelection[3].setValue(11);
    testSelection[4].setSuit(2); testSelection[4].setValue(13);
    testSelection[5].setSuit(2); testSelection[5].setValue(12);
    testSelection[6].setSuit(2); testSelection[6].setValue(1);

    Card testSelection2[7];
    testSelection2[0].setSuit(3); testSelection2[0].setValue(8);
    testSelection2[1].setSuit(1); testSelection2[1].setValue(6);
    testSelection2[2].setSuit(2); testSelection2[2].setValue(5);
    testSelection2[3].setSuit(0); testSelection2[3].setValue(5);
    testSelection2[4].setSuit(0); testSelection2[4].setValue(7);
    testSelection2[5].setSuit(0); testSelection2[5].setValue(12);
    testSelection2[6].setSuit(3); testSelection2[6].setValue(5);

    ///CASE 1
    ///test sort
    num.sortCards(testSelection);
    cout << "Sort Testing 1 :";
    for (int i = 0; i < 7; i++)
    {
        cout << testSelection[i].displayCard();
    }
    cout << endl;

    int kick;
    ///test suit case
    kick = 0;
    cout << "Suit test case 1 :" << testSuit(testSelection, kick) << " With the kicker being : ";
    cout << kick << endl;

    ///test strait case
    kick = 0;
    cout << "Srait test case 1 :" << testStraight(testSelection, kick) << " With the kicker being : "; //<< kick1 << endl;
    cout << kick << endl;

    ///test pair case
    kick = 0;
    cout << "Pair test case 1 :" << testMatch(testSelection, 2 , kick) << " With the kicker being : ";
    cout << kick << endl;

    ///CASE 2
    ///test sort
    num.sortCards(testSelection2);
    kick = 0;
    cout << "Sort Testing 2 :";
    for (int i = 0; i < 7; i++)
    {
        cout << testSelection2[i].displayCard();
    }
    cout << endl;

    ///test suit case
    kick = 0;
    cout << "Suit test case 2 : " << testSuit(testSelection2, kick) << " With the kicker being : ";
    cout << kick << endl;

    ///test strait case
    kick = 0;
    cout << "Srait test case 2 : " << testStraight(testSelection2, kick) << " With the kicker being : ";
    cout << kick << endl;

    ///test pair case
    kick = 0;
    cout << "Pair test case 2 : " << testMatch(testSelection2, 3, kick) << " With the kicker being : ";
    cout << kick << endl;
}
