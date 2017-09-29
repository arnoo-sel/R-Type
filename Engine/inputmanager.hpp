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
    void setBindingKey(sf::Keyboard::Key, Action);
    Action getAction(sf::Keyboard::Key);
    //Action inputToAction(const sf::Input &input);
    sf::Keyboard::Key getKey(Action action);
private:
    sf::Clock clock;
    Action actionKey[sf::Keyboard::KeyCount];
    sf::Keyboard::Key actionCode[NB_KEY];
};

#endif // INPUTMANAGER_HPP
