#include "GameObjectHandler.h"
#include<fstream>
//#include<nlohmann/json.hpp>

//using json = nlohmann::json;

void ObjectLayer::load(){
    
}

void ObjectLayer::draw(){
    int x1, y1, x2, y2, mx, my;
    pair<int, int> n = {0, 0};
    x1 = (int(camera.getX())%TileSize)*-1;
    x2 = x1 +  drawingDistanceX*TileSize + (x1 == 0 ? 0 : TileSize);
    mx = int(camera.getX()) / TileSize;

    y1 = (int(camera.getY())%TileSize)*-1;
    y2 = y1 + drawingDistanceY*TileSize + (y1 == 0 ? 0 : TileSize);
    my = int(camera.getY()) / TileSize;

    //cout << "MX: " << mx << ", MY: " << my << ", MCOLS: " << m_cols << ", M_HEIGHT: " << m_height << endl;

    for (int y=y1; y < y2; y+=TileSize){
        for(int x=x1; x < x2; x+=TileSize){
            if(mx < m_cols && mx >= 0 && my >=0 && my < m_height){ 
                n = tilesID[my][mx];
                if(n.first != 0){
                    //cout << n.first << endl;
                    tiles[my][n.second]->draw();
                }
            }
            mx += 1;
        }
        mx = int(camera.getX()) / TileSize;
        my += 1;
    }
}

void ObjectLayer::update(bool scrollX, bool scrollY){
    //code
    int x1, y1, x2, y2, mx, my;
    pair<int, int> n = {0, 0};
    x1 = (int(camera.getX())%TileSize)*-1;
    x2 = x1 +  drawingDistanceX*TileSize + (x1 == 0 ? 0 : TileSize);
    mx = int(camera.getX()) / TileSize;

    y1 = (int(camera.getY())%TileSize)*-1;
    y2 = y1 + drawingDistanceY*TileSize + (y1 == 0 ? 0 : TileSize);
    my = int(camera.getY()) / TileSize;
    for (int y=y1; y < y2; y+=TileSize){
        for(int x=x1; x < x2; x+=TileSize){
            if(mx < m_cols && mx >= 0 && my >=0 && my < m_height){
                n = tilesID[my][mx];
                if(n.first != 0){
                    tiles[my][n.second]->update();
                    tiles[my][n.second]->setPosition(x, y);
                }
            }
            mx += 1;
        }
        mx = int(camera.getX()) / TileSize;
        my += 1;
    }
}

pair<int, int> ObjectLayer::checkCollision(Vector2D pos, int width, int height, bool interaction, bool attack){ 
    int leftTile = int(pos.getX()) / TileSize;
    int rightTile = (int(pos.getX()) + width) / TileSize;
    int topTile = int(pos.getY()) / TileSize;
    int bottomTile = (int(pos.getY()) + height) / TileSize;

    if(leftTile < 0){ leftTile = 0;}
    if(rightTile >= int(tilesID[0].size())){rightTile = tilesID[0].size() - 1;}
    if(topTile < 0){ topTile = 0; }
    if(bottomTile >= int(tilesID.size())){bottomTile = tilesID.size() - 1;}

    //cout << "X-Axis: " << leftTile << " " << rightTile << endl;
    //cout << "Y-Axis: " << topTile << " " << bottomTile << endl;

    for(int i=leftTile; i<=rightTile; i++){
        for(int j=topTile; j<=bottomTile; j++){
            pair<int, int> TheTile = tilesID[j][i];
            //tiles[j][TheTile.second]->OnCollision();
            if(TheTile.first != 0){
                tiles[j][TheTile.second]->OnCollision(pos, width, height, i, j, "");
                if(tiles[j][TheTile.second]->getCollideable() == true){
                    return {j, i};
                }
            }
        }
    }
    return {-1, -1};
}


void ObjectLayer::RemoveTile(int x, int y){
    //pair<int, int> TheTile = tilesID[y][x];
    //if(TheTile.first != 0){
    //    delete tiles[y][TheTile.second];
    //}
    tilesID[y][x] = {0, -1};
}

void ObjectLayer::Exit(){
    /*
    for(auto &t: tiles){
        for(auto &ti: t){
            delete ti;
        }
    }
    */
    tiles.clear();
}

