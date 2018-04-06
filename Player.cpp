#include "Player.h"
#include "Number.h"
#include <fstream>

Player::Player()
{
    user = true;
    name = "";
    money = 5000;
    inPot = 0;
    blind = 0;
    folded = false;
    justBet = false;
}

Player::~Player()
{

}

//Saving and Loading
void Player::savePlayer(int index)
{
    ofstream fout;
    fout.open("playerSave.txt", ios::app);
    if(fout.fail())
    {
        cout << endl << "Game cannot be saved/loaded at this moment. Missing an important file." << endl;
    }
    else
    {
        //save the player's money, hand, inpot
        fout << "p" << to_string(index) << "\n";
        fout << to_string(money) << "\n";
        fout << hand[0].getSuit() << "-" << hand[0].getValue() << "\n";
        fout << hand[1].getSuit() << "-" << hand[1].getValue() << "\n";
        fout << to_string(inPot) << "\n";
    }
}

void Player::loadPlayer(int index)
{
    ifstream fin;
    fin.open("playerSave.txt");
    if(fin.fail())
    {
        cout << endl << "Game cannot be saved/loaded at this moment. Missing an important file." << endl;
    }
    else
    {
        string dump = "";
        getline(fin,dump);

        while(fin.eof()) //find the right player to load
        {
            if(dump[0] == 'p')
            {
               if(index == stoi(dump.substr(1,1)))
               {
                   break;
               }
            }
            getline(fin,dump);
        }

        //money
        getline(fin,dump);
        money = stoi(dump);
        //hand 1
        int s = 0;
        int v = 0;
        getline(fin,dump);
        for(int i = 0; i < dump.length(); i++)
        {
            if(dump[i] == '-')
            {
                s = stoi(dump.substr(0,1));
                v = stoi(dump.substr(i+1));
            }
        }
        hand[0].setSuit(s);
        hand[0].setValue(v);
        //hand 2
        getline(fin,dump);
        for(int i = 0; i < dump.length(); i++)
        {
            if(dump[i] == '-')
            {
                s = stoi(dump.substr(0,1));
                v = stoi(dump.substr(i+1));
            }
        }
        hand[1].setSuit(s);
        hand[1].setValue(v);
        //inPot
        getline(fin,dump);
        inPot = stoi(dump);
    }
}

//Game Methods
void Player::resetForRound()
{
    inPot = 0;
    folded = false;

    //computer specific
    handValue = 0;

}

bool Player::isFolded()
{
    return folded;
}

void Player::dealt(Card dealtCards[])
{
    hand[0].setSuit(dealtCards[0].getSuit());
    hand[0].setValue(dealtCards[0].getValue());
    hand[1].setSuit(dealtCards[1].getSuit());
    hand[1].setValue(dealtCards[1].getValue());
}

void Player::putInMoney(int amount)
{
    if(amount <= money)
    {
        money -= amount;
        inPot += amount;
    }
    else
    {
        inPot += money;
        money = 0;
    }
}

void Player::setStats(bool isUser, string nameIn)
{
    //basic data
    user = isUser;
    name = nameIn;

    //game
    folded = false;
    blind = 0;

    //non-user
    handValue = 0;
}

//User specific
void Player::promptPlayer(int ante)
{
    if(justBet)
    {
        justBet = false;
    }
    else
    {
        //Output Prompt
        cout << "You have " << money << " to play with. " << "You have " << inPot << " in the pot" << endl;
        cout << "You were dealt : " << hand[0].displayCard() << " " << hand[1].displayCard() << endl;
        cout << "Type in what would you like to do: ";
        if (inPot == ante)
        {
            cout << "check, ";
        }
        if(ante - inPot < money )
        {
            cout << "bet, call, ";
        }

        cout << "fold, help, exit.  " ;

        //Process request
        string input = ""; getline(cin, input);

        for(int i = 0; i < input.length(); i++)
        {
            if(input[i] == ' ')
                input = input.substr(0,i);
        }

        if(input == "check")
        {
            if(inPot != ante)
            {
                cout << "You cannot check right now..." << endl;
                promptPlayer(ante);
            }
            else check();
        }
        else if(input == "call")
            call(ante);
        else if(input == "bet")
            bet();
        else if(input == "fold")
            fold();
        else if(input == "help")
            inPot += 700000;
        else if(input == "exit")
        {
            cout << "Saving and exiting the game";
            inPot += 800000;
        }
        else
        {
            cout << "Cannot request your input... ";
            promptPlayer(ante);
        }
    }
}

