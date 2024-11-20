#include "Camera.h"

void Camera::setX(float x){
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->setCameraX(x);   
        }
    }
    m_position.setX(x);
}

void Camera::setY(float y){
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->setCameraY(y);   
        }
    }
    m_position.setY(y);
}

void Camera::update(){
    if(Target){
        //scroll_speed = Target->getVelocity();
        pair <int, int> dims = getDimensions();
        setX(Target->getRealPos().getX() - (dims.first/2));
        setY(Target->getRealPos().getY() - (dims.second/2));
    }else{
        setX(m_position.getX() + scroll_speed.getX());
        setY(m_position.getY() + scroll_speed.getY());
    }
    for (auto &t : *TileMapsToMove){
        t->update();   
    }
    if(GameO){
        for(auto &o : *GameO){
            o->update();
        }
    }
}

void Camera::render(){
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->draw();  
        }
    }
    if(GameO){
        for (auto &o : *GameO){
            o->setPosition(o->getRealPos().getX() - m_position.getX(), o->getRealPos().getY() - m_position.getY());
            o->draw();
        }
    }
}

void Camera::Exit(){
    if(TileMapsToMove){
        for(auto &t : *TileMapsToMove){
            t->Exit();
        }
        
        TileMapsToMove->clear();
    }
}

void Camera::SetGameObjects(vector<unique_ptr<GameObject>> &objects){
    GameO = &objects;
}