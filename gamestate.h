
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "mbed.h"
#include "stdint.h"
#include "MbedJSONValue.h"
#include "graphics.h" 
#include <string>  

struct Coord {
    int8_t x; 
    int8_t y;
};

class Graphics; 

class GameState {
    // TODO: make the syntax consistent please
    private: 
        Coord p1_loc; 
        Coord p2_loc; 
        Coord ball_loc; 
        char is_done; 
        char has_started; 
        int countdown; 
        char localPlayerNum; 
        char lobbyHash[21]; 
        int score[2]; 
    public:
        GameState();
        Coord getPlayerLocation(char player);   
        Coord getPlayerOneLocation(); 
        Coord getPlayerTwoLocation(); 
        Coord getBallLocation();
        char *getLobbyHash();
        char getLocalPlayerNum(); 
        int getCountdown(); 
        char hasStarted();
        void setCountdown(int val); 
        int getPlayerOneScore();
        int getPlayerTwoScore();
        int getPlayerScore(int player); 
        void updateAndRender(MbedJSONValue *serverResponse, Graphics *gfx);
        char done();   
};

#endif // GAME_STATE_H
