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

    for (auto it = _playedCards.begin(); it != _playedCards.end(); ++it)
    {
        delete *it;
    }
    _playedCards.clear();
    for (int i = 0; i < _nPlayers; ++i)
    {
        _playedCards.push_back(nullptr);
    }

    _currentPlayer = rand() % _nPlayers;
}

bool GameManager::update()
{
    draw();
    getInput();
    _playedCards[_currentPlayer] = new Card(_hands[_currentPlayer][_action]);
    _hands[_currentPlayer].erase(_hands[_currentPlayer].begin() + _action);

    //check if round is ended
    bool end = true;
    for (int i = 0; i < _nPlayers && end; ++i)
    {
        end = _playedCards[i] != nullptr;
    }
    if (end)
    {
        std::cout << std::endl;
        std::cout << "Briscola: " << *_briscola << std::endl;
        std::cout << "Played cards: ";
        for (int i = 0; i < _nPlayers; ++i)
        {
            std::cout << *(_playedCards[i]) << " ";
        }
        int firstPlayer = (_currentPlayer + 1) % _nPlayers;
        int strongest = firstPlayer;        //by default
        for (int i = 0; i < _nPlayers; ++i) //for each player
        {
            if (i != strongest) //for each not strongest player
            {
                //if different suits
                if (_playedCards[i]->getSuit() != _playedCards[strongest]->getSuit())
                {
                    //if player suit is briscola suit then he is the strongest
                    if (_playedCards[i]->getSuit() == _briscola->getSuit())
                    {
                        strongest = i;
                    }
                    //else strongest is still strongest
                }
                //if same suit
                else
                {
                    //if value of i is more than the value of strongest
                    if (_playedCards[i]->getValue() > _playedCards[strongest]->getValue())
                    {
                        strongest = i;
                    }
                    //if same value
                    if (_playedCards[i]->getValue() == _playedCards[strongest]->getValue())
                    {
                        //rank wins
                        if (_playedCards[i]->getRank() > _playedCards[strongest]->getRank())
                        {
                            strongest = i;
                        }
                        //else strongest is still strongest, since ranks of same suit cannot be equal
                    }
                    //else strongest is still strongest because more value in same suit
                }
            }
        }
        //strongest calculated
        std::cout << "Player " << strongest << " gets all the cards" << std::endl;
        std::cout << std::endl;
        //next round first player is the strongest of this round.
        _currentPlayer = strongest;
        //strongest gets all the cards played in this round
        for (int i = 0; i < _nPlayers; ++i)
        {
            //copies card into the card collected by the strongest
            _collected[strongest].push_back(*(_playedCards[i]));
            delete _playedCards[i];
            _playedCards[i] = nullptr;
        }
        //everyone draws a card
        int i = 0;
        int howManyDraws = _nPlayers;

        if (_deck.size() != 0)
        {
            //if last round
            if (_deck.size() == _nPlayers - 1)
            {
                //last to draw draws briscola
                _hands[(strongest + _nPlayers - 1) % _nPlayers].push_back(*_briscola);
                //since the last to draw has already drawn, one less has to draw
                howManyDraws--;
            }
            while (i < howManyDraws)
            {
                _hands[(strongest + i) % _nPlayers].push_back(_deck.draw());
                i++;
            }
        }
        else //deck.size == 0
        {
            //check if game is ended
            bool stillEnd = true;
            for (int i = 0; i < _nPlayers && stillEnd; ++i)
            {
                for (int j = 0; j < 3 && stillEnd; ++j)
                {
                    stillEnd = _hands[i].size() == 0;
                }
            }

            if (stillEnd) //game has ended
            {
                int *sum = new int[_nPlayers];
                for (int i = 0; i < _nPlayers; ++i)
                {
                    sum[i] = 0;
                    std::cout << "Cards collected by Player" << i << ": ";
                    for (auto it = _collected[i].begin(); it != _collected[i].end(); ++it)
                    {
                        std::cout << *it << " ";
                        sum[i] += it->getValue();
                    }
                    std::cout << std::endl;
                }
                std::cout << "POINTS" << std::endl;
                for (int i = 0; i < _nPlayers; ++i)
                {
                    std::cout << "Player " << i << ": " << sum[i] << std::endl;
                }
                int winner = 0;
                int max = sum[0];
                for (int i = 1; i < _nPlayers; ++i)
                {
                    if (sum[i] > max)
                    {
                        winner = i;
                        max = sum[i];
                    }
                }
                std::cout << "Player " << winner << " wins!" << std::endl;
                return true;
            }
        }
    }
    else
    {
        _currentPlayer = (_currentPlayer + 1) % _nPlayers;
    }
    return false;
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
        if (*it)
            std::cout << **it << " ";
        else
            std::cout << "[ ] ";
    }
    std::cout << std::endl
              << std::endl;
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