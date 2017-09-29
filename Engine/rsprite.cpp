#include "rsprite.hpp"
#include "window.hpp"
#include "transition.hpp"
#include <sstream>

QMap<QString, RSprite::action> RSprite::actions;

RSprite::RSprite(QString name, RImage *rImage) :
        sf::Sprite(rImage->texture()),
		Ressource::Ressource(name)
{
	_image = rImage;
	initActions();
	first = true;
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RSprite::do_display(QMap<QString, QString>& properties)
{
	Window &win = Window::instance();

	DEFAULT_PROP_VALUE("x", "0");
	DEFAULT_PROP_VALUE("y", "0");
	DEFAULT_PROP_VALUE("sx", "1");
	DEFAULT_PROP_VALUE("sy", "1");
	DEFAULT_PROP_VALUE("r", "0");
	DEFAULT_PROP_VALUE("a", "255");

	if (first)
	{
        setOrigin(_image->getSize().x / 2., _image->getSize().y / 2.);

		_properties = properties;
		first = false;
	}

    setColor(sf::Color(255,255,255, _properties["a"].toFloat()));
    setPosition(_properties["x"].toFloat() + _image->getSize().x / 2., _properties["y"].toFloat() + _image->getSize().y / 2.);
    setScale(_properties["sx"].toFloat(), _properties["sy"].toFloat());
    setRotation(_properties["r"].toFloat());
    win.draw(*dynamic_cast<sf::Sprite*>(this));
	return true;
}

bool RSprite::do_transition(QMap<QString, QString> &properties)
{
	float time = times[properties["id"]];
	float time_ratio = time / properties["length"].toFloat();

	if (time_ratio > 1)
		time_ratio = 1;

	DEFAULT_PROP_VALUE("transition", "linear_up");

	float ratio = Transition::transFunct[properties["transition"]](time_ratio);
	float value = ratio * (properties["to"].toFloat() - properties["from"].toFloat()) + properties["from"].toFloat();

	std::stringstream s;
	s << value;

	_properties[properties["property"]] = QString(s.str().c_str());
	return true;
}

void RSprite::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RSprite::do_display;
	if (!actions.count("transition"))
		actions["transition"] = &RSprite::do_transition;
}
