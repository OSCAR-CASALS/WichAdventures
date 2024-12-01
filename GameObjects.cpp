#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "GameObjects.h"
#include "TileClass.h"
#include "GameObjectHandler.h"
#include<map>

void DinamicObject::HandleMovement(){
    Vector2D vel = getVelocity() + getAcceleration();
    Vector2D offsetPos = Vector2D(getOffsetPosX(), getOffsetPosY());
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
            vector<pair <int, int>> colX = o->checkCollision(newPosition + offsetPos, getWidth() + getOffsetX(), getHeight() + getOffsetY());
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
            vector<pair <int, int>> colY = o->checkCollision(newPosition + offsetPos, getWidth() + getOffsetX(), getHeight() + getOffsetY());
            
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
        SDL_Rect re = {getPosition().getX() + getOffsetPosX(), getPosition().getY() + getOffsetPosY(), getWidth() + getOffsetX(), getHeight() + getOffsetY()};
        draw_rect(re);
    }
}

void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    setAcceleration(0, 0.4);

    if(state[SDL_SCANCODE_D]){
        setAccelerationX(acceleration);
        animate = getWidth();
        head = 32;
        Flip = SDL_FLIP_NONE;
    }else if(state[SDL_SCANCODE_A]){
        setAccelerationX(-acceleration);
        animate = getWidth();
        head = 32;
        Flip = SDL_FLIP_HORIZONTAL;
    }
    else{
        setAccelerationX(0);
        animate = 0;
        head = 0;
    }

    if(mouse.Left_Click == true){
        if(getVelocity().getX() != 0){
            head = 48;
        }else{
            head = 16;
        }
    }

    if(state[SDL_SCANCODE_W]){
        if(canJump == true){
            setAccelerationY(-acceleration);
            initialPos = getRealPos().getY();
            m_jumping = true;
            canJump = false;
        }else if(m_jumping == true){
            if (getRealPos().getY() > (initialPos - maxJump)){
                setAccelerationY(-acceleration);
            }
        }
    }

    if(getAcceleration().getY() > 0.0){
        m_jumping = false;
    }

    if(state[SDL_SCANCODE_UP]){
        maxJump += 2;
        cout << maxJump << endl;
    }else if(state[SDL_SCANCODE_DOWN]){
        maxJump -= 2;
        cout << maxJump << endl;
    }

    DinamicObject::update();

    canJump = getAcceleration().getY() == 0 ? true : false;
}

void Player::OnCollisionY(){
    if(getVelocity().getY() > 0){
        canJump = true;
    }
}

void Player::draw(){
    if(getVelocity().getY() != 0){
        drawFrame("PlayerTexture", 96, getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
        head = (head < 32) ? head + 32 : head;
    } else if(animate > 0){
        drawFrame("PlayerTexture", 96 + (animate*update_anim(128, 4)), getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
    }else{
        drawFrame("PlayerTexture", 80, getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
    }
    drawFrame("PlayerTexture", head, getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
    //DinamicObject::draw();
}

void Player::OnLoad(){
    //setTileWidthHeight(12, 16);
    SetMaxSpeed(2, 4);
    setTag("Player");
    SetDeacceleration(acceleration);
    SetOffsetY(-2);
    setShowHitbox(true);
    setTileWidthHeight(16, 26);
}

// Goomba functions

void Goomba::update(){
    Vector2D offsetPos = Vector2D(getOffsetPosX(), getOffsetPosY());
    setAccelerationY(0.4);
    
    if(getPosition().getX() < 0){
        AutoDestroy();
    }

    vector<unique_ptr<GameObject>> &O = getObjects().getVector();
    
    if(O.size() > 0){
        GameObject* Pl = O[0].get();

        Vector2D PlOffset = Vector2D(Pl->getOffsetPosX(), Pl->getOffsetPosY());

        if(vectors_cols(getRealPos() + offsetPos, getWidth() + getOffsetX(), getHeight() + getOffsetY(), 
            Pl->getRealPos() + PlOffset, Pl->getWidth() + Pl->getOffsetX(), Pl->getHeight() + Pl->getOffsetY()
            )){
                AutoDestroy();
            }
        }
    
    setVelocity(direction, getVelocity().getY());
    DinamicObject::update();
}

void Goomba::OnCollisionX(){
    direction = direction * (-1);
}

// spawner

void GoombaSpawner::AddGoomba(){
    Vector2D Rpos = getRealPos();
    if(Obj && Tiles){
        unique_ptr<Goomba> G = make_unique<Goomba>("Enemies", Rpos, 16, 0);
        G->SetTiles(*Tiles);
        G->OnLoad();
        G->SetObj(*Obj, Obj->getSize());
        Obj->AddObject(move(G));
    }
}

void GoombaSpawner::update(){
    if(Spawned == false){
        AddGoomba();
        Spawned = true;
    }
}