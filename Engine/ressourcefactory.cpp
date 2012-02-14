#include "loadressourceexception.hpp"
#include "ressourcefactory.hpp"
#include "main.hpp"
#include "application.hpp"
#include <QStringList>
#include <QFile>

QMap<QString, RessourceFactory::ptr> RessourceFactory::factoryFuncts;

void RessourceFactory::initFunctsMap()
{
	if (!factoryFuncts.count("music"))
		factoryFuncts["music"] = &RessourceFactory::newRMusic;
	if (!factoryFuncts.count("level"))
		factoryFuncts["level"] = &RessourceFactory::newRLevel;
	if (!factoryFuncts.count("image"))
		factoryFuncts["image"] = &RessourceFactory::newRImage;
	if (!factoryFuncts.count("sprite"))
		factoryFuncts["sprite"] = &RessourceFactory::newRSprite;
	if (!factoryFuncts.count("text"))
		factoryFuncts["text"] = &RessourceFactory::newRText;
	if (!factoryFuncts.count("bg"))
		factoryFuncts["bg"] = &RessourceFactory::newRBackGround;
	if (!factoryFuncts.count("menu"))
		factoryFuncts["menu"] = &RessourceFactory::newRMenu;
	if (!factoryFuncts.count("map"))
		factoryFuncts["map"] = &RessourceFactory::newRMap;
	if (!factoryFuncts.count("hud"))
		factoryFuncts["hud"] = &RessourceFactory::newRHud;
	if (!factoryFuncts.count("network"))
		factoryFuncts["network"] = &RessourceFactory::newRNetwork;
	if (!factoryFuncts.count("ships"))
		factoryFuncts["ships"] = &RessourceFactory::newRShips;
	if (!factoryFuncts.count("wait"))
		factoryFuncts["wait"] = &RessourceFactory::newRWait;
	if (!factoryFuncts.count("input"))
		factoryFuncts["input"] = &RessourceFactory::newRInput;
	if (!factoryFuncts.count("monsters"))
		factoryFuncts["monsters"] = &RessourceFactory::newRMonsters;
}


Ressource* RessourceFactory::newRMusic(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "file";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
	COUT << "New MUSIC : " << ENDL;
	RessourceFactory::showProperties(properties);
	return new RMusic(properties["file"], properties["id"]);
}

Ressource* RessourceFactory::newRLevel(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "file";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
	COUT << "New LEVEL : " << ENDL;
	RessourceFactory::showProperties(properties);
	return new RLevel(properties["id"], properties["file"]);
}

Ressource* RessourceFactory::newRImage(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "file";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
	COUT << "New IMAGE : " << ENDL;
	RessourceFactory::showProperties(properties);
	return new RImage(properties["id"], properties["file"]);
}

Ressource* RessourceFactory::newRMenu(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "file";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
	COUT << "New MENU : " << ENDL;
	RessourceFactory::showProperties(properties);
	return new RMenu(properties["id"], properties["file"]);
}

Ressource* RessourceFactory::newRMap(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "file";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
	COUT << "New MAP : " << ENDL;
	RessourceFactory::showProperties(properties);
	return new RMap(properties["id"], properties["file"]);
}

Ressource* RessourceFactory::newRWait(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "network";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
	COUT << "New WAIT : " << ENDL;
	RessourceFactory::showProperties(properties);
	return new RWait(properties["id"]);
}

Ressource* RessourceFactory::newRShips(QMap<QString, QString> &properties)
{
	//  QStringList mandatoryFields;
	//  mandatoryFields << "file";
	//  RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
        COUT << "New SHIPS : " << ENDL;
        RessourceFactory::showProperties(properties);
        return new RShips(properties["id"]);
}

Ressource* RessourceFactory::newRMonsters(QMap<QString, QString> &properties)
{
        COUT << "New MONSTERS : " << ENDL;
        RessourceFactory::showProperties(properties);
        return new RMonsters(properties["id"]);
}


Ressource* RessourceFactory::newRInput(QMap<QString, QString> &properties)
{
        COUT << "New INPUT : " << ENDL;
        RessourceFactory::showProperties(properties);
        return new RInput(properties["id"]);
}



