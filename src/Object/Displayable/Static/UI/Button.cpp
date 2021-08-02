/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Button
*/

#include "Button.hpp"
#include <iostream>

Button::Button(std::string name) : Static(name)
{
}

Button::Button(std::string name, const Vector3 &pos, const Vector3 &rot, std::string TexturePath, Vector2 size, std::string soundPath) : Static(name, pos, rot)
{
    Init(pos,rot,TexturePath, size, soundPath);
}

Button::~Button()
{
    if (soundPath != "")
        my_Raylib::_Sound::Unload_Sound(sound);
}
