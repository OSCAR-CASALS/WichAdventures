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
    buttons.push_back(Button("Play_text",104, 50, Vector2D(188, 110), PlayButtonClicked));
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
    /*
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
    */
    for(auto &go : m_gameObjects){
        go->update();
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
    camera.render();
    for(auto &g : m_gameObjects){
        g->draw();
    }

}

bool first_level::OnEnter(){
    //loadTexture("floorTile", "Sprites/HGTiles.png");
    loadTexture("floorTile", "Sprites/TileMap_Mario.png");
    loadTexture("PlayerTexture", "Sprites/mario.png");
    loadTexture("Item", "Sprites/Items.png");
    //loadTexture("PlayerTextura", "Sprites/GreyScaleDaddy.png");
    //loadTexture("DaddyProfile", "Sprites/ProfilePicks.png");
    //vector<int> testLevel = {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1};

    fstream file("Sprites/test.json");
    json data = json::parse(file);
    file.close();

    vector<int> testLevel = data["layers"][0]["data"].get<vector<int>>();

    // Loading first layer

    int MapWidth = data["layers"][0]["width"].get<int>();
    int MapHeight = data["layers"][0]["height"].get<int>();
    testLevel.push_back(-1);

    tileMapsCol.emplace_back(make_unique<TileMap>(testLevel, MapHeight, MapWidth, 16, 30, 19));

    // Loading GameObjects Layer

    for (auto &i : data["layers"][1]["objects"]){

        int posX = i["x"].get<int>();

        int posY = i["y"].get<int>();

        if(i["name"].get<string>() == "PlayerSpawn"){
            unique_ptr<Player> Pl = make_unique<Player>("PlayerTexture", Vector2D(posX, posY), 8, 0);

            Pl->SetTiles(tileMapsCol);

            m_gameObjects.emplace_back(move(Pl));
        }
    }
    //tileMapsCol.push_back(TileMap("Sprites/test.txt", 26, 40, 16, 30, 24));

    

    /*
    for(auto&tilemap : tileMapsCol){
       tilemap->setCameraY(26.0);
    }
    */
    Set_Background_Color(147, 148, 254, 1);
    camera.SetTileMaps(tileMapsCol);
    camera.SetGameObjects(m_gameObjects);
    camera.setY(40.0);

    camera.setTarget(m_gameObjects[0]);

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
    m_gameObjects.clear();
    cout << "Deleted Pointers" << endl;
    return true;
}