#include "monsterType.hpp"

MonsterType::MonsterType(const string& name, const int qty) : name(name), qty(qty)
{
    try {
        lib = new AbstractLibrary(string("monsters/") + name);
    } catch (std::exception *e) {
        lib = new AbstractLibrary(string("../../monsters/") + name);
    }
    typedef int (*getHp)();
    typedef char (*getType)();
    typedef float (*getFireRate)();

    hp = (*(lib->getSym<getHp>("getHp")))();
    type = (*(lib->getSym<getType>("getType")))();
    fireRate = (*(lib->getSym<getFireRate>("getFireRate")))();

    move = lib->getSym<DllFuncPtr>("move");
    fire = lib->getSym<DllFuncPtr>("fire");
    canon = lib->getSym<DllFuncPtr>("canon");
    spawnPos = lib->getSym<DllFuncPtr>("spawnPos");

    //cout << " * hp = " << hp << ",  fireRate = " << fireRate << endl;
}

MonsterType::~MonsterType()
{
    delete lib;
}

Vertex<int>     MonsterType::fMove(float time) const
{
    return ((*move)(time));
}

Vertex<int>     MonsterType::fFire(float time) const
{
    return ((*fire)(time));
}

Vertex<int>     MonsterType::fCanon(float time) const
{
    return ((*canon)(time));
}

Vertex<int>     MonsterType::fSpawnPos(float time) const
{
    return ((*spawnPos)(time));
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
	return (type);
}

int             MonsterType::getHp() const
{
    return (hp);
}

float           MonsterType::getFireRate() const
{
    return (fireRate);
}
