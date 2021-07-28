#include "Deck.h"

Deck::Deck()
{

}

void Deck::reset()
{
    _cards.clear();
    for(int i = 0; i < 40; ++i)
    {
        _cards.push_back(Card(i));
    }
}