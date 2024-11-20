#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "TileClass.h"
#include<memory>
#include<map>
#include<cmath>

using namespace std;


// Base Class

class DinamicObject : public GameObject{
    private:
        vector<unique_ptr<TileMap>> *Tiles = nullptr;
        vector<unique_ptr<GameObject>> *Obj = nullptr;
        float maxSpeedX = 100;
        float maxSpeedY = 100;
        float deacceleration = 0;
        int offsetX = 0;
        int offsetY = 0;
        float offsetPosX = 0;
        float offsetPosY = 0;
        bool showHitbox = false;
    public:
        DinamicObject(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl) {}
        
        void HandleMovement();
        
        void SetTiles(vector<unique_ptr<TileMap>> &objects){
            Tiles = &objects;
        }
        
        void SetObj(vector<unique_ptr<GameObject>> &objects){
            Obj = &objects;
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

        void draw();

        virtual void OnCollisionX(){}

        virtual void OnCollisionY(){}

        void SetOffsetX(int x){
            offsetX = x;
        }

        void SetOffsetY(int y){
            offsetY = y;
        }

        int getOffsetX(){
            return offsetX;
        }

        int getOffsetY(){
            return offsetY;
        }

        void setShowHitbox(bool x){
            showHitbox = x;
        }

        void setOffsetPosX(float x){
            offsetPosX = x;
        }

        void setOffsetPosY(float y){
            offsetPosY = y;
        }

};

// Derivates

class Player : public DinamicObject{
    private:
        bool m_jumping = false;
        bool canJump = true;
        float acceleration = 0.1;
    public:
        Player(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : DinamicObject(tex, pos, row, column, dir, Collideable, angl){}
        void update();
        void OnLoad();
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

#endif