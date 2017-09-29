#include "identifiable.hpp"

int Identifiable::_nextId = 0;

Identifiable::Identifiable()
{
    _id = _nextId;
    _nextId++;
}

Identifiable::~Identifiable()
{
}

int Identifiable::getId() const
{
    return (_id);
}
