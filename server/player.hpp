#ifndef PLAYER
# define PLAYER

#include <string>
#include "math/vertex.hpp"
#include "math/time.hpp"
#include "sockets/iSocket.hpp"
#include "identifiable.hpp"
#include "entity.hpp"

#define PLAYER_ALIVE	5  // Player lag tolerance (seconds)

#define CMD_CHAR    0x04   // Player charging
#define CMD_PDIE    0x05   // Player dying
#define CMD_REAL    0x10  // Player release charge
#define CMD_MOVE    0x51  // Player move
#define CMD_RTOM    0x52  // Rocket hits Monster
#define CMD_BTOP    0x53  // Bullet hits Player
#define CMD_PTOL    0x54  // Player hits Landscape
#define CMD_PTOM    0x55  // Player hits Monster
#define CMD_PTOP    0x56  // Player hits Player
#define CMD_STAR    0x57  // Referee start the game
#define CMD_LIVE    0x42  // Client keep alive

using namespace std;

class Game;
class MonsterType;
class Spawn;

class Player : public Identifiable, public Entity
{
public:
	Player(Game* game, string ip);
	~Player();
	void		send(string data); // send data to graphic terminal
	void		recv(string& data); // callback on data receive
    void        update(Seconds); // update player's position
    char        getColor() const;
    bool	    stuck() const;
    void        die();
    bool        isAlive() const;
    Seconds     getAliveTime() const;
    string      getIp() const;
    void        init(); // called when the game start
    void        sendMovePacket() const;
    void        checkBounds();

private:
	int			color;
	int         level;
	bool        _isAlive;
	Game*		game;
	char        life;
	ISocket*	socket;
	string		ip;
    Seconds     begin, charge, alive, lastDeath;
};

#endif // PLAYER




