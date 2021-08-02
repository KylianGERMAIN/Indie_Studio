/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Slider
*/

#include "Slider.hpp"

Slider::Slider() : Static("")
{
    texture.id = -1;
}

Slider::Slider(std::string name, const Vector3 &pos, const Vector3 &rot, const Vector3 &newsize, const Vector3 &newscale, const Color &newcolor) : Static(name, pos, rot), size(newsize), color(newcolor), value(newsize.x), max(newsize.x), min(newsize.z), scale(newscale)
{
    texture.id = -1;
}

Slider::~Slider()
{
}

void Slider::Draw()
{
    DrawRectangle(position.x, position.y, value * scale.x, size.y * scale.y, color);
    DrawRectangleLines(position.x, position.y, size.x * scale.x, size.y * scale.y, BLUE);
}

float Slider::Touch_Value()
{
    Vector2 mousePosition;
    if (my_Raylib::_Input::Is_Mouse_Button_Down(MOUSE_BUTTON_LEFT)) {
        mousePosition = my_Raylib::_Input::Get_Mouse_Position();
        if (mousePosition.x <= position.x + size.x * scale.x &&
            mousePosition.x > position.x && 
            mousePosition.y <= position.y + size.y * scale.y &&
            mousePosition.y > position.y)
            value = (mousePosition.x - position.x) / scale.x; ;
    }
    return value;
}