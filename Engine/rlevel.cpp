#include "rlevel.hpp"
#include "application.hpp"

QMap<QString, RLevel::action> RLevel::actions;

RLevel::RLevel(QString name, QString filename) :
		Ressource(name)
{
	initActions();
	_filename = filename;
}

const QString &RLevel::getFilename() const
{
	return(_filename);
}

bool RLevel::do_infinite(QMap<QString, QString> &properties, const sf::Input &input)
{
	Application &app = Application::instance();

	app.noTimeEnd();
	return true;
}

void RLevel::initActions()
{
	if (!actions.count("infinite"))
		actions["infinite"] = &RLevel::do_infinite;
}
