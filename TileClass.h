#ifndef TILECLASS_H
#define TILECLASS_H

#include "Vector.h"
#include "Functions.h"
#include "Objects.h"
//#include "GameObjects.h"
#include <map>
#include <memory>
#include <algorithm>

class TileMap {
    private:
        string m_TextureID;
        int m_height;
        int m_cols;
        int TileSize;
        int drawingDistanceX;
        int drawingDistanceY;
        vector<vector<pair<int, int>>> tilesID;
        vector<vector<unique_ptr<GameObject>>> tiles;
        Vector2D camera;
        int m_tileset_twidth;
        vector<int> m_Collideable_IDs;
    public:
        void load(vector<int> tilemapInput);
        TileMap(string TextureID, vector<int> levelvector, int height, int cols, int tileSize, int renderDistanceX, int renderDistanceY, int tileset_twidth, vector<int> Cols) : m_TextureID(TextureID),m_height(height), m_cols(cols), TileSize(tileSize), drawingDistanceX(renderDistanceX), drawingDistanceY(renderDistanceY) ,camera(0, 0), m_tileset_twidth(tileset_twidth){
            m_Collideable_IDs = Cols;
            m_Collideable_IDs.push_back(-1);
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

        void ChangeTile(unique_ptr<GameObject> obj, int ID, int y, int x){
            pair<int, int> OldEntry = tilesID[y][x];
            pair<int, int> NewEntry = {ID, OldEntry.second};
            tiles[y][OldEntry.second] = move(obj);
            tilesID[y][x] = NewEntry;
        }

        vector<vector<pair<int, int>>> GetIDs(){
            return tilesID;
        }

        void UpdateTilePos(int x, int y, int x2, int y2);

        void Exit();

        vector<vector<unique_ptr<GameObject>>>& getTilesObj(){
            return tiles;
        }
        //void DefineSprites(){}
};

#endif