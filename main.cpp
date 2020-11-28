
#include "mbed.h"
#include "DebouncedInterrupt.h"

#include "gamestate.h"
#include "graphics.h" 
#include "network.h"

#define DEBOUNCE 25

DebouncedInterrupt leftButton(p21);
DebouncedInterrupt middleButton(p22);
DebouncedInterrupt rightButton(p23);

EthernetInterface eth; 
UDPSocket sock; 
Endpoint nist; 

volatile int sendFlag = 0; 
volatile int moveDelta = 0;
volatile int menuPress = 0;  

// interrupts service routines 

void pressButtonMenu(void) {
    menuPress = 1; 
}

void pressLeftGame( void ) {
    sendFlag = 1;
    moveDelta -= 5; 
}

void pressRightGame() {
    sendFlag = 1;
    moveDelta += 5; 
}
 
int main() {
    initEthernet(&eth, &sock, &nist);
    Graphics *gfx = new Graphics();    
      
    // attach ISR
    leftButton.attach(&pressButtonMenu, IRQ_RISE, DEBOUNCE);
    middleButton.attach(&pressButtonMenu, IRQ_RISE, DEBOUNCE);
    rightButton.attach(&pressButtonMenu, IRQ_RISE, DEBOUNCE);
    
    MbedJSONValue serverResponse; 
    MbedJSONValue serverRequest; 
    
//    char connectionRequest[] = "{\"type\": \"connected\"}";
    char tmp_buffer[256]; 
    
    string serverRequestContent = ""; 
    int serverRequestLength = 0; 
    char *serverRequestPayload = NULL; 
    
    gfx->renderLaunchScreen(); 
    
    while (1) { // keep program running
        if (menuPress) {
            GameState *gs = new GameState();
            
            // change ISRs to game controls 
            leftButton.attach(&pressLeftGame, IRQ_RISE, DEBOUNCE);
            middleButton.reset(); 
            rightButton.attach(&pressRightGame, IRQ_RISE, DEBOUNCE);
            
            // request an open lobby from the server 
            sock.sendTo(nist, CONNECTION_REQ, strlen(CONNECTION_REQ)); 
            
            // play an individual game to completion  
            while (!gs->done()) {
                if (sendFlag) {
                    serverRequest["type"] = "move"; 
                    serverRequest["hash"] = LOBBY_HASH; 
                    serverRequest["player"] = gs->getLocalPlayerNum(); 
                    serverRequest["delta"] = (int)moveDelta; 
                    
                    // prepare and send JSON payload 
                    serverRequestContent = serverRequest.serialize(); 
                    serverRequestLength = serverRequestContent.size(); 
                    serverRequestPayload = (char *)serverRequestContent.c_str(); 
                    sock.sendTo(nist, serverRequestPayload, serverRequestLength);
                    
                    // reset 
                    sendFlag = 0; 
                    moveDelta = 0; 
                }
                int bytesRead = sock.receiveFrom(nist, tmp_buffer, sizeof(tmp_buffer));
                tmp_buffer[bytesRead] = 0; 
                
                // populate serverResponse JSON and update local gamestate 
                if (bytesRead > 0) {
                    parse(serverResponse, tmp_buffer); 
                    gs->updateAndRender(&serverResponse, gfx);
                } 
                wait(.1);
            }
            // once game ends, leave lobby and disconnect 
            MbedJSONValue disconnectRequest; 
            disconnectRequest["hash"] = LOBBY_HASH; 
            disconnectRequest["type"] = "disconnect"; 
            
            string disconnectRequestContent = disconnectRequest.serialize(); 
            int len = disconnectRequestContent.size(); 
            char *disconnectRequestPayload = (char *)disconnectRequestContent.c_str(); 
            sock.sendTo(nist, disconnectRequestPayload, len); 
            
            // flush the socket from the previous game
            int flushBytes = 0; 
            while ((flushBytes = sock.receiveFrom(nist, tmp_buffer, sizeof(tmp_buffer))) != 0) {
                printf("reading bytes: %i\n\r", flushBytes); 
                printf("tmp_buffer %s\n\r", tmp_buffer); 
            }
             
            gfx->renderGameOver(gs);
            
            // reset
            leftButton.attach(&pressButtonMenu, IRQ_RISE, DEBOUNCE);
            middleButton.attach(&pressButtonMenu, IRQ_RISE, DEBOUNCE);
            rightButton.attach(&pressButtonMenu, IRQ_RISE, DEBOUNCE);
            
            menuPress = 0; 
            delete gs; 
        }
        wait(0.3); 
    }
    // cleanupEthernet(&eth, &sock);
}


