#include "rimage.hpp"

RImage::RImage(QString name, QString filename) :
		sf::Image(), Ressource(name)
{
	_filename = filename;
	LoadFromFile("ressources/image/" + _filename.toStdString());
}
