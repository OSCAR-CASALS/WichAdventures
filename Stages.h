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

// Menu

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

// Level

class first_level: public GameState{
    private:
        static const string s_first_levelID;
        vector<unique_ptr<TileMap>> tileMapsCol;
        ObjectLayer m_gameObjects;
        Camera camera;
        bool GameOver = false;
        bool Goal = false;
        int playerIndex = 0;
    public:
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        virtual string getStateID() const {return s_first_levelID;}
};


// GameOver Scene

class GameOverScene : public GameState{
    private:
        static const string s_menuID;
        vector <Button> buttons;
        static void PlayButtonClicked();
    public:
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        virtual string getStateID() const {return s_menuID;}
};


// Win Scene

class WinScene : public GameState{
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

#endif
