#include "bullet.hpp"

Bullet::Bullet(sf::Image& img, int id)
{
    _id = id;
    _img = img;
    _spr.SetImage(_img);
}

void Bullet::move()
{
    float time = clock.GetElapsedTime();
    _spr.SetPosition(_coord);
    _spr.Move(_move.x * time, _move.y * time);
    _coord = _spr.GetPosition();
    clock.Reset();
}

void Bullet::setTrajectory(int pos_x, int pos_y, float speed_x, float speed_y, float time)
{
    float t = Application::instance().getTimePlusLag();
    _coord.x = pos_x - (t * SPEED_COEF);
    _coord.y = pos_y;
    _move.x = speed_x - (SPEED_COEF);
    _move.y = speed_y;
}

sf::Sprite& Bullet::getSprite()
{
    return _spr;
}

sf::Vector2f Bullet::getPosition()
{
    return _pos;
}

int Bullet::getId()
{
    return _id;
}

