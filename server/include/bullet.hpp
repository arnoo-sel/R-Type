#ifndef BULLET
#define BULLET

#include "entity.hpp"
#include "identifiable.hpp"
#include "game.hpp"
#include "monster.hpp"

#define CMD_BLDIE   0x12 // Bullet explode
#define CMD_BLPOP   0x11 // Bullet appeared

class Monster;
class Game;

// Bullet class (monster's bullet)
class Bullet : public Identifiable, public Entity
{
public:
    Bullet(Game* game, Monster* monster);
    ~Bullet();
    void    update(Seconds elapsedTime);

private:
    Game*   game;
    Monster* monster;
};

#endif // BULLET


