#include "rmap.hpp"
#include <QString>
#include <QFile>
#include <iostream>
#include <cmath>

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
    imageAlpha.loadFromFile("ressources/map/alpha.png");
    iBottomLeft.loadFromFile("ressources/map/bottomleft.png");
    iTopLeft.loadFromFile("ressources/map/topleft.png");
    iMiddle.loadFromFile("ressources/map/middle.png");
    iMiddle1.loadFromFile("ressources/map/middle1.png");
    iMiddle2.loadFromFile("ressources/map/middle2.png");
    iMiddle3.loadFromFile("ressources/map/middle3.png");
    iMiddle4.loadFromFile("ressources/map/middle4.png");
    iLeft1.loadFromFile("ressources/map/left1.png");

    iAlone.loadFromFile("ressources/map/alone.png");
    iTopRight.loadFromFile("ressources/map/topright.png");
    iTop1.loadFromFile("ressources/map/top1.png");
    iBottomRight.loadFromFile("ressources/map/bottomright.png");
    iBottom1.loadFromFile("ressources/map/bottom1.png");
    iMiddle5.loadFromFile("ressources/map/middle5.png");
    iRight1.loadFromFile("ressources/map/right1.png");
    iMiddle6.loadFromFile("ressources/map/middle6.png");

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
                    s.setTexture(iLeft1);
                else if (BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.setTexture(iBottomLeft);
                else if (!BLOCK_ABOVE(x, y) && BLOCK_BELOW(x, y))
                    s.setTexture(iTopLeft);
                else
                    s.setTexture(iMiddle4);
            }
            else
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.setTexture(iMiddle1);
                else if (BLOCK_BELOW(x, y) && !BLOCK_ABOVE(x, y))
                    s.setTexture(iMiddle2);
                else if (!BLOCK_BELOW(x, y) && BLOCK_ABOVE(x, y))
                    s.setTexture(iMiddle3);
                else
                    s.setTexture(iMiddle);
            }
        }
        else
        {
            if (x == 0 || txtMap[x - 1][y] != 'X') //si pas block a gauche
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.setTexture(iAlone);
                else if (BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.setTexture(iBottom1);
                else if (!BLOCK_ABOVE(x, y) && BLOCK_BELOW(x, y))
                    s.setTexture(iTop1);
                else
                    s.setTexture(iMiddle6);
            }
            else
            {
                if (!BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.setTexture(iRight1);
                else if (BLOCK_ABOVE(x, y) && !BLOCK_BELOW(x, y))
                    s.setTexture(iBottomRight);
                else if (!BLOCK_ABOVE(x, y) && BLOCK_BELOW(x, y))
                    s.setTexture(iTopRight);
                else
                    s.setTexture(iMiddle5);
            }
        }
    }
    else
        s.setTexture(imageAlpha);
}

bool RMap::do_display(QMap<QString, QString> &properties)
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
            screen[x][y].setPosition(((blockId + (NB_BLOCK_WIDTH - 1)) < txtMap.size()) ?
                                         x  * BLOCK_SIZE - ((int)floor(time * SPEED_COEF) % BLOCK_SIZE) :
                                         x  * BLOCK_SIZE,
                                     384 - y * BLOCK_SIZE);
            window.draw(screen[x][y]);
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
    // D�finition de deux objets repr�sentant les dimensions de s1 et s2.
    //sf::Vector2f pos = s1.getPosition() - s1.getOrigin();
    const sf::Rect<float> r1 = s1.getGlobalBounds();
    //pos = s2.getPosition() - s2.getOrigin();
    const sf::Rect<float> r2 = s2.getGlobalBounds();

    // Espace de collision potentiel.
    sf::Rect<float> zone;

    // Testons si les Sprites se superposent.
    if (r1.intersects(r2, zone))
    {
        //on recupere les limites des superposition des zones
        int left1 = static_cast<int>(zone.left - r1.left);
        int top1 = static_cast<int>(zone.top - r1.top);

        int left2 = static_cast<int>(zone.left - r2.left);
        int top2 = static_cast<int>(zone.top - r2.top);
        int width = static_cast<int>(zone.width);
        int height = static_cast<int>(zone.height);

        sf::Image s1Img = s1.getTexture()->copyToImage();
        sf::Image s2Img = s2.getTexture()->copyToImage();

        // On calcul pour chaque pixel de la zone de collision si les pixel autre que transparent se superpose
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                //si c'est le cas on renvois true
                if (s1Img.getPixel(x + left1 + s1.getTextureRect().left, y + top1 + s1.getTextureRect().top).a >= 1 &&
                        s2Img.getPixel(x + left2 + s2.getTextureRect().left, y + top2 + s2.getTextureRect().top).a >= 1)
                    return true;
            }
        }
        return false;
    }

    return false;
}

