#include "game.hpp"
#include "monster.hpp"
#include "level.hpp"
#include "spawn.hpp"
#include "monsterType.hpp"
#include "math/time.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "server.hpp"

Game::Game(Server* server) : server(server)
{
    cout << "New game " << getId() << endl;
    life = 5;
    score = 0;
    referee = NULL;
    thread = NULL;
    begin = -1;
    level = new Level(1, this);
}

Game::~Game()
{
    cout << "Destroying game " << getId() << endl;
    if (thread)
    	delete thread;
 	Player *pl;
	while (players.size() > 0)
	{
		pl = players.front();
		delete (pl);
		server->getPlayers().remove(pl);
		players.pop_front();
	}
    while (rockets.size() > 0)
    {
        delete rockets.front();
        rockets.pop_front();
    }
    while (bullets.size() > 0)
    {
        delete bullets.front();
        bullets.pop_front();
    }
    while (monsters.size() > 0)
    {
        delete monsters.front();
        monsters.pop_front();
    }
    server->getCurrentGame() = NULL;
    delete level;
}

void	Game::start()
{
    if (started())
    	return;
    begin = now();
    cout << "Starting game " << getId() << endl;
    time = 0;
    last = 0;
    pos = 0;
    endTime = -1;
    if (!thread)
        thread = new AbstractThread(threadFunc, (void*) this);

    string t(1, CMD_RUN);
    sendAll(t);
    std::cout << "start" << std::endl;
    PlayerList::iterator pl, plEnd = players.end();
	for (pl = players.begin(); pl != plEnd; ++pl)
	{
		(*pl)->init();
	}
}

int    Game::pixPos() const
{
    return (time * BLOCKS_PER_SECOND * blockSize);
}

bool   Game::nextLevel()
{
    int     oldLevel = level->getId();

    string t;
    t += CMD_NEXT;
    sendAll(t);
    if (oldLevel == LEVELS)
    {
        return false;
    }
    while (rockets.size() > 0)
    {
        delete rockets.front();
        rockets.pop_front();
    }
    while (bullets.size() > 0)
    {
        delete bullets.front();
        bullets.pop_front();
    }
    while (monsters.size() > 0)
    {
        delete monsters.front();
        monsters.pop_front();
    }
    cout << "Next level " << oldLevel + 1 << " (still " <<
        players.size() << " players connected)" << endl;
    begin = -1;
    delete level;
    level = new Level(oldLevel + 1, this);
    start();
    return true;
}


bool    Game::started() const
{
    return (begin > 0);
}

void    Game::sendMapInfo() const
{
    std::cout << "sendMapInfo" << std::endl;
    PlayerList::const_iterator pl, plEnd = players.end();
    for (pl = players.begin(); pl != plEnd; ++pl)
    {
        string  t;

        t += CMD_INFO;
        if (*pl == referee) // referee or not ?
            t = Formater::pack<char>(t, 1);
        else
            t = Formater::pack<char>(t, 0);
        t = Formater::pack<char>(t, players.size()); // nb players
        t = Formater::pack<int>(t, (*pl)->getId()); // player uniq id
        if ((*pl) == players.back()) // player color
            t = Formater::pack<char>(t, players.size());
        else
            t = Formater::pack<char>(t, (*pl)->getColor());
        (*pl)->send(t);
    }
}

int		Game::addPlayer(Player* p)
{
	if (players.size() < MAX_PLAYERS)
	{
		if (referee == NULL)
			referee = p;
		players.push_back(p);

        // Send map info
		sendMapInfo();
		return (players.size());
	}
	else
		return (-1);
}

void 	Game::removePlayer(Player* p)
{
	players.remove(p);
	if (players.size() == 0)
		delete this;
	if (referee == p)
		referee = players.front();
	// Notify user deco
}

void	Game::sendAll(string& data) const
{
    std::cout << "sendAll" << std::endl;
 	PlayerList::const_iterator pl, plEnd = players.end();
	for (pl = players.begin(); pl != plEnd; ++pl)
	{
		(*pl)->send(data);
	}
}


