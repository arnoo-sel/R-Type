#include "main.h"

int         getHp()
{
    return (10);
}

float       getFireRate()
{
    return (1);
}

char        getType()
{
	return (2);
}

Vertex<int> move(float time)
{
    return (Vertex<int>((time > 3) ? 64 : 0, (((int)round(time / 2.) % 2) * 2 - 1) * 150));
}

Vertex<int> fire(float time)
{
    return (Vertex<int>(-300, 0));
}

Vertex<int> canon(float time)
{
    return (Vertex<int>(-11, 27));
}

Vertex<int> spawnPos(float time)
{
    return (Vertex<int>(RANDOM, 200));
}
