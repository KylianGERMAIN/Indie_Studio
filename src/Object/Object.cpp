/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Object
*/

#include "Object.hpp"

Object::Object(std::string name) : name(name)
{
    
}

Object::Object(std::string name, const Vector3 &pos, const Vector3 &rot) : name(name), position(pos), rotation(rot)
{
    
}