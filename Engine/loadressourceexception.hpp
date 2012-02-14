#ifndef LOADRESSOURCEEXCEPTION_HPP
#define LOADRESSOURCEEXCEPTION_HPP

#include <iostream>
#include <QString>

class LoadRessourceException : public std::exception
{
public:
	LoadRessourceException(QString name, QString _desc = "", QString file = "", int line = -1);
	~LoadRessourceException() throw() {};
	virtual const char* what() const throw();
private:
	std::string _file;
	std::string _desc;
	std::string _name;
	int _line;

};

#endif // LOADRESSOURCEEXCEPTION_HPP
