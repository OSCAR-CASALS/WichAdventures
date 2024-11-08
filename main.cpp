#include <iostream>
#include "Functions.h"
#include "Game_class.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char * args[]){
    if(initSystem("You know") == 0){
        Uint32 frameStart, frameTime;
        Game::Instance()->start();
        while(get_close_state() != 1){
            frameStart = SDL_GetTicks();
            //game->init();
            Game::Instance()->init();
            //game->update();
            Game::Instance()->update();
            //game->render();
            Game::Instance()->render();
            //game->end();
            Game::Instance()->end();
            frameTime = SDL_GetTicks() - frameStart;
            
            
            if(frameTime < DELAY_TIME){
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
            
        }
        clean();
        return 0;
    }
    return 1;
}