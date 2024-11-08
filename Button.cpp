#include "Functions.h"
#include "Vector.h"
#include "Button.h"

void Button::draw(){
    //drawFrame(m_TextureID, m_column, m_row, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
    if(draw_rect == true){
        draw_fill_rect(filler, 255, 255, 255, 255, false);
    }
    drawFull(ID_text, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
}

void Button::update(){
    if (mouse.mouse_pos.getX() > m_position.getX() &&
    mouse.mouse_pos.getX() < (m_position.getX() + m_width) &&
    mouse.mouse_pos.getY() > m_position.getY() &&
    mouse.mouse_pos.getY() < (m_position.getY() + m_height)){
        draw_rect = true;
        if(mouse.Left_Click == true){
            //m_column = 256;
            mouse.Left_Click = false;
            m_callback();
        }
    }
    else{
        draw_rect = false;
    }
}