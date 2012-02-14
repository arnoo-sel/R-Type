#ifndef ROCKET
#define ROCKET

#include "entity.hpp"
#include "identifiable.hpp"
#include "game.hpp"
#include "player.hpp"

#define CMD_RKDIE   0x07 // Rocket explode
#define CMD_RKPOP   0x06 // Rocket appeared

class Player;
class Game;

// Rocket class (player's bullet)
class Rocket : public Identifiable, public Entity
{
public:
    Rocket(Game* game, Player* player, int size);
    ~Rocket();
    void    update(Seconds elapsedTime);
    int     getSize() const;

private:
    Game*   game;
    Player* player;
    int     size;
};

#endif // ROCKET

