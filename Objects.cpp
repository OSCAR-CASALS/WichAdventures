#include"Objects.h"
#include "TileClass.h"


void GameObject::draw(){
    //cout << "Drawn" << endl;
    drawFrame(m_Texture_ID, m_column, m_row, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, direction, angle);
}

void GameObject::update(){
    if(m_apply_acceleration == true){
        if(m_acceleration.getX() == 0){
            m_velocity.setX(0);
        }
        if(m_acceleration.getY() == 0){
            m_velocity.setY(0);
        }
    }

    if(m_velocity.getX() >= maxSpeedX){
        m_velocity.setX(maxSpeedX);
    }else if(m_velocity.getX() <= ((-1)*maxSpeedX)){
        m_velocity.setX((-1)*maxSpeedX);
    }else{
        m_velocity.setX(m_velocity.getX() + m_acceleration.getX());
    }
    
    if(m_velocity.getY() >= maxSpeedY){
        m_velocity.setY(maxSpeedY);
    }else if(m_velocity.getY() <= ((-1)*maxSpeedY)){
        m_velocity.setY((-1)*maxSpeedY);
    }else{
        m_velocity.setY(m_velocity.getY() + m_acceleration.getY());
    }

    realPosition += m_velocity;
    m_position += m_velocity;
}