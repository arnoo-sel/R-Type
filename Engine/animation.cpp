#include "animation.hpp"

Animation::Animation() : _ospr(_spr)
{
}

Animation::Animation(sf::Texture& img, sf::Sprite& spr, ANIMATION anim, bool repeat, int mod_x, int mod_y) : _ospr(spr)
{
    _img = img;
    _spr.setTexture(img);
    _anim = anim;
    _pos = _spr.getPosition();
    _isSpriteExist = true;
    _repeat = repeat;
    _cycle = 0;
    _mod.x = mod_x;
    _mod.y = mod_y;
    _play = true;
    setAnimationList(anim);
}

Animation::Animation(sf::Texture& img, sf::Vector2f pos, ANIMATION anim, bool repeat, int mod_x, int mod_y) : _ospr(_spr)
{
    _isSpriteExist = false;
    _img = img;
    _spr.setTexture(_img);
    _anim = anim;
    _pos = pos;
    _repeat = repeat;
    _cycle = 0;
    _mod.x = mod_x;
    _mod.y = mod_y;
    _play = true;
    setAnimationList(anim);
}

void Animation::init(sf::Texture& img, sf::Sprite& spr, ANIMATION anim, bool repeat, int mod_x, int mod_y)
{
    _img = img;
    _spr.setTexture(img);
    _anim = anim;
    _pos = _spr.getPosition();
    _isSpriteExist = true;
    _repeat = repeat;
    _cycle = 0;
    _mod.x = mod_x;
    _mod.y = mod_y;
    _play = true;
    setAnimationList(anim);
}

void Animation::setAnimationList(ANIMATION anim)
{
    switch (anim)
    {
    case PREP_ROCKET :
        {
            _animList.push_back(ANIM_PREP_ROCKET_0);
            _animList.push_back(ANIM_PREP_ROCKET_1);
            _animList.push_back(ANIM_PREP_ROCKET_2);
            _animList.push_back(ANIM_PREP_ROCKET_3);
            _animList.push_back(ANIM_PREP_ROCKET_4);
            _animList.push_back(ANIM_PREP_ROCKET_5);
            _animList.push_back(ANIM_PREP_ROCKET_6);
            _animList.push_back(ANIM_PREP_ROCKET_7);
            _time = TIME_PREP_ROCKET;
            _play = false;
            break;
        }
    case EXPLOSION :
        {
            _animList.push_back(ANIM_EXPLOSION_0);
            _animList.push_back(ANIM_EXPLOSION_1);
            _animList.push_back(ANIM_EXPLOSION_2);
            _animList.push_back(ANIM_EXPLOSION_3);
            _animList.push_back(ANIM_EXPLOSION_4);
            _animList.push_back(ANIM_EXPLOSION_5);
            _time = TIME_EXPLOSION;
            break;
        }
    case FIRE_ROCKET :
        {
            _animList.push_back(ANIM_FIRE_ROCKET_0);
            _animList.push_back(ANIM_FIRE_ROCKET_1);
            _time = TIME_FIRE_ROCKET;
            _play = false;
            break;
        }
    case EXPLOSION_MID :
        {
            _animList.push_back(ANIM_EXPLOSION_MID_0);
            _animList.push_back(ANIM_EXPLOSION_MID_1);
            _animList.push_back(ANIM_EXPLOSION_MID_2);
            _animList.push_back(ANIM_EXPLOSION_MID_3);
            _animList.push_back(ANIM_EXPLOSION_MID_4);
            _animList.push_back(ANIM_EXPLOSION_MID_5);
            _time = TIME_EXPLOSION_MID;
            break;
        }
    case EXPLOSION_BIG :
        {
            _animList.push_back(ANIM_EXPLOSION_BIG_0);
            _animList.push_back(ANIM_EXPLOSION_BIG_1);
            _animList.push_back(ANIM_EXPLOSION_BIG_2);
            _animList.push_back(ANIM_EXPLOSION_BIG_3);
            _animList.push_back(ANIM_EXPLOSION_BIG_4);
            _animList.push_back(ANIM_EXPLOSION_BIG_5);
            _animList.push_back(ANIM_EXPLOSION_BIG_6);
            _animList.push_back(ANIM_EXPLOSION_BIG_7);
            _time = TIME_EXPLOSION_BIG;
            break;
        }
    case EXPLOSION_ROCKET :
        {
            _animList.push_back(ANIM_EXPLOSION_ROCKET_0);
            _animList.push_back(ANIM_EXPLOSION_ROCKET_1);
            _animList.push_back(ANIM_EXPLOSION_ROCKET_2);
            _time = TIME_EXPLOSION_ROCKET;
            break;
        }
    default : break;
    }
    _spr.setTextureRect(NONE);
}

bool Animation::play()
{
    if (_play == true)
    {
        if (_isSpriteExist == true)
            _pos = _ospr.getPosition();
        _spr.setPosition(_pos.x + _mod.x, _pos.y + _mod.y);
        if (_pos.x == 0 && _pos.y == 0)
            return true;
        if (_clock.getElapsedTime().asSeconds() > _time)
        {
            _clock.restart();
            if (_cycle < _animList.size())
            {
                _spr.setTextureRect(_animList[_cycle]);
                _cycle++;
                return true;
            }
            else if (_repeat == true)
                _cycle = 0;
            else
            {
                _spr.setTextureRect(NONE);
                _play = false;
                return false;
            }
        }
    }
    return true;
}

sf::Sprite& Animation::getSprite()
{
    return _spr;
}

void Animation::pause()
{
    if (_play == false)
    {
        _cycle = 0;
    }
    _spr.setTextureRect(NONE);
    _play = false;
}

void Animation::start()
{
    _play = true;
    _clock.restart();
}

void Animation::playOnce()
{
    _play = true;
    _clock.restart();
    _cycle = 0;
}

void Animation::setModification(int x, int y)
{
    _mod.x = x;
    _mod.y = y;
}
