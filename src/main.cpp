#include "Game.h"

int main(void){
    Game game{1920, 1080, "Ant-simulator"};
    while (!game.Close()){
        game.Tick();
    }
    game.Close();
    return 0;
}