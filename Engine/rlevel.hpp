#ifndef RLEVEL_HPP
#define RLEVEL_HPP

#include <iostream>
#include "ressource.hpp"
#include "SFML/Graphics.hpp"

class RLevel : public Ressource
{
public:
    typedef bool (RLevel::*action)(QMap<QString, QString>&);

	RLevel(QString name, QString filename);
	const QString &getFilename() const;
	static QMap<QString, action> actions;
protected:
    bool do_infinite(QMap<QString, QString>& properties);
	void initActions();

	QString _filename;	
};

#endif // RLEVEL_HPP
