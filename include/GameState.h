#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Deck.h"

class GameState
{
private:
    Deck _deck;
    Card _briscola;
    std::vector<Card> _p1Hand;
    std::vector<Card> _p2Hand;

    std::vector<Card> _p1Collected;
    std::vector<Card> _p2Collected;

public:
    GameState(
        const Deck &deck, 
        const Card &briscola, 
        const std::vector<Card> &p1Hand, 
        const std::vector<Card> &p2Hand,
        const std::vector<Card> &p1Collected,
        const std::vector<Card> &p2Collected);

    int getPoints(int player) const;
};

#endif