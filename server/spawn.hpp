#ifndef SPAWN
# define SPAWN

#include <string>

using namespace std;

class MonsterType;
class Level;

class Spawn
{
public:
    Spawn(MonsterType *monster, Level& level);
    ~Spawn();
    const MonsterType     *getMonster() const;
    float                 getPos() const;
    int                   getOffset() const;

private:
    float               pos;
    int                 offset;
    const MonsterType   *monster;
};

#endif //SPAWN



