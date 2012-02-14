#include "loadressourceexception.hpp"
#include "main.hpp"

LoadRessourceException::LoadRessourceException(QString name, QString desc, QString file, int line)
{
	_file = file.toStdString();
	_desc = desc.toStdString();
	_name = name.toStdString();
	_line = line;
	if (_desc != "")
		_desc.insert(0, " : ");
}

const char* LoadRessourceException::what() const throw()
{
	if (_file == "" && _line < 0)
		return std::string("Error loading ressource `" + _name + "'" + _desc).c_str();
	else if (_line < 0)
		return std::string("Error loading ressource `" + _name + "' in "+ _file + _desc).c_str();
	else
		return std::string("Error loading ressource `" + _name + "' in " + _file +
						   ":" + intToString(_line) + _desc).c_str();
}
