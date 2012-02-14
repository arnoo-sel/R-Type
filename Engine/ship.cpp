#include "ship.hpp"
#include "application.hpp"
#include "rmap.hpp"
#include "application.hpp"
// Verifier les cout de debug et penser a les enlever pour le rendu


Ship::Ship(int id, sf::Image& img, Ship::Color color)
{
	_spr.SetColor(sf::Color(255, 255, 255, 0));
	spawnTime = -1;
    _id = id;
    _img = img;
    _spr.SetImage(_img);
    _move.x = 0;
    _move.y = 0;
    _coord.x = 100;
    fclock.Reset();
    switch(color)
    {
    case Ship::BLUE :
        {
            _coord.y = 110;
            std::cout << "set BLUE ship" << std::endl;
            _spr.SetSubRect(C_BLUE);
            break;
        }
    case Ship::RED :
        {
            _coord.y = 170;
            std::cout << "set RED ship" << std::endl;
            _spr.SetSubRect(C_RED);
            break;
        }
    case Ship::YELLOW :
        {
            _coord.y = 230;
            std::cout << "set YELLOW ship" << std::endl;
            _spr.SetSubRect(C_YELLOW);
            break;
        }
    case Ship::GREEN :
        {
            _coord.y = 290;
            std::cout << "set GREEN ship" << std::endl;
            _spr.SetSubRect(C_GREEN);
            break;
        }
    default :
            break;
}
}

void Ship::setTrajectory(int coord_x, int coord_y, float speed_x, float speed_y, float time)
{
    Application &app = Application::instance();
    float t = app.getTimePlusLag();
    app.getTheLag() -= (time / 5);
    _coord.x = coord_x - (t * SPEED_COEF);
    _coord.y = coord_y;
    _move.x = speed_x - (SPEED_COEF);
    _move.y = speed_y;
    _time = time;
    _coord += _move * time;
}

void Ship::setLagLimit()
{
    _limit = SPEED / (1 + lclock.GetElapsedTime());
    lclock.Reset();
}

void Ship::moveToCoord()
{
    float t = fclock.GetElapsedTime();

	if (spawnTime < 0)
		spawnTime = Application::instance().getTheTime();
	std::cout << (Application::instance().getTheTime() - spawnTime) << std::endl;
    if ((Application::instance().getTheTime() - spawnTime) > INVIS_TIME)
        _spr.SetColor(sf::Color(255, 255, 255, 255));
	else if ((Application::instance().getTheTime() - spawnTime) < (INVIS_TIME / 4.))
		_spr.SetColor(sf::Color(255, 255, 255, 0));
	else
		_spr.SetColor(sf::Color(255, 255, 255, (((int)((Application::instance().getTheTime() - spawnTime) * 4)) % 2) * 128 + 0));
	_spr.SetPosition(_coord);
    _spr.Move(_move.x * t, _move.y * t);
    _coord = _spr.GetPosition();
    fclock.Reset();
}

void Ship::resetClock()
{
    clock.Reset();
}

sf::Sprite& Ship::getSprite()
{
    return _spr;
}

float Ship::getSpawnTime() const
{
    return spawnTime;
}
