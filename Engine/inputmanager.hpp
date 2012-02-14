#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "singleton.hpp"

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class InputManager : public Singleton<InputManager>
{
public:
    enum Action
    {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        USE_WEAPON_1,
        USE_WEAPON_2,
        ENTER,
        EXIT,
        NB_KEY
    };

    InputManager();
    void setBindingKey(sf::Key::Code, Action);
    Action getAction(sf::Key::Code);
    Action inputToAction(const sf::Input &input);
    sf::Key::Code getKey(Action action);
private:
    sf::Clock clock;
    Action actionKey[sf::Key::Count];
    sf::Key::Code actionCode[NB_KEY];
};

#endif // INPUTMANAGER_HPP
