
#ifndef DEPS_H_
#define DEPS_H_

#include <iostream> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>
#include<ctype.h>

struct Coordinate
{
    int8_t x;
    int8_t y;
};

typedef struct Coordinate Vector2d;

#endif // DEPS_H_