//Computer specific
/**
    0 check
    1 call
    2 raise
    3 fold
*/
void Player::executeNextPlay(int play, int ante)
{
    if(play == 0)
    {
        cout << "Conrad checks.";
        check();
    }

    else if(play == 1)
    {
        cout << "Conrad calls.";
        call(ante);
    }

    else if(play == 2)
    {
        cout << "Conrad raises by " << baseBet << ".";
        bet(baseBet);
    }

    else if(play == 3)
    {
        cout << "Conrad folds.";
        fold();
    }

    else cout << "ERROR";
    cout << endl;
}

void Player::getBestPlay(int ante, vector<Card> flop)
{
    /** Algorithm
    judge hand
        pre flop
            same card; card values + 12
            in straight range; card values + 5
            same suit; card values + 3
            if value is less than 15, fold
            how close am i to making a hand
                closer the hand, the higher the value
            raise if hand value is more than 30
        flop
            raise if has a winning hand
            else if close, call/check (pairs, outs)
    raising
        percentage of raise based on a certain percent
    */
    Number num;
    handValue = checkMatching(flop) + checkStraightRange(flop) + checkFlush(flop);

    if(justBet)
    {
        justBet = false;
    }

    else
    {
        if(hand[0].getValue() >= 9 || hand[1].getValue() >= 9 )
            handValue += 2;

        if(flop.size() == 0) //pre flop
        {
            baseBet = ante;
            if(handValue < 3)
            {
                executeNextPlay(3, ante);
            }

            else if(handValue >= 4 && handValue < 12)
            {
                if(inPot < ante)
                {
                    executeNextPlay(1, ante);
                }

                if(handValue > 5)
                {
                    num.setBounds(0,100);
                    int random = num.random();
                    if(random < 25)
                        executeNextPlay(2, ante);
                }
                else executeNextPlay(0, ante);
            }

            else if(handValue >= 12)
            {
                num.setBounds(0,100);
                int random = num.random();

                if(random <= 75)
                {
                    executeNextPlay(2, ante);
                }

                else
                {
                    if(inPot < ante)
                    {
                        executeNextPlay(1, ante);
                    }
                    else executeNextPlay(0, ante);
                }
            }
        }

        else if(flop.size() == 3)
        {
            baseBet = ante/2;

            if(checkWinningHand(flop) > 0)
            {
                executeNextPlay(2, ante);
            }

            else if(handValue <= 5)
            {
                if(ante == inPot) //hand value too low
                {
                    executeNextPlay(0,ante);
                }
                else executeNextPlay(3,ante);
            }

            else if(handValue > 5 && handValue <= 15) //in range to stay
            {
                if(inPot < ante)
                {
                    executeNextPlay(1, ante);
                }
                else executeNextPlay(0, ante);
            }

            else if(handValue > 15)
            {
                num.setBounds(0,100);
                int random = num.random();

                if(random <= 75)
                {
                    executeNextPlay(2, ante);
                }

                else if(inPot < ante)
                {
                    executeNextPlay(1, ante);
                }
                else executeNextPlay(0, ante);
            }
        }

        else if(flop.size() == 4)
        {
            baseBet = ante/2;

            if(checkWinningHand(flop) > 0)
            {
                executeNextPlay(2, ante);
            }

            else if(handValue <= 12)
            {
                if(ante - inPot > 50) //hand value too low
                {
                    if(ante == inPot)
                        executeNextPlay(0,ante);
                    else executeNextPlay(1, ante);
                }
                else executeNextPlay(3,ante);
            }

            else if(handValue > 12 && handValue < 16) //in range to stay
            {
                if(inPot < ante)
                {
                    executeNextPlay(1, ante);
                }
                else executeNextPlay(0, ante);
            }

            else if(handValue >= 16 && handValue <= 20) //somewhat good hand
            {
                num.setBounds(0,100);
                int random = num.random();

                if(random <= 15)
                {
                    executeNextPlay(2, ante);
                }

                else if(inPot < ante)
                {
                    executeNextPlay(1, ante);
                }
                else executeNextPlay(0, ante);
            }

            else if(handValue > 20) //great hand
            {
                num.setBounds(0,100);
                int random = num.random();

                if(random <= 50)
                {
                    executeNextPlay(2, ante);
                }

                else if(inPot < ante)
                {
                    executeNextPlay(1, ante);
                }
                else executeNextPlay(0, ante);
            }
        }

        else
        {
            baseBet = ante;
            if(checkWinningHand(flop) == 0)
            {
                if(ante - inPot < 100) //hand value too low
                {
                    if(ante == inPot)
                        executeNextPlay(0,ante);
                    else executeNextPlay(1, ante);
                }
                else executeNextPlay(3,ante);
            }

            else if(checkWinningHand(flop) == 1)
            {
                num.setBounds(0,100);
                int random = num.random();

                if(hand[0].getValue() > 8 || hand[1].getValue() > 8)
                {
                    executeNextPlay(2, ante);
                }

                else if(random < 65)
                {
                    executeNextPlay(2, ante);
                }
            }

            else if(checkWinningHand(flop) == 2)
            {
                num.setBounds(0,100);
                int random = num.random();

                if(random <= 75)
                {
                    executeNextPlay(2, ante);
                }
            }

            else if(checkWinningHand(flop) >= 3)
            {
                baseBet = ante * 2;
                executeNextPlay(2, ante);
            }
        }
    }
}

