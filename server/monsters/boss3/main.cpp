#include "main.h"
#include "stdlib.h"

int         getHp()
{
    return (2000);
}

float       getFireRate()
{
    return (4);
}

char        getType()
{
	return (5);
}

Vertex<int> move(float time)
{
    static int mode = 3;
    static float lastTime = 0;
    int y;

    if (time - lastTime > 1)
    {
        lastTime = time;
        mode = (mode + 1) % 4;
    }

    if (mode == 0)
        y = 0;
    if (mode == 1)
        y = -15;
    if (mode == 2)
        y = 0;
    if (mode == 3)
        y = +15;

    return (Vertex<int>((time >  2.2) ? (64) : 0, y * 10));
}

Vertex<int> fire(float time)
{
    return (Vertex<int>(-100, rand() % 100 - 50));
}

Vertex<int> canon(float time)
{
    Vertex<int> canons[6];
    canons[0] = Vertex<int>(80, 8);
    canons[1] = Vertex<int>(0, 60);
    canons[2] = Vertex<int>(90, 90);
    canons[3] = Vertex<int>(45, 158);
    canons[4] = Vertex<int>(-4, 200);
    canons[5] = Vertex<int>(90, 250);
    return (canons[rand() % 6]);
}

Vertex<int> spawnPos(float time)
{
    return (Vertex<int>(178 * 64, 20));
//    return (Vertex<int>(13 * 64, 20));  // place at begining for testing
}
