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
    Vector2D newPosition = getRealPos() + getVelocity();
    Vector2D vel = getVelocity();

    if(Tiles){
        for(auto &o : *Tiles){
            pair <int, int> colX = o->checkCollision(newPosition, getWidth(), getHeight());
            if(colX.first != -1){
                vel.setX(0);
                break;
            }
        }
        for(auto &o : *Tiles){
            pair <int, int> colY = o->checkCollision(newPosition, getWidth(), getHeight());
            
            if(colY.first != -1){
                cout << "ColHapened" << endl;
                vel.setY(0);
                break;
            }
        }
    }
    setVelocity(vel.getX(), vel.getY());
}


void DinamicObject::update(){
    HandleMovement();
    GameObject::update();
}

void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    if(state[SDL_SCANCODE_D]){
        setVelocity(2, 0);
    }else if(state[SDL_SCANCODE_A]){
        setVelocity(-2, 0);
    } else if(state[SDL_SCANCODE_W]){
        setVelocity(0, -2);
    } else if(state[SDL_SCANCODE_S]){
        setVelocity(0, 2);
    }
    else{
        setVelocity(0, 0);
    }
    DinamicObject::update();
}