
#include "Sprite.h"

Sprite::Sprite(Coordinate position)
{
    this->position = position; 
}

Coordinate Sprite::getPosition()
{
    return this->position;
}

sprite_type Sprite::getType()
{
    return this->type;
}

void Sprite::setPosition(int8_t x, int8_t y)
{
    this->position.x = x; 
    this->position.y = y; 
}