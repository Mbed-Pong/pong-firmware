
#include "graphics.h"

Graphics::Graphics() {
    printf("\n\rInitializing Graphics: initializing TFT\n\r");
    this->tft = new Adafruit_ST7735(P_MOSI, P_MISO, P_SOCK, P_CS, P_RS, P_DC);
    printf("Initializing Graphics: optimizing display for resolution\n\r");
    tft->initR(INITR_144GREENTAB); 
    tft->setTextColor(ST7735_WHITE);
}

void Graphics::renderLaunchScreen() {
    tft->fillScreen(LAUNCH_SCREEN_COLOR);
    tft->setTextCursor(18, 20); 
    tft->printf("%s", "Multiplayer Pong");
    tft->setTextCursor(15, 60); 
    tft->printf("%s", "press any button"); 
    tft->setTextCursor(15, 70); 
    tft->printf("%s", "to continue"); 
}

void Graphics::renderWaitingRoom() {
    tft->fillScreen(WAITING_SCREEN_COLOR);
    tft->setTextCursor(18, 20); 
    tft->printf("%s", "Waiting For");
    tft->setTextCursor(18, 30);
    tft->printf("%s", "Player..."); 
}

void Graphics::renderBall(GameState *gs) {
    Coord ball_loc = gs->getBallLocation(); 
    tft->drawPixel(ball_loc.x, ball_loc.y, ST7735_WHITE); 
}

void Graphics::eraseBall(GameState *gs) {
    Coord ball_loc = gs->getBallLocation(); 
    tft->drawPixel(ball_loc.x, ball_loc.y, BACKGROUND_COLOR); 
}

void Graphics::renderPlayers(GameState *gs) {
    int8_t topPaddleRenderPos = gs->getPlayerLocation(0).x;    
    int8_t bottomPaddleRenderPos = gs->getPlayerLocation(1).x;
    
    uint16_t top_color = YOUR_PADDLE_COLOR;
    uint16_t bottom_color = OTHER_PADDLE_COLOR; 
    
    if (gs->getLocalPlayerNum() == 1) {
        top_color = OTHER_PADDLE_COLOR; 
        bottom_color = YOUR_PADDLE_COLOR; 
    }
    
    // draw top paddle
    tft->drawFastHLine(topPaddleRenderPos - PADDLE_WIDTH / 2,
        ELEVATION, PADDLE_WIDTH, top_color);
    
    // draw bottom paddle
    tft->drawFastHLine(bottomPaddleRenderPos - PADDLE_WIDTH / 2,
        127 - ELEVATION, PADDLE_WIDTH, bottom_color);
}

void Graphics::erasePlayers(GameState *gs) {
    int8_t topPaddleRenderPos = gs->getPlayerLocation(0).x;    
    int8_t bottomPaddleRenderPos = gs->getPlayerLocation(1).x;
    
    // erase top paddle
    tft->drawFastHLine(topPaddleRenderPos - PADDLE_WIDTH / 2,
        ELEVATION, PADDLE_WIDTH, BACKGROUND_COLOR);
    
    // erase bottom paddle
    tft->drawFastHLine(bottomPaddleRenderPos - PADDLE_WIDTH / 2,
        127 - ELEVATION, PADDLE_WIDTH, BACKGROUND_COLOR);
}

void Graphics::renderScore(GameState *gs) {
    tft->setTextColor(ST7735_WHITE);
    tft->setTextCursor(120, 50); 
    tft->printf("%i", gs->getPlayerOneScore());
    tft->setTextCursor(120, 77); 
    tft->printf("%i", gs->getPlayerTwoScore());
}

void Graphics::eraseScore(GameState *gs) {
    tft->setTextColor(BACKGROUND_COLOR);
    tft->setTextCursor(120, 50); 
    tft->printf("%i", gs->getPlayerOneScore());
    tft->setTextCursor(120, 77); 
    tft->printf("%i", gs->getPlayerTwoScore());
}

void Graphics::renderGameOver(GameState *gs) {
    reset(); 
    tft->setTextColor(DEFAULT_TEXT_COLOR);
    tft->setTextCursor(15, 20); 
    tft->printf("Game Over"); 
    tft->setTextCursor(15, 40); 
    
    bool winner = gs->getPlayerOneScore() > gs->getPlayerTwoScore() ? 0 : 1;  
    
    if (winner == gs->getLocalPlayerNum()) {
        tft->printf("You won, %i:%i", 
            gs->getPlayerScore(winner), gs->getPlayerScore(1 - winner));
    } else {
        tft->printf("You lost, %i:%i", 
            gs->getPlayerScore(1 - winner), gs->getPlayerScore(winner)); 
    }
    
    tft->setTextCursor(15, 60); 
    tft->printf("Press any button");
    tft->setTextCursor(15, 70);
    tft->printf("to play again!"); 
}

void Graphics::renderCountdown(GameState *gs) {
    tft->setTextColor(DEFAULT_TEXT_COLOR); 
    tft->setTextCursor(63, 63); 
    tft->printf("%i", gs->getCountdown()); 
}

void Graphics::eraseCountdown(GameState *gs) {
    tft->setTextColor(BACKGROUND_COLOR); 
    tft->setTextCursor(63, 63); 
    tft->printf("%i", gs->getCountdown());
}

void Graphics::renderGameState(GameState *gs) {
    renderBall(gs); 
    renderPlayers(gs);
    renderScore(gs); 
}

void Graphics::eraseGameState(GameState *gs) {
    eraseBall(gs); 
    erasePlayers(gs); 
    eraseScore(gs);
}

void Graphics::reset() {
    tft->fillScreen(BACKGROUND_COLOR);
}
