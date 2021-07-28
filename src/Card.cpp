#include "Card.h"
#include <stdexcept>

Card::Card(int id) : _id(id)
{
    if (id < 0 || id > 39)
        throw std::runtime_error("Exception in Card::Card(int x): x must be 0 <= x <= 39");
}

Card::Card(int suit, int rank) : _id(suit * 10 + (rank - 1))
{
    if (suit < 0 || suit > 3)
        throw std::runtime_error("Exception in Card::Card(int x, int y): x must be 0 <= x <= 3\n");
    if (rank < 1 || rank > 10)
        throw std::runtime_error("Exception in Card::Card(int x, int y): y must be 1 <= y <= 10");
}

int Card::getValue() const
{
    switch (getRank())
    {
    case 1:
        return 11;
        break;
    case 3:
        return 10;
        break;
    case 8:
        return 2;
        break;
    case 9:
        return 3;
        break;
    case 10:
        return 4;
        break;
    default:
        return 0;
        break;
    }
}

std::ostream &operator<<(std::ostream& os, Card c)
{
    char suit = '\2' + c.getSuit();    
    return os << c.getRank() << suit;
}