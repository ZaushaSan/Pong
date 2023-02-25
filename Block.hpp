#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Block{
public:
    static const int BLOCK_WIDTH = 10;
    static const int BLOCK_HEIGHT = 60;

    static const int BLOCK_VEL = 10;

    void draw(int x, int y);
    void handleEventArrows(SDL_Event &e);
    void handleEventWASD(SDL_Event &e);
    void render();
    void move();

    int getColliderX();
    int getColliderY();
private:
    int blockPosX, blockPosY;
    int blockVelY;

    SDL_Rect blockCollider;
    
    friend class Dot;
};

#endif