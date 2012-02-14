#include "rnetwork.hpp"
#include <iomanip>

QMap<QString, RNetwork::action> RNetwork::actions;

RNetwork::RNetwork() :
		Ressource("NETWORK")
{
    app = &(Application::instance());

    cmds[2] = &RNetwork::cmd_gameInfo;
    cmds[3] = &RNetwork::cmd_playerMoving;
    cmds[4] = &RNetwork::cmd_playerCharging;
    cmds[0x10] = &RNetwork::cmd_playerStopCharging;
    cmds[5] = &RNetwork::cmd_playerDying;
    cmds[6] = &RNetwork::cmd_rocketMoving;
    cmds[7] = &RNetwork::cmd_rocketExploding;
    cmds[8] = &RNetwork::cmd_monsterMoving;
    cmds[9] = &RNetwork::cmd_monsterDying;
    cmds[0x11] = &RNetwork::cmd_bulletMoving;
    cmds[0x12] = &RNetwork::cmd_bulletExploding;
    cmds[0x13] = &RNetwork::cmd_gameStart;
    cmds[0x14] = &RNetwork::cmd_changeLevel;
    cmds[0x15] = &RNetwork::cmd_updateScore;
    cmds[0x16] = &RNetwork::cmd_changeLevelMessage;
    cmds[0x17] = &RNetwork::cmd_gameOver;
    initActions();
    timers["NETWORK"].Reset();
    gameStarted = false;
    _levelChanged = false;
    score = 0;
	lives = 5;
    gameOver = false;
}

void RNetwork::init(const std::string _host, unsigned short _port, RShips* _ships, RMonsters* _monsters)
{
    unsigned short p = 2469;
    sf::IPAddress address(_host);
    if (!address.IsValid())
        throw "Invalid adress!";
    else
        std::cout << "Host okay" << std::endl;
    if (!socket.Bind(p))
        throw "Bind Error!";

    socket.SetBlocking(false);
    host = _host;
    port = _port;
    monsters = _monsters;
    ships = _ships;
    ships->setMonsters(monsters);
    playerId = -1;
}

bool RNetwork::do_receive(QMap<QString, QString>& properties, const sf::Input& input)
{
	// Envoi regulierement un signe de vie au serveur.
	static float _lifeSign = 0;
	Application &app = Application::instance();
	float currentTime = timers["NETWORK"].GetElapsedTime();
	if (currentTime - _lifeSign > 0.5)
	{
		_lifeSign = currentTime;
		send("\x42");
	}

    char buf[BUFFER_SIZE];
    std::size_t received;
    sf::IPAddress sender;
    sf::Socket::Status st;
    unsigned short p = 2469;
    while ((st = socket.Receive(buf, BUFFER_SIZE, received, sender, p)) == sf::Socket::Done)
    {
        std::string dataReceived(buf, received);
        char cmd = Formater::unpack<char>(dataReceived);
        if (cmds.contains(cmd))
        {
            (this->*cmds[cmd])(dataReceived);
        }
    }
	if (getNbPlayers() <= 0)
	{
		//      std::cout << "disconnected" << std::endl;
		//app.getWeWantToQuit() = true;
		//return false;
		send("P");
    }
        //throw "Socket Error: impossible to receive data";
    return true;
}

bool& RNetwork::levelChanged()
{
    return _levelChanged;
}

void RNetwork::send(const std::string data)
{
//    std::cout << "Send : " << data << std::endl;
    if (socket.Send(data.c_str() , data.size() , host, port) != sf::Socket::Done);
		//throw "Socket Error: impossible to send data";
}

void RNetwork::cmd_gameInfo(std::string& data)
{
    referee = Formater::unpack<bool>(data);
    nbPlayers = Formater::unpack<char>(data);
    playerId = Formater::unpack<int>(data);
	color = Formater::unpack<char>(data) - 1;
    ships->add(playerId, color);
}

void RNetwork::cmd_playerMoving(std::string& data)
{
    int id = Formater::unpack<int>(data);
    char color = Formater::unpack<char>(data) - 1;
    float time = Formater::unpack<float>(data);
    int posX = Formater::unpack<int>(data);
    int posY = Formater::unpack<int>(data);
    float speedX = Formater::unpack<float>(data);
    float speedY = Formater::unpack<float>(data);
    ships->move(id, color, time, posX, posY, speedX, speedY);
}

