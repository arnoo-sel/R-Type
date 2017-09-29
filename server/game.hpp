#ifndef GAME
# define GAME
#include <string>
#include <list>
#include <math.h>
#include "math/vertex.hpp"
#include "math/time.hpp"
#include "identifiable.hpp"
#include "threads/iThread.hpp"
#include "rocket.hpp"

using namespace std;

class Monster;
class Level;
class Player;
class Rocket;
class Bullet;
class Server;

#define CMD_INFO    0x02    // Info befor game start
#define CMD_MVPL    0x03    // Player move
#define CMD_RUN     0x13    // game start
#define CMD_NEXT    0x14    // next level
#define CMD_SCOR    0x15    // Update score
#define CMD_NLVL    0x16    // Next level msg
#define CMD_OVER    0x17    // Game Over

#define LEVELS  3
#define REFRESH	2
#define MAX_PLAYERS 4

class Game : public Identifiable
{
public:
    typedef list<Monster*> MonsterList;
    typedef list<Rocket*>  RocketList;
    typedef list<Bullet*>  BulletList;
    typedef list<Player*>	PlayerList;

    Game(Server* server);
    ~Game();
    int         run();
	int			loop();
	void		start();
	bool        started() const;
	int 		addPlayer(Player*);
	void 		removePlayer(Player*);
	float		loadingBlock() const;
	void		sendAll(string& data) const; // send data to all players
	Monster*    findMonster(int id);
	Rocket*     findRocket(int id);
	Player*     findPlayer(int id);
    Bullet*     findBullet(int id);
    void        addPoints(int pts);
    bool        nextLevel();
    int         pixPos() const; // Get pix position
    void        sendMapInfo() const; // send map info to players
    bool        gameOver() const;
    BulletList& getBullets();
    PlayerList& getPlayers();
    RocketList& getRockets();
    float       getTime() const;
    Player*     getReferee() const;

private:
    int         pos; // game position (in pixels)
    Seconds     time; // game position (in seconds)
    Seconds     begin; // game start (in seconds)
    Seconds     last; // last frame (in seconds)
    Seconds     endTime; // Level end time (used for tempo)
    int         life; // players life (when 0, restart at the level begining)
    int         score; // game total score
    Level       *level; // current game level
    MonsterList monsters; // visible monsters on screen
    IThread*    thread;
	PlayerList	players;
	RocketList  rockets;
	BulletList  bullets;
	Player*		referee;
    Server*	server;
};

int     threadFunc(void *data);

#endif // GAME




