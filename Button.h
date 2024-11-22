#ifndef BUTTON_H
#define BUTTON_H

#include "Functions.h"
#include "Vector.h"
#include <array>

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
        array<int, 4> BgColour;
        array<int, 4> hoverColor;
    public:
        Button(string text_id, int width, int height, Vector2D pos, void (*callback)(), array<int, 4> background_colour = {255, 255, 255, 1}, array<int, 4> hover_color = {255, 255, 255, 1}) : ID_text(text_id), m_width(width), m_height(height), m_position(pos), m_callback(callback), BgColour(background_colour),hoverColor(hover_color) {
            filler = {(int)m_position.getX() - 4, (int)m_position.getY() - 4, m_width, m_height};
        }
        void draw();
        void update();
};


#endif