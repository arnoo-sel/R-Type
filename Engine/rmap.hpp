#ifndef RMAP_HPP
#define RMAP_HPP

#include <QString>
#include <QVector>
#include <QMap>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ressource.hpp"

#define BLOCK_ABOVE(x, y) (((y != (NB_BLOCK_HEIGHT - 1) && txtMap[x][y + 1] == 'X') || (y == (NB_BLOCK_HEIGHT - 1))) ? 1 : 0)
#define BLOCK_BELOW(x, y) (((y != 0 && txtMap[x][y - 1] == 'X') || (y == 0)) ? 1 : 0)
#define SPEED_COEF 64
#define NB_BLOCK_HEIGHT 7
#define NB_BLOCK_WIDTH 12
#define BLOCK_SIZE 64

class RMap : public Ressource
{
public:
	typedef bool (RMap::*action)(QMap<QString, QString>&, const sf::Input&);
	static QMap<QString, action> actions;

protected:
    QVector<QString> txtMap;
    sf::Sprite  **screen;
    int blockId;
    void initActions();
    bool first;
    sf::Image iBottomLeft;
    sf::Image iTopLeft;
    sf::Image iMiddle;
    sf::Image iMiddle1;
    sf::Image iMiddle2;
    sf::Image iMiddle3;
    sf::Image iMiddle4;
    sf::Image iLeft1;
    sf::Image imageAlpha;

    sf::Image iAlone;
    sf::Image iTopRight;
    sf::Image iBottomRight;
    sf::Image iTop1;
    sf::Image iBottom1;
    sf::Image iMiddle6;
    sf::Image iMiddle5;
    sf::Image iRight1;


    void setImage(sf::Sprite &s, int x, int y);
public:
    sf::Sprite** getSprites() const;
    static bool checkCollision(const sf::Sprite& s1, const sf::Sprite& s2);
    RMap(QString name, const QString& fileName);
    bool do_display(QMap<QString, QString>& properties, const sf::Input& input);
};

#endif // RMAP_HPP