//helper methods
int Player::checkMatching(vector<Card> flop)
{
    /**
        return the matching int
        0 if no matching
    */
    int ret = 0;

    if(flop.size() == 0) //preflop
    {
         if(hand[0].getValue() == hand[1].getValue())
         {
             ret += 12;
         }
    }

    else if(flop.size() == 3)
    {
        for(int i = 0; i < 3; i++)
        {
            if(hand[0].getValue() == flop[i].getValue())
            {
                ret += 12;
            }

            else if(hand[1].getValue() == flop[i].getValue())
            {
                ret += 12;
            }
        }
    }

    else if(flop.size() == 4)
    {
        if(hand[0].getValue() == flop[3].getValue() || hand[1].getValue() == flop[3].getValue() )
        {
            ret += 12;
        }
    }

    else if(flop.size() == 5)
    {
        if(hand[0].getValue() == flop[4].getValue() || hand[1].getValue() == flop[4].getValue())
        {
            ret += 12;
        }
    }

    return ret;
}

int Player::checkStraightRange(vector<Card> flop)
{
    /**
        return 5 if in range
    */
    int ret = 0;

    if(flop.size() == 0)
    {
        if(abs(hand[0].getValue() - hand[1].getValue()) <= 4)
        {
            ret += 5;
        }
    }

    else if(flop.size() >= 3)
    {
        int between = abs(hand[0].getValue() - hand[1].getValue());
        if(between <= 4 && between > 0)
        {
            int bigger, smaller;
            if(hand[0].getValue() > hand[1].getValue())
            {
                bigger = hand[0].getValue();
                smaller = hand[1].getValue();
            }
            else
            {
                bigger = hand[1].getValue();
                smaller = hand[0].getValue();
            }


            for(int i = 0; i < flop.size(); i++)
            {
                if(flop[i].getValue() < bigger && flop[i].getValue() > smaller)
                {
                    handValue += 5;
                }

                else if(flop[i].getValue() >= smaller - (4 - between))
                {
                    handValue += 5;
                }

                else if(flop[i].getValue() <= bigger + (4 - between))
                {
                    handValue += 5;
                }
            }
        }
    }
}

