#include "bullet.hpp"
#include "monsterType.hpp"

Bullet::Bullet(Game* game, Monster* monster) : game(game), monster(monster)
{
    string  t;

    setSpeed(monster->getType()->fFire(monster->getTime()));
    setPos(monster->getPos() + monster->getType()->fCanon(monster->getTime()));
    game->getBullets().push_back(this);
    t += CMD_BLPOP;
    t = Formater::pack(t, getId());
    t = Formater::pack<float>(t, game->getTime());
    t += netPosition();
//    cout << "new bullet " << pos << speed << endl;
    game->sendAll(t);
}

Bullet::~Bullet()
{
    string  t;

    t += CMD_BLDIE;
    t = Formater::pack(t, getId());
    game->sendAll(t);
}

void    Bullet::update(Seconds elapsedTime)
{
    pos += speed * elapsedTime; // move the bullet
}
