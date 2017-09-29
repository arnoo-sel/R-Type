#ifndef RMONSTERS_HPP
#define RMONSTERS_HPP

#include <QMap>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ressource.hpp"
#include "ship.hpp"
#include "rocket.hpp"
#include "monster.hpp"
#include "bullet.hpp"
#include "animation.hpp"

class RMonsters : public Ressource
{
private:
    QMap<int, Monster*> monsters;
    QMap<int, Bullet*> bullets;
    QMap<char, sf::Texture> monstersImages;
    QVector<Animation*> annimations;
	QVector<sf::Sound*> sounds;

    sf::Texture bulletsImage;
    sf::Texture animExplosionImage;
	sf::SoundBuffer explosionSound;

protected:
    void initActions();
public:
    typedef bool (RMonsters::*action)(QMap<QString, QString>&);

    RMonsters(QString name);
    ~RMonsters();

    const QMap<int, Monster*>& getMonsters() const;
    const QMap<int, Bullet*>& getBullets() const;
    void move(int id, char type, int pX, int pY, float sX, float sY, float time);
    void fire(int id, int pX, int pY, float sX, float sY);
    void bulletExplode(int id);
    void die(int id);
    bool do_move(QMap<QString, QString>& properties);
    static QMap<QString, action> actions;
};

#endif // RMONSTERS_HPP
