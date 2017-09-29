#include "blork.hpp"
#include "stdlib.h"

int         Blork::getHp() const
{
    return (2);
}

float       Blork::getFireRate() const
{
    return (0.5);
}

char        Blork::getType() const
{
	return (1);
}

Vertex<int> Blork::move(float time) const
{
    return (Vertex<int>(-50, (((int)round(time) % 2) * 2 - 1) * 100));
}

Vertex<int> Blork::fire(float time) const
{
    return (Vertex<int>(-150, rand() % 100 - 60));
}

Vertex<int> Blork::canon(float time) const
{
    return (Vertex<int>(0, 14));
}

Vertex<int> Blork::spawnPos(float time) const
{
    return (Vertex<int>(RANDOM, RANDOM));
}
