#include "Deck.h"

Deck::Deck()
{

}

void Deck::reset()
{
    for(auto it = _cards.begin(); it != _cards.end(); ++it)
    {
        delete *it;
    }
    _cards.clear();
    for(int i = 0; i < 40; ++i)
    {
        _cards.push_back(new Card(i));
    }
}