
#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "deps.h"
#include "Sprite.h"

class Platform : public Sprite
{
private:
    sprite_type type; 
public:
    Platform(Coordinate position);
};

#endif // PLATFORM_H_