#ifndef RSHIPS_HPP
#define RSHIPS_HPP

#include <QMap>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ressource.hpp"
#include "ship.hpp"
#include "rocket.hpp"
#include "rmonsters.hpp"
#include "monster.hpp"
#include "animation.hpp"

class RShips : public Ressource
{
private:
    QMap<int, Ship*> ships;
    QMap<int, Rocket*> rockets;
    QMap<int, Animation*> animPrepRocket;
    QVector<Animation*> annimations;
    QVector<sf::Sound*> sounds;

    short nbShips;
    sf::Image shipsImage;
    sf::Image rocketsImage;
    sf::Image explosionImage;
    sf::Image explosion2Image;
    sf::Image animShipImage;
    RMonsters* monsters;
	sf::SoundBuffer explosionSound;
	sf::SoundBuffer hitSound;
	sf::SoundBuffer rocketSound;

protected:
    void initActions();
public:
    typedef bool (RShips::*action)(QMap<QString, QString>&, const sf::Input&);

    RShips(QString name);
    ~RShips();

    void move(int id, char color, float time, int pX, int pY, float sX, float sY);
    void fire(int id, char color, float time, char size, int pX, int pY, float sX, float sY);
    void add(int id, char color);
    void rocketExplode(int id);
    void setMonsters(RMonsters *m);
    void die(int id);
    void isLoading(int, bool);
    bool do_move(QMap<QString, QString>& properties, const sf::Input& input);
    static QMap<QString, action> actions;
};

#endif // RSHIPS_HPP
