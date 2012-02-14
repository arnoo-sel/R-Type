#include "window.hpp"

Window::Window() :
		sf::RenderWindow(sf::VideoMode(640, 480, 32), "R-Type")
{
	UseVerticalSync(true);
}