Ressource* RessourceFactory::newRSprite(QMap<QString, QString> &properties)
{
	Application &app = Application::instance();
	QStringList mandatoryFields;
	mandatoryFields << "image";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);

	COUT << "New SPRITE" << ENDL;
	RessourceFactory::showProperties(properties);
	return new RSprite(properties["id"], dynamic_cast<RImage*>(app.getRessources()["image"][properties["image"]]));
}

Ressource* RessourceFactory::newRHud(QMap<QString, QString> &properties)
{
	Application &app = Application::instance();
	QStringList mandatoryFields;
	mandatoryFields << "image";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);

	COUT << "New HUD" << ENDL;
	RessourceFactory::showProperties(properties);
	return new RHud(properties["id"], dynamic_cast<RImage*>(app.getRessources()["image"][properties["image"]]));
}

Ressource* RessourceFactory::newRBackGround(QMap<QString, QString> &properties)
{
	Application &app = Application::instance();
	QStringList mandatoryFields;
	mandatoryFields << "fg" << "bg";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);

	COUT << "New BACKGROUND" << ENDL;
	RessourceFactory::showProperties(properties);
	return new RBackGround(properties["id"], dynamic_cast<RImage*>(app.getRessources()["image"][properties["bg"]]),
						   dynamic_cast<RImage*>(app.getRessources()["image"][properties["fg"]]));
}

Ressource* RessourceFactory::newRText(QMap<QString, QString> &properties)
{
	QStringList mandatoryFields;
	mandatoryFields << "text";
	RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);

	COUT << "New TEXT" << ENDL;
	RessourceFactory::showProperties(properties);
	return new RText(properties["id"], properties["text"]);
}

Ressource* RessourceFactory::newRNetwork(QMap<QString, QString> &properties)
{
    Application &app = Application::instance();
    QStringList mandatoryFields;
    mandatoryFields << "ships";
    RessourceFactory::checkMandatoryProperties(properties, mandatoryFields);
    COUT << "New NETWORK" << ENDL;
    RessourceFactory::showProperties(properties);
    Ressource *r = &(RNetwork::instance());
    try
    {
		QString host;
		unsigned short port;
		QFile conf("server.conf");
		conf.open(QIODevice::ReadOnly | QIODevice::Text);
		while (!conf.atEnd())
		{
			QByteArray tmp = conf.readLine();
			QString tmp2(tmp);
			if (tmp2.startsWith("#"))
				continue;
			if (tmp2.startsWith("host:"))
			{
				host = tmp2.split(":").at(1);
				host.chop(1);
			}
			if (tmp2.startsWith("port:"))
				port = tmp2.split(":").at(1).toInt();
		}
		std::cout << "SERVER CONF : " << host.toStdString() << ":" << port << std::endl;
		conf.close();
                RNetwork::instance().init(host.toStdString(), port,
                                          dynamic_cast<RShips*>(app.getRessources()["ships"][properties["ships"]]),
                                          dynamic_cast<RMonsters*>(app.getRessources()["monsters"][properties["monsters"]]));
    }
    catch (char const *a)
    {
        std::cout << "exp: " << a << std::endl;
        getchar();
    }
    return r;
}

Ressource* RessourceFactory::newRessource(QDomElement &elem, QString fromFile)
{
	QMap<QString, QString> properties;
	QDomNamedNodeMap attributes = elem.attributes();

	initFunctsMap();
	for (uint i = 0; i < attributes.length(); ++i)
		properties[attributes.item(i).nodeName()] = attributes.item(i).nodeValue();
	if (!properties.count("id"))
		throw(new LoadRessourceException("", "Field id missing", fromFile, elem.lineNumber()));
	return factoryFuncts[elem.tagName().toLower()](properties);
}

void RessourceFactory::showProperties(QMap<QString, QString> &properties)
{
	QMapIterator<QString, QString> i(properties);
	while (i.hasNext())
	{
		i.next();
		COUT << "\t" << i.key().toStdString() << ": " << i.value().toStdString() << ENDL;
	}
}

void RessourceFactory::checkMandatoryProperties(QMap<QString, QString>& properties, QStringList &mandatoryFields)
{
	for (int i = 0 ; i < mandatoryFields.size() ; ++i)
	{
		if (!properties.count(mandatoryFields.at(i)))
			throw(new LoadRessourceException(properties["id"], "Field "+ mandatoryFields.at(i) +" is missing"));
	}
}
