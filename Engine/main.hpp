#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

#define COUT std::cout
#define ENDL std::endl

#include <sstream>

template<typename T>
std::string intToString(T i)
{
	std::stringstream s;
	s << i;
	return (s.str());
}
#endif // MAIN_HPP
