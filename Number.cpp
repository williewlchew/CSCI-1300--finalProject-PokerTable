#include "Number.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Number::Number()
{
    index = 1;
    minimum = 0;
    maximum = 52;
}

Number::~Number()
{

}

void Number::setBounds(int minIn, int maxIn)
{
    minimum = minIn;
    maximum = maxIn;
}

void Number::updateIndex()
{
    if(index > 32)
        index = 2;
    else index++;
}

int Number::random()
{
    //get a random sequence
    string randDump = "";
    int ret = 0;
    //generate random number
    srand(index*time(NULL) + 5);
    int dumpdump = rand() % maximum - minimum;
    ret = dumpdump;
    //return the number
    updateIndex();
    return ret;
}

int Number::getLargest(int arr[], int amm)
{
    int largest = 0;
    for(int i = 0; i < amm; i++)
    {
        if(arr[i] > largest && arr[i] != 13)
        {
            largest = arr[i];
        }
    }
    return largest;
}

bool Number::arrContains(int arr[], int contains[])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            int temp = i + j;
            if(arr[temp] != contains[j])
            {
                break;
            }
            else if(j = 4)
            {
                return true;
            }
        }
    }
    return false;
}

void Number::sortCards(Card cardArr[]) //largest card is at 0
{
    int largest;
    int largestIndex;
    for(int i = 0; i < 6; i++)
    {
        largest = cardArr[i].getValue();
        for(int j = i; j < 7; j++)
        {
            if(cardArr[j].getValue() > largest)
            {
                largest = cardArr[j].getValue();
                largestIndex = j;
            }
        }

        //switch cards if largest card is bigger than the ith card
        if (largest > cardArr[i].getValue())
        {
            Card tempCard(cardArr[i].getSuit(),cardArr[i].getValue()); //stores card i as temp card
            //turn i into the largest
            cardArr[i].setSuit(cardArr[largestIndex].getSuit());
            cardArr[i].setValue(cardArr[largestIndex].getValue());
            //put i in this correct place
            cardArr[largestIndex].setSuit(tempCard.getSuit());
            cardArr[largestIndex].setValue(tempCard.getValue());
        }
    }
}

void Number::cardValToArray(Card cardArr[], int valArr[])
{
    for(int i = 0; i < 7; i++)
    {
        valArr[i] = cardArr[i].getValue();
    }
}

void Number::cardValToArray(Card cardArr[], int valArr[],int amm)
{
    for(int i = 0; i < amm; i++)
    {
        valArr[i] = cardArr[i].getValue();
    }
}
