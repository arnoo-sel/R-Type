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
	sfg = new sf::Sprite(*_fg);
	sbg = new sf::Sprite(*_bg);
	sfg2 = new sf::Sprite(*_fg);
	sbg2 = new sf::Sprite(*_bg);
	sfg2->SetX(_fg->GetWidth());
	sbg2->SetX(_bg->GetWidth());
	initActions();
	first = true;
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RBackGround::do_display(QMap<QString, QString>& properties, const sf::Input& input)
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

	sbg->SetColor(sf::Color(255,255,255, _properties["a"].toFloat()));
	sfg->SetColor(sf::Color(255,255,255, _properties["a"].toFloat()));
	sbg2->SetColor(sf::Color(255,255,255, _properties["a"].toFloat()));
	sfg2->SetColor(sf::Color(255,255,255, _properties["a"].toFloat()));

	sbg->Move(-movementBG, 0);
	sfg->Move(-movementFG, 0);
	sbg2->Move(-movementBG, 0);
	sfg2->Move(-movementFG, 0);

	if (sbg->GetPosition().x < -(int)_bg->GetWidth())
		sbg->Move(_bg->GetWidth() * 2., 0);
	if (sbg2->GetPosition().x < -(int)_bg->GetWidth())
		sbg2->Move(_bg->GetWidth() * 2., 0);
	if (sfg->GetPosition().x < -(int)_fg->GetWidth())
		sfg->Move(_fg->GetWidth() * 2., 0);
	if (sfg2->GetPosition().x < -(int)_fg->GetWidth())
		sfg2->Move(_fg->GetWidth() * 2., 0);

	win.Draw(*sbg);
	win.Draw(*sbg2);
	win.Draw(*sfg);
	win.Draw(*sfg2);

	return true;
}

bool RBackGround::do_transition(QMap<QString, QString> &properties, const sf::Input& input)
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
