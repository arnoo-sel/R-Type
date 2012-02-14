#include "monster.hpp"

Monster::Monster(sf::Image& img, int id, int type, int pos_x, int pos_y, float speed_x, float speed_y)
{
    _img = img;
    _type = type;
    _pos.x = pos_x;
    _pos.y = pos_y;
    _speed.x = speed_x;
    _speed.y = speed_y;
    _spr.SetImage(_img);
    _spr.SetPosition(_pos);
}

void Monster::setTrajectory(float pos_x, float pos_y, float speed_x, float speed_y, float time)
{
    Application &app = Application::instance();
    float t = app.getTimePlusLag();
    _pos.x = pos_x - (t * SPEED_COEF);
    _pos.y = pos_y;
    _speed.x = speed_x - (SPEED_COEF);
    _speed.y = speed_y;
    _pos += _speed * time;
}

void Monster::move()
{
    float time = _clock.GetElapsedTime();

    _spr.SetPosition(_pos);
    _spr.Move(_speed.x * time, _speed.y * time);
    _pos = _spr.GetPosition();
    _clock.Reset();
}

sf::Sprite Monster::getSprite()
{
    return _spr;
}

int Monster::getId()
{
    return _id;
}

int Monster::getType()
{
    return _type;
}

void Monster::resetClock()
{
    _clock.Reset();
}
