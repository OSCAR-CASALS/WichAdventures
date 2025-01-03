#include "TileClass.h"
#include<fstream>

void TileMap::load(vector<int> tilemapInput){
    int col = 0;
    float x = 0;
    float y = 0;
    int tilesetWidth = m_tileset_twidth / TileSize;
    vector<pair<int, int>> ids;
    int tCount = 0;
    tiles.emplace_back(vector<unique_ptr<GameObject>>{});
    int rowCount = 0;
    for(int tile : tilemapInput){
        if(col >= m_cols){
            col = 0;
            x = 0;
            y += TileSize;
            tiles.emplace_back(vector<unique_ptr<GameObject>>{});
            rowCount += 1;
            tilesID.push_back(ids);
            ids.clear();
            tCount = 0;
        }

        if((tile != 0) && (tile != -1)){
            int trow = ((tile - 1) / tilesetWidth) * TileSize;
            int tcol = ((tile - 1) % tilesetWidth) * TileSize;
            bool Collideable = find(m_Collideable_IDs.begin(), m_Collideable_IDs.end(), tile - 1) != m_Collideable_IDs.end() ? true : false;
            
            unique_ptr<NormalTile> Bl = make_unique<NormalTile>(m_TextureID, Vector2D(x, y), trow, tcol, SDL_FLIP_NONE, Collideable);
            Bl->setWidth(TileSize);
            Bl->setHeight(TileSize);
            tiles[rowCount].emplace_back(move(Bl));

            ids.push_back({tile, tCount});
            tCount += 1;
            tiles[rowCount].back()->OnLoad();
        }else{
            ids.push_back({tile, -1});
        }

        col += 1;
        x += TileSize;
    }
}

void TileMap::draw(){
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
                    tiles[my][n.second]->draw();
                }
            }
            mx += 1;
        }
        mx = int(camera.getX()) / TileSize;
        my += 1;
    }
}

void TileMap::update(bool scrollX, bool scrollY){
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

pair<vector<pair<int, int>>, vector<pair<int, int>>> TileMap::checkCollision(Vector2D pos, int width, int height, bool interaction, bool attack, string objectTag){ 
    int leftTile = int(pos.getX()) / TileSize;
    int rightTile = (int(pos.getX()) + width) / TileSize;
    int topTile = int(pos.getY()) / TileSize;
    int bottomTile = (int(pos.getY()) + height) / TileSize;

    if(leftTile < 0){ leftTile = 0;}
    if(rightTile >= int(tilesID[0].size())){rightTile = tilesID[0].size() - 1;}
    if(topTile < 0){ topTile = 0; }
    if(bottomTile >= int(tilesID.size())){bottomTile = tilesID.size() - 1;}


    vector<pair<int, int>> res;
    vector<pair<int, int>> All;

    for(int i=leftTile; i<=rightTile; i++){
        for(int j=topTile; j<=bottomTile; j++){
            pair<int, int> TheTile = tilesID[j][i];
            if(TheTile.first != 0){
                tiles[j][TheTile.second]->OnCollision(pos, width, height, i, j, objectTag);
                if(tiles[j][TheTile.second]->getCollideable() == true){
                    res.push_back({j, i});
                }
                All.push_back({j, i});
            }
        }
    }
    return {res, All};
}


void TileMap::RemoveTile(int x, int y){
    pair<int, int> TheTile = tilesID[y][x];

    if(TheTile.first != 0){
        tiles.erase(tiles.begin() + TheTile.second);
    }

    tilesID[y][x] = {0, -1};
}

void TileMap::Exit(){
    tiles.clear();
}

