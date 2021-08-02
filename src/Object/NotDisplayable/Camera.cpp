/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Camera
*/

#include "Camera.hpp"

_Cam::_Cam(std::string name) : NotDisplayable(name)
{
    
}

_Cam::_Cam(std::string name, const Vector3 &pos, const Vector3 &up, const Vector3 &rot, const int mode, const float fov, const int projection) : NotDisplayable(name, pos, rot)
{
    Init(pos, up, mode, fov, projection);
}