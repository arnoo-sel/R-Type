#include "rwait.hpp"
#include "window.hpp"
#include "application.hpp"
#include "rnetwork.hpp"

QMap<QString, RWait::action> RWait::actions;

RWait::RWait(QString name) :
		Ressource::Ressource(name)
{
	initActions();
	waitForPlayers.SetString("Waiting for players ...");
	waitForPlayers.SetPosition(175, 100);
	pressStart.SetString("Press space to launch game");
	pressStart.SetPosition(140, 400);
	shipsImg.LoadFromFile("ressources/image/ships2.png");
	ships.SetImage(shipsImg);
	ships.SetPosition(288, 200);
	ships.SetSubRect(sf::IntRect(0, 0, 64, 30));
	you.SetString("<<< You !");
	connectError.SetString("Can't connect to server");
	connectError.SetPosition(160, 400);
	help.SetString("Specify server in server.conf");
	help.SetCharacterSize(15);
	help.SetX(220);
	help.SetY(448);
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RWait::do_wait(QMap<QString, QString>& properties, const sf::Input& input)
{
	Window &win = Window::instance();
	Application &app = Application::instance();
	RNetwork &net = RNetwork::instance();

	if (net.isReferee() && net.getNbPlayers() && input.IsKeyDown(sf::Key::Space))
		app.getContinue() = false;

	ships.SetSubRect(sf::IntRect(0, 0, 64, net.getNbPlayers() * 30));
	you.SetPosition(360, 197 + 30 * net.getColor());

	win.Draw(waitForPlayers);
	if (net.getNbPlayers())
	{
		if (net.isReferee())
			win.Draw(pressStart);
		win.Draw(ships);
		win.Draw(you);
	}
	else
	{
		win.Draw(connectError);
		win.Draw(help);
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
