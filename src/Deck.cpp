#include "Deck.h"
#include <cmath>
#include <ctime>
#include <algorithm>
Deck::Deck()
{
}

void Deck::reset()
{
    _cards.clear();
    for (int i = 0; i < 40; ++i)
    {
        _cards.push_back(Card(i));
    }
}

void Deck::shuffle()
{
    srand(time(0));
    for (int i = _cards.size() - 1; i > 0; ++i)
    {
        int index = rand() % (i + 1);
        std::iter_swap(_cards.begin() + index, _cards.begin() + i);
    }
}