int Player::checkFlush(vector<Card> flop)
{
    /**
        return 4 if in range
    */
    int ret = 0;

    if(flop.size() == 0) //preflop
    {
         if(hand[0].getSuit() == hand[1].getSuit())
         {
             ret += 4;
         }
    }

    else if(flop.size() >= 3)
    {
        int card1Match = 0;
        int card2Match = 0;

        for(int i = 0; i < 3; i++)
        {
            if(hand[0].getSuit() == flop[i].getSuit())
            {
                ret += 4;
                card1Match++;
            }

            else if(hand[1].getSuit() == flop[i].getSuit())
            {
                ret += 4;
                card2Match++;
            }
        }
        if(abs(card1Match - card2Match) <= 1)
        {
           ret -= 3;
        }
    }

    else if(flop.size() == 4)
    {
        if(hand[0].getSuit() == flop[3].getSuit() || hand[1].getSuit() == flop[3].getSuit() )
        {
            ret += 3;
        }

        int card1Match = 0;
        int card2Match = 0;

        for(int i = 0; i < 3; i++)
        {
            if(hand[0].getSuit() == flop[i].getSuit())
            {
                card1Match++;
            }

            else if(hand[1].getSuit() == flop[i].getSuit())
            {
                card2Match++;
            }
        }

        if(abs(card1Match - card2Match) <= 1)
        {
           ret -= 3;
        }
    }
    return ret;
}

int Player::checkWinningHand(vector<Card> flop)
{
    /**
    high card 0
    pair 1
    two pair/trips 2
    straight 3
    flush 4
    full/fours 5
    straight flush 6
    */

    int winning = 0;
    int testCase;

    testCase = checkMatching(flop);
    if(testCase > 0)
    {
        if(testCase == 12)
        {
            winning = 1;
        }

        else if(testCase == 24)
        {
            winning = 2;
        }

        else if(testCase > 24)
        {
            winning = 5;
        }
    }

    vector<Card> cards(flop);
    cards.push_back(hand[0]); cards.push_back(hand[1]);
    if(haveSuit(cards) && winning < 5)
    {
        winning = 4;
    }

    if(haveStraight(cards) && winning < 5)
    {
        winning = 3;
    }

    if(haveSuit(cards) && haveStraight(cards))
    {
        winning = 6;
    }

    return winning;
}

bool Player::haveSuit(vector<Card> cards)
{
    Number num;
    int c = 0; int d = 0; int h = 0; int s = 0;
    //tally suits
    for(int i = 0; i < cards.size(); i++)
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
        return true;
    }
    else return false;
}

bool Player::haveStraight(vector<Card> cards)
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
                    return true;
                }
            }
            else break;
        }
    }
    //special case
    if(cards[0].getValue() == 13 && cards[6].getValue() == 2 && cards[5].getValue() == 3 && cards[4].getValue() == 4 && cards[3].getValue() == 5)
    {
        return true;
    }
    return false;
}

//Game Controls
void Player::check()
{

}


void Player::bet()
{
    cout << "How much money would you like to bet? ";
    string dump = ""; getline(cin,dump); int temp = stoi(dump.substr(0,8));
    if(temp <= money && temp > 0)
    {
        putInMoney(temp);
        justBet = true;
    }

    else
    {
        cout << "You cannot bet that amount, enter another value";
        bet();
    }
}

void Player::bet(int amm)
{
    putInMoney(amm);
    justBet = true;
}

void Player::call(int ante)
{
    putInMoney(ante - inPot);
}

void Player::fold()
{
    folded = true;
}
