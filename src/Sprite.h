
#ifndef SPRITE_H_
#define SPRITE_H_

#include "deps.h"

enum sprite_type
{
    BALL,
    PLATFORM,
};

class Sprite
{
private:
    Coordinate position;
    sprite_type type;

public:
    Sprite(Coordinate position);
    ~Sprite();
    Coordinate getPosition();
    sprite_type getType();
    void setPosition(int8_t x, int8_t y);
};

class Platform : public Sprite
{
private:
    sprite_type type; 
public:
    Platform(Coordinate position);
};


class Ball : public Sprite
{
private:
    sprite_type type; 
public:
    Ball(Coordinate position);
};

#endif // SPRITE_H_