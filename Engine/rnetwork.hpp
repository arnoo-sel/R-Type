#ifndef RNETWORK_HPP
#define RNETWORK_HPP

#include "singleton.hpp"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "ressource.hpp"
#include <QMap>
#include "application.hpp"
#include "rships.hpp"
#include "rmonsters.hpp"

#define BUFFER_SIZE 128

class RNetwork : public Singleton<RNetwork>, public Ressource
{
public:
    typedef bool (RNetwork::*action)(QMap<QString, QString>&);
	friend class Singleton<RNetwork>;
	RNetwork();
        ~RNetwork();
    bool do_receive(QMap<QString, QString>& properties);
	void send(std::string data);
        void init(const std::string host, unsigned short port, RShips*, RMonsters*);
	static QMap<QString, action> actions;
        bool isReferee() const;
        bool isGameStared() const;
        int getNbPlayers() const;
        int getPlayerId() const;
        char getColor() const;
        int getScore() const;
        char getLives() const;
        bool& levelChanged();
        bool isGameOver() const;
private:
        bool gameOver;
        char lives;
        int score;
        bool referee;
        bool _levelChanged;
        int nbPlayers;
        bool gameStarted;
        int playerId;
        RShips *ships;
        RMonsters *monsters;
                char color;
	typedef void (RNetwork::*cmd)(std::string& data);
	Application *app;
    sf::UdpSocket socket;
	std::string host;
	unsigned short port;
	QMap<char, cmd> cmds;
	void cmd_gameInfo(std::string& data);
	void cmd_playerMoving(std::string& data);
	void cmd_playerCharging(std::string& data);
	void cmd_playerStopCharging(std::string& data);
	void cmd_playerDying(std::string& data);
	void cmd_rocketMoving(std::string& data);
	void cmd_rocketExploding(std::string& data);
	void cmd_monsterMoving(std::string& data);
	void cmd_monsterDying(std::string& data);
	void cmd_bulletMoving(std::string& data);
	void cmd_bulletExploding(std::string& data);
        void cmd_gameStart(std::string& data);
        void cmd_changeLevel(std::string& data);
        void cmd_changeLevelMessage(std::string& data);
        void cmd_gameOver(std::string& data);
        void cmd_updateScore(std::string& data);
        void initActions();
};

class Formater
{
public:
    template <class TYPE>
            static std::string& pack(std::string &data, TYPE val) {
        data += std::string((char *)&val, sizeof(TYPE));
        return data;
    }
    template <class TYPE>
            static TYPE unpack(std::string &data) {
        TYPE    out;
        out = *((TYPE *)data.c_str());
        data.erase(0, sizeof(TYPE));
        return out;
    }
};

#endif // RNETWORK_HPP
