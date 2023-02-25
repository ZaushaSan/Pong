#ifndef DOT_HPP
#define DOT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Dot{
public:
    static const int DOT_WIDTH = 10;
    static const int DOT_HEIGHT = 10;

    void draw(int x, int y);
    void render();
    void move();
    bool collisionDetecter(SDL_Rect a, SDL_Rect b);
private:
    int dotPosX, dotPosY;
    int dotVelX, dotVelY;

    SDL_Rect dotCollider;
};

#endif