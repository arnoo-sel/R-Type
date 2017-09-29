#ifndef RMUSIC_HPP
#define RMUSIC_HPP

#include <QMap>
#include <QVariant>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ressource.hpp"
#include "rhud.hpp"

class RMusic : public sf::Music, public Ressource
{
public:
	friend class RHud;
    typedef bool (RMusic::*action)(QMap<QString, QString>&);

	RMusic(QString filename, QString name);

	static QMap<QString, action> actions;
protected:
    bool do_launch(QMap<QString, QString>& properties);
    bool do_stop(QMap<QString, QString>& properties);
    bool do_pause(QMap<QString, QString>& properties);
    bool do_volume(QMap<QString, QString>& properties);
    bool do_transition(QMap<QString, QString>& properties);

	void initActions();
	bool _first;
	QMap<QString, QString> _properties;
	QString _filename;
};

#endif // RMUSIC_HPP
