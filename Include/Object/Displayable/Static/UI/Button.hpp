/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Static.hpp"

class Button : public Static {
    public:
        Button(std::string name);
        Button(std::string name, const Vector3 &pos, const Vector3 &rot, std::string TexturePath, Vector2 size, std::string soundPath = "");
        ~Button();

        void Init(const Vector3 &pos, const Vector3 &rot, std::string TexturePath, Vector2 size, std::string SoundPath = "") {
            _size = size;
            _pos = pos;
            PosRect.x = pos.x;
            PosRect.y = pos.y;
            frameHeight = size.y / 3;
            Load_Texture(TexturePath);
            sourceRec = {0, 0, size.x, frameHeight};
            float size_x = size.x;
            btnBounds = {pos.x, pos.y, size_x, frameHeight};
            if (SoundPath != "")
                sound = my_Raylib::_Sound::Load_Sound(SoundPath);
            soundPath = SoundPath;
        }

        void Action(float volumeEffect) {
            if (soundPath != "")
                my_Raylib::_Sound::Set_Volume(sound, volumeEffect);
            MousePosition = my_Raylib::_Input::Get_Mouse_Position();
            BtnAction = false;
            if (my_Raylib::_Colision::Check_Collision_Point_Rec(MousePosition, btnBounds))
            {
                if (my_Raylib::_Input::Is_Mouse_Button_Down(MOUSE_BUTTON_LEFT))
                    BtnState = 2;
                else
                    BtnState = 1;
                if (my_Raylib::_Input::Is_Mouse_Button_Released(MOUSE_BUTTON_LEFT)) {
                    if (soundPath != "")
                        my_Raylib::_Sound::Play_Sound(sound);
                    BtnAction = true;
                }
            }
            else
                BtnState = 0;
            sourceRec.y = BtnState * frameHeight;
        }

        bool Get_Action() { return (BtnAction);}
    
        void Draw_Button(Color color = WHITE) {
            btnBounds = {position.x, position.y, _size.x, frameHeight};
            PosRect.x = position.x;
            PosRect.y = position.y;
            my_Raylib::_Texture2D::Draw_Texture_Rec(texture, sourceRec, {PosRect.x, PosRect.y}, color);
        }

    protected:
        int BtnState = 0;
        bool BtnAction = false;
        std::string soundPath = "";
        Sound sound;
        Rectangle sourceRec;
        Vector2 _size;
        Vector2 MousePosition = {0.0f, 0.0f};
        float frameHeight;
        Rectangle btnBounds;
        Vector3 _pos;
        Vector2 PosRect = {0.0f, 0.0f};

    private:
};

#endif /* !BUTTON_HPP_ */
