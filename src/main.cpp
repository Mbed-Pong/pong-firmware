
#include "GameState.h"

using namespace std;

int play_game()
{
    GameState *gameState = new GameState();
    while (!gameState->done()) {
        cout << gameState->serialize();
    }
    
    // ping it to server
    // listen for response
    return 0;
}

int main()
{
    play_game();
}
