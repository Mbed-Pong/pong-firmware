
#include "GameState.h"

GameState::GameState() {
    this->ball_loc = std::make_pair(0, 0); 
    this->player1_loc = std::make_pair(0, 0); 
    this->player2_loc = std::make_pair(0, 0); 
}

GameState::~GameState() {
    // delete dynammically allocated data 
}

void GameState::serialize() {
    
}

std::pair<int8_t, int8_t> GameState::get_ball_loc() {
    return this->ball_loc;
}

std::pair<int8_t, int8_t> GameState::get_player1_loc() {
    return this->player1_loc;
}

std::pair<int8_t, int8_t> GameState::get_player2_loc() {
    return this->player2_loc;
}


