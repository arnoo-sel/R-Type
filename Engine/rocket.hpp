#ifndef ROCKET_HPP
#define ROCKET_HPP

#include <SFML/Graphics.hpp>

#define R_POW_0 sf::IntRect(82, 0, 111 ,9)
#define R_POW_1 sf::IntRect(78, 15, 111, 31)
#define R_POW_2 sf::IntRect(57, 36, 111, 55)
#define R_POW_3 sf::IntRect(47, 61, 111, 81)
#define R_POW_4 sf::IntRect(16, 87, 111, 110)
#define R_POW_5 sf::IntRect(0, 116, 111, 140)

#define R_SPEED 400

class Rocket
{
public:
    Rocket(sf::Image&, int id, sf::Vector2f, int pow);
    void setTrajectory(int, int, float, float);
    void move();
    sf::Sprite getSprite();
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
#endif // ROCKET_HPP
