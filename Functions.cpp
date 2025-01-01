#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Functions.h"
#include "structs.h"
#include "GameStateMachine.h"
#include "Game_class.h"

using namespace std;


SDL_Window *screen = 0;
SDL_Renderer *render = 0;
TTF_Font *f;
TTF_Font *font;
TTF_Font *smaller_font;
int screen_width = 480;
int screen_height = 270;
int window_size = 960;
int window_height = 540;
int close;
map <string, SDL_Texture*> textures;
float pr = 0.0;
int cl = 0;
int x;
int y;
int z;
int alpha;
bool EscapePressed = false;
//Extern variavles
Mouse mouse {Vector2D(0, 0), false, false};

int initSystem(string title){
    int renderFlags = 0; //windowFlags
    //windowFlags = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Couldn't initialise SDL: " << SDL_GetError() << endl;
        return 1; 
    }
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0){
        cout << "Couldn't initialise SDL_IMG: " << SDL_GetError() << endl;
        return 1;
    }
    if (TTF_Init() < 0){
        cout << "Couldn't initialise TTF: " << SDL_GetError() << endl;
        return 1;
    }
    screen = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderFlags = SDL_RENDERER_ACCELERATED;
    font = TTF_OpenFont("Sprites/joystix_monospace.otf", 30); //Loading text font, the first parameter indicates the font and the second one is the size.
    smaller_font = TTF_OpenFont("Sprites/joystix_monospace.otf", 12);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    render = SDL_CreateRenderer(screen, -1, renderFlags);
    SDL_RenderSetLogicalSize(render, screen_width, screen_height);
    return 0;
}

void DoInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                close = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    mouse.Left_Click = true;
                }
                if(event.button.button == SDL_BUTTON_RIGHT){
                    mouse.Right_Click = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT){
                    mouse.Left_Click = false;
                }
                if(event.button.button == SDL_BUTTON_RIGHT){
                    mouse.Right_Click = false;
                }
                break;
            case SDL_MOUSEMOTION:
                mouse.mouse_pos.setX(event.motion.x);
                mouse.mouse_pos.setY(event.motion.y);
                break;
            case SDL_KEYUP: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    if(EscapePressed == true){
                        EscapePressed = false;
                    }else{
                        EscapePressed = true;
                    }
                    
                    //printf("Escape key pressed!\n");
                }
                break;
            }
            default:
                break;
        }
    }
}

void PrepScene(){
    SDL_SetRenderDrawColor(render, x, y, z, alpha);
    SDL_RenderClear(render);
}

void presentScene(){
    SDL_RenderPresent(render);
}

void loadTexture(string id, const char *filename){
    SDL_Texture *tex;
    tex = IMG_LoadTexture(render, filename);
    textures[id] = tex;
}

void create_text(string id, const char *text, const SDL_Color &color, bool small){
    if (small == false){
        f = font;
    }
    else{
        f = smaller_font;
    }
    SDL_Surface * surface = TTF_RenderText_Solid(f, text, color);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(render, surface);
    textures[id] = tex;
    SDL_FreeSurface(surface);
}

void drawFrame(string id, int columnFrame, int rowFrame, int width, int height, int x, int y, bool show_hitbox, const SDL_RendererFlip flip, float angle){
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_Rect image_r;
    image_r.x = columnFrame;
    image_r.y = rowFrame;
    image_r.w = r.w = width;
    image_r.h = r.h = height;
    
    SDL_RenderCopyEx(render, textures[id], &image_r, &r, angle, 0, flip);
    if(show_hitbox == true){
        draw_rect(r);
    }
}

void drawFull(string id, int x, int y, bool show_hitbox, const SDL_RendererFlip flip, bool fillBackground, bool fillScreen){
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_QueryTexture(textures[id], NULL, NULL, &r.w, &r.h);
    
    if(fillBackground == true){
        draw_fill_rect(r, 0, 0, 0, 1);
    }

    if(fillScreen == true){
        r.w = screen_width;
        r.h = screen_height;
    }

    SDL_RenderCopyEx(render, textures[id], NULL, &r, 0, 0, flip);
    if(show_hitbox == true){
        draw_rect(r);
    }
}

void removeTexture(string id){
    SDL_DestroyTexture(textures[id]);
    textures.erase(id);
}

int update_anim(int fpms, int n_frames){
    int m_Frame = int((SDL_GetTicks()/fpms)%n_frames);
    return m_Frame;
}

void draw_rect(SDL_Rect &re, int col1 , int col2, int col3, int col4){
    SDL_SetRenderDrawColor(render, col1, col2, col3, col3);
    SDL_RenderDrawRect(render, &re);
}

void draw_fill_rect(SDL_Rect &re, int col1, int col2, int col3, int col4, bool center){
    if (center == true){
        re.x -= re.w/2;
        re.y -= re.h/2;
    }
    SDL_SetRenderDrawColor(render, col1, col2, col3, col4);
    SDL_RenderFillRect(render, &re);
}

void clean(){
    //Destroy GameStateMachine
    Game::Instance()->getStateMachine()->clean();
    //Destroy textures
    if(textures.size() > 0){
        for(auto &t:textures){
        SDL_DestroyTexture(t.second);
        }
    }
    // Destroy render
    SDL_DestroyRenderer(render);
    // Destroy window
    SDL_DestroyWindow(screen);
    //Destroy font
    TTF_CloseFont(font);
    TTF_CloseFont(smaller_font);
    //Destroy GameStageMachinePointer
    
    // Close SDL
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int get_close_state(){
    return close;
}

void Set_Background_Color(int col1, int col2, int col3, int col4){
    x = col1;
    y = col2;
    z = col3;
    alpha = col4;
}

void finish(){
    close = 1;
}

bool vectors_cols(Vector2D pos1, int width1, int height1, Vector2D pos2, int width2, int height2){
    int left_1 = pos1.getX();
    int right_1 = pos1.getX() + width1;
    int top_1 = pos1.getY();
    int bottom_1 = pos1.getY() + height1;

    int left_2 = pos2.getX();
    int right_2 = pos2.getX() + width2;
    int top_2 = pos2.getY();
    int bottom_2 = pos2.getY() + height2;

    if(right_1 >= left_2 && left_1 <= right_2 && bottom_1 >= top_2 && top_1 <= bottom_2){
        return true;
    }
    return false;
}

pair<int, int> getDimensions(){
    return {screen_width, screen_height};
}

bool getEscapePressed(){
    return EscapePressed;
}