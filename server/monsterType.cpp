#include "monsterType.hpp"
#include "monsters/blork/blork.hpp"
#include "monsters/murloc/murloc.hpp"
#include "monsters/boss/boss.hpp"
#include "monsters/boss2/boss2.hpp"
#include "monsters/boss3/boss3.hpp"
#include <iostream>

MonsterType::MonsterType(const string& name, const int qty) : name(name), qty(qty)
{
    if (name == "blork")
        monster = new Blork;
    else if (name == "murloc")
        monster = new Murloc;
    else if (name == "boss")
        monster = new Boss;
    else if (name == "boss2")
        monster = new Boss2;
    else if (name == "boss3")
        monster = new Boss3;
    else
    {
        std::cout << "Unknown monster type: " << name << "\n";
        throw new std::exception("unknown monster type");
    }
}

MonsterType::~MonsterType()
{
    delete monster;
}

Vertex<int>     MonsterType::fMove(float time) const
{
    return monster->move(time);
}

Vertex<int>     MonsterType::fFire(float time) const
{
    return monster->fire(time);
}

Vertex<int>     MonsterType::fCanon(float time) const
{
    return monster->canon(time);
}

Vertex<int>     MonsterType::fSpawnPos(float time) const
{
    return monster->spawnPos(time);
}

const string&   MonsterType::getName() const
{
    return (name);
}

int             MonsterType::getQty() const
{
    return (qty);
}

char			MonsterType::getType() const
{
    return monster->getType();
}

int             MonsterType::getHp() const
{
    return monster->getHp();
}

float           MonsterType::getFireRate() const
{
    return monster->getFireRate();
}
