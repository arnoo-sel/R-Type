#include "rtext.hpp"
#include "window.hpp"
#include "transition.hpp"
#include "fonts.h"
#include <sstream>

QMap<QString, RText::action> RText::actions;

RText::RText(QString name, QString text) :
		Ressource::Ressource(name)
{
	_text = text;
	initActions();
    setString(_text.toStdString());
    setFont(Fonts::getGlobalFont("arial"));
	first = true;
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RText::do_display(QMap<QString, QString>& properties)
{
	Window &win = Window::instance();

	DEFAULT_PROP_VALUE("x", "0");
	DEFAULT_PROP_VALUE("y", "0");
	DEFAULT_PROP_VALUE("sx", "1");
	DEFAULT_PROP_VALUE("sy", "1");
	DEFAULT_PROP_VALUE("r", "0");
	DEFAULT_PROP_VALUE("a", "255");
	DEFAULT_PROP_VALUE("size", "20");

	if (first)
	{
		_properties = properties;
		first = false;
	}
	
	if (_properties["a"].toFloat() >= 255)
		_properties["a"] = "254";
    setColor(sf::Color(255,255,255, _properties["a"].toFloat()));
    setCharacterSize(properties["size"].toFloat());
    setPosition(_properties["x"].toFloat(), _properties["y"].toFloat());
    setScale(_properties["sx"].toFloat(), _properties["sy"].toFloat());
    setRotation(_properties["r"].toFloat());
    win.draw(*dynamic_cast<sf::Text*>(this));
	return true;
}

bool RText::do_transition(QMap<QString, QString> &properties)
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

void RText::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RText::do_display;
	if (!actions.count("transition"))
		actions["transition"] = &RText::do_transition;
}
