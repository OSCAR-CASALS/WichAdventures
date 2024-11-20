#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "GameObjects.h"
#include "TileClass.h"
#include<map>

void DinamicObject::HandleMovement(){
    Vector2D vel = getVelocity() + getAcceleration();
    Vector2D offsetPos = Vector2D(offsetPosX, offsetPosY);
    Vector2D newPosition = getRealPos();
    //Vector2D drawPosition = getPosition();
    Vector2D Acceleration = getAcceleration();
    
    if(vel.getX() > maxSpeedX){
        vel.setX(maxSpeedX);
    }else if(vel.getX() < ((-1) * maxSpeedX)){
        vel.setX(((-1) * maxSpeedX));
    }

    if(vel.getY() > maxSpeedY){
        vel.setY(maxSpeedY);
    }else if(vel.getY() < ((-1) * maxSpeedY)){
        vel.setY(((-1) * maxSpeedY));
    }


    if(Acceleration.getX() == 0){
        if(vel.getX() > 0){
            vel.setX(round((vel.getX() - deacceleration) * 100.0)/100.0);
        }else if(vel.getX() < 0){
            vel.setX(round((vel.getX() + deacceleration) * 100.0)/100.0);
        }
    }

    if(Acceleration.getY() == 0){
        if(vel.getY() > 0){
            vel.setY(round((vel.getY() - deacceleration) * 100.0)/100.0);
        }else if(vel.getY() < 0){
            vel.setY(round((vel.getY() + deacceleration) * 100.0)/100.0);
        }
    }


    if(Tiles){
        newPosition.setX(newPosition.getX() + vel.getX());
        for(auto &o : *Tiles){
            vector<pair <int, int>> colX = o->checkCollision(newPosition + offsetPos, getWidth() + offsetX, getHeight() + offsetY);
            if(colX.size() != 0){
                newPosition.setX(getRealPos().getX());
                vel.setX(0);
                Acceleration.setX(0);
                OnCollisionX();
                break;
            }
        }
        newPosition.setY(newPosition.getY() + vel.getY());
        for(auto &o : *Tiles){
            vector<pair <int, int>> colY = o->checkCollision(newPosition + offsetPos, getWidth() + offsetX, getHeight() + offsetY);
            
            if(colY.size() != 0){
                //cout << "ColHapened" << endl;
                newPosition.setY(getRealPos().getY());
                vel.setY(0);
                Acceleration.setY(0);
                OnCollisionY();
                break;
            }
        }
    }
    setVelocity(vel.getX(), vel.getY());
    setAcceleration(Acceleration.getX(), Acceleration.getY());
    setRealPos(newPosition.getX(), newPosition.getY());
}


void DinamicObject::update(){
    HandleMovement();
    //GameObject::update();
}

void DinamicObject::draw(){
    GameObject::draw();
    if(showHitbox == true){
        SDL_Rect re = {getPosition().getX() + offsetPosX, getPosition().getY() + offsetPosY, getWidth() + offsetX, getHeight() + offsetY};
        draw_rect(re);
    }
}

void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    setAcceleration(0, 0.4);

    if(state[SDL_SCANCODE_D]){
        setAccelerationX(acceleration);
    }else if(state[SDL_SCANCODE_A]){
        setAccelerationX(-acceleration);
    }
    else{
        setAccelerationX(0);
    }

    if(state[SDL_SCANCODE_K]){
        if((getAcceleration().getX() < (acceleration*2)) & (getAcceleration().getX() > -(acceleration*2))){
            setAccelerationX(getAcceleration().getX() * 2);
        }
        SetMaxSpeed(2, 4);
    }else{
        SetMaxSpeed(0.5, 4);
    }

    if(state[SDL_SCANCODE_W]){
        if((m_jumping == false) && (canJump == true)){
            setAccelerationY(-acceleration);
        }
    }

    DinamicObject::update();
}

void Player::OnLoad(){
    //setTileWidthHeight(12, 16);
    SetMaxSpeed(0.5, 1);
    setTag("Player");
    SetDeacceleration(acceleration);
    SetOffsetY(-2);
    setShowHitbox(true);
}

// Goomba functions

void Goomba::update(){
    setAccelerationY(0.4);
    if(getPosition().getX() < (getDimensions().first - 10)){
        // Destroy object
    }
    setVelocity(direction, getVelocity().getY());
    DinamicObject::update();
}

void Goomba::OnCollisionX(){
    cout << direction << endl;
    direction = direction * (-1);
}