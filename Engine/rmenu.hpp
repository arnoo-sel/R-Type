#ifndef RMENU_HPP
#define RMENU_HPP

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"

class RMenu : public Ressource
{
public:
    typedef bool (RMenu::*action)(QMap<QString, QString>&);
	struct menuElem
	{
		QList<menuElem> subElems;
		QString text;
		sf::Text *str;
	};

	RMenu(QString name, QString filename);

	static QMap<QString, action> actions;
protected:
    bool do_display(QMap<QString, QString>& properties);
    bool do_transition(QMap<QString, QString>& properties);
	void initActions();

    void aff_menu(QList<menuElem>, int i = 0);
    void createSFMLText(QList<menuElem>& menu);


	QMap<QString, QString> _properties;
	QString _filename;
	QList<menuElem> _elems;
	QList<int> _pos;
	float lastMove;
	int nbCols;
};

#endif // RMENU_HPP
