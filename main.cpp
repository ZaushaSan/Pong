#include "Game.hpp"

int main(int argc, char *args[]){
    Game game;

    game.init();
    game.start();
    game.load();
    game.gameLoop();

    return 0;
}