#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "GameObjects.h"
#include "TileClass.h"
#include<map>

void Player::OnLoad(){
    setTileWidthHeight(12, 16);
}

void DinamicObject::HandleMovement(){
    Vector2D vel = getVelocity() + getAcceleration();
    Vector2D newPosition = getRealPos() + vel;
    Vector2D Acceleration = getAcceleration();



    if(Tiles){
        for(auto &o : *Tiles){
            pair <int, int> colX = o->checkCollision(newPosition, getWidth(), getHeight());
            if(colX.first != -1){
                vel.setX(0);
                Acceleration.setX(0);
                break;
            }
        }
        for(auto &o : *Tiles){
            pair <int, int> colY = o->checkCollision(newPosition, getWidth(), getHeight());
            
            if(colY.first != -1){
                vel.setY(0);
                Acceleration.setY(0);
                break;
            }
        }
    }
    setVelocity(vel.getX(), vel.getY());
    setAcceleration(Acceleration.getX(), Acceleration.getY());
}


void DinamicObject::update(){
    HandleMovement();
    GameObject::update();
}

void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if(m_jumping == false){
        setAcceleration(0, -0.2);
    }
    
    if(state[SDL_SCANCODE_D]){
        setAcceleration(0.2, 0);
    }else if(state[SDL_SCANCODE_A]){
        setAcceleration(-0.2, 0);
    } else if(state[SDL_SCANCODE_W]){
        setAcceleration(0, -0.2);
    } else if(state[SDL_SCANCODE_S]){
        setAcceleration(0, 0.2);
    }
    else{
        setAcceleration(0, 0);
    }
    DinamicObject::update();
}