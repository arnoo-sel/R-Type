#ifndef RBACKGROUND_HPP
#define RBACKGROUND_HPP

#include <QMap>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"
#include "rimage.hpp"

class RBackGround : public Ressource
{
public:
    typedef bool (RBackGround::*action)(QMap<QString, QString>&);

	RBackGround(QString name, RImage* bg, RImage *fg);

	static QMap<QString, action> actions;
protected:
    bool do_display(QMap<QString, QString>& properties);
    bool do_transition(QMap<QString, QString>& properties);

	void initActions();

	bool first;
	QMap<QString, QString> _properties;
	QMap<QString, float> _times;
	RImage* _fg;
	RImage* _bg;
	sf::Sprite *sfg, *sfg2;
	sf::Sprite *sbg, *sbg2;
};


#endif // RBACKGROUND_HPP
