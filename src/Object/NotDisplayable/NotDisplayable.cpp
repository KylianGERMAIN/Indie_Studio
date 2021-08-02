/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** NotDisplayable
*/

#include "NotDisplayable.hpp"

NotDisplayable::NotDisplayable(std::string name) : Object(name)
{
}

NotDisplayable::NotDisplayable(std::string name, const Vector3 &pos, const Vector3 &rot) : Object(name, pos, rot)
{
}

NotDisplayable::~NotDisplayable()
{
}
