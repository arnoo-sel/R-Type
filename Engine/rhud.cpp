#include "rhud.hpp"
#include "rnetwork.hpp"
#include "rmusic.hpp"
#include "window.hpp"
#include "transition.hpp"
#include <sstream>
#include "main.hpp"

QMap<QString, RHud::action> RHud::actions;

RHud::RHud(QString name, RImage *rImage) :
		Ressource::Ressource(name)
{
	_image = rImage;
	initActions();
	first = true;
	_sprite.SetImage(*dynamic_cast<sf::Image*>(_image));

	_levelName.SetString("Level 1");
	_levelName.SetCharacterSize(20);
	_levelName.SetY(455);
	_levelName.SetX(20);

	_pts.SetString("00000 pts");
	_pts.SetCharacterSize(20);
	_pts.SetY(455);
	_pts.SetX(300);

	life.SetY(455);
	life.SetX(160);
	life.SetString("3 lives");
	life.SetCharacterSize(20);

	_shipsImg[0].LoadFromFile("ressources/image/shipb.png");
	_shipsImg[1].LoadFromFile("ressources/image/shipr.png");
	_shipsImg[2].LoadFromFile("ressources/image/shipy.png");
	_shipsImg[3].LoadFromFile("ressources/image/shipg.png");

	_shipsSpr[0].SetImage(_shipsImg[0]);
	_shipsSpr[1].SetImage(_shipsImg[1]);
	_shipsSpr[2].SetImage(_shipsImg[2]);
	_shipsSpr[3].SetImage(_shipsImg[3]);

	_shipsSpr[0].SetPosition(384, 455);
	_shipsSpr[1].SetPosition(448, 455);
	_shipsSpr[2].SetPosition(512, 455);
	_shipsSpr[3].SetPosition(576, 455);

	_shipsSpr[0].SetColor(sf::Color(255, 255, 255, 32));
	_shipsSpr[1].SetColor(sf::Color(255, 255, 255, 32));
	_shipsSpr[2].SetColor(sf::Color(255, 255, 255, 32));
	_shipsSpr[3].SetColor(sf::Color(255, 255, 255, 32));

	_KOBG.Resize(640, 480);
	_KOBG.SetPosition(0, 0);
	_KOBG.SetColor(sf::Color(0, 0, 0, 0));
	_KOTime = 10000;
	_KO = _KOSound = false;
	_KOStr.SetString("GAME OVER");
	_KOStr.SetCharacterSize(64);
	_KOStr.SetOrigin(390, 48);
	_KOStr.SetPosition(320, 200);
	_KOFont.LoadFromFile("ressources/font/LVDCGO__.TTF");
	_KOStr.SetFont(_KOFont);

}

#define DEFAULT_PROP_VALUE(prop, val) if (!properties.count(prop)) properties[prop] = val

bool RHud::do_display(QMap<QString, QString>& properties, const sf::Input& input)
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
		_sprite.SetOrigin(_image->GetWidth() / 2., _image->GetHeight() / 2.);

		_properties = properties;
		first = false;
	}

	_pts.SetString(intToString(net.getScore()) + " pts");

	//        life.SetString(std::string(1, '0' + net.getLives()) + " lives");
	life.SetString(intToString((int)net.getLives()) + " lives");

	_sprite.SetColor(sf::Color(255,255,255, _properties["a"].toFloat()));
	_sprite.SetX(_properties["x"].toFloat() + _image->GetWidth() / 2.);
	_sprite.SetY(_properties["y"].toFloat() + _image->GetHeight() / 2.);
	win.Draw(_sprite);
	win.Draw(_levelName);
	win.Draw(life);

	_shipsSpr[net.getColor()].SetColor(sf::Color(255, 255, 255, 255));

	win.Draw(_shipsSpr[0]);
	win.Draw(_shipsSpr[1]);
	win.Draw(_shipsSpr[2]);
	win.Draw(_shipsSpr[3]);

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
					dynamic_cast<RMusic*>(i.value())->Stop();
			}

			_KOSound = true;
			std::cout << "KO !" << std::endl;
			QMap<QString, QString> tmp;
			tmp["ressource"] = "__KO__";
			dynamic_cast<RMusic*>(app.getRessources()["music"]["__KO__"])->do_launch(tmp, input);
			dynamic_cast<RMusic*>(app.getRessources()["music"]["__KO__"])->SetLoop(false);
		}

		_KOBG.SetColor(sf::Color(0, 0, 0, std::min((double)255, (app.getTheTime() - _KOTime) * 200.)));
		_KOStr.SetColor(sf::Color(255, 255, 255, std::min((double)255, (app.getTheTime() - _KOTime) * 200.)));
		if (app.getTheTime() - _KOTime > 2.5)
			_KOStr.SetColor(sf::Color(255, 255, 255, std::max(0., std::min(255., (3 - (app.getTheTime() - (_KOTime + 2.5))) * 100.))));
		_KOStr.SetScale((app.getTheTime() - _KOTime) / 5.5, (app.getTheTime() - _KOTime) / 5.5);
		win.Draw(_KOBG);
		win.Draw(_KOStr);
	}
	win.Draw(_pts);
	return true;
}

void RHud::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RHud::do_display;
//	if (!actions.count("transition"))
//		actions["transition"] = &RSprite::do_transition;
}
