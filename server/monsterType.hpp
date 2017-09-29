#ifndef MONSTERTYPE
# define MONSTERTYPE

#include <string>
#include <map>
#include "math/vertex.hpp"

class IMonster;

using namespace std;

class MonsterType
{
public:
    typedef Vertex<int> (*DllFuncPtr)(float);

    MonsterType(const string& name, const int qty = 5);
    ~MonsterType();
    const string&   getName() const;
    int             getQty() const;
    char			getType() const;
    int             getHp() const;
    float           getFireRate() const;
    Vertex<int>     fMove(float time) const;
    Vertex<int>     fFire(float time) const;
    Vertex<int>     fCanon(float time) const;
    Vertex<int>     fSpawnPos(float time) const;

private:
    const string    name;
    const int       qty;
    IMonster *monster;
};

#endif //MONSTERTYPE



