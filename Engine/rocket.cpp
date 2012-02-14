#include "rocket.hpp"
#include <iostream>
#include "rmap.hpp"
#include "application.hpp"

Rocket::Rocket(sf::Image& img, int id, sf::Vector2f pos, int pow)
{
    _img = img;
    _spr.SetImage(_img);
    switch (pow)
    {
    case 0 :
        {
            _spr.SetSubRect(R_POW_0);
            break;
        }
    case 1 :
        {
            _spr.SetSubRect(R_POW_1);
            break;
        }
    case 2 :
        {
            _spr.SetSubRect(R_POW_2);
            break;
        }
    case 3 :
        {
            _spr.SetSubRect(R_POW_3);
            break;
        }
    case 4 :
        {
            _spr.SetSubRect(R_POW_4);
            break;
        }
    case 5 :
        {
            _spr.SetSubRect(R_POW_5);
            break;
        }
    default : break;
    }
}

void Rocket::move()
{
    float time = clock.GetElapsedTime();
    _spr.SetPosition(_coord);
    _spr.Move(_move.x * time, 0);
    _coord = _spr.GetPosition();
    clock.Reset();
}

void Rocket::setTrajectory(int pos_x, int pos_y, float speed, float time)
{
    float t = Application::instance().getTimePlusLag();
    _coord.x = pos_x - (t * SPEED_COEF);
    _coord.y = pos_y;
    _move.x = speed - (SPEED_COEF);
    _move.y = 0;
}

sf::Sprite Rocket::getSprite()
{
    return _spr;
}

sf::Vector2f Rocket::getPosition()
{
    return _pos;
}

int Rocket::getId()
{
    return _id;
}
