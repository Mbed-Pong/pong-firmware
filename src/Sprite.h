
#ifndef SPRITE_H_
#define SPRITE_H_

#include "deps.h"

enum sprite_type
{
    BALL,
    PLAYER,
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

class Player : public Sprite
{
private:
    sprite_type type;
    int8_t score; 

public:
    Player(Coordinate position);
    void incrementScore();
    int8_t getScore(); 
};

class Ball : public Sprite
{
private:
    sprite_type type;

public:
    Ball(Coordinate position);
};

#endif // SPRITE_H_