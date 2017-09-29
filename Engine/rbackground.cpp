#include "rbackground.hpp"
#include "window.hpp"
#include "transition.hpp"
#include <sstream>

QMap<QString, RBackGround::action> RBackGround::actions;

RBackGround::RBackGround(QString name, RImage *bg, RImage *fg) :
		Ressource::Ressource(name)
{
	_bg = bg;
	_fg = fg;
    sfg = new sf::Sprite(_fg->texture());
    sbg = new sf::Sprite(_bg->texture());
    sfg2 = new sf::Sprite(_fg->texture());
    sbg2 = new sf::Sprite(_bg->texture());
    sfg2->setPosition(_fg->getSize().x, sfg2->getPosition().y);
    sbg2->setPosition(_bg->getSize().x, sbg2->getPosition().y);
	initActions();
	first = true;
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RBackGround::do_display(QMap<QString, QString>& properties)
{
	Window &win = Window::instance();


	DEFAULT_PROP_VALUE("sfg", "20");
	DEFAULT_PROP_VALUE("sbg", "15");
	DEFAULT_PROP_VALUE("a", "255");

	if (first)
	{
		_properties = properties;
		_times[properties["id"]] = 0;
		first = false;
	}

	float timeDiff = times[properties["id"]] - _times[properties["id"]];
	float movementBG = _properties["sbg"].toFloat() * timeDiff;
	float movementFG = _properties["sfg"].toFloat() * timeDiff;

	_times[properties["id"]] = times[properties["id"]];

    sbg->setColor(sf::Color(255,255,255, _properties["a"].toFloat()));
    sfg->setColor(sf::Color(255,255,255, _properties["a"].toFloat()));
    sbg2->setColor(sf::Color(255,255,255, _properties["a"].toFloat()));
    sfg2->setColor(sf::Color(255,255,255, _properties["a"].toFloat()));

    sbg->move(-movementBG, 0);
    sfg->move(-movementFG, 0);
    sbg2->move(-movementBG, 0);
    sfg2->move(-movementFG, 0);

    if (sbg->getPosition().x < -(int)_bg->getSize().x)
        sbg->move(_bg->getSize().x * 2., 0);
    if (sbg2->getPosition().x < -(int)_bg->getSize().x)
        sbg2->move(_bg->getSize().x * 2., 0);
    if (sfg->getPosition().x < -(int)_fg->getSize().x)
        sfg->move(_fg->getSize().x * 2., 0);
    if (sfg2->getPosition().x < -(int)_fg->getSize().x)
        sfg2->move(_fg->getSize().x * 2., 0);

    win.draw(*sbg);
    win.draw(*sbg2);
    win.draw(*sfg);
    win.draw(*sfg2);

	return true;
}

bool RBackGround::do_transition(QMap<QString, QString> &properties)
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

void RBackGround::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RBackGround::do_display;
	if (!actions.count("transition"))
		actions["transition"] = &RBackGround::do_transition;
}
