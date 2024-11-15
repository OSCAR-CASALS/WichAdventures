#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "GameObjects.h"
#include "TileClass.h"
#include<map>

void Player::OnLoad(){
    //setTileWidthHeight(12, 16);
    SetMaxSpeed(2, 2);
    setApplyAcceleration(true);
}

void DinamicObject::HandleMovement(){
    Vector2D vel = getVelocity() + getAcceleration();
    Vector2D newPosition = getRealPos();
    //Vector2D drawPosition = getPosition();
    Vector2D Acceleration = getAcceleration();



    if(Tiles){
        newPosition.setX(newPosition.getX() + vel.getX());
        for(auto &o : *Tiles){
            pair <int, int> colX = o->checkCollision(newPosition, getWidth(), getHeight());
            if(colX.first != -1){
                newPosition.setX(getRealPos().getX());
                vel.setX(0);
                Acceleration.setX(0);
                break;
            }
        }
        newPosition.setY(newPosition.getY() + vel.getY());
        for(auto &o : *Tiles){
            pair <int, int> colY = o->checkCollision(newPosition, getWidth(), getHeight());
            
            if(colY.first != -1){
                //cout << "ColHapened" << endl;
                newPosition.setY(getRealPos().getY());
                vel.setY(0);
                Acceleration.setY(0);
                break;
            }
        }
    }
    setVelocity(vel.getX(), vel.getY());
    setAcceleration(Acceleration.getX(), Acceleration.getY());
    setRealPos(newPosition.getX(), newPosition.getY());
    //setPosition(drawPosition.getX() + vel.getX(), drawPosition.getY() + vel.getY());
}


void DinamicObject::update(){
    HandleMovement();
    //GameObject::update();
}

void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    if(state[SDL_SCANCODE_D]){
        setVelocity(2, 0);
    }else if(state[SDL_SCANCODE_A]){
        setVelocity(-2, 0);
    }else if(state[SDL_SCANCODE_W]){
        setVelocity(0, -2);
    } else if(state[SDL_SCANCODE_S]){
        setVelocity(0, 2);
    }else if(state[SDL_SCANCODE_K]){
        setRealPos(40, 10);
    }
    else{
        setVelocity(0,0);
        /*
        setAcceleration(getAcceleration().getX(), 0);
        if(m_jumping == false){
            setAcceleration(getAcceleration().getX(), 0.2);
        }
        */
    }

    DinamicObject::update();
}