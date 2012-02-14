#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

#include "rmap.hpp"
#include "application.hpp"

class Bullet
{
public:
    Bullet(sf::Image&, int);
    void setTrajectory(int, int, float, float, float);
    void move();
    sf::Sprite& getSprite();
    sf::Vector2f getPosition();
    int getId();

private:
    sf::Image _img;
    sf::Sprite _spr;
    sf::Vector2f _pos;
    sf::Vector2f _move;
    sf::Vector2f _coord;
    sf::Clock clock;
    int _id;
};

#endif // BULLET_HPP

