#include "Loader.hpp"

SDL_Window *Loader::gWindow = NULL;
SDL_Renderer *Loader::gRenderer = NULL;
TTF_Font *Loader::gFont = NULL;

Loader::Loader(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Loader::~Loader(){
    free();
}

bool Loader::loadFile(std::string path){
    free();

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    mTexture = newTexture;
    return mTexture != NULL;
}

bool Loader::loadText(std::string textTexture, SDL_Color textColor){
    free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textTexture.c_str(), textColor);

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    mWidth = textSurface->w;
    mHeight = textSurface->h;
        
    SDL_FreeSurface(textSurface);

    return mTexture != NULL;
}

bool Loader::loadBlank(int w, int h, SDL_TextureAccess access){
    free();

    mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, w, h);

    mWidth = w;
    mHeight = h;

    return mTexture != NULL;
}

void Loader::renderTextures(int x, int y){
    SDL_Rect quad = {x, y, mWidth, mHeight};

	SDL_RenderCopy(gRenderer, mTexture, NULL, &quad);
}

void Loader::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;  
    }
}

void Loader::setRenderTarget(){
    SDL_SetRenderTarget(gRenderer, mTexture);
}

int Loader::getWidth(){
    return mWidth;
}

int Loader::getHeight(){
    return mHeight;
}