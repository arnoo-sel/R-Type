#ifndef MONSTER
# define MONSTER

#include <string>
#include "library/iLibrary.hpp"
#include "math/vertex.hpp"
#include "math/time.hpp"
#include "identifiable.hpp"
#include "entity.hpp"

#define CMD_DEAD    9 // when a monster die
#define CMD_MMOV    8 // monster move

using namespace std;

class Game;
class MonsterType;
class Spawn;

class Monster : public Identifiable, public Entity
{
public:
    Monster(Game*, const Spawn*, Seconds begin);
    ~Monster();
    const MonsterType*  getType() const;
    int                 getHp() const;
	Vertex<int>			getPos() const;
	void                setHp(int hp);
    void                update(float time);
    void				sendMovePacket();
    Seconds             getTime() const;

private:
    const MonsterType*  type;
    int                 hp;
    Vertex<float>       lastSpeed;
    Seconds             begin, time, nextShoot;
    Game*               game;
};

#endif // MONSTER




