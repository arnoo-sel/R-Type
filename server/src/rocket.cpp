#include "rocket.hpp"

Rocket::Rocket(Game* game, Player* player, int size) : game(game), player(player), size(size)
{
    string  t;

    if (size > 5)
        size = 5;
    setSpeed(Vertex<float>(blockSize * BLOCKS_PER_SECOND * 8, 0));
    setPos(player->getPos() + Vertex<int>(50, 10));
    game->getRockets().push_back(this);
    t += CMD_RKPOP;
    t = Formater::pack<int>(t, getId());
    t = Formater::pack<char>(t, player->getColor());
    t = Formater::pack<float>(t, game->getTime());
    t = Formater::pack<char>(t, size);
    t += netPosition();
    game->sendAll(t);
}

Rocket::~Rocket()
{
    string  t;

    t += CMD_RKDIE;
    t = Formater::pack(t, getId());
    game->sendAll(t);
}

int     Rocket::getSize() const
{
        return (this->size);
}

void    Rocket::update(Seconds elapsedTime)
{
    pos += speed * elapsedTime; // move the rocket
}
