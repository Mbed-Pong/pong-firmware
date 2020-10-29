#include <utility>
#include <stdlib.h>

class GameState {
    private:
        std::pair<int8_t, int8_t> ball_loc; 
        std::pair<int8_t, int8_t> player1_loc; 
        std::pair<int8_t, int8_t> player2_loc; 
    public: 
        GameState(); 
        ~GameState();
        std::pair<int8_t, int8_t> get_ball_loc(); 
        std::pair<int8_t, int8_t> get_player1_loc(); 
        std::pair<int8_t, int8_t> get_player2_loc(); 

        void serialize(); 
};
