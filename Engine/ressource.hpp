#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

#include <iostream>
#include <QString>
#include <QMap>
#include "SFML/System.hpp"

class Ressource
{
public:
	QMap<QString, sf::Clock> timers;
	QMap<QString, float> times;
	QString _name;
	virtual ~Ressource(){std::cout << "DELETE" << std::endl;};
protected:
	Ressource(QString name);
};

#endif // RESSOURCE_HPP
