#ifndef RHUD_HPP
#define RHUD_HPP

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"
#include "rimage.hpp"

class RHud : public Ressource
{
public:
	typedef bool (RHud::*action)(QMap<QString, QString>&, const sf::Input&);

	RHud(QString name, RImage *rImage);

	static QMap<QString, action> actions;
protected:
	bool do_display(QMap<QString, QString>& properties, const sf::Input& input);

	void initActions();

	QMap<QString, QString> _properties;
	RImage *_image;
	sf::Sprite _sprite;
	bool first;
	sf::Text _levelName, _pts, life;
	QMap<int, sf::Image> _shipsImg;
	QMap<int, sf::Sprite> _shipsSpr;

	sf::Sprite _KOBG;
	sf::Text _KOStr;
	float _KOTime;
	bool _KO, _KOSound;
	sf::Font _KOFont;
};

#endif // RHUD_HPP
