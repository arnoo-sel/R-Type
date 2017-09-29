#include "rhud.hpp"
#include "rnetwork.hpp"
#include "rmusic.hpp"
#include "window.hpp"
#include "transition.hpp"
#include "fonts.h"
#include <sstream>
#include "main.hpp"

QMap<QString, RHud::action> RHud::actions;

RHud::RHud(QString name, RImage *rImage) :
		Ressource::Ressource(name)
{
	_image = rImage;
	initActions();
	first = true;
    _sprite.setTexture(_image->texture());

    _levelName.setString("Level 1");
    _levelName.setCharacterSize(20);
    _levelName.setPosition(20, 455);
    _levelName.setFont(Fonts::getGlobalFont("arial"));

    _pts.setString("00000 pts");
    _pts.setCharacterSize(20);
    _pts.setPosition(300, 455);
    _pts.setFont(Fonts::getGlobalFont("arial"));

    life.setPosition(160, 455);
    life.setString("3 lives");
    life.setCharacterSize(20);
    life.setFont(Fonts::getGlobalFont("arial"));

    _shipsImg[0].loadFromFile("ressources/image/shipb.png");
    _shipsImg[1].loadFromFile("ressources/image/shipr.png");
    _shipsImg[2].loadFromFile("ressources/image/shipy.png");
    _shipsImg[3].loadFromFile("ressources/image/shipg.png");

    _shipsSpr[0].setTexture(_shipsImg[0]);
    _shipsSpr[1].setTexture(_shipsImg[1]);
    _shipsSpr[2].setTexture(_shipsImg[2]);
    _shipsSpr[3].setTexture(_shipsImg[3]);

    _shipsSpr[0].setPosition(384, 455);
    _shipsSpr[1].setPosition(448, 455);
    _shipsSpr[2].setPosition(512, 455);
    _shipsSpr[3].setPosition(576, 455);

    _shipsSpr[0].setColor(sf::Color(255, 255, 255, 32));
    _shipsSpr[1].setColor(sf::Color(255, 255, 255, 32));
    _shipsSpr[2].setColor(sf::Color(255, 255, 255, 32));
    _shipsSpr[3].setColor(sf::Color(255, 255, 255, 32));

    // _KOBG.Resize(640, 480); TODO
    _KOBG.setPosition(0, 0);
    _KOBG.setColor(sf::Color(0, 0, 0, 0));
	_KOTime = 10000;
	_KO = _KOSound = false;
    _KOStr.setString("GAME OVER");
    _KOStr.setCharacterSize(64);
    _KOStr.setOrigin(390, 48);
    _KOStr.setPosition(320, 200);
    _KOFont.loadFromFile("ressources/font/LVDCGO__.TTF");
    _KOStr.setFont(_KOFont);

}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RHud::do_display(QMap<QString, QString>& properties)
{
	Window &win = Window::instance();
	RNetwork &net = RNetwork::instance();
	Application &app = Application::instance();

	DEFAULT_PROP_VALUE("x", "0");
	DEFAULT_PROP_VALUE("y", "448");
	DEFAULT_PROP_VALUE("a", "255");

	if (net.isGameOver() && !_KO)
	{
		_KOTime = app.getTheTime();
		_KO = true;
	}

	if (first)
	{
        _sprite.setOrigin(_image->getSize().x / 2., _image->getSize().y / 2.);

		_properties = properties;
		first = false;
	}

    _pts.setString(intToString(net.getScore()) + " pts");

	//        life.SetString(std::string(1, '0' + net.getLives()) + " lives");
    life.setString(intToString((int)net.getLives()) + " lives");

    _sprite.setColor(sf::Color(255,255,255, _properties["a"].toFloat()));
    _sprite.setPosition(_properties["x"].toFloat() + _image->getSize().x / 2., _properties["y"].toFloat() + _image->getSize().y / 2.);
    win.draw(_sprite);
    win.draw(_levelName);
    win.draw(life);

    _shipsSpr[net.getColor()].setColor(sf::Color(255, 255, 255, 255));

    win.draw(_shipsSpr[0]);
    win.draw(_shipsSpr[1]);
    win.draw(_shipsSpr[2]);
    win.draw(_shipsSpr[3]);

	if (_KO && app.getTheTime() > _KOTime)
	{
		if (app.getTheTime() - _KOTime > 8)
		{
			app.getWeWantToQuit() = true;
		}

		if (app.getTheTime() - _KOTime > 0.5 && !_KOSound && app.getTheTime() - _KOTime < 3)
		{
			QMapIterator<QString, Ressource*> i(app.getRessources()["music"]);
			while (i.hasNext())
			{
				i.next();
				if (i.key() != "__KO__")
                    dynamic_cast<RMusic*>(i.value())->stop();
			}

			_KOSound = true;
			std::cout << "KO !" << std::endl;
			QMap<QString, QString> tmp;
			tmp["ressource"] = "__KO__";
            dynamic_cast<RMusic*>(app.getRessources()["music"]["__KO__"])->do_launch(tmp);
            dynamic_cast<RMusic*>(app.getRessources()["music"]["__KO__"])->setLoop(false);
		}

        _KOBG.setColor(sf::Color(0, 0, 0, std::min((double)255, (app.getTheTime() - _KOTime) * 200.)));
        _KOStr.setColor(sf::Color(255, 255, 255, std::min((double)255, (app.getTheTime() - _KOTime) * 200.)));
		if (app.getTheTime() - _KOTime > 2.5)
            _KOStr.setColor(sf::Color(255, 255, 255, std::max(0., std::min(255., (3 - (app.getTheTime() - (_KOTime + 2.5))) * 100.))));
        _KOStr.setScale((app.getTheTime() - _KOTime) / 5.5, (app.getTheTime() - _KOTime) / 5.5);
        win.draw(_KOBG);
        win.draw(_KOStr);
	}
    win.draw(_pts);
	return true;
}

void RHud::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RHud::do_display;
//	if (!actions.count("transition"))
//		actions["transition"] = &RSprite::do_transition;
}
