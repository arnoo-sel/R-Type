#include "main.h"
#include "stdlib.h"

int         getHp()
{
    return (2);
}

float       getFireRate()
{
    return (0.5);
}

char        getType()
{
	return (1);
}

Vertex<int> move(float time)
{
    return (Vertex<int>(-50, (((int)round(time) % 2) * 2 - 1) * 100));
}

Vertex<int> fire(float time)
{
    return (Vertex<int>(-150, rand() % 100 - 60));
}

Vertex<int> canon(float time)
{
    return (Vertex<int>(0, 14));
}

Vertex<int> spawnPos(float time)
{
    return (Vertex<int>(RANDOM, RANDOM));
}
