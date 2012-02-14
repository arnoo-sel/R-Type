#include "entity.hpp"

string      Entity::netPosition() const
{
    string  t;

    t = Vertex<int>(pos).serialize();
    t += speed.serialize();
    return (t);
}

void        Entity::setPos(Vertex<float> pos)
{
    this->pos = pos;
}

void        Entity::setSpeed(Vertex<float> speed)
{
    this->speed = speed;
}

const Vertex<float>& Entity::getPos() const
{
    return (pos);
}

const Vertex<float>& Entity::getSpeed() const
{
    return (speed);
}
