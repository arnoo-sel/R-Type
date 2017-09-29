#include "rwait.hpp"
#include "window.hpp"
#include "application.hpp"
#include "rnetwork.hpp"
#include "fonts.h"

QMap<QString, RWait::action> RWait::actions;

RWait::RWait(QString name) :
		Ressource::Ressource(name)
{
	initActions();
    waitForPlayers.setString("Waiting for players ...");
    waitForPlayers.setPosition(175, 100);
    waitForPlayers.setFont(Fonts::getGlobalFont("arial"));
    pressStart.setString("Press space to launch game");
    pressStart.setPosition(140, 400);
    pressStart.setFont(Fonts::getGlobalFont("arial"));
    shipsImg.loadFromFile("ressources/image/ships2.png");
    ships.setTexture(shipsImg);
    ships.setPosition(288, 200);
    ships.setTextureRect(sf::IntRect(0, 0, 64, 30));
    you.setString("<<< You !");
    you.setFont(Fonts::getGlobalFont("arial"));
    connectError.setString("Can't connect to server");
    connectError.setPosition(160, 400);
    connectError.setFont(Fonts::getGlobalFont("arial"));
    help.setString("Specify server in server.conf");
    help.setCharacterSize(15);
    help.setPosition(220, 448);
    help.setFont(Fonts::getGlobalFont("arial"));
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RWait::do_wait(QMap<QString, QString>& properties)
{
	Window &win = Window::instance();
	Application &app = Application::instance();
	RNetwork &net = RNetwork::instance();

    if (net.isReferee() && net.getNbPlayers() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		app.getContinue() = false;

    ships.setTextureRect(sf::IntRect(0, 0, 64, net.getNbPlayers() * 30));
    you.setPosition(360, 197 + 30 * net.getColor());

    win.draw(waitForPlayers);
	if (net.getNbPlayers())
	{
		if (net.isReferee())
            win.draw(pressStart);
        win.draw(ships);
        win.draw(you);
	}
	else
	{
        win.draw(connectError);
        win.draw(help);
	}
	if (net.isGameStared())
		app.getContinue() = false;
	return true;
}

void RWait::initActions()
{
	if (!actions.count("wait"))
		actions["wait"] = &RWait::do_wait;
}
