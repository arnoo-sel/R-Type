#ifndef RIMAGE_HPP
#define RIMAGE_HPP

#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"

class RImage : public sf::Image, public Ressource
{
public:
	RImage(QString name, QString filename);
private:
	QString _filename;
};

#endif // RIMAGE_HPP
