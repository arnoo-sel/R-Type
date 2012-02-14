#include "rmenu.hpp"

#include "rmenu.hpp"
#include "window.hpp"
#include "transition.hpp"
#include "application.hpp"
#include "rnetwork.hpp"
#include <sstream>

QMap<QString, RMenu::action> RMenu::actions;

RMenu::RMenu(QString name, QString filename) :
		Ressource::Ressource(name)
{
	_filename = filename;
	initActions();

	menuElem d2;
	d2.text="Play";
	menuElem d3;
	d3.text="Quit";

	_elems << d2 << d3;

	RMenu::aff_menu(_elems);
	RMenu::createSFMLText(_elems);

	_pos << 0;
	lastMove = 0;
	nbCols = 2;
}

void RMenu::createSFMLText(QList<menuElem> &menu)
{
	for (int j = 0 ; j < menu.size() ; ++j)
	{
		menu[j].str = new sf::Text(menu.at(j).text.toStdString());
		if (menu.at(j).subElems.size())
			RMenu::createSFMLText(menu[j].subElems);
	}
}


void RMenu::aff_menu(QList<menuElem> menu, int i)
{
	for (int j = 0 ; j < menu.size() ; ++j)
	{
		std::cout << QString(i, '\t').toStdString() << menu.at(j).text.toStdString() << std::endl;
		if (menu.at(j).subElems.size())
			RMenu::aff_menu(menu.at(j).subElems, i + 1);
	}
}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RMenu::do_display(QMap<QString, QString>& properties, const sf::Input& input)
{
	Window &win = Window::instance();
	Application &app = Application::instance();

//	DEFAULT_PROP_VALUE("x", "0");
//	DEFAULT_PROP_VALUE("y", "0");
//	DEFAULT_PROP_VALUE("sx", "1");
//	DEFAULT_PROP_VALUE("sy", "1");
//	DEFAULT_PROP_VALUE("r", "0");
	DEFAULT_PROP_VALUE("a", "255");
//	DEFAULT_PROP_VALUE("size", "20");

	static bool first = true;
	if (first)
	{
		_properties = properties;
		first = false;
	}	

	QList<menuElem> elemsToDisplay;
	QList<menuElem> tmp;

	elemsToDisplay = _elems;
	int columns = 0;
	for (; columns < _pos.size() ; ++columns)
	{
		if (_pos.size() > columns + 1)
		{
			tmp = elemsToDisplay[_pos[columns]].subElems;
			elemsToDisplay = tmp;
		}
	}
	columns--;

	if (times[properties["id"]] - lastMove > 0.15 && input.IsKeyDown(sf::Key::Down))
	{
		_pos[columns]++;
		_pos[columns] %= elemsToDisplay.size();
		lastMove = times[properties["id"]];
	}
	if (times[properties["id"]] - lastMove > 0.15 && input.IsKeyDown(sf::Key::Up))
	{
		_pos[columns]--;
		if (_pos[columns] < 0)
		_pos[columns] = elemsToDisplay.size() - 1;
		lastMove = times[properties["id"]];
	}


	for (int i = 0; i < elemsToDisplay.size() ; ++i)
	{
		if (_properties["a"].toFloat() >= 255)
			_properties["a"] = "255";
		if (i == _pos[columns])
			elemsToDisplay[i].str->SetColor(sf::Color(128, 128, 255, _properties["a"].toFloat()));
		else
			elemsToDisplay[i].str->SetColor(sf::Color(255, 255, 255, _properties["a"].toFloat()));
		elemsToDisplay[i].str->SetPosition(290, 200 + i * 55);
		win.Draw(*(elemsToDisplay[i].str));
	}

	if (times[properties["id"]] - lastMove > 0.2 && input.IsKeyDown(sf::Key::Return))
	{
		if (elemsToDisplay[_pos.last()].subElems.size())
			_pos << 0;
		else
		{
			if (_pos[0] == 1)
				app.getWeWantToQuit() = true;
			else if (_pos[0] == 0)
			{
                                RNetwork::instance().send("P");
				app.getContinue() = false;
			}
		}
		lastMove = times[properties["id"]];

	}
	if (times[properties["id"]] - lastMove > 0.2 && input.IsKeyDown(sf::Key::Back))
	{
		if (_pos.size() > 1)
			_pos.pop_back();
		lastMove = times[properties["id"]];

	}
	if (times[properties["id"]] - lastMove > 0.2 && input.IsKeyDown(sf::Key::Escape))
	{
		if (_pos.size() > 1)
			_pos.pop_back();
		else
			app.getWeWantToQuit() = true;
		lastMove = times[properties["id"]];
	}

	return true;
}

bool RMenu::do_transition(QMap<QString, QString> &properties, const sf::Input& input)
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

void RMenu::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RMenu::do_display;
	if (!actions.count("transition"))
		actions["transition"] = &RMenu::do_transition;
}
