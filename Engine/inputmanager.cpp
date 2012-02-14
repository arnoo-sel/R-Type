#include "inputmanager.hpp"

InputManager::InputManager()
{
    std::cout << "Binding Keys." << std::endl;
    for (int i = 0; i < sf::Key::Count ; i++)
    {
        actionKey[i] = NB_KEY;
    }

    setBindingKey(sf::Key::Up, MOVE_UP);
    setBindingKey(sf::Key::Down, MOVE_DOWN);
    setBindingKey(sf::Key::Left, MOVE_LEFT);
    setBindingKey(sf::Key::Right, MOVE_RIGHT);
    setBindingKey(sf::Key::Space, USE_WEAPON_1);
    setBindingKey(sf::Key::X, USE_WEAPON_2);
    setBindingKey(sf::Key::Return, ENTER);
    setBindingKey(sf::Key::Escape, EXIT);
    std::cout << "Binding Keys Done." << std::endl;
}

void InputManager::setBindingKey(sf::Key::Code key, Action action)
{
    if (action < NB_KEY && key < sf::Key::Count)
    {
        actionKey[key] = action;
        actionCode[action] = key;
    }
}

InputManager::Action InputManager::getAction(sf::Key::Code key)
{
    return actionKey[key];
}

sf::Key::Code InputManager::getKey(Action action)
{
    return actionCode[action];
}

