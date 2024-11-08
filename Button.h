#ifndef BUTTON_H
#define BUTTON_H

#include "Functions.h"
#include "Vector.h"

class Button{
    private:
        string ID_text;
        int m_width;
        int m_height;
        Vector2D m_position;
        int m_row = 0;
        int m_column = 0;
        SDL_Rect filler;
        bool draw_rect = false;
        void (*m_callback)();
    public:
        Button(string text_id, int width, int height, Vector2D pos, void (*callback)()) : ID_text(text_id), m_width(width), m_height(height), m_position(pos), m_callback(callback) {
            filler = {(int)m_position.getX() - 4, (int)m_position.getY() - 4, m_width, m_height};
        }
        void draw();
        void update();
};


#endif