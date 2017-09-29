#ifndef __MURLOC_H__
#define __MURLOC_H__

#include "../iMonster.hpp"
#include "math.h"

#define RANDOM -1

class Murloc : public IMonster
{
public:
    int         getHp() const override; // Heal point
    float       getFireRate() const override; // Fire Rate (shoot / sec)
    char        getType() const override; // Monster type (unique id)
    Vertex<int> move(float time) const override; // How to move the entity at time
    Vertex<int> fire(float time) const override; // Get shoot direction
    Vertex<int> canon(float time) const override; // Get shoot origin
    Vertex<int> spawnPos(float time) const override; // Get spawn position (-1 means random)
};

#endif // __LURLOC_H__
