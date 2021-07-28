#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card
{
    friend std::ostream &operator<<(std::ostream& os, Card c);
public:
    Card(int id);
    Card(int suit, int rank);

    // 0 <= suit <= 3
    int getSuit() const { return _id / 10; }
    // 1 <= rank <= 10
    int getRank() const { return (_id % 10) + 1; }
    //
    int getValue() const;
private:
    // 0 <= _id <= 39
    int _id;
};
std::ostream &operator<<(std::ostream& os, Card c);
#endif