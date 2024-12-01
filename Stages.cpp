#include "Stages.h"
#include "Game_class.h"
#include <set>
#include<algorithm>
//#include "Enemy.h"

//menu
const string MenuStage::s_menuID = "MENU";

void MenuStage::update(){
    for(auto &btn:buttons){
        btn.update();
    }
}

void MenuStage::render(){
    drawFull("Title", 12, 20, false, SDL_FLIP_NONE);
    for(auto &btn:buttons){
        btn.draw();
    }
}

bool MenuStage::OnEnter(){
    create_text("Play_text", "PLAY", {0, 128, 0, 255}, true);
    create_text("Title", "ANOTHER CLONE", {0, 128, 0, 255}, false);
    buttons.push_back(Button("Play_text",48, 24, Vector2D(188, 110), PlayButtonClicked,{255, 0, 0, 1}, {255, 255, 255, 1}));
    return true;
}

bool MenuStage::OnExit(){
    removeTexture("Play_text");
    removeTexture("Title");
    return true;
}

void MenuStage::PlayButtonClicked(){
    Game::Instance()->getStateMachine()->changeState(new first_level());
}

const string first_level::s_first_levelID = "FIRST_LEVEL";


void first_level::update(){
    //PlayerHandler();
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_RIGHT]){
        camera.setSpeed(2, 0);
    }else if(state[SDL_SCANCODE_LEFT]){
        camera.setSpeed(-2, 0);
    } else if(state[SDL_SCANCODE_UP]){
        camera.setSpeed(0, -2);
    } else if(state[SDL_SCANCODE_DOWN]){
        camera.setSpeed(0, 2);
    }
    else{
        camera.setSpeed(0, 0);
    }
    

   vector<unique_ptr<GameObject>> &O = m_gameObjects.getVector();
    // && (O[0]->getVelocity().getX() != 0)
    if(O[0]->getRealPos().getX() > ((getDimensions().first/2) - 16)){
        camera.setSpeed(O[0]->getVelocity().getX(), O[0]->getVelocity().getY());
    }else{
        camera.setSpeed(0, O[0]->getVelocity().getY());
    }
    camera.update();  

}

void first_level::render(){
    //SDL_Rect re = {0, 0, 1280, 720};
    //draw_fill_rect(re, 0, 0, 255, 1, false);
    /*
    player.draw();
    */
    //drawFull("DaddyProfile", 0, 0, false, SDL_FLIP_NONE);
    pair<int, int> Dims =  getDimensions();
    SDL_Rect re = {0, 0,Dims.first, Dims.second};
    draw_fill_rect(re, 147, 148, 254, 1);
    camera.render();
    /*
    for(auto &g : m_gameObjects){
        g->draw();
    }
    */

}

bool first_level::OnEnter(){
    //loadTexture("floorTile", "Sprites/HGTiles.png");
    loadTexture("floorTile", "Sprites/TilesMario.png");
    loadTexture("PlayerTexture", "Sprites/Witch_imported.png");
    loadTexture("Item", "Sprites/Items.png");
    loadTexture("Enemies", "Sprites/Enemies.png");
    //loadTexture("PlayerTextura", "Sprites/GreyScaleDaddy.png");
    //loadTexture("DaddyProfile", "Sprites/ProfilePicks.png");
    //vector<int> testLevel = {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1};

    fstream file("Sprites/TestLevel.json");
    json data = json::parse(file);
    file.close();

    vector<int> testLevel = data["layers"][0]["data"].get<vector<int>>();

    // Loading first layer

    int MapWidth = data["layers"][0]["width"].get<int>();
    int MapHeight = data["layers"][0]["height"].get<int>();
    testLevel.push_back(-1);
    vector<int> CollideableIDs = {0, 32, 1, 33, 2, 3, 34, 35};
    tileMapsCol.emplace_back(make_unique<TileMap>("floorTile",testLevel, MapHeight, MapWidth, 32, 50, 50, 1024, CollideableIDs));

    // Loading GameObjects Layer
    int cameraPosX = 0;
    int cameraPosY = 0;
    for (auto &i : data["layers"][1]["objects"]){

        int posX = i["x"].get<int>();

        int posY = i["y"].get<int>();

        if(i["name"].get<string>() == "PlayerSpawn"){
            unique_ptr<Player> Pl = make_unique<Player>("PlayerTexture", Vector2D(posX, posY), 0, 0);
            Pl->SetTiles(tileMapsCol);
            Pl->OnLoad();
            m_gameObjects.AddObject(move(Pl));
            cameraPosX = posX;
            cameraPosY = posY;
        }/*else if(i["name"].get<string>() == "GoombaSpawn"){
            unique_ptr<Goomba> G = make_unique<Goomba>("Enemies", Vector2D(posX, posY), 16, 0);
            G->SetTiles(tileMapsCol);
            G->OnLoad();
            G->SetObj(m_gameObjects, m_gameObjects.getSize());
            m_gameObjects.AddObject(move(G));
        }*/
    }
    //tileMapsCol.push_back(TileMap("Sprites/test.txt", 26, 40, 16, 30, 24));

    

    /*
    for(auto&tilemap : tileMapsCol){
       tilemap->setCameraY(26.0);
    }
    */
    //Set_Background_Color(147, 148, 254, 1);
    camera.SetTileMaps(tileMapsCol);
    camera.SetGameObjects(m_gameObjects);
    pair<int, int> Dims = getDimensions();
    camera.setX(cameraPosX - (Dims.first / 2));
    camera.setY(cameraPosY - (Dims.second / 2)); 

    for(auto &t : tileMapsCol){
        vector<vector<unique_ptr<GameObject>>>& TObjs = t->getTilesObj();
        vector<vector<pair<int, int>>> TIDs = t->GetIDs();

        for(int y = 0; y < TIDs.size(); y++){
            vector<pair<int, int>> ID = TIDs[y];
            for(int x = 0; x < ID.size(); x++){
                pair<int, int> e = ID[x];
                if(e.first == 857){
                    unique_ptr<GoombaSpawner> NewG = make_unique<GoombaSpawner>(TObjs[y][e.second]->getRealPos());
                    NewG->SetObj(m_gameObjects, m_gameObjects.getSize());
                    NewG->SetTiles(tileMapsCol);
                    t->ChangeTile(move(NewG), 50, y, x);
                }
            }
        }
    }

    //camera.setTarget(m_gameObjects[0]);

    return true;
}

bool first_level::OnExit(){
    //Set_Background_Color(0, 0, 0, 1);
    removeTexture("floorTile");
    removeTexture("PlayerTexture");
    
    camera.Exit();
    tileMapsCol.clear();
    /*
    for(auto &tilemap: tileMapsCol){
        tilemap->Exit();
    }

    tileMapsCol.clear();
    */
    /*
    for(auto &go: m_gameObjects){
        delete go;
    }
    */
    m_gameObjects.Exit();
    cout << "Deleted Pointers" << endl;
    return true;
}