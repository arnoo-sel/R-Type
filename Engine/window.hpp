#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "singleton.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Window : public Singleton<Window>, public sf::RenderWindow
{
public:
	friend class Singleton<Window>;
protected:
    Window();
};

#endif // WINDOW_HPP
