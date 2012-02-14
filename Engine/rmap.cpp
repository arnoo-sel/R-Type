#include "rmap.hpp"
#include <QString>
#include <QFile>
#include <iostream>

#include "window.hpp"
#include "application.hpp"
#include "rnetwork.hpp"

QMap<QString, RMap::action> RMap::actions;

RMap::RMap(QString name, const QString& fileName) :
		Ressource(name)
{
    first = true;
	initActions();
	QFile file("ressources/map/" + fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))    
		throw "ERROR: Unable to open file ";
    else
        while (!file.atEnd())
            txtMap << QString(file.readLine()).left(8);
    file.close();
	imageAlpha.LoadFromFile("ressources/map/alpha.png");
	iBottomLeft.LoadFromFile("ressources/map/bottomleft.png");
	iTopLeft.LoadFromFile("ressources/map/topleft.png");
	iMiddle.LoadFromFile("ressources/map/middle.png");
	iMiddle1.LoadFromFile("ressources/map/middle1.png");
	iMiddle2.LoadFromFile("ressources/map/middle2.png");
	iMiddle3.LoadFromFile("ressources/map/middle3.png");
	iMiddle4.LoadFromFile("ressources/map/middle4.png");
	iLeft1.LoadFromFile("ressources/map/left1.png");

	iAlone.LoadFromFile("ressources/map/alone.png");
	iTopRight.LoadFromFile("ressources/map/topright.png");
	iTop1.LoadFromFile("ressources/map/top1.png");
	iBottomRight.LoadFromFile("ressources/map/bottomright.png");
	iBottom1.LoadFromFile("ressources/map/bottom1.png");
	iMiddle5.LoadFromFile("ressources/map/middle5.png");
	iRight1.LoadFromFile("ressources/map/right1.png");
	iMiddle6.LoadFromFile("ressources/map/middle6.png");

    blockId = 0;

    for(int i = 0; i < txtMap.size(); i++)
		;//std::cout << txtMap[i].toStdString();
    screen = new sf::Sprite*[NB_BLOCK_WIDTH];
    for (int x = 0; x < NB_BLOCK_WIDTH; x++)
        screen[x] = new sf::Sprite[NB_BLOCK_HEIGHT];
}

void RMap::setImage(sf::Sprite &s, int x, int y)
{
    if (x < txtMap.size() - 1 && txtMap[x][y] == 'X')
    {
        if (x + 1 != txtMap.size() -1 && txtMap[x + 1][y] == 'X') //si block a droite
        {
            if (x == 0 || txtMap[x - 1][y] != 'X') //si pas block a gauche
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iLeft1);
                else if (BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iBottomLeft);
                else if (!BLOCK_ABOVE(x, y) && BLOCK_BELOW(x, y))
                    s.SetImage(iTopLeft);
                else
                    s.SetImage(iMiddle4);
            }
            else
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iMiddle1);
                else if (BLOCK_BELOW(x, y) && !BLOCK_ABOVE(x, y))
                    s.SetImage(iMiddle2);
                else if (!BLOCK_BELOW(x, y) && BLOCK_ABOVE(x, y))
                    s.SetImage(iMiddle3);
                else
                    s.SetImage(iMiddle);
            }
        }
        else
        {
            if (x == 0 || txtMap[x - 1][y] != 'X') //si pas block a gauche
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iAlone);
                else if (BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iBottom1);
                else if (!BLOCK_ABOVE(x, y) && BLOCK_BELOW(x, y))
                    s.SetImage(iTop1);
                else
                    s.SetImage(iMiddle6);
            }
            else
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iRight1);
                else if (BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.SetImage(iBottomRight);
                else if (!BLOCK_ABOVE(x, y) && BLOCK_BELOW(x, y))
                    s.SetImage(iTopRight);
                else
                    s.SetImage(iMiddle5);
            }
        }
    }
    else
        s.SetImage(imageAlpha);
}

bool RMap::do_display(QMap<QString, QString> &properties, const sf::Input &input)
{
	Window &window = Window::instance();
	Application &app = Application::instance();

        float time = app.getTimePlusLag();

    if (first)
        for (int x = 0; x < NB_BLOCK_WIDTH; x++)
            for (int y = 0; y < NB_BLOCK_HEIGHT; y++)
                setImage(screen[x][y], x, y);
    first = false;
    if ((int)floor(time / (BLOCK_SIZE / (float)SPEED_COEF)) > blockId && (blockId + (NB_BLOCK_WIDTH - 1)) < txtMap.size())
    {
        for (int x = 0; x < NB_BLOCK_WIDTH; x++)
        {
            for (int y = 0; y < NB_BLOCK_HEIGHT; y += 1)
            {
                if (x != (NB_BLOCK_WIDTH - 1))
                {
                    screen[x][y] = screen[x + 1][y];
                }
                else
                {
                    sf::Sprite s;
                    setImage(s, blockId + NB_BLOCK_WIDTH, y);
                    screen[x][y] = s;
                }
            }
        }
        blockId++;
    }

    for (int x = 0; x < NB_BLOCK_WIDTH; x += 1)
    {
        for (int y = 0; y < NB_BLOCK_HEIGHT; y += 1)
        {
            if ((blockId + (NB_BLOCK_WIDTH - 1)) < txtMap.size())
                screen[x][y].SetX(x  * BLOCK_SIZE - ((int)floor(time * SPEED_COEF) % BLOCK_SIZE));
            else
                screen[x][y].SetX(x  * BLOCK_SIZE);
            screen[x][y].SetY(384 - y * BLOCK_SIZE);
            window.Draw(screen[x][y]);
        }
    }
	//return ((blockId + (NB_BLOCK_WIDTH - 1)) < txtMap.size());
	return true;
}

void RMap::initActions()
{
	if (!actions.count("display"))
		actions["display"] = &RMap::do_display;
}

sf::Sprite** RMap::getSprites() const
{
    return screen;
}

bool RMap::checkCollision(const sf::Sprite& s1, const sf::Sprite& s2)
{
    // Définition de deux objets représentant les dimensions de s1 et s2.
    sf::Vector2f pos = s1.GetPosition() - s1.GetOrigin();
    const sf::Rect<float> r1(pos.x, pos.y, pos.x + s1.GetSize().x, pos.y + s1.GetSize().y);
    pos = s2.GetPosition() - s2.GetOrigin();
    const sf::Rect<float> r2(pos.x, pos.y, pos.x + s2.GetSize().x, pos.y + s2.GetSize().y);

    // Espace de collision potentiel.
    sf::Rect<float> zone;

    // Testons si les Sprites se superposent.
    if (r1.Intersects(r2, zone))
    {
            //on recupere les limites des superposition des zones
            int left1 = static_cast<int>(zone.Left - r1.Left);
            int top1 = static_cast<int>(zone.Top - r1.Top);

            int left2 = static_cast<int>(zone.Left - r2.Left);
            int top2 = static_cast<int>(zone.Top - r2.Top);
            int width = static_cast<int>(zone.GetSize().x);
            int height = static_cast<int>(zone.GetSize().y);

            // On calcul pour chaque pixel de la zone de collision si les pixel autre que transparent se superpose
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    //si c'est le cas on renvois true
                    if (s1.GetPixel(x + left1, y + top1).a >= 1 && s2.GetPixel(x + left2, y + top2).a >= 1)
                        return true;
                }
            }
            return false;
        }

    return false;
}

