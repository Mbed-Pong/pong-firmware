
#include "gamestate.h"  

GameState::GameState() {
    Coord playerOneLocation = {0, 0};
    Coord playerTwoLocation = {0, 0};
    Coord ballLocation = {0, 0};
    this->localPlayerNum = 0; 
    this->p1_loc = playerOneLocation;
    this->p2_loc = playerTwoLocation; 
    this->ball_loc = ballLocation; 
    this->has_started = 0; 
    this->countdown = 0; 
    this->is_done = 0; 
    this->score[0] = 0; 
    this->score[1] = 0; 
}

Coord GameState::getPlayerOneLocation() {
    return this->p1_loc; 
}

Coord GameState::getPlayerTwoLocation() {
    return this->p2_loc; 
} 

Coord GameState::getBallLocation() {
    return this->ball_loc; 
}

void GameState::updateAndRender(MbedJSONValue *serverResponse, Graphics *gfx) {
    string typeResponse = (*serverResponse)["type"].get<std::string>(); 
    if (typeResponse == "connected") { 
        printf("connected!!!!!\n\r"); 
        if (serverResponse->hasMember("player")) {
          this->localPlayerNum = (char)(*serverResponse)["player"].get<int>();    
        }
        gfx->renderWaitingRoom(); 
    } else if (typeResponse == "gameState") {
        MbedJSONValue &serverGameState = (*serverResponse)["gameState"];
        if (!has_started && serverGameState.hasMember("countdown")) {
            int countdownValue = (serverGameState)["countdown"].get<int>() / 1000;
            if (countdownValue > 0) {
                gfx->eraseCountdown(this); 
                setCountdown(countdownValue);  
                gfx->renderCountdown(this); 
                return; 
            } else {
                has_started = 1; 
                printf("reseting display\n\r");
                gfx->reset(); 
            }
        }
        gfx->eraseGameState(this); 
        
        if (serverGameState.hasMember("playerOnePos")) {
            this->p1_loc.x = (serverGameState)["playerOnePos"].get<int>();       
        }
        if (serverGameState.hasMember("playerTwoPos")) {
            this->p2_loc.x = (serverGameState)["playerTwoPos"].get<int>(); 
        }
        if (serverGameState.hasMember("ballPos")) {
            
            int8_t updated_ball_x = (int8_t)(serverGameState)["ballPos"][0].get<int>(); 
            int8_t updated_ball_y = (int8_t)(serverGameState)["ballPos"][1].get<int>(); 
            this->ball_loc.x = updated_ball_x; 
            this->ball_loc.y = updated_ball_y;
        }
        if (serverGameState.hasMember("isOver")) {
            this->is_done = (char)(serverGameState)["isOver"].get<int>();    
        }
        if (serverGameState.hasMember("score")) {
            this->score[0] = (serverGameState)["score"][0].get<int>(); 
            this->score[1] = (serverGameState)["score"][1].get<int>();
        }
        // TODO: check if hash has already been set
        if (serverGameState.hasMember("hash")) {
            strcpy(this->lobbyHash, 
                (serverGameState)["hash"].get<std::string>().c_str());
            this->lobbyHash[20] = 0; 
        }
        gfx->renderGameState(this); 
    }
}

Coord GameState::getPlayerLocation(char player) {
    if (player == 0) {
        return getPlayerOneLocation(); 
    }
    return getPlayerTwoLocation(); 
}

char *GameState::getLobbyHash() {
    return this->lobbyHash; 
}

char GameState::getLocalPlayerNum() {
    return this->localPlayerNum; 
}

int GameState::getCountdown() {
    return this->countdown; 
}

void GameState::setCountdown(int val) {
    this->countdown = val; 
}

int GameState::getPlayerOneScore() {
    return this->score[0];
}

int GameState::getPlayerTwoScore() {
    return this->score[1];
}

int GameState::getPlayerScore(int player) {
    if (player == 0) {
        return getPlayerOneScore(); 
    }
    return getPlayerTwoScore(); 
}

char GameState::hasStarted() {
    return this->has_started; 
}

char GameState::done() {
    return this->is_done; 
}


