#ifndef STAGES_H
#define STAGES_H

#include "Functions.h"
#include "GameState.h"
#include "Button.h"
#include "TileClass.h"
#include "Objects.h"
#include "Camera.h"
#include "GameObjects.h"
#include "GameObjectHandler.h"
#include <memory>
#include<fstream>
#include<nlohmann/json.hpp>

using json = nlohmann::json;


class MenuStage : public GameState{
    private:
        static const string s_menuID;
        vector <Button> buttons;
        //Functions
        static void PlayButtonClicked();
    public:
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        virtual string getStateID() const {return s_menuID;}
};

class first_level: public GameState{
    private:
        static const string s_first_levelID;
        vector<unique_ptr<TileMap>> tileMapsCol;
        ObjectLayer m_gameObjects;
        Camera camera;
    public:
        // first_level() : player("PlayerTexture", Vector2D(228, 119), Vector2D(231, 128), Vector2D(230,288),12, 6, 16, 6, 0, 0, "Item"){}
        // first_level() : player("PlayerTexture", Vector2D(228, 131), Vector2D(231, 140), Vector2D(336, 288), 12, 6, 16, 6, 0, 0, "Item"){}
        // first_level() : player("PlayerTexture", Vector2D(270, 321), Vector2D(273, 330), Vector2D(273, 330),12, 6, 16, 6, 0, 0, "Item"){}
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        //virtual void PlayerHandler();

        virtual string getStateID() const {return s_first_levelID;}
};

#endif
