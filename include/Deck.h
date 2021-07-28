#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck
{
public:
    Deck();
    void reset();
    void shuffle();
    void draw(int n);
private:
    std::vector<Card *> _cards;
};

#endif