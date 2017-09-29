#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define TIME_PREP_ROCKET 0.07f
#define TIME_EXPLOSION 0.05f
#define TIME_FIRE_ROCKET 0.05f
#define TIME_EXPLOSION_BIG 0.08f
#define TIME_EXPLOSION_MID 0.08f
#define TIME_EXPLOSION_ROCKET 0.05f

#define ANIM_PREP_ROCKET_0 sf::Rect<int>(0  , 51, 33       , 83)
#define ANIM_PREP_ROCKET_1 sf::Rect<int>(34 , 51, 63  - 34 , 80  - 51)
#define ANIM_PREP_ROCKET_2 sf::Rect<int>(68 , 53, 96  - 68 , 81  - 53)
#define ANIM_PREP_ROCKET_3 sf::Rect<int>(102, 54, 127 - 102, 104 - 54)
#define ANIM_PREP_ROCKET_4 sf::Rect<int>(135, 56, 163 - 135, 77  - 56)
#define ANIM_PREP_ROCKET_5 sf::Rect<int>(168, 57, 193 - 168, 75  - 57)
#define ANIM_PREP_ROCKET_6 sf::Rect<int>(200, 59, 222 - 200, 73  - 59)
#define ANIM_PREP_ROCKET_7 sf::Rect<int>(233, 60, 252 - 233, 71  - 60)

#define ANIM_EXPLOSION_0 sf::Rect<int>(248, 303, 265 - 248, 320 - 303)
#define ANIM_EXPLOSION_1 sf::Rect<int>(218, 300, 242 - 218, 320 - 300)
#define ANIM_EXPLOSION_2 sf::Rect<int>(180, 296, 214 - 180, 322 - 296)
#define ANIM_EXPLOSION_3 sf::Rect<int>(146, 295, 178 - 146, 325 - 295)
#define ANIM_EXPLOSION_4 sf::Rect<int>(108, 295, 142 - 108, 326 - 295)
#define ANIM_EXPLOSION_5 sf::Rect<int>(72 , 295, 104 - 72 , 326 - 295)

#define ANIM_EXPLOSION_BIG_0 sf::Rect<int>(140, 47, 182 - 140, 84  - 47)
#define ANIM_EXPLOSION_BIG_1 sf::Rect<int>(202, 46, 253 - 202, 88  - 46)
#define ANIM_EXPLOSION_BIG_2 sf::Rect<int>(265, 40, 319 - 265, 92  - 40)
#define ANIM_EXPLOSION_BIG_3 sf::Rect<int>(1  , 99, 64  - 1  , 162 - 99)
#define ANIM_EXPLOSION_BIG_4 sf::Rect<int>(66 , 99, 129 - 66 , 162 - 99)
#define ANIM_EXPLOSION_BIG_5 sf::Rect<int>(131, 99, 194 - 131, 162 - 99)
#define ANIM_EXPLOSION_BIG_6 sf::Rect<int>(196, 99, 259 - 196, 162 - 99)
#define ANIM_EXPLOSION_BIG_7 sf::Rect<int>(261, 99, 324 - 261, 162 - 99)

#define ANIM_EXPLOSION_MID_0 sf::Rect<int>(130, 1, 159 - 130, 29 - 1)
#define ANIM_EXPLOSION_MID_1 sf::Rect<int>(162, 1, 192 - 162, 32 - 1)
#define ANIM_EXPLOSION_MID_2 sf::Rect<int>(194, 1, 225 - 194, 32 - 1)
#define ANIM_EXPLOSION_MID_3 sf::Rect<int>(226, 1, 258 - 226, 32 - 1)
#define ANIM_EXPLOSION_MID_4 sf::Rect<int>(260, 1, 291 - 260, 32 - 1)
#define ANIM_EXPLOSION_MID_5 sf::Rect<int>(294, 1, 324 - 294, 32 - 1)

#define ANIM_FIRE_ROCKET_0 sf::Rect<int>(215, 85, 228 - 215, 96 - 85)
#define ANIM_FIRE_ROCKET_1 sf::Rect<int>(233, 87, 243 - 233, 95 - 87)

#define ANIM_EXPLOSION_ROCKET_0 sf::Rect<int>(151, 21, 161 - 151, 30 - 21)
#define ANIM_EXPLOSION_ROCKET_1 sf::Rect<int>(167, 20, 179 - 167, 31 - 20)
#define ANIM_EXPLOSION_ROCKET_2 sf::Rect<int>(183, 19, 197 - 183, 32 - 19)

#define NONE sf::Rect<int>(0, 0, 0, 0)

class Animation
{
public:
    enum ANIMATION
    {
        PREP_ROCKET,
        FIRE_ROCKET,
        EXPLOSION,
        EXPLOSION_MID,
        EXPLOSION_BIG,
        EXPLOSION_ROCKET,
        NB_ANIMATION
    };
    Animation();
    Animation(sf::Texture &, sf::Sprite&, ANIMATION, bool repeat = false, int mod_x = 0, int mod_y = 0);
    Animation(sf::Texture &, sf::Vector2f, ANIMATION, bool repeat = false, int mod_x = 0, int mod_y = 0);
    void init(sf::Texture &, sf::Sprite&, ANIMATION, bool repeat = false, int mod_x = 0, int mod_y = 0);
    sf::Sprite& getSprite();
    bool play();
    void pause();
    void start();
    void playOnce();
    void setModification(int, int);
private:
    void setAnimationList(ANIMATION anim);
    bool _isSpriteExist;
    bool _repeat;
    sf::Texture _img;
    sf::Sprite& _ospr;
    sf::Sprite _spr;
    sf::Vector2f _pos;
    sf::Vector2f _mod;
    sf::Clock _clock;
    ANIMATION _anim;
    std::vector<sf::Rect<int> > _animList;
    double _time;
    int _cycle;
    bool _play;
};

#endif // ANIMATION_HPP
