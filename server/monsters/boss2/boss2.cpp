#include "boss2.hpp"
#include "stdlib.h"

int         Boss2::getHp() const
{
    return (1000 / 4);
}

float       Boss2::getFireRate() const
{
    return (2);
}

char        Boss2::getType() const
{
	return (4);
}

Vertex<int> Boss2::move(float time) const
{
    static int mode = 3;
    static int rage = 0;
    static float lastTime = 0;
    int y;
    int x = 0;

    if (time - lastTime > 1)
    {
        lastTime = time;
        mode = (mode + 1) % 4;
        rage = rand() % 7;
    }

    if (mode == 0)
        y = 0;
    if (mode == 1)
        y = -10;
    if (mode == 2)
        y = 0;
    if (mode == 3)
        y = +10;

    if (rage == 0)
    {
        if ((time - lastTime) > 0.2)
        {
            if ((time - lastTime) < 0.6)
                x = -400 / 0.4;
            else
                x = 400 / 0.4;
        }
    }
    return (Vertex<int>((time > 4) ? (64 + x) : 0, y * 10));
}

Vertex<int> Boss2::fire(float time) const
{
    return (Vertex<int>(-100, rand() % 100 - 70));
}

Vertex<int> Boss2::canon(float time) const
{
    Vertex<int> canons[3];
    canons[0] = Vertex<int>(35, 115);
    canons[1] = Vertex<int>(127, 152);
    canons[2] = Vertex<int>(75, 262);
    return (canons[rand() % 3]);
}

Vertex<int> Boss2::spawnPos(float time) const
{
    return (Vertex<int>(140 * 64, 20));
//    return (Vertex<int>(10 * 64, 20));  // place at begining for testing
}
