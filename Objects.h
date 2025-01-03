#ifndef OBJECTS_H
#define OBJECTS_H

#include"Functions.h"
#include "Vector.h"
#include<map>

extern int my_pause;
extern bool is_cinematic;

class GameObject{
    private:
        string m_Texture_ID;
        Vector2D m_position;
        int m_width = 16;
        int m_height = 16;
        int m_column;
        int m_row;
        SDL_RendererFlip direction;
        bool CanCollide;
        float angle;
        Vector2D m_velocity;
        Vector2D realPosition;
        Vector2D m_acceleration;
        int offsetX = 0;
        int offsetY = 0;
        float offsetPosX = 0;
        float offsetPosY = 0;
        string tag = "None";
    protected:
        GameObject(string tex, Vector2D pos, int row, int column, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : m_Texture_ID(tex), m_position(pos), m_column(column), m_row(row), direction(dir), CanCollide(Collideable), angle(angl), m_velocity(0, 0), realPosition(pos), m_acceleration(0, 0) {}
    public:
        virtual ~GameObject() {}
        virtual void update();
        virtual void OnCollision(Vector2D ColPosition, int width, int height, int &tileX, int &tileY, string signal=""){}
        virtual void OnLoad() {}
        virtual void draw();
        void setPosition(float x, float y){
            m_position = Vector2D(x, y);
        }
        Vector2D getPosition(){
            return m_position;
        }
        bool getCollideable(){
            return CanCollide;
        }
        void setCollideable(bool Collideable){
            CanCollide = Collideable;
        }
        void setTileWidthHeight(int w, int h){
            m_width = w;
            m_height = h;
        }

        void setVelocity(float x, float y){
            m_velocity = Vector2D(x, y);
        }

        Vector2D getVelocity(){
            return m_velocity;
        }
        int getWidth(){
            return m_width;
        }
        int getHeight(){
            return m_height;
        }

        Vector2D getRealPos(){
            return realPosition;
        }

        void setRealPos(float x, float y){
            realPosition = Vector2D(x, y);
        }

        Vector2D getAcceleration(){
            return m_acceleration;
        }

        void setAcceleration(float x, float y){
            m_acceleration = Vector2D(x, y);
        }
        void setAccelerationX(float x){
            m_acceleration.setX(x);
        }
        void setAccelerationY(float y){
            m_acceleration.setY(y);
        }
        string getTag(){
            return tag;
        }
        void setTag(string t){
            tag = t;
        }

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

        float getOffsetPosX(){
            return offsetPosX;
        }

        float getOffsetPosY(){
            return offsetPosY;
        }

        void setOffsetPosX(float x){
            offsetPosX = x;
        }

        void setOffsetPosY(float y){
            offsetPosY = y;
        }
        
        void setWidth(int w){
            m_width = w;
        }

        void setHeight(int h){
            m_height = h;
        }

        void setRow(int r){
            m_row = r;
        }

        int getRow(){
            return m_row;
        }

        void setColumn(int c){
            m_column = c;
        }

        int getColumn(){
            return m_column;
        }

        string getTextureID(){
            return m_Texture_ID;
        }
};

class NormalTile : public GameObject{
    public:
        NormalTile(string tex, Vector2D pos, int row, int column, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl) {}
        void update(){}
        void onLoad(){}
};

// Objects particular to the game

class GameOverFloor : public GameObject{
    private:
        bool *GameOverBool = nullptr;
        string Tex = "";
    public:
        GameOverFloor(string tex, Vector2D pos, int row, int column, SDL_RendererFlip dir = SDL_FLIP_NONE, bool Collideable = false, float angl = 0.0) : GameObject(tex, pos, row, column, dir, Collideable, angl), Tex(tex) {}
        void OnCollision(Vector2D ColPosition, int width, int height, int &tileX, int &tileY, string signal=""){
            if(signal == "Player"){
                if(GameOverBool){
                    *GameOverBool = true;
                }
            }
        }
        void setBoolean(bool &Modify){
            GameOverBool = &Modify;
        }
        void draw();
};

#endif