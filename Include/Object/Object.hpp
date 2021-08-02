/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "raylib.h"
#include <iostream>
#include <string>

class Object {
    public:
        Object(std::string name);
        Object(std::string name, const Vector3 &pos, const Vector3 &rot);
        virtual ~Object() = default;

        void Set_Position(const Vector3 &pos) {
            position = pos;
        }

        void Set_Position_x(const float x) {
            position.x = x;
        }

        void Set_Position_y(const float y) {
            position.y = y;
        }

        void Set_Position_z(const float z) {
            position.z = z;
        }

        void Add_Position(const Vector3 pos) {
            position.x += pos.x;
            position.y += pos.y;
            position.z += pos.z;
        }
        
        void Add_Position_x(const float x) {
            position.x += x;
        }

        void Add_Position_y(const float y) {
            position.y += y;
        }

        void Add_Position_z(const float z) {
            position.z += z;
        }

        void Print_Position() const {
            std::cout << name << "pos = {" << position.x << "," << position.y << "," << position.z << "}" << std::endl;
        }

        Vector3 Get_Position() { return position;}

        Vector3 Get_Rotation() { return rotation;}

        void Set_Rotation(const Vector3 &rot) {
            rotation = rot;
        }

        std::string Get_Name() { return name;}

    protected:
        Vector3 position = {0,0,0};
        Vector3 rotation = {0,0,0};
        std::string name = "";
    private:
};

#endif /* !OBJECT_HPP_ */
