#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Deck.h"
#include <string>
class GameManager
{
public:
    GameManager(int nPlayers);
    void init();
    bool update();
    ~GameManager();
private:
    void getInput();
    void draw() const;

    int _currentPlayer;
    int _nPlayers;
    Deck _deck;
    Card *_briscola;
    std::vector<std::vector<Card>> _hands;
    std::vector<std::vector<Card>> _collected;
    std::vector<Card *> _playedCards;

    int _action;
};

#endif