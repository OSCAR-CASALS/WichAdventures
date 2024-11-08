#include "GameStateMachine.h"

void GameStageMachine::pushState(GameState *pState){
    m_gameStates.push_back(pState);
    m_gameStates.back()->OnEnter();
}

void GameStageMachine::popState(){
    if(!m_gameStates.empty()){
        if(m_gameStates.back()->OnExit()){
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStageMachine::changeState(GameState *pState){
    if(!m_gameStates.empty()){
        if(m_gameStates.back()->getStateID() == pState->getStateID()){
            return; //do nothing
        }
        if (m_gameStates.back()->OnExit()){
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
        m_gameStates.push_back(pState);
        m_gameStates.back()->OnEnter();
}

void GameStageMachine::update(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->update();
    }
}

void GameStageMachine::render(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->render();
    }
}

void GameStageMachine::clean(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->OnExit();

        delete m_gameStates.back();
        
        m_gameStates.clear();
    }
}
