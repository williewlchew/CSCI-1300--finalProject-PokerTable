#ifndef NUMBER_H
#define NUMBER_H
#include "Card.h"

class Number
{
    public:
        Number();
        ~Number();
        //random number generator
        void setBounds(int, int);
        int random();
        //number comparison
        bool arrContains(int[], int[]);
        int getLargest(int[], int);
        //utilities
        void sortCards(Card[]);
        void cardValToArray(Card[],int[]);
        void cardValToArray(Card[],int[],int);

    private:
        void updateIndex();


    private:
        int index;
        int minimum;
        int maximum;
};

#endif // NUMBER_H
