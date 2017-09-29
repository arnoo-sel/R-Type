#ifndef RWAIT_HPP
#define RWAIT_HPP

#include <QMap>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"

class RWait : public Ressource
{
public:
    typedef bool (RWait::*action)(QMap<QString, QString>&);

	RWait(QString name);

	static QMap<QString, action> actions;
protected:
    bool do_wait(QMap<QString, QString>& properties);

	void initActions();

	sf::Text waitForPlayers, pressStart, you, connectError, help;
    sf::Texture shipsImg;
	sf::Sprite ships;
};

#endif // RWAIT_HPP
