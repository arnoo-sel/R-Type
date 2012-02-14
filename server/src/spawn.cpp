#include <stdlib.h>

#include "spawn.hpp"
#include "level.hpp"
#include "monsterType.hpp"

int     randPos(int min, int max)
{
    return (rand() % (max - min) + min);
}

Spawn::Spawn(MonsterType *monster, Level& level) : monster(monster)
{
    int min = 12;
    int max = level.getLen() - 12;

    // min = randPos(min, max); // activate more and more monsters
    Vertex<int> spawnPos = monster->fSpawnPos(0);
    if (spawnPos.x == -1)
        this->pos = randPos(min, max) + ((float)(rand() % blockSize) / (float)blockSize);
    else
        this->pos = (float)spawnPos.x / (float)blockSize;
    if (spawnPos.y == -1)
        this->offset = randPos(blockSize * 0.5, blockSize * 5);
    else
        this->offset = spawnPos.y;
}

Spawn::~Spawn()
{
}

const MonsterType     *Spawn::getMonster() const
{
    return (monster);
}

float             Spawn::getPos() const
{
    return (pos);
}

int               Spawn::getOffset() const
{
    return (offset);
}
