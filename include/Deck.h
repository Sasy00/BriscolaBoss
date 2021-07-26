#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck
{
public:
    Deck();
private:
    std::vector<Card *> _cards;
};

#endif