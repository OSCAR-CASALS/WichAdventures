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
    drawFull("Title", 0,-30, false, SDL_FLIP_NONE, false, true);
    for(auto &btn:buttons){
        btn.draw();
    }
}

bool MenuStage::OnEnter(){
    create_text("Play_text", "Click here to play", {255, 255, 255, 255}, true);

    loadTexture("Title", "Sprites/Logo.png");
    buttons.push_back(Button("Play_text",190, 24, Vector2D(150, 220), PlayButtonClicked,{0, 0, 0, 1}, {255, 255, 255, 1}));
    SDL_ShowCursor(SDL_ENABLE);
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

// Play Scene

const string first_level::s_first_levelID = "FIRST_LEVEL";


void first_level::update(){

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if(getEscapePressed() && (is_cinematic == false)){
        my_pause = 1;
        //is_cinematic = true;
    }else if((is_cinematic == true) && (state[SDL_SCANCODE_J] || state[SDL_SCANCODE_K] || state[SDL_SCANCODE_L] || state[SDL_SCANCODE_L] || state[SDL_SCANCODE_I])){
        is_cinematic = false;
        my_pause = -1;
    }else if(is_cinematic == false){
        my_pause = -1;
    }

    if(my_pause == -1){
    
        vector<unique_ptr<GameObject>> &O = m_gameObjects.getVector();
        
        camera.setY(O[playerIndex]->getRealPos().getY() - (getDimensions().second / 2));

        camera.update();

        if(Goal == true){
            Game::Instance()->getStateMachine()->changeState(new WinScene()); 
        }

        if(GameOver == true){
            Game::Instance()->getStateMachine()->changeState(new GameOverScene());
        }
    }

}

void first_level::render(){
    pair<int, int> Dims =  getDimensions();
    SDL_Rect re = {0, 0,Dims.first, Dims.second};
    draw_fill_rect(re, 147, 148, 254, 1);
    camera.render();
    
    if(is_cinematic == true){
        drawFull("Instructions_Item", 12, 20, false, SDL_FLIP_NONE, true);
        drawFull("Instructions_1", 12, 32, false, SDL_FLIP_NONE, true);
        drawFull("Instructions_2", 12, 44, false, SDL_FLIP_NONE, true);
        drawFull("Instructions_3", 12, 56, false, SDL_FLIP_NONE, true);
    }

}

bool first_level::OnEnter(){
    // Loading Textures
    loadTexture("floorTile", "Sprites/nestle.png");
    loadTexture("PlayerTexture", "Sprites/Witch_imported.png");
    loadTexture("Enemies", "Sprites/Enemies.png");
    loadTexture("Magic", "Sprites/Magics.png");
    loadTexture("ObjectsTextures", "Sprites/Objects.png");
    // Text
    create_text("Instructions_Item", "You have obtained the magic wand!!!", {255, 255, 255, 255}, true);
    create_text("Instructions_1", "Press J to shoot left, K to shoot down, L to", {255, 255, 255, 255}, true);
    create_text("Instructions_2", "shoot right, and I to shoot up.", {255, 255, 255, 255}, true);
    create_text("Instructions_3", "Press any shooting button to continue.", {255, 255, 255, 255}, true);

    fstream file("Sprites/OverworldSideScroller.json");
    json data = json::parse(file);
    file.close();

    // Loading map Layer
    vector<int> CollideableIDs = {6193, 6322, 6194, 6192, 6320, 6321, 3841, 3844, 3842, 11781, 11783, 5673, 5936, 5937, 5938, 9149, 3840, 6191, 6319};

    int cameraPosX = 0;
    int cameraPosY = 0;

    for(const auto &element : data["layers"]){

        if(element.at("type").get<string>() == "tilelayer"){
            int MapWidth = element.at("width").get<int>();
            int MapHeight = element.at("height").get<int>();
            vector<int> Level = element.at("data").get<vector<int>>();
            Level.push_back(-1);
            tileMapsCol.emplace_back(make_unique<TileMap>("floorTile",Level, MapHeight, MapWidth, 16, 50, 50, 2048, CollideableIDs));
        }else if(element.at("type").get<string>() == "objectgroup"){
            
            for(auto &obj : element["objects"]){
                int posX = obj.at("x").get<int>();

                int posY = obj.at("y").get<int>();
                if(obj.at("name").get<string>() == "PlayerSpawn"){
                    unique_ptr<Player> Pl = make_unique<Player>("PlayerTexture", Vector2D(posX, posY), 0, 0);
                    Pl->SetTiles(tileMapsCol);
                    Pl->SetObj(m_gameObjects, m_gameObjects.getSize());
                    playerIndex = m_gameObjects.getSize();
                    
                    m_gameObjects.AddObject(move(Pl));
                    cameraPosX = posX;
                    cameraPosY = posY;
                } else if(obj.at("name").get<string>() == "MagicWand"){
                    unique_ptr<Wand> GO = make_unique<Wand>("ObjectsTextures", Vector2D(posX, posY), 16, 0);
                    GO->SetObj(m_gameObjects, m_gameObjects.getSize());
                    
                    m_gameObjects.AddObject(move(GO));
                }
            }
        }
    }


    camera.SetTileMaps(tileMapsCol);
    camera.SetGameObjects(m_gameObjects);
    pair<int, int> Dims = getDimensions();
    camera.setX(cameraPosX - (Dims.first / 2));
    camera.setY(cameraPosY - (Dims.second / 2)); 

    // Loading tiles that have references to objects particular of the scene

    for(auto &t : tileMapsCol){
        vector<vector<unique_ptr<GameObject>>>& TObjs = t->getTilesObj();
        vector<vector<pair<int, int>>> TIDs = t->GetIDs();

        for(int y = 0; y < TIDs.size(); y++){
            vector<pair<int, int>> ID = TIDs[y];
            for(int x = 0; x < ID.size(); x++){
                pair<int, int> e = ID[x];
                switch(e.first){
                    case 3846: {
                        unique_ptr<Bonsai> NewG = make_unique<Bonsai>("ObjectsTextures", TObjs[y][e.second]->getRealPos(), 0, 0, playerIndex);
                        //NewG->SetObj(m_gameObjects, m_gameObjects.getSize());
                        NewG->SetTiles(tileMapsCol);
                        NewG->SetObj(m_gameObjects, m_gameObjects.getSize());
                        t->ChangeTile(move(NewG), 300, y, x); 
                        break;
                    }
                    case 54: {
                        unique_ptr<GameOverFloor> GF = make_unique<GameOverFloor>("", TObjs[y][e.second]->getRealPos(), 0, 0);
                        GF->setBoolean(GameOver);
                        t->ChangeTile(move(GF), 53, y, x);
                        break;
                    }case 811: {
                        unique_ptr<GameOverFloor> Gl = make_unique<GameOverFloor>("floorTile", TObjs[y][e.second]->getRealPos(), 96, 672);
                        Gl->setBoolean(Goal);
                        t->ChangeTile(move(Gl), 53, y, x);
                        break;
                    }case 939: {
                        unique_ptr<GameOverFloor> Gl = make_unique<GameOverFloor>("floorTile", TObjs[y][e.second]->getRealPos(), 112, 672);
                        Gl->setBoolean(Goal);
                        t->ChangeTile(move(Gl), 53, y, x);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
    SDL_ShowCursor(SDL_DISABLE);

    return true;
}

bool first_level::OnExit(){

    removeTexture("floorTile");
    removeTexture("PlayerTexture");
    removeTexture("Enemies");
    removeTexture("Magic");
    removeTexture("ObjectsTextures");

    removeTexture("Instructions_1");
    removeTexture("Instructions_2");
    removeTexture("Instructions_3");
    
    camera.Exit();
    tileMapsCol.clear();
    
    m_gameObjects.Exit();
    
    return true;
}

// Game Over

const string GameOverScene::s_menuID = "GAMEOVER";

void GameOverScene::update(){
    for(auto &btn:buttons){
        btn.update();
    }
}

void GameOverScene::render(){
    drawFull("Title", 120, 20, false, SDL_FLIP_NONE);
    for(auto &btn:buttons){
        btn.draw();
    }
}

bool GameOverScene::OnEnter(){
    create_text("Play_text", "Click here to Play Again", {255, 255, 255, 255}, true);
    create_text("Title", "GAME OVER", {255, 0, 0, 255}, false);
    buttons.push_back(Button("Play_text",246, 24, Vector2D(120, 110), PlayButtonClicked,{255, 0, 0, 1}, {255, 255, 255, 1}));
    SDL_ShowCursor(SDL_ENABLE);
    return true;
}

bool GameOverScene::OnExit(){
    removeTexture("Play_text");
    removeTexture("Title");
    return true;
}

void GameOverScene::PlayButtonClicked(){
    Game::Instance()->getStateMachine()->changeState(new first_level());
}

// Win Scene

const string WinScene::s_menuID = "YOUWON";

void WinScene::update(){
    for(auto &btn:buttons){
        btn.update();
    }
}

void WinScene::render(){
    drawFull("Title_1", 0, 0, false, SDL_FLIP_NONE, false, true);
    //drawFull("Title_2", 12, 50, false, SDL_FLIP_NONE);
    for(auto &btn:buttons){
        btn.draw();
    }
}

bool WinScene::OnEnter(){
    create_text("Play_text", "Click here to Play Again", {0, 255, 0, 255}, true);
    loadTexture("Title_1", "Sprites/WinScreen.png");
    //create_text("Title_1", "Congratulations!", {0, 255, 0, 255}, false);
    //create_text("Title_2", "You have finished the test level!", {0, 255, 0, 255}, true);
    //buttons.push_back(Button("Play_text",246, 24, Vector2D(120, 250), PlayButtonClicked,{0, 0, 0, 1}, {255, 255, 255, 1}));
    SDL_ShowCursor(SDL_ENABLE);
    
    return true;
}

bool WinScene::OnExit(){
    removeTexture("Play_text");
    removeTexture("Title_1");
    //removeTexture("Title_2");

    return true;
}

void WinScene::PlayButtonClicked(){
    Game::Instance()->getStateMachine()->changeState(new first_level());
}