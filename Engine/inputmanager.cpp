#include "inputmanager.hpp"

InputManager::InputManager()
{
    std::cout << "Binding Keys." << std::endl;
    for (int i = 0; i < sf::Keyboard::KeyCount ; i++)
    {
        actionKey[i] = NB_KEY;
    }

    setBindingKey(sf::Keyboard::Up, MOVE_UP);
    setBindingKey(sf::Keyboard::Down, MOVE_DOWN);
    setBindingKey(sf::Keyboard::Left, MOVE_LEFT);
    setBindingKey(sf::Keyboard::Right, MOVE_RIGHT);
    setBindingKey(sf::Keyboard::Space, USE_WEAPON_1);
    setBindingKey(sf::Keyboard::X, USE_WEAPON_2);
    setBindingKey(sf::Keyboard::Return, ENTER);
    setBindingKey(sf::Keyboard::Escape, EXIT);
    std::cout << "Binding Keys Done." << std::endl;
}

void InputManager::setBindingKey(sf::Keyboard::Key key, Action action)
{
    if (action < NB_KEY && key < sf::Keyboard::KeyCount)
    {
        actionKey[key] = action;
        actionCode[action] = key;
    }
}

InputManager::Action InputManager::getAction(sf::Keyboard::Key key)
{
    return actionKey[key];
}

sf::Keyboard::Key InputManager::getKey(Action action)
{
    return actionCode[action];
}

