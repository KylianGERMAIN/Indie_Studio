/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Displayable
*/

#include "Displayable.hpp"

Displayable::Displayable() : Object("")
{
}

Displayable::Displayable(std::string name) :Object(name)
{
}

Displayable::Displayable(std::string name, const Vector3 &pos, const Vector3 &rot) : Object(name, pos, rot)
{
}

Displayable::Displayable(std::string name, const Vector3 &pos, const Vector3 &rot, std::string path) : Object(name, pos, rot)
{
    Load_Texture(path);
}

Displayable::~Displayable()
{
    Unload_Texture();
    std::cout << "UNLOAD_TEXXTURE " << name.c_str() << std::endl;
}
