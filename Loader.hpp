#ifndef LOADER_HPP
#define LOADER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include <string>

class Loader{
public:
    static SDL_Window *gWindow;
    static SDL_Renderer *gRenderer;
    static TTF_Font *gFont;

    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    Loader();
    ~Loader();

    bool loadFile(std::string path);
    bool loadText(std::string textTexture, SDL_Color textColor);
    bool loadBlank(int w, int h, SDL_TextureAccess access);

    void free();
    void renderTextures(int x, int y);
    void setRenderTarget();

    int getWidth();
    int getHeight();
private:
    int mWidth;
    int mHeight;

    SDL_Texture *mTexture;
};

#endif