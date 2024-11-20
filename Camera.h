#include "TileClass.h"
#include "Objects.h"
#include "GameObjects.h"
#include <memory>

using namespace std;

class Camera {
    private:
        vector<unique_ptr<TileMap>>* TileMapsToMove = nullptr;
        GameObject* Target = nullptr;
        vector<unique_ptr<GameObject>>* GameO = nullptr;
        Vector2D scroll_speed;
        Vector2D m_position;
    public:

        Camera() : scroll_speed(0, 0), m_position(0, 0) {}

        void SetTileMaps (vector<unique_ptr<TileMap>> &TMaps){
            TileMapsToMove = &TMaps;
        }

        void SetGameObjects(vector<unique_ptr<GameObject>> &objects);

        void update();

        void render();

        void setX(float x);
        void setY(float y);
        
        float getX(){
            return m_position.getX();
        }

        float getY(){
            return m_position.getY();
        }

        void setTarget(unique_ptr<GameObject>& T){
            if(T){
                Target = T.get();
            }
        }

        void setSpeed(float x, float y){
            scroll_speed = Vector2D(x, y);
        }

        Vector2D getSpeed(){
            return scroll_speed;
        }

        void Exit();
};