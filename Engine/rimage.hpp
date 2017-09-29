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
    sf::Texture& texture();

private:
	QString _filename;
    sf::Texture _texture;
};

#endif // RIMAGE_HPP
