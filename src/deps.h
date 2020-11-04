
#ifndef DEPS_H_
#define DEPS_H_

#include <stdlib.h>
#include <iostream>
#include <string>

struct Coordinate
{
    int8_t x;
    int8_t y;
};

typedef struct Coordinate Vector2d; 

struct Score
{
    int8_t playerOne;
    int8_t playerTwo; 
};

#endif // DEPS_H_