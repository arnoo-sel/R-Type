#include "application.hpp"
#include "main.hpp"
#include "loadressourceexception.hpp"
#include "ressourcefactory.hpp"
#include "window.hpp"
#include "rmusic.hpp"
#include "rmenu.hpp"
#include "transition.hpp"
#include <iostream>
#include <QFileInfo>
#include <QStringList>
#include "rships.hpp"
#include "rmonsters.hpp"

Application::Application()
{
	std::cout << "*** Starting Application ***" << std::endl;
	Transition::initTransition();
	weWantToQuit = false;
	levelIsInfinite = false;
	_restartLevel = false;
}

QStringList *Application::loadRessources(QString rFile)
{
	QStringList *addedRessources = new QStringList;
	QFileInfo fileInfo(rFile);
	QDomDocument doc(fileInfo.baseName());
	QFile file(rFile);
	if (!file.open(QIODevice::ReadOnly))
		throw new LoadRessourceException(file.fileName(), "Can't load file" , __FILE__, __LINE__);
	if (!doc.setContent(&file))
	{
		QString filename = file.fileName();
		file.close();
		throw new LoadRessourceException(filename, "Can't parse XML", __FILE__, __LINE__);
	}
	file.close();

	COUT << "LOADING RESSOURCES FROM " << rFile.toStdString() << "..." << ENDL;
	QDomElement docElem = doc.documentElement();
	QDomNode n = docElem.firstChildElement("ressources").firstChild();
	while(!n.isNull())
	{
		QDomElement e = n.toElement();
		if(!e.isNull())
		{
			if (ressources[e.tagName().toLower()].count(e.attribute("id")))
				throw(new LoadRessourceException(e.attribute("id", "__undefined"),
												 "Ressource id already exists", fileInfo.fileName(), e.lineNumber()));
			ressources[e.tagName().toLower()][e.attribute("id")] = RessourceFactory::newRessource(e, fileInfo.fileName());
			*addedRessources << (e.tagName().toLower() + "/" +  e.attribute("id"));
		}
		n = n.nextSibling();
	}
	COUT << "DONE" << ENDL;
	return addedRessources;
}

int Application::launch()
{
	QMap<QString, RLevel*> levels;
	QMutableMapIterator<QString, Ressource*> it(ressources["level"]);
	while(it.hasNext())
	{
		it.next();
		levels[it.key()] = dynamic_cast<RLevel*>(it.value());
	}
	COUT << "LEVELS ARE :"<< ENDL;
	foreach(RLevel *value, levels)
		COUT << "\t" << value->_name.toStdString() << ":" << value->getFilename().toStdString() << ENDL;

	QMapIterator<QString, RLevel*> i(levels);
	while (!weWantToQuit && i.hasNext())
	{
		i.next();
		startUpLevel(i.value());
	}

	COUT << "PRESS ENTER TO EXIT" << ENDL;
	//getchar();
	return 0;
}

void Application::quit(QStringList *ressourcesNames)
{
	for (int i = 0 ; i < ressourcesNames->size() ; ++i)
	{
		delete ressources[ressourcesNames->at(i).split("/").at(0)][ressourcesNames->at(i).split("/").at(1)];
		ressources[ressourcesNames->at(i).split("/").at(0)].remove(ressourcesNames->at(i).split("/").at(1));
	}
}

void Application::startUpLevel(RLevel *level)
{
	actionsList *actions;

	COUT << ENDL << "STARTING UP LEVEL : " << level->_name.toStdString() << ENDL;
	try
	{
		localRessources = loadRessources("ressources/level/" + level->getFilename());
		actions = loadScript("ressources/level/" + level->getFilename());
	}
	catch(std::exception *e)
	{
		COUT << e->what() << ENDL;
		getchar();
		exit(-1);
	}
	launchLevel(actions);
	quit(localRessources);
}

Application::actionsList *Application::loadScript(QString rFile)
{
	actionsList *actions = new actionsList;

	QFileInfo fileInfo(rFile);
	QDomDocument doc(fileInfo.baseName());
	QFile file(rFile);
	if (!file.open(QIODevice::ReadOnly))
		throw new LoadRessourceException(file.fileName(), "Can't load file" , __FILE__, __LINE__);
	if (!doc.setContent(&file))
	{
		QString filename = file.fileName();
		file.close();
		throw new LoadRessourceException(filename, "Can't parse XML", __FILE__, __LINE__);
	}
	file.close();

	COUT << "LOADING SCRIPT FROM " << rFile.toStdString() << "..." << ENDL;
	QDomElement docElem = doc.documentElement();
	QDomNode n = docElem.firstChildElement("script").firstChild();
	while(!n.isNull())
	{
		QDomElement e = n.toElement();
		if(!e.isNull())
		{
			QMap<QString, QString> *properties = new QMap<QString, QString>;
			QDomNamedNodeMap attributes = e.attributes();

			for (uint i = 0; i < attributes.length(); ++i)
				(*properties)[attributes.item(i).nodeName()] = attributes.item(i).nodeValue();
			if (!properties->count("time"))
				throw(new LoadRessourceException("", "Field time missing", rFile, e.lineNumber()));
			(*properties)["type"] = e.tagName().toLower();
			actions->insert((*properties)["time"].toFloat(), properties);
		}
		n = n.nextSibling();
	}
	COUT << "DONE" << ENDL;
	return actions;
}

