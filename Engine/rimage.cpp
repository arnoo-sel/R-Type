#include "rimage.hpp"

RImage::RImage(QString name, QString filename) :
		sf::Image(), Ressource(name)
{
	_filename = filename;
    loadFromFile("ressources/image/" + _filename.toStdString());
    _texture.loadFromImage(*this);
}

sf::Texture &RImage::texture()
{
    return _texture;
}
