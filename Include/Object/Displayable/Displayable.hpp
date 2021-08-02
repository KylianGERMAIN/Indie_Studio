/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Displayable
*/

#ifndef DISPLAYABLE_HPP_
#define DISPLAYABLE_HPP_

#include "Object.hpp"
#include "raylib.hpp"
#include <string>

class Displayable : public Object{
    public:
        Displayable();
        Displayable(std::string name);
        Displayable(std::string name, const Vector3 &pos, const Vector3 &rot);
        Displayable(std::string name, const Vector3 &pos, const Vector3 &rot, std::string path);
        virtual ~Displayable();

        void Load_Texture(const std::string path) {
            texture = my_Raylib::_Texture2D::Load(path);
        }

        void Unload_Texture() {
            if (texture.id > 0)
                my_Raylib::_Texture2D::Unload(texture);
        }

        void Draw_Texture(const Color tint = Color {245, 245, 245, 255}) {
            my_Raylib::_Texture2D::Draw(texture, position.x, position.y, tint);
        }

        void Draw_Texture(const int x, const int y, const Color tint = Color {245, 245, 245, 255}) {
            my_Raylib::_Texture2D::Draw(texture, x, y, tint);
        }

        Texture2D Get_Texture() {
            return texture;
        }
    protected:
        Texture2D texture;
    private:
};

#endif /* !DISPLAYABLE_HPP_ */
