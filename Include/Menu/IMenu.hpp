/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** IMenu
*/

#ifndef IMENU_HPP_
#define IMENU_HPP_

#include "raylib.h"
#include "Camera.hpp"
#include <memory>
#include "raylib.h"
#include "raylib.hpp"
#include "allInclude.hpp"
#include "IMenu.hpp"

#define SPLASH_SCREEN -1
#define MENU_PRE 0
#define MENU_MENU 1
#define MENU_SETTINGS 2
#define MENU_TOURNAMENT 3
#define MENU_PAUSE 4
#define MENU_SAVE 6
#define MENU_PERSONALISATION 7
#define MENU_GAME 10
#define MENU_REAL_TOURNAMENT 11
#define MENU_END 12

class IMenu {
    public:
        IMenu(){};
        virtual ~IMenu() = default;

        virtual void Init_Object(){}
        virtual void Init_Object(std::vector<Player *> Players){};
        virtual void Position_Object(){}
        virtual void Music_Gestion(){}
        virtual void Draw_Object(){}
        virtual int Interaction_Object(){
            return (0);
        }
        int Loop(float nvolumeMusic, float nvolumeEffect) {
            volumeMusic = nvolumeMusic;
            volumeEffect = nvolumeEffect;
            int result = 0;
            Position_Object();
            Music_Gestion();
            while (!my_Raylib::_Window::Should_Close())
            {
                result = Interaction_Object();
                if (result != 0)
                    return (result);
                BeginDrawing();
                Draw_Object();
                EndDrawing();
            }
            return (404);
        }
        void Update_sound(float nvolumeMusic, float nvolumeEffect) {
            volumeEffect = nvolumeEffect;
            volumeMusic = nvolumeMusic;
        }
        virtual void Delete_Object(){}

    protected:
        float volumeMusic = 1;
        float volumeEffect = 1;
    private:
};

#endif /* !IMENU_HPP_ */