int		Game::loop()
{
	// Move players
    std::cout << "loop" << std::endl;
 	PlayerList::iterator pl, plEnd = players.end();
	for (pl = players.begin(); pl != plEnd; ++pl)
	{
		(*pl)->update(time - last);
		if ((*pl)->stuck())
		{
			cout << "Deleting player " << (*pl)->getId() << " dead for " << (time - (*pl)->getAliveTime()) << " s" << endl;
			delete (*pl);
			server->getPlayers().remove(*pl);
			pl = players.erase(pl);
            if (pl == plEnd)
                break;
		}
	}

	// Remove oudated rockets and move them
    std::cout << "loop 2" << std::endl;
 	RocketList::iterator rk, rkEnd = rockets.end();
	for (rk = rockets.begin(); rk != rkEnd; ++rk)
	{
		(*rk)->update(time - last);
		// Out of screen
		if ((*rk)->getPos().x > pos + blockSize * 11)
		{
			//cout << "deleting rocket " << (*rk)->getId() << endl;
			delete (*rk);
			rk = rockets.erase(rk);
            if (rk == rkEnd)
                break;
		}
	}

	// Remove oudated monster and move them
    std::cout << "loop 3" << std::endl;
 	MonsterList::iterator it, itEnd = monsters.end();
	for (it = monsters.begin(); it != itEnd; ++it)
	{
	    string t;
		(*it)->update(time);

		// Out of screen
		if (((*it)->getPos().x <= pos - 2*blockSize) || ((*it)->getHp() <= 0))
		{
			//cout << "deleting monster " << (*it)->getId() << endl;
            if ((*it)->getHp() <= 0)
                addPoints((*it)->getType()->getHp());
			delete (*it);
			it = monsters.erase(it);
            if (it == itEnd)
                break;
		}
	}

	// Remove oudated bullets and move them
    std::cout << "loop 4" << std::endl;
 	BulletList::iterator bl, blEnd = bullets.end();
	for (bl = bullets.begin(); bl != blEnd; ++bl)
	{
		(*bl)->update(time - last);
		// Out of screen
		if ((*bl)->getPos().x <= pos - blockSize)
		{
			//cout << "deleting bullet " << (*bl)->getId() << endl;
			delete (*bl);
			bl = bullets.erase(bl);
            if (bl == blEnd)
                break;
		}
	}
	// Spawn new monsters
 	Spawn	*spawn;
	while ((spawn = level->getNextSpawn(loadingBlock())))
	{
		monsters.push_back(new Monster(this, spawn, time));
		delete spawn;
	}

	return (players.size());
}

bool    Game::gameOver() const
{
    std::cout << "gameover" << std::endl;
    PlayerList::const_iterator pl, plEnd = players.end();
	for (pl = players.begin(); pl != plEnd; ++pl)
	{
		if ((*pl)->isAlive())
            return (false);
	}
	return (true);
}

int     Game::run()
{
    while ((level->getSpawnList().size() > 0 || monsters.size() > 0) || ((time - endTime) < 5))
    {
        //cout << "time = " << time << " endTime = " << endTime << endl;
    	//cout.precision(3);
        //cout << "t : " << time << " s\tpos : " << pos / blockSize << " block / " << pos << " pix" << endl;
		if (loop() == 0) // No more players
			return (1);
        if (gameOver())
            return (2);

		// Loop time stabilization to REFRESH ms
		double targetTime = round(time * 1000 / REFRESH + 1) * REFRESH / 1000;
        sleep(static_cast<int>((targetTime - time) * 1000));
        last = time;
        time = (now() - begin);
        pos = time * BLOCKS_PER_SECOND * blockSize;

        // Detect end of level
        if (!(level->getSpawnList().size() > 0 || monsters.size() > 0) && endTime < 0)
        {
            endTime = time;
            string  t;
            t += CMD_NLVL;
            sendAll(t);
        }
    }
    return (0);
}

void        Game::addPoints(int pts)
{
    string  t;

    score += pts;
    t += CMD_SCOR;
    t = Formater::pack<int>(t, score * 10);
    sendAll(t);
}

float		Game::loadingBlock() const
{
	return ((float)pos / (float)blockSize + 10); // Anticipative loading
}

Monster*    Game::findMonster(int id)
{
    std::cout << "findMonster" << std::endl;
    MonsterList::iterator it, itEnd = monsters.end();
	for (it = monsters.begin(); it != itEnd; ++it)
	{
	    if ((*it)->getId() == id)
            return ((*it));
	}
	return (NULL);
}

Rocket*    Game::findRocket(int id)
{
    std::cout << "findRocket" << std::endl;
    RocketList::iterator it, itEnd = rockets.end();
	for (it = rockets.begin(); it != itEnd; ++it)
	{
	    if ((*it)->getId() == id)
            return ((*it));
	}
	return (NULL);
}

Player*    Game::findPlayer(int id)
{
    std::cout << "game::findPlayer" << std::endl;
    PlayerList::iterator it, itEnd = players.end();
	for (it = players.begin(); it != itEnd; ++it)
	{
	    if ((*it)->getId() == id)
            return ((*it));
	}
	return (NULL);
}

Bullet*    Game::findBullet(int id)
{
    std::cout << "findBullet" << std::endl;
    BulletList::iterator it, itEnd = bullets.end();
	for (it = bullets.begin(); it != itEnd; ++it)
	{
	    if ((*it)->getId() == id)
            return ((*it));
	}
	return (NULL);
}

Game::BulletList& Game::getBullets()
{
    return bullets;
}

Game::PlayerList& Game::getPlayers()
{
    return players;
}

Game::RocketList& Game::getRockets()
{
    return rockets;
}

float       Game::getTime() const
{
    return time;
}

Player*     Game::getReferee() const
{
    return referee;
}

int     threadFunc(void *data)
{
    Game*   game = static_cast<Game*>(data);

    while (true)
    {
        game->run();
        if (game->getPlayers().size() > 0)
            if (game->gameOver())
            {
                cout << "Game Over " << game->getId() << endl;
                string  t;
                t += CMD_OVER;
                game->sendAll(t);
                break;
            }
            else
            {
                if (!game->nextLevel())
                    break;
            }
        else
            break;
    }
    delete game;
    return (0);
}
