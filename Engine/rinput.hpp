#ifndef RINPUT_HPP
#define RINPUT_HPP

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "ressource.hpp"
#include "rnetwork.hpp"
#include "inputmanager.hpp"

class RInput : public Ressource
{
public:
    typedef bool (RInput::*action)(QMap<QString, QString>&, const sf::Input&);

    RInput(QString name);

    static QMap<QString, action> actions;
protected:
    bool do_catch(QMap<QString, QString>& properties, const sf::Input& input);
    void initActions();
private:
    float _canFire;
    bool first;
    float speedX;
    float speedY;
    bool isCharging;
};
#endif // RINPUT_HPP
