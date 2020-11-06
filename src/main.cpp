
#include "GameState.h"
#include "Network.h"

using namespace std;

int play_game()
{
    GameState *gameState = new GameState();
    cout << gameState->serialize();
    testSocket();

    // ping it to server
    // listen for response
    return 0;
}

int main()
{
    play_game();
}
