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