#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck
{
public:
    Deck();
    /**
     * @brief resets the deck removing all old cards and recreating the entire deck
     */ 
    void reset();

    /**
     * @brief shuffles the deck
     */ 
    void shuffle();
    
    /**
     * @brief removes a card from the deck and returns a copy of that card
     */ 
    Card draw();
private:
    std::vector<Card> _cards;
};

#endif