
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#define PLAYER_1_INIT_X 0
#define PLAYER_1_INIT_Y 63

#define PLAYER_2_INIT_X 127
#define PLAYER_2_INIT_Y 63

#define BALL_INIT_X 63
#define BALL_INIT_Y 63

#define BALL_DIR_INIT_X 1;
#define BALL_DIR_INIT_Y 0;

#include "deps.h"
#include "Sprite.h"

// make abstraction more intuitive Player1-->(pos, score), Player2

class GameState
{
private:
    Player *p1;
    Player *p2;
    Ball *ball;
    Vector2d ballDirection;
    int8_t turn;

public:
    GameState();
    ~GameState();
    std::string serialize();

    bool done();
    void update();

    // getters and setters
};

#endif // GAME_STATE_H_