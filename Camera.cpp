#include "Camera.h"

void Camera::setX(float x){
    float diff = x - m_position.getX();
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->setCameraX(x);   
        }
    }
    if(GameO){
        //cout << diff << endl;
        for (auto &o : *GameO){
            o->setPosition(o->getPosition().getX() - diff, o->getPosition().getY());
        }
    }
    m_position.setX(x);
}

void Camera::setY(float y){
    float diff = y - m_position.getY();
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->setCameraY(y);   
        }
    }
    if(GameO){
        //cout << diff << endl;
        for (auto &o : *GameO){
            o->setPosition(o->getPosition().getX(), o->getPosition().getY() - diff);
        }
    }
    m_position.setY(y);
}

void Camera::update(){
    if(Target){
        //setX((Target->getPosition().getX() - (getDimensions().first / 2)) / 16);
        scroll_speed = Target->getVelocity();
        //setY((Target->getPosition().getY() - (getDimensions().second / 2)) / 16);
    }
    setX(m_position.getX() + scroll_speed.getX());
    setY(m_position.getY() + scroll_speed.getY());
    for (auto &t : *TileMapsToMove){
        t->update();   
    }
}

void Camera::render(){
    for (auto &t : *TileMapsToMove){
        t->draw();  
    }
}

void Camera::Exit(){
    
    for(auto &t : *TileMapsToMove){
        t->Exit();
    }
    
    TileMapsToMove->clear();
}