#include <iostream>
#include <stdlib.h>

#include "monster.hpp"
#include "spawn.hpp"
#include "monsterType.hpp"
#include "math/time.hpp"
#include "game.hpp"
#include "bullet.hpp"

using namespace std;

Monster::Monster(Game* game, const Spawn* spawn, Seconds begin) : begin(begin), time(0), game(game)
{
    type = spawn->getMonster();
    pos.x = spawn->getPos() * blockSize;
    pos.y = spawn->getOffset();
    speed = Vertex<float>(0, 0);
    hp = type->getHp();
    nextShoot = 0;
//    cout << "monster instance " << this << " : " << type->getName() <<
//        " (" << hp << " hp) at " << pos << endl;
    sendMovePacket();
}

Monster::~Monster()
{
    string  t;

    t += CMD_DEAD;
    t = Formater::pack<int>(t, getId());
    game->sendAll(t);
}

void		Monster::sendMovePacket()
{
	string	t;

    t += CMD_MMOV;
    t = Formater::pack<int>(t, getId());
    t = Formater::pack<char>(t, type->getType());
    t = Formater::pack<float>(t, game->getTime());
    t += netPosition();
  //  cout << "monster move at " << pos << speed << " - hp " << getHp() << endl;
    game->sendAll(t);
}

void                Monster::update(float time)
{
    float diff = time - (this->time + this->begin);

    nextShoot += diff;
    if (nextShoot >= (1 / type->getFireRate()))
    {
        nextShoot -= (1 / type->getFireRate());
//        cout << "fire" << endl;
        new Bullet(game, this);
        // TODO : Fire
    }
    speed = type->fMove(this->time);
    if (!(lastSpeed == speed))
        sendMovePacket();
    lastSpeed = speed;
    speed *= diff;
    pos += speed;
    this->time = time - begin;
}


const MonsterType*  Monster::getType() const
{
    return (type);
}

void                Monster::setHp(int hp)
{
    this->hp = hp;
}

Vertex<int>			Monster::getPos() const
{
	return (Vertex<int>(pos));
}

int                 Monster::getHp() const
{
    return (hp);
}

Seconds             Monster::getTime() const
{
    return time;
}
