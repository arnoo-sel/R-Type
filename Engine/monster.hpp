#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include "application.hpp"
#include "rmap.hpp"

class Monster
{
public:
    Monster(sf::Image&, int, int, int, int, float, float);
    void setTrajectory(float, float, float, float, float);
    void move();
    void resetClock();
    sf::Sprite getSprite();
    int getId();
    int getType();
private:
    sf::Image _img;
    sf::Sprite _spr;
    sf::Clock _clock;
    sf::Vector2f _pos;
    sf::Vector2f _speed;
    int _type;
    int _id;
    float _time;
};

#endif // MONSTER_HPP
