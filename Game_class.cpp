#include "Functions.h"
#include "Game_class.h"
#include "Vector.h"
#include"Stages.h"

Game* Game::s_pInstance = 0;

void Game::start(){
    m_pgameStatemachine = new GameStageMachine();
    m_pgameStatemachine->changeState(new MenuStage());
}

void Game::init(){
    PrepScene();
    DoInput();
}

void Game::update(){
    m_pgameStatemachine->update();
}

void Game::render(){
    m_pgameStatemachine->render();
}

void Game::end(){
    presentScene();
    //SDL_Delay(delay);
}