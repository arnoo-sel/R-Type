#include "rmonsters.hpp"
#include "window.hpp"
#include "application.hpp"
#include "rmap.hpp"
#include "rnetwork.hpp"
#include "main.hpp"

QMap<QString, RMonsters::action> RMonsters::actions;

RMonsters::RMonsters(QString name) : Ressource(name)
{
    std::cout << "Create Monsters" << std::endl;
    monstersImages[1].LoadFromFile("ressources/image/monster1.png");
    monstersImages[2].LoadFromFile("ressources/image/robot.png");
    monstersImages[3].LoadFromFile("ressources/image/boss.png");
    monstersImages[4].LoadFromFile("ressources/image/boss2.png");
    monstersImages[5].LoadFromFile("ressources/image/boss3.png");
        bulletsImage.LoadFromFile("ressources/image/bullet.png");
	animExplosionImage.LoadFromFile("ressources/image/explosions.png");
	explosionSound.LoadFromFile("ressources/sounds/explosion.wav");
	initActions();
}

bool RMonsters::do_move(QMap<QString, QString>& properties, const sf::Input& input)
{
    Window& w = Window::instance();
    foreach(Monster *m, monsters)
    {
        m->move();
        w.Draw(m->getSprite());
    }
    foreach(Bullet *b, bullets)
    {
        b->move();
        w.Draw(b->getSprite());
    }
	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i]->GetStatus() == sf::Sound::Stopped)
		{
			delete sounds[i];
			sounds.erase(sounds.begin() + i);
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
                    w.Draw(annimations[i]->getSprite());
	}
    return true;
}

void RMonsters::die(int id)
{
	if (!monsters[id])
		return;
    int type = monsters[id]->getType();
    if (type == 1)
        annimations.push_back(new Animation(animExplosionImage, monsters[id]->getSprite().GetPosition(),Animation::EXPLOSION_MID, false));
    if (type == 2)
        annimations.push_back(new Animation(animExplosionImage, monsters[id]->getSprite().GetPosition(),Animation::EXPLOSION_BIG, false));
    if (type == 3)
    {
        int coord[28][2] = {{10, 79}, {19, 103}, {36, 50}, {55, 42}, {105, 14}, {143, 49}, {88, 78}, {163, 94}, {132, 131}, {137, 144},
                            {160, 130}, {192, 116}, {148, 166}, {179, 156}, {213, 153}, {145, 179}, {171, 173}, {208, 163}, {144, 189}, {176, 187},
                            {212,182}, {131, 207}, {157, 207}, {195, 202}, {146, 238}, {179, 243}, {150, 268}, {109, 283}};
        for (int i = 0; i < 28; i++)
            annimations.push_back(new Animation(animExplosionImage, monsters[id]->getSprite().GetPosition(),Animation::EXPLOSION_BIG, false,coord[i][0], coord[i][1]));
    }
    if (type == 4)
    {
        int coord[28][2] = {{10, 79}, {19, 103}, {36, 50}, {55, 42}, {105, 14}, {143, 49}, {88, 78}, {163, 94}, {132, 131}, {137, 144},
                            {160, 130}, {192, 116}, {148, 166}, {179, 156}, {213, 153}, {145, 179}, {171, 173}, {208, 163}, {144, 189}, {176, 187},
                            {212,182}, {131, 207}, {157, 207}, {195, 202}, {146, 238}, {179, 243}, {150, 268}, {109, 283}};
        for (int i = 0; i < 28; i++)
            annimations.push_back(new Animation(animExplosionImage, monsters[id]->getSprite().GetPosition(),Animation::EXPLOSION_BIG, false,coord[i][0], coord[i][1]));
    }
    if (type == 5)
    {
        int coord[28][2] = {{10, 79}, {19, 103}, {36, 50}, {55, 42}, {105, 14}, {143, 49}, {88, 78}, {163, 94}, {132, 131}, {137, 144},
                            {160, 130}, {192, 116}, {148, 166}, {179, 156}, {213, 153}, {145, 179}, {171, 173}, {208, 163}, {144, 189}, {176, 187},
                            {212,182}, {131, 207}, {157, 207}, {195, 202}, {146, 238}, {179, 243}, {150, 268}, {109, 283}};
        for (int i = 0; i < 28; i++)
            annimations.push_back(new Animation(animExplosionImage, monsters[id]->getSprite().GetPosition(),Animation::EXPLOSION_BIG, false,coord[i][0], coord[i][1]));
    }
	// Sound
	if (monsters[id]->getSprite().GetPosition().x > 0)
	{
		sf::Sound *sound = new sf::Sound;
		sound->SetBuffer(explosionSound);
		sound->SetVolume(40.f);
		sound->Play();
		sounds.push_back(sound);
	}

	delete monsters[id];
	monsters.remove(id);
}

void RMonsters::move(int id, char type, int pX, int pY, float sX, float sY, float time)
{
    Application &app = Application::instance();
    if (!monsters.contains(id))
    {
        Monster *m = new Monster(monstersImages[type], id, type, pX, pY, sX, sY);
        monsters[id] = m;
    }
    monsters[id]->setTrajectory(pX, pY, sX, sY, app.getTimePlusLag() - time);
}

void RMonsters::fire(int id, int pX, int pY, float sX, float sY)
{
    if (!bullets.contains(id))
    {
        Bullet *b = new Bullet(bulletsImage, id);
        bullets[id] = b;
    }
    bullets[id]->setTrajectory(pX, pY, sX, sY, 0);
}

void RMonsters::bulletExplode(int id)
{
    delete bullets[id];
    bullets.remove(id);
}

void RMonsters::initActions()
{
    if (!actions.count("move"))
            actions["move"] = &RMonsters::do_move;
}

RMonsters::~RMonsters()
{
    foreach(Monster* m, monsters)
        delete m;
}


const QMap<int, Monster*>& RMonsters::getMonsters() const
{
    return monsters;
}

const QMap<int, Bullet*>& RMonsters::getBullets() const
{
    return bullets;
}