#define REGISTER_ACTIONS(TYPE, TAG) if ((*currentActions.at(i))["type"] == TAG) \
	ok_to_continue = ((dynamic_cast<TYPE*>(ressources[TAG] \
	[(*currentActions.at(i))["ressource"]])) \
	->*(TYPE::actions[(*currentActions.at(i))["do"]]))((*currentActions.at(i)), input);

bool Application::launchLevel(actionsList *actions)
{
	Window &window = Window::instance();
	weWantToQuit = false;
	levelIsInfinite = false;
	sf::Clock timer;
	_continue = true;
	theTime = 0;
	theLag = 0;
	QList<QMap<QString, QString>* > currentActions;

	window.SetFramerateLimit(60);
	COUT << "LAUNCH LEVEL" << ENDL;
	timer.Reset();

	while (_continue && !weWantToQuit)
	{
		//On met a jour tous les timers
		theTime = timer.GetElapsedTime();
		for (int i = 0 ; i < currentActions.size() ; ++i)
		{
			ressources[(*currentActions.at(i))["type"]][(*currentActions.at(i))["ressource"]]->times[(*currentActions.at(i))["id"]] =
					ressources[(*currentActions.at(i))["type"]][(*currentActions.at(i))["ressource"]]->timers[(*currentActions.at(i))["id"]].GetElapsedTime();
		}

		//On purge la liste des actions en cours
		if (!levelIsInfinite)
		{
			QList<int> toRemove;
			for (int i = 0 ; i < currentActions.size() ; ++i)
			{
				if (!(*currentActions.at(i)).count("length"))
				{
					toRemove.append(i);
				}
				else
				{
					if (ressources[(*currentActions.at(i))["type"]]
							[(*currentActions.at(i))["ressource"]]
							->times[(*currentActions.at(i))["id"]] >
							(*currentActions.at(i))["length"].toFloat())
					{
						toRemove.append(i);
					}
				}
			}
			for (int i = 0 ; i < toRemove.size() ; ++i)
			{
				currentActions.removeAt(toRemove.at(i));
			}
		}

		//On ajoute de nouvelles actions a la liste des actions en cours
		while (actions->keys().size() && actions->keys().at(0) < theTime)
		{
			QList<QMap<QString, QString>* > instantActions = actions->values(actions->keys().at(0));
			for (int i = 0 ; i < instantActions.size() ; ++i)
			{
				if ((*instantActions.at(i)).count("length"))
				{
					ressources[(*instantActions.at(i))["type"]][(*instantActions.at(i))["ressource"]]->timers[(*instantActions.at(i))["id"]];
					ressources[(*instantActions.at(i))["type"]][(*instantActions.at(i))["ressource"]]->times[(*instantActions.at(i))["id"]] = 0;
				}
			}
			currentActions += instantActions;
			actions->remove(actions->keys().at(0));
		}
		if (!actions->keys().size() && !currentActions.size())
			_continue = false;


		sf::Event event;
		while (window.GetEvent(event))
		{
			// Fenêtre fermée
			if (event.Type == sf::Event::Closed || (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape))
				weWantToQuit = true;

		}

		//On efface la fenetre
		window.Clear(sf::Color(0, 0, 0));

		const sf::Input& input = window.GetInput();

		//On execute les actions
		bool ok_to_continue = true;
		for (int i = 0 ; i < currentActions.size() ; ++i)
		{
			REGISTER_ACTIONS(RMusic, "music");
			REGISTER_ACTIONS(RSprite, "sprite");
			REGISTER_ACTIONS(RText, "text");
			REGISTER_ACTIONS(RBackGround, "bg");
			REGISTER_ACTIONS(RMenu, "menu");
			REGISTER_ACTIONS(RLevel, "level");
			REGISTER_ACTIONS(RMap, "map");
			REGISTER_ACTIONS(RHud, "hud");
			REGISTER_ACTIONS(RNetwork, "network");
			REGISTER_ACTIONS(RShips, "ships");
			REGISTER_ACTIONS(RMonsters, "monsters");
			REGISTER_ACTIONS(RWait, "wait");
			REGISTER_ACTIONS(RInput, "input");
		}


		//On re-affiche le conntenu de la fenetre
		window.Display();
		if (!ok_to_continue)
			_continue = false;
	}
	COUT << "END OF LEVEL" << ENDL;
	return true;
}

QMap<QString, QMap<QString, Ressource*> >&  Application::getRessources()
{
	return ressources;
}

void Application::noTimeEnd()
{
	levelIsInfinite = true;
}

float Application::getTheTime()
{
	return theTime;
}

float& Application::getTheLag()
{
	return theLag;
}

float Application::getTimePlusLag() const
{
	return theLag + theTime;
}

bool &Application::getContinue()
{
	return _continue;
}

bool &Application::getWeWantToQuit()
{
	return weWantToQuit;
}

void Application::weWantToRestartLevel()
{
	_restartLevel  = true;
}
