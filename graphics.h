
#ifndef GRAPHICS_H 
#define GRAPHICS_H 

#include "Adafruit_ST7735.h" 
#include "gamestate.h" 

#define P_MOSI  p5
#define P_MISO  p6
#define P_SOCK  p7
#define P_CS    p9
#define P_RS    p20 
#define P_DC    p19

#define BACKGROUND_COLOR        ST7735_BLACK 
#define DEFAULT_TEXT_COLOR      ST7735_WHITE
#define LAUNCH_SCREEN_COLOR     ST7735_BLACK  
#define WAITING_SCREEN_COLOR    ST7735_BLACK  

#define OTHER_PADDLE_COLOR      ST7735_WHITE
#define YOUR_PADDLE_COLOR       ST7735_GREEN
#define BALL_COLOR              ST7735_RED

#define PADDLE_WIDTH 30 
#define ELEVATION    5  

class GameState; 

class Graphics {
    private: 
        Adafruit_ST7735 *tft; 
    public: 
        Graphics(); 
        void renderLaunchScreen(); 
        void renderWaitingRoom(); 
        void renderGameState(GameState *gs); 
        void renderBall(GameState *gs); 
        void renderPlayers(GameState *gs); 
        void renderScore(GameState *gs);
        void renderGameOver(GameState *gs); 
        void renderCountdown(GameState *gs);  
        void eraseBall(GameState *gs);
        void erasePlayers(GameState *gs); 
        void eraseGameState(GameState *gs);
        void eraseScore(GameState *gs); 
        void eraseCountdown(GameState *gs);
        void reset();
};

#endif // GRAPHICS_H
