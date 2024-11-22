#include "Functions.h"
#include "Vector.h"
#include "Button.h"

void Button::draw(){
    //drawFrame(m_TextureID, m_column, m_row, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
    if(draw_rect == true){
        draw_fill_rect(filler, hoverColor[0], hoverColor[1], hoverColor[2], hoverColor[3], false);
    }else{
        draw_fill_rect(filler, BgColour[0], BgColour[1], BgColour[2], BgColour[3], false);
    }
    drawFull(ID_text, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
}

void Button::update(){
    if (mouse.mouse_pos.getX() > filler.x &&
    mouse.mouse_pos.getX() < (filler.x + filler.w) &&
    mouse.mouse_pos.getY() > filler.y &&
    mouse.mouse_pos.getY() < (filler.y + filler.h)){
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