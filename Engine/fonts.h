#ifndef FONTS_H
#define FONTS_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class Fonts
{
public:
    static void initialize();
    static const sf::Font& getGlobalFont(const std::string& name);

private:
    static std::unordered_map<std::string, sf::Font> fonts;
};

#endif // FONTS_H
