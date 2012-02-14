#include "rsprite.hpp"
#include "window.hpp"
#include "transition.hpp"
#include <sstream>

QMap<QString, RSprite::action> RSprite::actions;

RSprite::RSprite(QString name, RImage *rImage) :
		sf::Sprite(*dynamic_cast<sf::Image*>(rImage)),
		Ressource::Ressource(name)
{
	_image = rImage;
	initActions();
	first = true;
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RSprite::do_display(QMap<QString, QString>& properties, const sf::Input& input)
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
		SetOrigin(_image->GetWidth() / 2., _image->GetHeight() / 2.);

		_properties = properties;
		first = false;
	}

	SetColor(sf::Color(255,255,255, _properties["a"].toFloat()));
	SetX(_properties["x"].toFloat() + _image->GetWidth() / 2.);
	SetY(_properties["y"].toFloat() + _image->GetHeight() / 2.);
	SetScale(_properties["sx"].toFloat(), _properties["sy"].toFloat());
	SetRotation(_properties["r"].toFloat());
	win.Draw(*dynamic_cast<sf::Sprite*>(this));
	return true;
}

bool RSprite::do_transition(QMap<QString, QString> &properties, const sf::Input& input)
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
