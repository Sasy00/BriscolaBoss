#include "GameManager.h"
#include <cmath>
#include <ctime>
GameManager::GameManager(int nPlayers) : _nPlayers(nPlayers),
                                         _briscola(nullptr)
{

}

void GameManager::init()
{
    srand(time(0));
    _deck.reset();
    _deck.shuffle();
    _briscola = new Card(_deck.draw());
    _hands.clear();
    _collected.clear();
    _playedCards.clear();
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < _nPlayers; ++j)
        {
            _hands[j].push_back(_deck.draw());
        }
    }
    _currentPlayer = rand() % _nPlayers;
}
