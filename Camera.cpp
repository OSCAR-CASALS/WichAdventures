#include "Camera.h"

void Camera::setX(float x){
    float diff = x - m_position.getX();
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->setCameraX(x);   
        }
    }
    /*
    if(GameO){
        //cout << diff << endl;
        for (auto &o : *GameO){
            o->setPosition(o->getRealPos().getX() - diff, o->getPosition().getY());
        }
    }
    */
    m_position.setX(x);
}

void Camera::setY(float y){
    float diff = y - m_position.getY();
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->setCameraY(y);   
        }
    }
    /*
    if(GameO){
        for (auto &o : *GameO){
            o->setPosition(o->getRealPos().getX(), o->getPosition().getY() - diff);
        }
    }
    */
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
    if(TileMapsToMove){
        for (auto &t : *TileMapsToMove){
            t->draw();  
        }
    }
    if(GameO){
        //cout << diff << endl;
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