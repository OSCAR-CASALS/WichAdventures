#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "TileClass.h"
#include "GameObjectHandler.h"
#include<memory>
#include<map>
#include<cmath>

using namespace std;


// Base Class

class DinamicObject : public GameObject{
    private:
        vector<unique_ptr<TileMap>> *Tiles = nullptr;
        ObjectLayer *Obj = nullptr;
        float maxSpeedX = 100;
        float maxSpeedY = 100;
        float deacceleration = 0;
        bool showHitbox = false;
        int index = 0;
    public:
        DinamicObject(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl) {}
        
        void HandleMovement();
        
        void SetTiles(vector<unique_ptr<TileMap>> &objects){
            Tiles = &objects;
        }
        
        void SetObj(ObjectLayer &objects, int i){
            Obj = &objects;
            index = i;
        }

        ObjectLayer& getObjects(){
            return *Obj;
        }

        void AutoDestroy(){
            //Obj->erase(Obj->begin() + index);
            Obj->setIndexToRemove(index);
        }

        void SetMaxSpeed(float x, float y){
            maxSpeedX = x; 
            maxSpeedY = y;
        }

        pair<float, float> getMaxSpeed(){
            pair<float, float> result = {maxSpeedX, maxSpeedY};
            return result;
        }

        void SetDeacceleration(float d){
            deacceleration = d;
        }

        void update();

        virtual void draw();

        virtual void OnCollisionX(){}

        virtual void OnCollisionY(){}

        

        void setShowHitbox(bool x){
            showHitbox = x;
        }

};

// Derivates

class Player : public DinamicObject{
    private:
        bool m_jumping = false;
        bool canJump = true;
        float acceleration = 0.1;
        int animate = 0;
        SDL_RendererFlip Flip = SDL_FLIP_NONE;
    public:
        Player(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : DinamicObject(tex, pos, row, column, dir, Collideable, angl){}
        void update();
        void OnLoad();
        void draw();
};

class Goomba : public DinamicObject{
    private:
        float direction = 1;
    public:
        Goomba(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : DinamicObject(tex, pos, row, column, dir, Collideable, angl){}
        void OnLoad(){
            SetOffsetY(-2);
            SetOffsetX(-2);
            SetMaxSpeed(2, 2);
            setShowHitbox(true);
            setOffsetPosX(1);
        }
        void update();

        void OnCollisionX();
};

// Spawner

class GoombaSpawner : public GameObject{
    private:
        bool Spawned = false;
        ObjectLayer *Obj = nullptr;
        int index;
        vector<unique_ptr<TileMap>> *Tiles = nullptr;
    public:
        GoombaSpawner(Vector2D pos, bool Collideable = false) : GameObject("", pos, 16, 0) {}
        void update();
        void draw(){}

        void SetObj(ObjectLayer &objects, int i){
            Obj = &objects;
            index = i;
        }

        ObjectLayer& getObjects(){
            return *Obj;
        }

        void SetTiles(vector<unique_ptr<TileMap>> &objects){
            Tiles = &objects;
        }

        void AddGoomba();
};

#endif