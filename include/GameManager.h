#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Deck.h"

class GameManager
{
public:
    GameManager(int nPlayers);
    void init();
    void update();
private:
    void getInput();
    void draw();
    
    int _currentPlayer;
    int _nPlayers;
    Deck _deck;
    Card *_briscola;
    std::vector<std::vector<Card>> _hands;
    std::vector<std::vector<Card>> _collected;
    std::vector<Card> _playedCards;
};

#endif