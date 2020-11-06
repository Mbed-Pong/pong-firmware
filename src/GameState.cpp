
#include "GameState.h"

GameState::GameState()
{
    Coordinate playerOnePos = {PLAYER_1_INIT_X, PLAYER_1_INIT_Y};
    Coordinate playerTwoPos = {PLAYER_2_INIT_X, PLAYER_2_INIT_Y};
    Coordinate ballPos = {BALL_INIT_X, BALL_INIT_Y};
    this->p1 = new Player(playerOnePos);
    this->p2 = new Player(playerTwoPos);
    this->ball = new Ball(ballPos);
    this->turn = std::rand() % 1 == 0 ? -1 : 1;
    this->ballDirection = {turn, 0};
}

GameState::~GameState()
{
    // TODO
}

bool GameState::done()
{
    return this->p1->getScore() >= 3 || this->p2->getScore() >= 3;
}

// can ommit sending the x coord for platforms since they should be static
std::string GameState::serialize()
{
    Coordinate playerOnePos = this->p1->getPosition();
    Coordinate playerTwoPos = this->p2->getPosition();
    Coordinate ballPos = this->ball->getPosition();
    int8_t turn = this->turn;
    Vector2d ballDir = this->ballDirection;

    std::string serializedGameState;
    serializedGameState = "{ playerOnePos: [" + std::to_string(playerOnePos.x) + ", " + std::to_string(playerOnePos.y) +
                          "], playerTwoPos: [" + std::to_string(playerTwoPos.x) + ", " + std::to_string(playerTwoPos.y) + "], ballPos: [" +
                          std::to_string(ballPos.x) + ", " + std::to_string(ballPos.y) + "], turn: " + std::to_string(turn) +
                          ", ballDir: [" + std::to_string(ballDir.x) + ", " + std::to_string(ballDir.y) + "]}\n";
    return serializedGameState;
}