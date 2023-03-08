#include "Game.hpp"

SDL_Color white = {255, 255, 255};
SDL_Color red = {255, 0, 0};
const int MAX_ROUNDS = 4;

bool Game::init(){
    bool success = true;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        success = false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    Loader::gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Loader::SCREEN_WIDTH, Loader::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    Loader::gRenderer = SDL_CreateRenderer(Loader::gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(Loader::gRenderer, 0x00, 0x00, 0x00, 0xFF);

    if(TTF_Init() == -1){
        printf("404 %s\t", TTF_GetError());
        success = false;
    }
    Loader::gFont = TTF_OpenFont("src/IpanemaSecco-463W.ttf", 60);
    
    return success;
}

void Game::start(){
    SDL_Event startEvent;
    bool proceed = false;
    bool inside = false;

    while(!proceed){
        int x, y;
        SDL_GetMouseState(&x, &y);

        while(SDL_PollEvent(&startEvent)){
            if((startEvent.type == SDL_MOUSEBUTTONUP) && (inside == true)){
                proceed = true;
                startTexture.free();
            }else if(startEvent.type == SDL_QUIT){
                close();
            }
                    
            if((x > (Loader::SCREEN_WIDTH - startTexture.getWidth()) / 2) && (x < (Loader::SCREEN_WIDTH - startTexture.getWidth()) / 2 + startTexture.getWidth()) && 
            (y > (Loader::SCREEN_HEIGHT - startTexture.getHeight()) / 2) && (y < (Loader::SCREEN_HEIGHT - startTexture.getHeight()) / 2 + startTexture.getHeight())){
                inside = true;
                startTexture.loadText("START", red);
            }else{
                inside = false;
                startTexture.loadText("START", white);
            }
        }
        SDL_SetRenderDrawColor(Loader::gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(Loader::gRenderer);

        startTexture.renderTextures((Loader::SCREEN_WIDTH - startTexture.getWidth()) / 2, (Loader::SCREEN_HEIGHT - startTexture.getHeight()) / 2);

        SDL_RenderPresent(Loader::gRenderer);
    }
}

void Game::whoWins(){
    if((count1 == 3) || (count2 == 3)){
        blockTexture.free();
        dotTexture.free();

        if(count1 == 3){
            winnerTexture.loadText("PLAYER ONE WON", white);
        }
        if(count2 == 3){
            winnerTexture.loadText("PLAYER TWO WON", white);
        }

        count1 = 0;
        count2 = 0;

        for(int i = 0; i < MAX_ROUNDS; ++i){
            count1Texture.free();
            count2Texture.free();
        }

        if(count1 == 3){
            winnerTexture.loadText("PLAYER ONE WON", white);
        }
        if(count2 == 3){
            winnerTexture.loadText("PLAYER TWO WON", white);
        }

        restartTexture.loadText("RESTART", white);
        quitTexture.loadText("QUIT", white);

        SDL_Event gameOver;

        bool proceed = false;
        bool insideQuit = false;
        bool insideRestart = false;

        while(!proceed){
            int x, y;
            SDL_GetMouseState(&x, &y);

            while(SDL_PollEvent(&gameOver)){
                if((gameOver.type == SDL_MOUSEBUTTONUP) && (insideRestart == true)){
                    proceed = true;
                    winnerTexture.free();
                    restartTexture.free();
                    quitTexture.free();
                    count1 = 0;
                    count2 = 0;
                    load();
                }else if((gameOver.type == SDL_QUIT) || ((gameOver.type == SDL_MOUSEBUTTONUP) && (insideQuit == true))){
                    proceed = true;
                    close();
                }

                if((x > (Loader::SCREEN_WIDTH - restartTexture.getWidth()) / 2) && (x < (Loader::SCREEN_WIDTH - restartTexture.getWidth()) / 2 + restartTexture.getWidth()) && 
                (y > (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3 + winnerTexture.getHeight()) && (y < (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3 + winnerTexture.getHeight() + restartTexture.getHeight())){
                    insideRestart = true;
                    restartTexture.loadText("RESTART", red);
                }else{
                    insideRestart = false;
                    restartTexture.loadText("RESTART", white);
                }

                if((x > (Loader::SCREEN_WIDTH - quitTexture.getWidth()) / 2) && (x < (Loader::SCREEN_WIDTH - quitTexture.getWidth()) / 2 + quitTexture.getWidth()) && 
                (y > (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3 + winnerTexture.getHeight() + restartTexture.getHeight()) && (y < (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3 + winnerTexture.getHeight() + restartTexture.getHeight() + quitTexture.getHeight())){
                    insideQuit = true;
                    quitTexture.loadText("QUIT", red);
                }else{
                    insideQuit = false;
                    quitTexture.loadText("QUIT", white);
                }
            }
            SDL_SetRenderDrawColor(Loader::gRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(Loader::gRenderer);

            winnerTexture.renderTextures((Loader::SCREEN_WIDTH - winnerTexture.getWidth()) / 2, (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3);
            restartTexture.renderTextures((Loader::SCREEN_WIDTH - restartTexture.getWidth()) / 2, (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3 + winnerTexture.getHeight());
            quitTexture.renderTextures((Loader::SCREEN_WIDTH - quitTexture.getWidth()) / 2, (Loader::SCREEN_HEIGHT - winnerTexture.getHeight()) / 3 + winnerTexture.getHeight() + restartTexture.getHeight());

            SDL_RenderPresent(Loader::gRenderer);
        }
    }
}

void Game::load(){
    srand(time(0));

    count1Texture.loadText(std::to_string(count1), white);
    count2Texture.loadText(std::to_string(count2), white);

    dot.draw((rand() % (380 - 260 + 1)) + 260, (Loader::SCREEN_HEIGHT - Dot::DOT_HEIGHT - count1Texture.getHeight()) / 2);
    block1.draw(0, (Loader::SCREEN_HEIGHT - Block::BLOCK_HEIGHT - count1Texture.getHeight()) / 2);
    block2.draw(Loader::SCREEN_WIDTH - Block::BLOCK_WIDTH, (Loader::SCREEN_HEIGHT - Block::BLOCK_HEIGHT - count1Texture.getHeight()) / 2);

    dotTexture.loadBlank(Loader::SCREEN_WIDTH / 64, Loader::SCREEN_HEIGHT / 48, SDL_TEXTUREACCESS_TARGET);
    blockTexture.loadBlank(Loader::SCREEN_WIDTH / 64, Loader::SCREEN_HEIGHT / 8, SDL_TEXTUREACCESS_TARGET);
}

void Game::gameLoop(){
    bool quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            block1.handleEventWASD(e);
            block2.handleEventArrows(e);
        }
        block1.move();
        block2.move();
        dot.move();

        renderSection();
        whoWins();
    }
    close();
}

void Game::renderSection(){
    SDL_SetRenderDrawColor(Loader::gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(Loader::gRenderer);

    SDL_SetRenderDrawColor(Loader::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //vertical line
    SDL_RenderDrawLine(Loader::gRenderer, Loader::SCREEN_WIDTH / 2, 0, Loader::SCREEN_WIDTH / 2, Loader::SCREEN_HEIGHT);
    //horizontal line
    SDL_RenderDrawLine(Loader::gRenderer, 0, Loader::SCREEN_HEIGHT - count1Texture.getHeight(), Loader::SCREEN_WIDTH, Loader::SCREEN_HEIGHT - count1Texture.getHeight());

    blockTexture.setRenderTarget();

    SDL_Rect rect = {0, 0, Loader::SCREEN_WIDTH / 64, Loader::SCREEN_HEIGHT / 8};
    SDL_RenderFillRect(Loader::gRenderer, &rect);

    SDL_SetRenderTarget(Loader::gRenderer, NULL);


    dotTexture.setRenderTarget();

    SDL_Rect ball = {0, 0, Loader::SCREEN_WIDTH / 64, Loader::SCREEN_HEIGHT / 48};
    SDL_RenderFillRect(Loader::gRenderer, &ball);

    SDL_SetRenderTarget(Loader::gRenderer, NULL);

    block1.render();
    block2.render();
    dot.render();

    count1Texture.renderTextures((Loader::SCREEN_WIDTH - count1Texture.getWidth()) / 4, Loader::SCREEN_HEIGHT - count1Texture.getHeight());
    count2Texture.renderTextures((Loader::SCREEN_WIDTH - count2Texture.getWidth()) * 3 / 4, Loader::SCREEN_HEIGHT - count2Texture.getHeight());

    SDL_RenderPresent(Loader::gRenderer);
}

void Game::close(){
    blockTexture.free();
    dotTexture.free();
    winnerTexture.free();
    restartTexture.free();
    quitTexture.free();

    for(int i = 0; i < MAX_ROUNDS; ++i){
        count1Texture.free();
        count2Texture.free();
    }

    TTF_CloseFont(Loader::gFont);
    Loader::gFont = NULL;

	SDL_DestroyRenderer(Loader::gRenderer);
	SDL_DestroyWindow(Loader::gWindow);
	Loader::gWindow = NULL;
	Loader::gRenderer = NULL;

    TTF_Quit();
    SDL_Quit();
}
