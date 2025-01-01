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
        float numberSteps = 1.0;
        int index = 0;
        bool atack = false;
        bool interact = false;
        bool collideWalls = true;
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

        vector<unique_ptr<TileMap>>& getTileMaps(){
            return *Tiles;
        }

        virtual void AutoDestroy(){
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

        virtual void OnCollisionX(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i){}

        virtual void OnCollisionY(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i){}

        void setNumberSteps(float x){
            numberSteps = x;
        }

        void setShowHitbox(bool x){
            showHitbox = x;
        }

        void setAttack(bool x){
            atack = x;
        }

        void setInteract(bool x){
            interact = x;
        }

        bool getAttack(){
            return atack;
        }

        bool getInteract(){
            return interact;
        }

        void setCollideWalls(bool x){
            collideWalls = x;
        }

};

// Derivates

class Player : public DinamicObject{
    private:
        bool m_jumping = false;
        bool canJump = true;
        float acceleration = 1;
        int animate = 0;
        int head = 0;
        SDL_RendererFlip Flip = SDL_FLIP_NONE;
        float initialPos = 0;
        float maxJump = 52;
        bool canShoot = true;
        bool wandObtained = false;
    public:
        Player(string tex, Vector2D pos, int row, int column,SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : DinamicObject(tex, pos, row, column, dir, Collideable, angl){
            OnLoad();
            setTag("Player");
        }
        void update();
        void OnLoad();
        void draw();
        void OnCollisionY(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i);
        void setWandObtained(bool x){
            wandObtained = x;
        }
        void ItemPicked();
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

        void OnCollisionX(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i);
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

// Bullets

class ExplosionMagic : public DinamicObject{
    private:
        bool *modBool = nullptr;
    public:
        ExplosionMagic(string tex, Vector2D pos, int row, int column, int speedX, int speedY, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : DinamicObject(tex, pos, row, column, dir, Collideable, angl) {
            setWidth(8);
            setHeight(8);
            setVelocity(speedX, speedY);
            setTag("Bullet");
            setShowHitbox(false);
            setCollideWalls(false);
        }
        void setBoolean(bool &Modify){
            modBool = &Modify;
        }
        void OnCollisionX(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i){
            //AutoDestroy();
            vector<unique_ptr<TileMap>>& T = getTileMaps();
            vector<vector<pair<int, int>>> TheIDs = T[i]->GetIDs();
            //vector<vector<unique_ptr<GameObject>>>& TObjs = T[0]->getTilesObj();
            for(auto &a : cols.second){
                pair<int, int> I = TheIDs[a.first][a.second];
                //cout << I.first << endl;
                if(I.first == 300){
                    AutoDestroy();
                }
            }
        }
        void OnCollisionY(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i){
            //AutoDestroy();
            vector<unique_ptr<TileMap>>& T = getTileMaps();
            vector<vector<pair<int, int>>> TheIDs = T[i]->GetIDs();
            //vector<vector<unique_ptr<GameObject>>>& TObjs = T[0]->getTilesObj();
            for(auto &a : cols.second){
                pair<int, int> I = TheIDs[a.first][a.second];
                //cout << I.first << endl;
                if(I.first == 300){
                    AutoDestroy();
                }
            }
        }

        void AutoDestroy(){
            if(modBool){
                *modBool = true;
            }

            DinamicObject::AutoDestroy();
        }

        void draw(){
            pair<int, int> Dims = getDimensions();
            if((getPosition().getX() < 0) | (getPosition().getX() > Dims.first) | (getPosition().getY() < 0) | (getPosition().getY() > Dims.second)){
                //cout << "By world: " << Dims.first << " " << Dims.second << " " << getPosition().getX() << " " << getPosition().getY() << endl;
                AutoDestroy();
                setAttack(true);
            }
            DinamicObject::draw();
        }
};

// Objects particular to the project

class Bonsai : public GameObject{
    private:
        ObjectLayer *Obj = nullptr;
        vector<unique_ptr<TileMap>> *Tiles = nullptr;
        int index = 0;
        int TileIndex = 0;
        float heightCloud = -4.0;
        int Pl_Index = 0;
    public:
        Bonsai(string tex, Vector2D pos, int row, int column, int PlayerIndex = 0, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl), Pl_Index(PlayerIndex) {}  
        void OnCollision(Vector2D ColPosition, int width, int height, int &tileX, int &tileY, string signal);
        
        void SetObj(ObjectLayer &objects, int i){
            Obj = &objects;
            index = i;
        }

        void SetTiles(vector<unique_ptr<TileMap>> &objects, int t_index = 0){
            Tiles = &objects;
            TileIndex = t_index;
        }

        void setHeightCloud(float y){
            heightCloud = y;
        }
        ObjectLayer& getObjects(){
            return *Obj;
        }
};

class cloud : public GameObject{
    private:
        ObjectLayer *Obj = nullptr;
        int index = 0;
        bool plInside = false;
        int Pl_Index = 0;
    public:
        cloud(string tex, Vector2D pos, int row, int column, int PlayerIndex = 0, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl), Pl_Index(PlayerIndex) {}
        void update();
        void onLoad(){}

        void SetObj(ObjectLayer &objects, int i){
            Obj = &objects;
            index = i;
        }

        ObjectLayer& getObjects(){
            return *Obj;
        }

        //void OnCollision(Vector2D ColPosition, int width, int height, int &tileX, int &tileY, string signal="");
};

class Wand : public GameObject{
    private:
        ObjectLayer *Obj = nullptr;
        int index = 0;
        int Pl_index = 0;
        int directionS = 1;
        Vector2D originalPos;
    public:
        Wand(string tex, Vector2D pos, int row, int column, int PlayerIndex = 0, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl), 
        Pl_index(PlayerIndex), originalPos(pos) {}
        void SetObj(ObjectLayer &objects, int i){
            Obj = &objects;
            index = i;
        }
        void update();

        void AutoDestroy(){
            //Obj->erase(Obj->begin() + index);
            Obj->setIndexToRemove(index);
        }
};

#endif