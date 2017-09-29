#include "server.hpp"
#include "time.h"
#include "stdlib.h"
#include <iostream>

Server::Server(int port) : running(false)
{
	socket = new AbstractSocket(port);
    game = NULL;
}

Server::~Server()
{
    while (games.size() > 0)
    {
        delete games.front();
        games.pop_front();
    }
	delete socket;
}

Player*     Server::findPlayer(string& ip)
{
    std::cout << "findPlayer" << std::endl;
    PlayerList::iterator pl, plEnd = players.end();
	for (pl = players.begin(); pl != plEnd; ++pl)
	{
		if ((*pl)->getIp() == ip)
            return (*pl);
	}

    return (NULL);
}

void		Server::stop()
{
    running = false;
}

Server::PlayerList& Server::getPlayers()
{
    return players;
}

Game*&      Server::getCurrentGame()
{
    return game;
}

void		Server::run()
{
	string	buff, ip;
    Player* p;

    srand(time(NULL));

    try {
	running = true;
	while ((running == true))
	{
		buff = socket->recv(100, &ip);

        if ((p = findPlayer(ip)))
        {
            p->recv(buff);
        }
        else if (buff == WELCOME_MSG)
        {
            cout << "New client " << ip << endl;
            if (!game)
                game = new Game(this);
            if (game->started() || game->getPlayers().size() >= MAX_PLAYERS)
            {
                // New game
//                games.push_back(game);
                game = new Game(this);
            }
            cout << "Added to game " << game->getId() << endl;
            p = new Player(game, ip);
            players.push_back(p);
        }
	}
    } catch (std::exception *e) {
        cerr << e->what() << endl;
        delete e;
        sleep(20000);
    }
}
