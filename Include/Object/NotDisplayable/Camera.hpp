/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "NotDisplayable.hpp"
#include "raylib.hpp"

struct Traveling
{
    Vector3 posStart;
    Vector3 posEnd;
    Vector3 posRate;
    Vector3 upStart;
    Vector3 upEnd;
    Vector3 upRate;
    float fov;
};


class _Cam : public NotDisplayable {
    public:
        _Cam(std::string name);
        _Cam(std::string name, const Vector3 &pos, const Vector3 &up, const Vector3 &rot = {0, 0, 0},
            const int mode = CAMERA_FREE, const float fov = 45, const int projection = CAMERA_PERSPECTIVE);
        ~_Cam() {};

        void Set_Target(const Vector3 &pos) {
            my_Raylib::_Cam::Set_Target(camera, pos);
        }

        void Set_Up(const Vector3 &pos) {
            my_Raylib::_Cam::Set_Up(camera, pos);
        }

        void Set_FOV(const float fov = 45.0f) {
            my_Raylib::_Cam::Set_FOV(camera, fov);
        }

        void Set_Projection(const int projection = CAMERA_PERSPECTIVE) {
            my_Raylib::_Cam::Set_Projection(camera, projection);
        }

        void Set_Mode(const int mode = CAMERA_FREE) {
            my_Raylib::_Cam::Set_Mode(camera, mode);
        }

        void Set_Position(const Vector3 &newpos) {
            position = newpos;
            my_Raylib::_Cam::Set_Position(camera, position);
        }

        void Add_Position(const Vector3 &newpos) {
            position.x += newpos.x;
            position.y += newpos.y;
            position.z += newpos.z;
            my_Raylib::_Cam::Set_Position(camera, position);
        }

        void add_Up(const Vector3 &newpos) {
            my_Raylib::_Cam::Set_Up(camera, 
                                    {camera.up.x + newpos.x,
                                    camera.up.y + newpos.y,
                                    camera.up.z + newpos.z});
        }

        void Update() {
            my_Raylib::_Cam::Update(camera);
        }

        void Init(const Vector3 &pos, const Vector3 &up, const int mode = CAMERA_FREE, const float fov = 45, const int projection = CAMERA_PERSPECTIVE) {
            position = pos;
            savePos = pos;
            saveUp = up;
            saveFov = fov;
            my_Raylib::_Cam::Init_Cam(camera, pos, up, mode, fov, projection);
        }

        Vector3 Get_savePos() { return savePos; }
        Vector3 Get_saveUp() { return saveUp; }

        Camera Get() {return camera;}
    private:
        Vector3 savePos = {0,0,0};
        Vector3 saveUp = {0,0,0};
        float saveFov;
        Camera camera = {0};
};

#endif /* !CAMERA_HPP_ */
