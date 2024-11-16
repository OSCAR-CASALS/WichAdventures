#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "TileClass.h"
#include<memory>
#include<map>

using namespace std;


class DinamicObject : public GameObject{
    private:
        vector<unique_ptr<TileMap>> *Tiles = nullptr;
        vector<unique_ptr<GameObject>> *Obj = nullptr;
    public:
        DinamicObject(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl){}
        void HandleMovement();
        void SetTiles(vector<unique_ptr<TileMap>> &objects){
            Tiles = &objects;
        }
        void SetObj(vector<unique_ptr<GameObject>> &objects){
            Obj = &objects;
        }
        void update();

};


class Player : public DinamicObject{
    private:
        bool m_jumping = false;
    public:
        Player(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : DinamicObject(tex, pos, row, column, dir, Collideable, angl){}
        void update();
        void OnLoad();
};

#endif