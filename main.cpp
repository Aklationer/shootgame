#include "Game.h"
#include <ctime>
#include "Arr.h"

bool c=false;
 int main(){
    srand(static_cast<unsigned int>(time(0)));
    Game game;
    while(game.run()){
        game.update();
        game.render();
    }
 }