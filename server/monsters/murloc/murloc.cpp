#include "murloc.hpp"

int         Murloc::getHp() const
{
    return (10);
}

float       Murloc::getFireRate() const
{
    return (1);
}

char        Murloc::getType() const
{
	return (2);
}

Vertex<int> Murloc::move(float time) const
{
    return (Vertex<int>((time > 3) ? 64 : 0, (((int)round(time / 2.) % 2) * 2 - 1) * 150));
}

Vertex<int> Murloc::fire(float time) const
{
    return (Vertex<int>(-300, 0));
}

Vertex<int> Murloc::canon(float time) const
{
    return (Vertex<int>(-11, 27));
}

Vertex<int> Murloc::spawnPos(float time) const
{
    return (Vertex<int>(RANDOM, 200));
}
