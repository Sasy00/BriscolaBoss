#ifndef CARD_H
#define CARD_H

class Card
{
public:
    Card(int id);
    Card(int suit, int rank);

    // 0 <= suit <= 3
    int getSuit() const { return id / 10; }
    // 1 <= rank <= 10
    int getRank() const { return (id % 10) + 1; }

private:
    // 0 <= _id <= 39
    const int _id;
};

#endif