void RNetwork::cmd_playerCharging(std::string& data)
{
    int id = Formater::unpack<int>(data);
    ships->isLoading(id, true);
}

void RNetwork::cmd_gameStart(std::string& data)
{
    std::cout << "GAME START!" << std::endl;
    gameStarted = true;
}

void RNetwork::cmd_playerStopCharging(std::string& data)
{
    int id = Formater::unpack<int>(data);
    ships->isLoading(id, false);
}

void RNetwork::cmd_playerDying(std::string& data)
{
    int id = Formater::unpack<int>(data);
    if (id == playerId)
        lives = Formater::unpack<char>(data);
    std::cout << "BOOM PLAYER DIE" << std::endl;
    ships->die(id);
}

void RNetwork::cmd_rocketMoving(std::string& data)
{
    int id = Formater::unpack<int>(data);
    char color = Formater::unpack<char>(data);
    float time = Formater::unpack<float>(data);
    char size = Formater::unpack<char>(data);
    int posX = Formater::unpack<int>(data);
    int posY = Formater::unpack<int>(data);
    float speedX = Formater::unpack<float>(data);
    float speedY = Formater::unpack<float>(data);
    ships->fire(id, color, time, size, posX, posY, speedX, speedY);
}

void RNetwork::cmd_rocketExploding(std::string& data)
{
    int id = Formater::unpack<int>(data);
    ships->rocketExplode(id);
}

void RNetwork::cmd_monsterMoving(std::string& data)
{
    int id = Formater::unpack<int>(data);
    char type = Formater::unpack<char>(data);
    float time = Formater::unpack<float>(data);
    int posX = Formater::unpack<int>(data);
    int posY = Formater::unpack<int>(data);
    float speedX = Formater::unpack<float>(data);
    float speedY = Formater::unpack<float>(data);
//    std::cout << "Monster Moving : " << posX << " " << posY << std::endl;
    monsters->move(id, type, posX, posY, speedX, speedY, time);

}

void RNetwork::cmd_monsterDying(std::string& data)
{
    int id = Formater::unpack<int>(data);
    monsters->die(id);
}

void RNetwork::cmd_changeLevel(std::string &data)
{
    _levelChanged = true;
    lives += 4;
}

void RNetwork::cmd_changeLevelMessage(std::string &data)
{
    std::cout << "Level change in 5 sec" << std::endl;

}


void RNetwork::cmd_gameOver(std::string &data)
{
    std::cout << "Game Over" << std::endl;
    gameOver = true;
}

void RNetwork::cmd_updateScore(std::string& data)
{
    score = Formater::unpack<int>(data);
}

int RNetwork::getScore() const
{
    return score;
}


void RNetwork::cmd_bulletMoving(std::string& data)
{
    int id = Formater::unpack<int>(data);
    float time = Formater::unpack<float>(data);
    int posX = Formater::unpack<int>(data);
    int posY = Formater::unpack<int>(data);
    float speedX = Formater::unpack<float>(data);
    float speedY = Formater::unpack<float>(data);
    monsters->fire(id, posX, posY, speedX, speedY);
}

void RNetwork::cmd_bulletExploding(std::string& data)
{
    int id = Formater::unpack<int>(data);
    monsters->bulletExplode(id);
}

void RNetwork::initActions()
{
	if (!actions.count("receive"))
		actions["receive"] = &RNetwork::do_receive;
}

RNetwork::~RNetwork()
{
    socket.Close();
}

bool RNetwork::isReferee() const
{
    return referee;
}

bool RNetwork::isGameStared() const
{
    return gameStarted;
}

bool RNetwork::isGameOver() const
{
    return gameOver;
}

int RNetwork::getNbPlayers() const
{
    return nbPlayers;
}

int RNetwork::getPlayerId() const
{
    return playerId;
}

char RNetwork::getColor() const
{
	return color;
}

char RNetwork::getLives() const
{
        return lives;
}
