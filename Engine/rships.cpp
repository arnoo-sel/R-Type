#include "rships.hpp"
#include "window.hpp"
#include "application.hpp"
#include "rmap.hpp"
#include "rnetwork.hpp"
#include "main.hpp"
#include "animation.hpp"

QMap<QString, RShips::action> RShips::actions;

RShips::RShips(QString name) : Ressource(name)
{
    nbShips = 0;
    shipsImage.loadFromFile("ressources/image/ships2.png");
    rocketsImage.loadFromFile("ressources/image/rockets.png");
    initActions();
    explosionImage.loadFromFile("ressources/image/explosions.png");
    explosion2Image.loadFromFile("ressources/image/anim_explosion_2.png");
    animShipImage.loadFromFile("ressources/image/anim_ship.png");
    explosionSound.loadFromFile("ressources/sounds/explosion.wav");
    hitSound.loadFromFile("ressources/sounds/hit-02.wav");
    rocketSound.loadFromFile("ressources/sounds/laser.wav");
}

void RShips::setMonsters(RMonsters *m)
{
    monsters = m;
}

bool RShips::do_move(QMap<QString, QString>& properties)
{
    Window& w = Window::instance();
    Application &app = Application::instance();

    RMap *map = dynamic_cast<RMap*>(app.getRessources()["map"][app.getRessources()["map"].keys().at(0)]);
    sf::Sprite **sprites = map->getSprites();
    RNetwork &ntw = RNetwork::instance();

    foreach(Ship* s, ships)
    {
        s->moveToCoord();
        w.draw(s->getSprite());

        if (ntw.isReferee() && (app.getTimePlusLag() - s->getSpawnTime()) > INVIS_TIME)
        {
            if (app.getRessources()["map"].size() == 1)
            {
                for (int x = 0; x < NB_BLOCK_WIDTH; x++)
                {
                    for (int y = 0; y < NB_BLOCK_HEIGHT; y++)
                    {
                        if (RMap::checkCollision(s->getSprite(), sprites[x][y]))
                        {
                            //std::cout << "BOOM COLLISION ! (" << x << "," << y << ")" <<  std::endl;
                            std::string p = "\x54";
                            Formater::pack<int>(p, ships.key(s));
                            ntw.send(p);
                        }
                    }
                }
                foreach (Monster* m, monsters->getMonsters())
                {
                    if (RMap::checkCollision(s->getSprite(), m->getSprite()))
                    {
                        std::string p = "\x55";
                        Formater::pack<int>(p, ships.key(s));
                        Formater::pack<int>(p, monsters->getMonsters().key(m));
                        ntw.send(p);
                    }
                }
                foreach (Bullet* b, monsters->getBullets())
                {
                    if (RMap::checkCollision(s->getSprite(), b->getSprite()))
                    {
                        std::string p = "\x53";
                        Formater::pack<int>(p, monsters->getBullets().key(b));
                        Formater::pack<int>(p, ships.key(s));
                        ntw.send(p);
                    }
                }
            }
            else
                std::cout << "<Collision> ERROR MAP :" << app.getRessources()["map"].size() << std::endl;
        }
    }
    foreach(Rocket* r, rockets)
    {
        if (ntw.isReferee())
        {
            foreach (Monster* m, monsters->getMonsters())
            {
                if (RMap::checkCollision(r->getSprite(), m->getSprite()))
                {
                    std::string p = "\x52";
                    Formater::pack<int>(p, rockets.key(r));
                    Formater::pack<int>(p, monsters->getMonsters().key(m));
                    ntw.send(p);
                }
            }
        }
        r->move();
        w.draw(r->getSprite());
    }

    if (ntw.levelChanged())
    {
        std::cout << "GO TO NEXT LEVEL" << std::endl;
        ntw.levelChanged() = false;
        app.getContinue() = false;
        foreach(Ship* ship, ships)
        {
            die(ships.key(ship));
        }
    }

    for (int i = 0; i < annimations.size(); i++)
    {
        bool st = annimations[i]->play();
        if (!st)
        {
            delete annimations[i];
            annimations.erase(annimations.begin() + i);
        }
        else
            w.draw(annimations[i]->getSprite());
    }
	for (int i = 0; i < sounds.size(); i++)
	{
        if (sounds[i]->getStatus() == sf::Sound::Stopped)
		{
			delete sounds[i];
			sounds.erase(sounds.begin() + i);
		}
	}
    foreach (Animation* a, animPrepRocket)
    {
        a->play();
        w.draw(a->getSprite());
    }
    return true;
}

void RShips::die(int id)
{
    std::cout << "Player " << id << " : I'm Dyyiiinnnngg!" << std::endl;
    if (ships.contains(id) && ships[id])
    {
        annimations.push_back(new Animation(explosionImage, ships[id]->getSprite().getPosition(), Animation::EXPLOSION_BIG, false, 10, 0));
        delete ships[id];
        ships.remove(id);

        delete animPrepRocket[id];
        animPrepRocket.remove(id);
        // Sound
        sf::Sound *sound = new sf::Sound;
        sound->setBuffer(explosionSound);
        sound->setVolume(50.f);
        sound->play();
        sounds.push_back(sound);
    }
}

void RShips::move(int id, char color, float time, int pX, int pY, float sX, float sY)
{
    Application &app = Application::instance();
    if (!ships.contains(id))
        add(id, color);
    ships[id]->setTrajectory(pX, pY, sX, sY, app.getTimePlusLag() - time);
}

void RShips::fire(int id, char color, float time, char size, int pX, int pY, float sX, float sY)
{
    Application &app = Application::instance();
    if (!rockets.contains(id))
    {
        Rocket *r = new Rocket(rocketsImage, id, sf::Vector2f(pX, pY), size);
        rockets[id] = r;

		sf::Sound *sound = new sf::Sound;
        sound->setBuffer(rocketSound);
        sound->setVolume(30.f + size * 10.f);
        sound->play();
		sounds.push_back(sound);
    }
    rockets[id]->setTrajectory(pX, pY, sX, app.getTimePlusLag() - time);
}

void RShips::rocketExplode(int id)
{
    if (rockets.contains(id) && rockets[id])
    {
        annimations.push_back(new Animation(explosion2Image, rockets[id]->getSprite().getPosition(), Animation::EXPLOSION_ROCKET, false, 7, 0));

        if (rockets[id]->getSprite().getPosition().x < 640)
		{
			sf::Sound *sound = new sf::Sound;
            sound->setBuffer(hitSound);
            sound->setVolume(20.f);
            sound->play();
			sounds.push_back(sound);
		}
        delete rockets[id];
        rockets.remove(id);
    }
}

void RShips::add(int id, char color)
{
    if (!ships.contains(id))
    {
        Ship *s = new Ship(id, shipsImage, (Ship::Color)color);
        ships[id] = s;
        animPrepRocket[id] = new Animation(animShipImage, s->getSprite(), Animation::PREP_ROCKET, true, 64, 8);
        animPrepRocket[id]->pause();
    }
}

void RShips::isLoading(int id, bool load)
{
    if (load == true)
        animPrepRocket[id]->start();
    else
        animPrepRocket[id]->pause();
}

void RShips::initActions()
{
        if (!actions.count("move"))
                actions["move"] = &RShips::do_move;
}

RShips::~RShips()
{
    foreach(Ship* s, ships)
        delete s;
}
