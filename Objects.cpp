#include"Objects.h"
#include "TileClass.h"


int my_pause = -1;
bool is_cinematic = false;

void GameObject::draw(){
    drawFrame(m_Texture_ID, m_column, m_row, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, direction, angle);
}

void GameObject::update(){

    m_velocity += m_acceleration;

    realPosition += m_velocity;
    m_position = realPosition;
}


void GameOverFloor::draw(){
    if(Tex != ""){
        GameObject::draw();
    }
}