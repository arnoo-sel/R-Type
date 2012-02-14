#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QMap>
#include <iostream>
#include <QDomDocument>
#include <QFile>
#include "singleton.hpp"
#include "SFML/System.hpp"

class RLevel;

#define RFILE(t, f) "ressources/" + t + "/" + f

class Ressource;

/// Base du jeu. Charge les ressources globales.
/**
  * L'application requiert le chargement des ressources globales avant d'etre lancee.
  * Un main classique serait :
  * \code
  * QStringList *globalRessources;
  *
  * Application app = Application::instance();   //Cree l'instance
  * try
  * {
  *   globalRessources = app.loadRessources();   //Charge les donnees depuis 'ressources/ressources.xml'
  * }
  * catch(LoadRessourceException *e)
  * {
  *	  //...
  * }
  * app.launch();                                 //Lance l'application
  * app.quit(globalRessources);                   //Libere les ressources
  * \endcode
  **/

class Application : public Singleton<Application>, public sf::NonCopyable
{
	friend class Singleton<Application>;
public:
	typedef QMultiMap<float, QMap<QString, QString>* > actionsList;
	/// Charge les ressources d'un xml.
	/** \return la liste des noms des ressources chargees **/
	QStringList*                                loadRessources(QString rFile = "ressources/ressources.xml");
	/// Lance l'application
	int                                         launch();
	/// Libere les ressources dont les noms sont dans la liste
	void                                        quit(QStringList *ressourcesNames);
	/// Accesseur
	QMap<QString, QMap<QString, Ressource*> >&  getRessources();
	/// Indique que les actions sur un niveau ne se finiront plus en fonction du temps
	/** Les deux seuls facon de finir un niveau apres l'appel de cette fonction sont :
	  * - une action qui renvoie false
	  * - l'appel Application::instance().getContinue() = false;
	  **/
	void noTimeEnd();
	/// Renvoi le temps en seconde depuis le debut du niveau.
	float getTheTime();
	/// Renvoie une reference sur le booleen gerant la poursuite ou non du niveau.
	/** \code app.getContinue() = false; \endcode
	  * Stop le niveau et passe au suivant.
	  **/
	bool &getContinue();
	bool &getWeWantToQuit();
	void weWantToRestartLevel();
        float& getTheLag();
        float getTimePlusLag() const;
        QStringList *globalRessources;
private:
	/// Appelee par la methode instance de Singleton<Application>
												Application();
	/// Charge, lance et libere un niveau
	void                                        startUpLevel(RLevel *level);
	/// Charge le script d'un niveau
	/** \return la liste des actions. **/
	actionsList*                                loadScript(QString rFile);
	/// Lance le niveau (demarre le script)
	/** Demarre une boucle infinie sur le modele suivant :
	  * \code
	  * while (encore_des_actions_a_faire)
	  * {
	  *   met_a_jour_les_timers(TODO);
	  *   met_a_jour_la_liste_des_actions_courantes;
	  *   efface_la_fenetre;
	  *   effectue_les_actions;
	  *   affiche_le_contenu_de_la_fenetre;
	  * }
	  * \endcode
	  **/
	bool                                        launchLevel(actionsList *actions);
	/// Contient toutes les ressources, classees par type.
	/** ressources["type"]["id_de_la_ressource"]
	  * -> ressources["music"]["GRUM"] par exemple. \n\n
	  * Les types sont level/music/image
	  **/
	QMap<QString, QMap<QString, Ressource*> >   ressources;
	bool levelIsInfinite;
	float theTime;
        float theLag;
	bool _continue;
	bool _restartLevel;
	bool weWantToQuit;
	QStringList *localRessources;

};

#endif // APPLICATION_HPP
