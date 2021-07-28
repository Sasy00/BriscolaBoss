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

    delete _briscola;
    _briscola = new Card(_deck.draw());

    _hands.clear();
    for (int i = 0; i < _nPlayers; ++i)
    {
        _hands.push_back(std::vector<Card>());
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < _nPlayers; ++j)
        {
            _hands[j].push_back(_deck.draw());
        }
    }

    _collected.clear();
    for (int i = 0; i < _nPlayers; ++i)
    {
        _collected.push_back(std::vector<Card>());
    }

    for(auto it = _playedCards.begin(); it!= _playedCards.end(); ++it)
    {
        delete *it;
    }
    _playedCards.clear();
    for(int i = 0;  i < _nPlayers; ++i)
    {
        _playedCards.push_back(nullptr);
    }

    _currentPlayer = rand() % _nPlayers;
}

void GameManager::update()
{
    draw();
    getInput();
}

void GameManager::draw() const
{
    std::cout << "Cards in deck: " << _deck.size() << std::endl;
    for (int i = 0; i < _nPlayers; ++i)
    {
        std::cout << "Card in player " << i << " hand: ";
        for (auto it = _hands[i].begin(); it != _hands[i].end(); ++it)
        {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "Briscola: " << *_briscola << std::endl;
    std::cout << "Played Cards: ";
    for (auto it = _playedCards.begin(); it != _playedCards.end(); ++it)
    {
        if(*it)
            std::cout << *it << " ";
        else
            std::cout << "[ ] ";
    }
    std::cout << std::endl;
}

void GameManager::getInput()
{

    bool ok = false;
    while (!ok)
    {
        ok = true;
        std::cout << "Player " << _currentPlayer << ", select a card: ";
        std::cin >> _action;
        try
        {
            _hands[_currentPlayer].at(_action);
        }
        catch (std::out_of_range const &exc)
        {
            ok = false;
            std::cout << "Index not valid. Please insert a valid number." << std::endl;
        }
    }
}