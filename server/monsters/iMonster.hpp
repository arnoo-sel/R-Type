#ifndef IMONSTER_HPP
#define IMONSTER_HPP

#include "../math/vertex.hpp"

class IMonster
{
public:
    virtual int         getHp() const = 0; // Heal point
    virtual float       getFireRate() const = 0; // Fire Rate (shoot / sec)
    virtual char        getType() const = 0; // Monster type (unique id)
    virtual Vertex<int> move(float time) const = 0; // How to move the entity at time
    virtual Vertex<int> fire(float time) const = 0; // Get shoot direction
    virtual Vertex<int> canon(float time) const = 0; // Get shoot origin
    virtual Vertex<int> spawnPos(float time) const = 0; // Get spawn position (-1 means random)
};

#endif // IMONSTER_HPP
