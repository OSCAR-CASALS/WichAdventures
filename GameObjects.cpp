#include"Functions.h"
#include "Vector.h"
#include "Objects.h"
#include "GameObjects.h"
#include "TileClass.h"
#include "GameObjectHandler.h"
#include<map>

//#define PI 3.14159265

void DinamicObject::HandleMovement(){
    Vector2D velProv = getVelocity() + getAcceleration();
    Vector2D offsetPos = Vector2D(getOffsetPosX(), getOffsetPosY());
    Vector2D newPosition = getRealPos();
    //Vector2D drawPosition = getPosition();
    Vector2D Acceleration = getAcceleration();
    
    if(velProv.getX() > maxSpeedX){
        velProv.setX(maxSpeedX);
    }else if(velProv.getX() < ((-1) * maxSpeedX)){
        velProv.setX(((-1) * maxSpeedX));
    }

    if(velProv.getY() > maxSpeedY){
        velProv.setY(maxSpeedY);
    }else if(velProv.getY() < ((-1) * maxSpeedY)){
        velProv.setY(((-1) * maxSpeedY));
    }


    if(Acceleration.getX() == 0){
        if(velProv.getX() > 0){
            velProv.setX(round((velProv.getX() - deacceleration) * 100.0)/100.0);
        }else if(velProv.getX() < 0){
            velProv.setX(round((velProv.getX() + deacceleration) * 100.0)/100.0);
        }
    }

    if(Acceleration.getY() == 0){
        if(velProv.getY() > 0){
            velProv.setY(round((velProv.getY() - deacceleration) * 100.0)/100.0);
        }else if(velProv.getY() < 0){
            velProv.setY(round((velProv.getY() + deacceleration) * 100.0)/100.0);
        }
    }

    Vector2D vel = velProv / numberSteps;
    if(Tiles){
        for (float i = 0.0;  i < numberSteps; i++){
            newPosition.setX(newPosition.getX() + vel.getX());
            int cx = 0;
            for(auto &o : *Tiles){
                pair<vector<pair<int, int>>, vector<pair<int, int>>> colX = o->checkCollision(newPosition + offsetPos, getWidth() + getOffsetX(), getHeight() + getOffsetY(), getInteract(), getAttack(), getTag());
                if(colX.second.size() != 0){
                    if((collideWalls == true) && (colX.first.size() != 0)){
                        newPosition.setX(getRealPos().getX());
                        velProv.setX(0);
                        Acceleration.setX(0);
                    }
                    OnCollisionX(colX, cx);
                    //break;
                }
                cx += 1;
            }
            newPosition.setY(newPosition.getY() + vel.getY());
            int cy = 0;
            for(auto &o : *Tiles){
                pair<vector<pair<int, int>>, vector<pair<int, int>>> colY = o->checkCollision(newPosition + offsetPos, getWidth() + getOffsetX(), getHeight() + getOffsetY(), getInteract(), getAttack(), getTag());
                
                if(colY.second.size() != 0){
                    //cout << "ColHapened" << endl;
                    if((collideWalls == true) && (colY.first.size() != 0)){
                        newPosition.setY(getRealPos().getY());
                        velProv.setY(0);
                        Acceleration.setY(0);
                    }
                    OnCollisionY(colY, cy);
                    //break;
                }
                cy += 1;
            }
        }
    }
    setVelocity(velProv.getX(), velProv.getY());
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

float get_Angle(int x1, int y1, int x2, int y2)
{
    float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / M_PI);
    return angle >= 0 ? angle : 360 + angle;
}


