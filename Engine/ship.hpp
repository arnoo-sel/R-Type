#ifndef SHIP_HPP
#define SHIP_HPP

//Verifier si les includes sont necessaire.

#include <SFML/Graphics.hpp>
#include <QString>
#include <iostream>

#define SPEED 400
#define LIMIT SPEED / 1.1

#define C_BLUE sf::IntRect(0, 0, 64, 26)
#define C_RED sf::IntRect(0, 30, 64, 57)
#define C_YELLOW sf::IntRect(0, 61, 64, 88)
#define C_GREEN sf::IntRect(0, 92, 64, 118)
#define INVIS_TIME 3
class Ship
{
public:
    enum Color
    {
        BLUE,
        RED,
        YELLOW,
        GREEN,
        NONE
    };

    //Enum de test
    enum Move
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STALL
    };

    Ship(int id, sf::Image&, Color);
    void moveToCoord();
    void setTrajectory(int, int, float, float, float);
    void resetClock();
    sf::Sprite& getSprite();
    void setLagLimit();
    float getSpawnTime() const;
private:
    int _id;
    float spawnTime;
    sf::Sprite _spr;
    sf::Image _img;
    sf::Clock clock;
    sf::Clock fclock;
    sf::Clock lclock;
    // a changer pour implementer Application
    sf::Window Window;
    sf::Vector2f _move;
    sf::Vector2f _coord;
    float _limit;
    int _speed;
    float _time;
};

#endif // SHIP_HPP
