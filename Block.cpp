#include "Block.hpp"
#include "globals.hpp"

void Block::draw(int x, int y){
    blockPosX = x;
    blockPosY = y;
 
    blockVelY = 0;

    blockCollider.w = BLOCK_WIDTH;
    blockCollider.h = BLOCK_HEIGHT;
}

void Block::handleEventArrows(SDL_Event &e){ // for block2
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_UP: blockVelY -= BLOCK_VEL;
        break;
        case SDLK_DOWN: blockVelY += BLOCK_VEL;
        break;
        }
    }else if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_UP: blockVelY += BLOCK_VEL;
        break;
        case SDLK_DOWN: blockVelY -= BLOCK_VEL;
        break;
        }
    }
}

void Block::handleEventWASD(SDL_Event &e){ // for block1
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_w: blockVelY -= BLOCK_VEL;
        break;
        case SDLK_s: blockVelY += BLOCK_VEL;
        break;
        }
    }else if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_w: blockVelY += BLOCK_VEL;
        break;
        case SDLK_s: blockVelY -= BLOCK_VEL;
        break;
        }
    }
}

void Block::move(){
    blockPosY += blockVelY;
    blockCollider.y = blockPosY;
    blockCollider.x = blockPosX;

    if((blockPosY < 0) || (blockPosY + BLOCK_HEIGHT > Loader::SCREEN_HEIGHT - count1Texture.getHeight())){
        blockPosY -= blockVelY;
        blockCollider.y = blockPosY;
        blockCollider.x = blockPosX;
    }
}

void Block::render(){
    blockTexture.renderTextures(blockPosX, blockPosY);
}

int Block::getColliderX(){
    return blockCollider.x;
}

int Block::getColliderY(){
    return blockCollider.y;
}