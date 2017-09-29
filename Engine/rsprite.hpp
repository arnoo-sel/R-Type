#ifndef RSPRITE_HPP
#define RSPRITE_HPP

#include <QMap>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"
#include "rimage.hpp"

/// Un sprite. Permet d'afficher une image.
/** Declaration de la ressource :
  * \code
  * <sprite id="MON_SPRITE" image="MON_IMAGE" />
  * \endcode
  * - id : l'id du sprite (obligatoire/unique)
  * - image : l'id de l'image qu'affiche de sprite (obligatoire)
  *
  * Actions associees :
  * - display : fait en sorte que le sprite soit affiche a chaque frame pendant le temps precise par 'length'
  * - transition : modifie une propriete du sprite
  *
  * Proprietes :
  * - x : la position X du sprite [0 par defaut]
  * - y : la posision Y du sprite [0]
  * - sx : le scale en X du sprite [1]
  * - sy : le scale en Y du sprite [1]
  * - r : la rotation (en degres) du sprite [0]
  * - a : la transparance du sprite (entre 0 et 255) [255]
  *
  **/

class RSprite : public sf::Sprite, public Ressource
{
public:
    typedef bool (RSprite::*action)(QMap<QString, QString>&);

	RSprite(QString name, RImage* rImage);

	static QMap<QString, action> actions;
protected:
    bool do_display(QMap<QString, QString>& properties);
    bool do_transition(QMap<QString, QString>& properties);

	void initActions();

	bool first;
	QMap<QString, QString> _properties;
	RImage* _image;
};

#endif // RSPRITE_HPP