void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    setAcceleration(0, 0.4);

    if(state[SDL_SCANCODE_D]){
        setAccelerationX(acceleration);
        animate = getWidth();
        head = 32;
        Flip = SDL_FLIP_NONE;
        //setOffsetPosX(3);
        //SetOffsetX(-3);
    }else if(state[SDL_SCANCODE_A]){
        setAccelerationX(-acceleration);
        animate = getWidth();
        head = 32;
        Flip = SDL_FLIP_HORIZONTAL;
        //setOffsetPosX(0);
    }
    else{
        setAccelerationX(0);
        animate = 0;
        head = 0;
    }
    // mouse.Left_Click == true

    int SX_Bullet = 0;
    int SY_Bullet = 0;
    bool Shoot = false;
    if(wandObtained == true){
        if(state[SDL_SCANCODE_J]){
            SX_Bullet = -8;
            Shoot = true;
        } else if(state[SDL_SCANCODE_L]){
            SX_Bullet = 8;
            Shoot = true;
        }

        if(state[SDL_SCANCODE_I]){
            SY_Bullet = -8;
            Shoot = true;
        } else if(state[SDL_SCANCODE_K]){
            SY_Bullet = 8;
            Shoot = true;
        }
    }

    if(Shoot){
        if(getVelocity().getX() != 0){
            head = 48;
        }else{
            head = 16;
        }
        if(canShoot){
            ObjectLayer& O_Layer = getObjects();
                //Vector2D OriginPoint = Vector2D(getRealPos().getX() + (getWidth() / 2), getRealPos().getY() + (getHeight() / 2));
                //Vector2D ScreenPoint = Vector2D(getPosition().getX() + (getWidth() / 2), getPosition().getY() + (getHeight() / 2));
                //Vector2D Diff = mouse.mouse_pos - ScreenPoint;
                /*
                float sX = 0;
                float sY = 0;

                if(Diff.getX() > 0){
                    sX = 1.0;
                }else if(Diff.getX() < 0){
                    sX = -1.0;
                }

                if(Diff.getY() > 0){
                    sY = 1.0;
                }else if(Diff.getY() < 0){
                    sY = -1.0;
                }
                */
                //float cosinus = ((Diff.getX())/(sqrt((Diff.getX()*Diff.getX()) + (Diff.getY()*Diff.getY()))));

                //float magnitude = sqrt((Diff.getX() + Diff.getX()) + (Diff.getY() * Diff.getY()))
                
                //float hypothenus = sqrt((Diff.getX() * Diff.getX()) + (Diff.getY() * Diff.getY()));

                //float angle = get_Angle(mouse.mouse_pos.getX(), mouse.mouse_pos.getY(), getPosition().getX(), getPosition().getY());
            //int direct = Flip == SDL_FLIP_NONE ? 1 : -1;

            unique_ptr<ExplosionMagic> ExpMagic = make_unique<ExplosionMagic>("Magic", 
                                                                                getRealPos(), 
                                                                                0, 0, 
                                                                                SX_Bullet, SY_Bullet
                                                                            );
            ExpMagic->SetTiles(getTileMaps());
            ExpMagic->SetObj(O_Layer, O_Layer.getSize());
            ExpMagic->setBoolean(canShoot);
            O_Layer.AddObject(move(ExpMagic));
            canShoot = false;
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

    //const Uint8 *state = SDL_GetKeyboardState(NULL);
    /*
    if(state[SDL_SCANCODE_UP]){
        SetOffsetY(getOffsetY() - 1);
        cout << "Offset Y: " << getOffsetY() << endl;
        cout << "Offset Pos Y: " << getOffsetPosY() << endl;
    }else if(state[SDL_SCANCODE_DOWN]){
        SetOffsetY(getOffsetY() + 1);
        cout << "Offset Y: " << getOffsetY() << endl;
        cout << "Offset Pos Y: " << getOffsetPosY() << endl;
    }else if(state[SDL_SCANCODE_E]){
        setOffsetPosY(getOffsetPosY() - 1);
        cout << "Offset Y: " << getOffsetY() << endl;
        cout << "Offset Pos Y: " << getOffsetPosY() << endl;
    }else if(state[SDL_SCANCODE_F]){
        setOffsetPosY(getOffsetPosY() + 1);
        cout << "Offset Y: " << getOffsetY() << endl;
        cout << "Offset Pos Y: " << getOffsetPosY() << endl;
    }
    */
    DinamicObject::update();

    canJump = getAcceleration().getY() > 0 ? false : canJump;
}

void Player::OnCollisionY(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i){
    if((cols.first.size() != 0)){
        m_jumping = false;
        if(getVelocity().getY() > 0){
            canJump = true;
        }
    }
    //unique_ptr<TileMap>& TM = getTileMaps()[i];
    //vector<vector<unique_ptr<GameObject>>>& TOb = TM->getTilesObj();
    


    /*for(auto &t : cols){
        if(TOb[t.first][t.second]){
            cout << t.first << " " << t.second << endl;
            GameObject* TObs = TOb[t.first][t.second].get();
            Vector2D P = TObs->getRealPos();
            if(P.getY() > (getRealPos().getY() + getOffsetPosY() + getHeight() + getOffsetY())){
                canJump = true;
            }
        }
    }*/

}

void Player::draw(){
    if(is_cinematic == false){
        if(canJump == false){
            drawFrame("PlayerTexture", 96, getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
            head = (head < 32) ? head + 32 : head;
        } else if(animate > 0){
            drawFrame("PlayerTexture", 96 + (animate*update_anim(128, 4)), getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
        }else{
            drawFrame("PlayerTexture", 80, getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);
        }
    }
    drawFrame("PlayerTexture", head, getRow(), getWidth(), getHeight(), getPosition().getX(), getPosition().getY(), false, Flip);

    //SDL_Rect re = {getPosition().getX() + getOffsetPosX(), getPosition().getY() + getOffsetPosY(), getWidth() + getOffsetX(), getHeight() + getOffsetY()};
    //draw_rect(re);
}

void Player::OnLoad(){
    //setTileWidthHeight(12, 16);
    SetMaxSpeed(2, 4);
    setTag("Player");
    SetDeacceleration(acceleration);
    SetOffsetY(-9);
    setOffsetPosY(6);
    setOffsetPosX(2);
    SetOffsetX(-4);
    setShowHitbox(true);
    setTileWidthHeight(16, 26);
    setNumberSteps(10);
}

void Player::ItemPicked(){
    head = 160;
    is_cinematic = true;
    my_pause = true;
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

void Goomba::OnCollisionX(pair<vector<pair<int, int>>, vector<pair<int, int>>> &cols, int &i){
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

void Bonsai::OnCollision(Vector2D ColPosition, int width, int height, int &tileX, int &tileY, string signal){
    Vector2D PosCloud = Vector2D(getRealPos().getX(), getRealPos().getY());
    Vector2D PosCloud_Two = Vector2D(getRealPos().getX() + 16, getRealPos().getY());
    Vector2D PosCloud_Three = Vector2D(getRealPos().getX() + 32, getRealPos().getY());
    if((signal == "Bullet") && Tiles){
        unique_ptr<cloud> Cloud = make_unique<cloud>("floorTile", PosCloud, 1472, 80, Pl_Index, SDL_FLIP_NONE, true);
        unique_ptr<cloud> CloudMiddle = make_unique<cloud>("floorTile", PosCloud_Two, 1472, 96, Pl_Index, SDL_FLIP_NONE, true);
        unique_ptr<cloud> CloudEnd = make_unique<cloud>("floorTile", PosCloud_Three, 1472, 112, Pl_Index, SDL_FLIP_NONE, true);
        
        TileMap* n = (*Tiles)[TileIndex].get();
        
        Cloud->SetObj(getObjects(), getObjects().getSize());
        CloudMiddle->SetObj(getObjects(), getObjects().getSize());
        CloudEnd->SetObj(getObjects(), getObjects().getSize());

        n->ChangeTile(move(Cloud), 11781, tileY + heightCloud, tileX - 1);
        n->ChangeTile(move(CloudMiddle), 11782, tileY + heightCloud, tileX);
        n->ChangeTile(move(CloudEnd), 11783, tileY + heightCloud, tileX + 1);
    }
}

void cloud::update(){
    ObjectLayer &O = getObjects();

    GameObject* Pl = O.getVector()[0].get();

    //cout << (Pl->getRealPos().getY() + Pl->getHeight() + Pl->getOffsetY() + Pl->getOffsetPosY()) << " " << getRealPos().getY() << endl;

    if(((Pl->getPosition().getY() + Pl->getOffsetPosY()) + (Pl->getHeight() + Pl->getOffsetY())) > getPosition().getY()){
        setCollideable(false);
    }else{
        setCollideable(true);
    }
}

void Wand::update(){
    
    setVelocity(0, 0.4 * directionS);

    if(((getRealPos().getY() + getVelocity().getY()) > (originalPos.getY() + 6)) || ((getRealPos().getY() + getVelocity().getY()) < (originalPos.getY() - 6))){
        directionS = -directionS;
    }

    if(Obj){
        auto Pl = dynamic_cast<Player*>(Obj->getVector()[Pl_index].get());
        Vector2D Off = Vector2D(Pl->getOffsetPosX(),Pl->getOffsetPosY());
        if(vectors_cols(Pl->getRealPos() + Off, Pl->getWidth() + Pl->getOffsetX(), Pl->getHeight() + Pl->getOffsetY(), getRealPos(), getWidth(), getHeight())){
            Pl->ItemPicked();
            Pl->setWandObtained(true);
            setRealPos(Pl->getRealPos().getX(), Pl->getRealPos().getY() - getHeight());
            AutoDestroy();
        }
    }

    GameObject::update();

}