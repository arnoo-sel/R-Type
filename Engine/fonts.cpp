#include "fonts.h"

std::unordered_map<std::string, sf::Font> Fonts::fonts;

void Fonts::initialize()
{
    sf::Font arial;
    arial.loadFromFile("ressources/font/arial.ttf");
    fonts.insert({"arial", arial});
}

const sf::Font &Fonts::getGlobalFont(const std::string &name)
{
    if (fonts.count(name))
        return fonts.at(name);
    return fonts.at("arial");
}
