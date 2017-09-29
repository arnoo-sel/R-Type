#include "player.hpp"
#include "game.hpp"
#include "monster.hpp"
#include "rocket.hpp"
#include "bullet.hpp"

Player::Player(Game* game, string ip) : game(game), ip(ip)
{
	socket = new AbstractSocket(ip, CLIENT_PORT);
	color = game->addPlayer(this);
	level = 1;
	charge = -1;
	speed = Vertex<float>(blockSize * BLOCKS_PER_SECOND, 0);
	pos = Vertex<int>(100, 50 + color * 60);
	alive = -1;
    life = 1;
	_isAlive = true;
}

Player::~Player()
{
	delete socket;
}

void Player::die()
{
    string t;

    if (game->getTime() - lastDeath < 2)
        return;
    lastDeath = game->getTime();
    life--;
    if (life == 0)
        this->_isAlive = false;
    t += CMD_PDIE;
    t = Formater::pack<int>(t, this->getId());
    t = Formater::pack<char>(t, this->life);
    game->sendAll(t);
    sendMovePacket();
}

bool        Player::isAlive() const
{
	return (this->_isAlive);
}

char        Player::getColor() const
{
    return (color);
}

Seconds     Player::getAliveTime() const
{
    return (alive);
}

string      Player::getIp() const
{
    return ip;
}

void        Player::update(Seconds elapsedTime)
{
	if (isAlive())
	{
	    checkBounds();
    	pos += speed * elapsedTime; // Move the player command
	}
}

bool	Player::stuck() const
{
	if (game->getTime() > PLAYER_ALIVE && game->getTime() - alive > PLAYER_ALIVE)
		return true;
	return false;
}

void        Player::init()
{
	speed = Vertex<float>(blockSize * BLOCKS_PER_SECOND, 0);
	pos = Vertex<int>(100, 50 + color * 60);
    alive = game->getTime();
	_isAlive = true;
	charge = -1;
    life += 4;
	level++;
	lastDeath = game->getTime();
	for (int i = 0; i < 10; i++)
	{
        //sleep(100);
        sendMovePacket();
	}
}

void		Player::send(string data)
{
	socket->send(data, ip, CLIENT_PORT);
}

void        Player::sendMovePacket() const
{
    string t;

	t += CMD_MVPL;
	t = Formater::pack<int>(t, getId());
	t = Formater::pack<char>(t, color);
	t = Formater::pack<float>(t, game->getTime());
	t += netPosition();
	if (isAlive())
		game->sendAll(t);
//    cout << "player " << getId() << " at " << pos << " - " << speed << endl;
}

void        Player::checkBounds()
{
    bool affected = false;

    if ((speed.x < 0) && ((pos.x - game->pixPos()) < 5))
    {
        speed.x = blockSize * BLOCKS_PER_SECOND;
        affected = true;
    }
    else if ((speed.x > 0) && ((pos.x - game->pixPos()) > (640 - 70)))
    {
        speed.x = blockSize * BLOCKS_PER_SECOND;
        affected = true;
    }
    if (speed.y < 0 && pos.y < 5)
    {
        speed.y = 0;
        affected = true;
    }
    else if (speed.y > 0 && pos.y > (480 - 62))
    {
        speed.y = 0;
        affected = true;
    }
    if (affected && isAlive())
        sendMovePacket();
}

void		Player::recv(string& data)
{
    unsigned char   command;

    command = data[0];
    data.erase(0, 1);
    cout << ip << " : command " << (void*)command << endl;
    if ((command == CMD_STAR) && game->getReferee() == this)
        game->start();
    else if ((command == CMD_MOVE) && isAlive())
    {
        speed = Vertex<float>(data);
        speed = speed.normalized();
        speed *= blockSize * 3;
        speed += Vertex<float>(blockSize * BLOCKS_PER_SECOND, 0);
        sendMovePacket();
        sendMovePacket();
    }
    else if ((command == CMD_CHAR) && isAlive())
    {
        charge = game->getTime();
        string  t;
        t += 0x4;
        t = Formater::pack<int>(t, getId());
        game->sendAll(t);
    }
    else if ((command == CMD_REAL) && isAlive())
    {
        new Rocket(game, this, (charge < 0 ? 0 :(game->getTime() - charge) / 0.4));
        string  t;
        t += 0x10;
        t = Formater::pack<int>(t, getId());
        game->sendAll(t);
        charge = -1;
    }
    else if ((command == CMD_RTOM) && (game->getReferee() == this)) // Rocket hits Monster
    {
        Rocket *rk = game->findRocket(Formater::unpack<int>(data));
        Monster *ms = game->findMonster(Formater::unpack<int>(data));

        if (rk && ms)
        {
            ms->setHp(ms->getHp() - (rk->getSize() + 1));
            if ((rk->getSize() < 1) || (ms->getHp() > 0))
            {
                delete rk;
                game->getRockets().remove(rk);
            }
        }
    }
    else if ((command == CMD_BTOP) && (game->getReferee() == this)) // Bullet hits Player
    {
        Bullet *bu = game->findBullet(Formater::unpack<int>(data));
        Player *pl = game->findPlayer(Formater::unpack<int>(data));

        if (pl && bu)
        {
            pl->die();
            delete bu;
            game->getBullets().remove(bu);
        }
    }
    else if ((command == CMD_PTOL) && (game->getReferee() == this)) // Player hits Landscape
    {
        Player *pl = game->findPlayer(Formater::unpack<int>(data));

        if (pl)
            pl->die();
    }
    else if ((command == CMD_PTOM) && (game->getReferee() == this)) // Player hits monster
    {
        Player *pl = game->findPlayer(Formater::unpack<int>(data));
        Monster *ms = game->findMonster(Formater::unpack<int>(data));

        if (pl && ms)
        {
            pl->die();
            ms->setHp(ms->getHp() - 5);
        }
    }
    else if ((command == CMD_PTOP) && (game->getReferee() == this)) // Player hits Player
    {
        Player *p1 = game->findPlayer(Formater::unpack<int>(data));
        Player *p2 = game->findPlayer(Formater::unpack<int>(data));

        if (p1 && p2)
        {
            p1->die();
            p2->die();
        }
    }
    else if (command == CMD_LIVE) // Client is alive
    {
    	alive = game->getTime();
    }
    else if (command == 0x50) // Welcom msg again
    {
        game->sendMapInfo();
    }
}
