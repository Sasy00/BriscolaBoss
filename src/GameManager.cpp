#include "GameManager.h"
#include <cmath>
#include <ctime>
#include <iostream>
GameManager::GameManager(int nPlayers) : _nPlayers(nPlayers),
                                         _briscola(nullptr)
{
}
GameManager::~GameManager()
{
    delete _briscola;
}
void GameManager::init()
{
    srand(time(0));
    
    _deck.reset();
    _deck.shuffle();
    
    _briscola = new Card(_deck.draw());
    
    _hands.clear();
    for(int i = 0; i < _nPlayers; ++i)
    {
        _hands.push_back(std::vector<Card>());
    }
    
    _collected.clear();
    for(int i = 0; i < _nPlayers; ++i)
    {
        _collected.push_back(std::vector<Card>());
    }
    
    _playedCards.clear();
    
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < _nPlayers; ++j)
        {
            _hands[j].push_back(_deck.draw());
        }
    }
    _currentPlayer = rand() % _nPlayers;
}

void GameManager::update()
{
    draw();
    //getInput();
}

void GameManager::draw() const
{
    std::cout << "Cards in deck: " << _deck.size() << std::endl;
    for (int i = 0; i < _nPlayers; ++i)
    {
        std::cout << "Card in player " << i << "hand: ";
        for (auto it = _hands[i].begin(); it != _hands[i].end(); ++it)
        {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "Played Cards: ";
    for (auto it = _playedCards.begin(); it != _playedCards.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
