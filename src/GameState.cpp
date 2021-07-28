#include "GameState.h"

GameState::GameState(
    const Deck &deck,
    const Card &briscola,
    const std::vector<Card> &p1Hand,
    const std::vector<Card> &p2Hand,
    const std::vector<Card> &p1Collected,
    const std::vector<Card> &p2Collected) : _deck(deck),
                                            _briscola(briscola),
                                            _p1Hand(p1Hand),
                                            _p2Hand(p2Hand),
                                            _p1Collected(p1Collected),
                                            _p2Collected(p2Collected)

{
}

int GameState::getPoints(int player) const
{
    int points = 0;
    if(player == 1)
    {
        for(auto it = _p1Collected.begin(); it != _p1Collected.end(); ++it)
        {
            points += it->getValue();
        }
    }
    if(player == 2)
    {
        for(auto it = _p2Collected.begin(); it != _p2Collected.end(); ++it)
        {
            points += it->getValue();
        }
    }
    return points;
}