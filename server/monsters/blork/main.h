#ifndef __MAIN_H__
#define __MAIN_H__

#include "../../include/math/vertex.hpp"
#include "math.h"

#define RANDOM -1

extern "C"
{
    int         getHp(); // Heal point
    float       getFireRate(); // Fire Rate (shoot / sec)
    char        getType(); // Monster type (unique id)
    Vertex<int> move(float time); // How to move the entity at time
    Vertex<int> fire(float time); // Get shoot direction
    Vertex<int> canon(float time); // Get shoot origin
    Vertex<int> spawnPos(float time); // Get spawn position (-1 means random)
}

#endif // __MAIN_H__
