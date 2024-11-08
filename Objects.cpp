#include"Objects.h"
#include "TileClass.h"


void GameObject::draw(){
    //cout << "Drawn" << endl;
    drawFrame(m_Texture_ID, m_column, m_row, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, direction, angle);
}

void GameObject::update(){
    realPosition += m_velocity;
    m_position += m_velocity;
}