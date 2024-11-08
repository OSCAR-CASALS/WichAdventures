#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <box2d/box2d.h>
#include "structs.h"
#include "GameStateMachine.h"


using namespace std;

//extern variables
extern Mouse mouse;

int initSystem(string title);
void DoInput();
void PrepScene();
void presentScene();
void loadTexture(string id, const char *filename);
void create_text(string id, const char *text, const SDL_Color &color, bool small = false);
void drawFrame(string id, int columnFrame, int rowFrame, int width, int height, int x, int y, bool show_hitbox, const SDL_RendererFlip flip, float angle=0.0);
void drawFull(string id, int x, int y, bool show_hitbox, const SDL_RendererFlip flip);
void removeTexture(string id);
int update_anim(int fpms, int n_frames);
void draw_rect(SDL_Rect &re, int col1 = 255, int col2 = 255, int col3 = 255, int col4 = 1);
void draw_fill_rect(SDL_Rect &re, int col1 = 255, int col2 = 255, int col3 = 255, int col4 = 1, bool center = false);
void clean();
int get_close_state();
void Set_Background_Color(int col1, int col2, int col3, int col4);
float deltaTime();
void finish();
bool vectors_cols(Vector2D pos1, int width1, int height1, Vector2D pos2, int width2, int height2);
pair<int, int> getDimensions();

#endif