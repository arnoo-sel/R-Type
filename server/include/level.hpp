#ifndef LEVEL
# define LEVEL

#include <string>
#include <map>
#include <list>
#include "filesystem/iFile.hpp"

using namespace std;

class MonsterType;
class Game;
class Spawn;

class Level
{
public:
    typedef list<MonsterType*>  MonsterList;
    typedef list<Spawn*>        SpawnList;

    Level(int id, Game* game);
    ~Level();
	Spawn*		getNextSpawn(float maxPos);
	SpawnList&  getSpawnList();
    int         getId() const;
    int         getLen() const;

private:
    int         id;
    int         len;
    Game        *game;
    MonsterList monsterList;
    SpawnList   spawnList;
};

bool		spawnSort(Spawn* a, Spawn* b);

#endif //LEVEL


