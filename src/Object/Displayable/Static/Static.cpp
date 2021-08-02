/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Static
*/

#include "Static.hpp"

Static::Static(std::string name) :Displayable(name)
{
}

Static::Static(std::string name, const Vector3 &pos, const Vector3 &rot): Displayable(name, pos, rot)
{
    
}

Static::Static(std::string name, const Vector3 &pos, const Vector3 &rot, std::string TexturePath): Displayable(name, pos, rot)
{
    
}

Static::~Static()
{
}
