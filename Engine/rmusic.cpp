#include "rmusic.hpp"
#include "transition.hpp"
#include <sstream>

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

QMap<QString, RMusic::action> RMusic::actions;

RMusic::RMusic(QString filename, QString name) :
		sf::Music(), Ressource(name)
{
	_filename = filename;
	initActions();
	OpenFromFile(("ressources/music/" + _filename).toStdString());
	SetLoop(true);
	_properties["volume"] = "100";
}

bool RMusic::do_launch(QMap<QString, QString> &properties, const sf::Input& input)
{
	if (GetStatus() != Playing)
	{
		std::cout << "PLAY MUSIC: " << properties["ressource"].toStdString() << std::endl;
		Play();
	}
	else
	{
		Stop();
		Play();
	}
	return true;
}

bool RMusic::do_stop(QMap<QString, QString> &properties, const sf::Input& input)
{
	if (GetStatus() != Stopped)
	{
		std::cout << "STOP MUSIC: " << properties["ressource"].toStdString() << std::endl;
		Stop();
	}
	return true;
}

bool RMusic::do_pause(QMap<QString, QString> &properties, const sf::Input& input)
{
	if (GetStatus() == Playing)
	{
		std::cout << "PAUSE MUSIC: " << properties["ressource"].toStdString() << std::endl;
		Pause();
	}
	return true;
}

bool RMusic::do_volume(QMap<QString, QString> &properties, const sf::Input& input)
{
	SetVolume(_properties["volume"].toFloat());
	return true;
}

bool RMusic::do_transition(QMap<QString, QString> &properties, const sf::Input& input)
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

void RMusic::initActions()
{
	if (!actions.count("launch"))
		actions["launch"] = &RMusic::do_launch;
	if (!actions.count("stop"))
		actions["stop"] = &RMusic::do_stop;
	if (!actions.count("pause"))
		actions["pause"] = &RMusic::do_pause;
	if (!actions.count("volume"))
		actions["volume"] = &RMusic::do_volume;
	if (!actions.count("transition"))
		actions["transition"] = &RMusic::do_transition;
}
