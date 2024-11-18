#ifndef TILECLASS_H
#define TILECLASS_H

#include "Vector.h"
#include "Functions.h"
#include "Objects.h"
//#include "GameObjects.h"
#include <map>
#include <memory>

class TileMap {
    private:
        int m_height;
        int m_cols;
        int TileSize;
        int drawingDistanceX;
        int drawingDistanceY;
        vector<vector<pair<int, int>>> tilesID;
        vector<vector<unique_ptr<GameObject>>> tiles;
        Vector2D camera;
    public:
        void load(vector<int> tilemapInput);
        TileMap(vector<int> levelvector, int height, int cols, int tileSize, int renderDistanceX, int renderDistanceY) : m_height(height), m_cols(cols), TileSize(tileSize), drawingDistanceX(renderDistanceX), drawingDistanceY(renderDistanceY) ,camera(0, 0){
            load(levelvector);
        }
        void draw();
        void update(bool scrollX = true, bool scrollY = true);
        Vector2D getCamera(){
            return camera;
        }
        void setCamera(float x, float y){
            camera.setX(x);
            camera.setY(y);
        }
        void setCameraX(float x){
            camera.setX(x);
        }
        void setCameraY(float y){
            camera.setY(y);
        }
        vector<pair<int, int>> checkCollision(Vector2D pos, int width, int height, bool interaction = false, bool attack = false, string objectTag = "");

        void RemoveTile(int x, int y);

        void UpdateTilePos(int x, int y, int x2, int y2);

        void Exit();
        //void DefineSprites(){}
};

#endif