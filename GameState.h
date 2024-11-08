#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Functions.h"
/*
class GameState{
    public:
        virtual ~GameState(){}
        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool OnEnter() = 0;
        virtual bool OnExit() = 0;
        
        virtual string getStateID() const = 0;   
};
*/

class GameState
{
public:
    
    virtual ~GameState() {}
    
    virtual void update() = 0;
    virtual void render() = 0;
    
    virtual bool OnEnter() = 0;
    virtual bool OnExit() = 0;
    
    virtual void resume() {}
    
    virtual std::string getStateID() const = 0;
    
protected:
    
    GameState() : m_loadingComplete(false), m_exiting(false)
    {
        
    }
    
    bool m_loadingComplete;
    bool m_exiting;
    
    std::vector<std::string> m_textureIDList;
};

#endif