#include "Dot.hpp"
#include "globals.hpp"

void Dot::draw(int x, int y){
    dotPosX = x;
    dotPosY = y;

    dotVelX = 5;
    dotVelY = 5;

    dotCollider.w = DOT_WIDTH;
    dotCollider.h = DOT_HEIGHT;
}

void Dot::render(){
    dotTexture.renderTextures(dotPosX, dotPosY);
}

void Dot::move(){
    SDL_Color white = {255, 255, 255};
    
    SDL_Rect a;
    a.w = Block::BLOCK_WIDTH;
    a.h = Block::BLOCK_HEIGHT;
    a.x = block1.getColliderX();
    a.y = block1.getColliderY();

    SDL_Rect b;
    b.w = Block::BLOCK_WIDTH;
    b.h = Block::BLOCK_HEIGHT;
    b.x = block2.getColliderX();
    b.y = block2.getColliderY();

    dotPosX -= dotVelX;
    dotPosY += dotVelY;

    dotCollider.x = dotPosX;
    dotCollider.y = dotPosY;

    if(dotPosY < 0){
        dotPosY = 0;
        dotVelY *= -1;
        dotCollider.y = dotPosY;
    }

    if(dotPosY > Loader::SCREEN_HEIGHT - DOT_HEIGHT - count1Texture.getHeight()){
        dotPosY = Loader::SCREEN_HEIGHT - DOT_HEIGHT - count1Texture.getHeight();
        dotVelY *= -1;
        dotCollider.y = dotPosY;
    }

    if(dotPosX < 0){
        dotPosX = 0;
        dotVelX *= -1;
        dotCollider.x = dotPosX;

        ++count2;
        count2Texture.loadText(std::to_string(count2), white);
    }

    if(dotPosX > Loader::SCREEN_WIDTH - DOT_WIDTH){
        dotPosX = Loader::SCREEN_WIDTH - DOT_WIDTH;
        dotVelX *= -1;
        dotCollider.x = dotPosX;
        
        ++count1;
        count1Texture.loadText(std::to_string(count1), white);
    }

    if(collisionDetecter(dotCollider, a) || collisionDetecter(dotCollider, b)){
        dotVelX *= -1;
    }
}

bool Dot::collisionDetecter(SDL_Rect a, SDL_Rect b){
    int rightA, rightB;
    int leftA, leftB;
    int topA, topB;
    int bottomA, bottomB;

    rightA = a.x + a.w;
    leftA = a.x;
    bottomA = a.y + a.h;
    topA = a.y;

    rightB = b.x + b.w;
    leftB = b.x;
    bottomB = b.y + b.h;
    topB = b.y;

    if((rightA <= leftB) || (leftA >= rightB) || (bottomA <= topB) || (topA >= bottomB)){
        return false;
    }
    return true;
}