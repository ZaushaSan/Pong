#ifndef GAME_HPP
#define GAME_HPP

#include "stdio.h"
#include "sstream"
#include "time.h"

#include "globals.hpp"

class Game{
public:
    bool init();
    
    void load();
    void start();
    void close();

    void gameLoop();
    void renderSection();
    void whoWins();
private:
    enum gameState{
        pause,
        run
    };
};

#endif