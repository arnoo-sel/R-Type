#ifndef ENTITY
#define ENTITY

#include "math/vertex.hpp"

// Entity abstract class for 2D movements
class Entity
{
public:
    string      netPosition() const; // get position formated packet
    void        setPos(Vertex<float>);
    void        setSpeed(Vertex<float>);
    const Vertex<float>& getPos() const;
    const Vertex<float>& getSpeed() const;

protected:
	Vertex<float>	pos, speed;
};

#endif // ENTITY
