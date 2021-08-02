/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Movable
*/

#include "Movable.hpp"

Movable::Movable(std::string name) :Displayable(name)
{
}

Movable::Movable(std::string name, const Vector3 &pos, const Vector3 &rot) : Displayable(name, pos, rot)
{
}

Movable::Movable(std::string name, const Vector3 &pos, const Vector3 &rot, std::string path) : Displayable(name, pos, rot, path)
{
}

Movable::~Movable()
{
    std::cout << "UNLOAD_MOVABLE " << name.c_str() << std::endl;
}