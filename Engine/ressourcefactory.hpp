#ifndef RESSOURCEFACTORY_HPP
#define RESSOURCEFACTORY_HPP

#include <map>
#include <QMap>
#include <QDomNode>
#include "ressource.hpp"
#include "rmusic.hpp"
#include "rlevel.hpp"
#include "rimage.hpp"
#include "rsprite.hpp"
#include "rtext.hpp"
#include "rbackground.hpp"
#include "rmenu.hpp"
#include "rmap.hpp"
#include "rhud.hpp"
#include "rnetwork.hpp"
#include "rships.hpp"
#include "rwait.hpp"
#include "rinput.hpp"
#include "rmonsters.hpp"

class RessourceFactory
{
public:
	typedef Ressource* (*ptr)(QMap<QString, QString>&);
	static Ressource* newRessource(QDomElement &elem, QString fromFile = "");
	static void showProperties(QMap<QString, QString> &properties);
private:
	static Ressource* newRMusic(QMap<QString, QString>& properties);
	static Ressource* newRLevel(QMap<QString, QString>& properties);
	static Ressource* newRImage(QMap<QString, QString>& properties);
	static Ressource* newRSprite(QMap<QString, QString>& properties);
	static Ressource* newRText(QMap<QString, QString>& properties);
	static Ressource* newRBackGround(QMap<QString, QString>& properties);
	static Ressource* newRMenu(QMap<QString, QString>& properties);
	static Ressource* newRMap(QMap<QString, QString>& properties);
	static Ressource* newRHud(QMap<QString, QString>& properties);
	static Ressource* newRNetwork(QMap<QString, QString>& properties);
	static Ressource* newRWait(QMap<QString, QString>& properties);
	static Ressource* newRShips(QMap<QString, QString>& properties);
        static Ressource* newRMonsters(QMap<QString, QString>& properties);
        static void checkMandatoryProperties(QMap<QString, QString>& properties, QStringList &mandatoryFields);
	static Ressource* newRInput(QMap<QString, QString>& properties);

	static void initFunctsMap();
	static QMap<QString, ptr> factoryFuncts;
};

#endif // RESSOURCEFACTORY_HPP
