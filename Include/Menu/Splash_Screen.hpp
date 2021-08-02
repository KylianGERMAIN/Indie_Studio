/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
**  Splash_Screen
*/

#ifndef _SPLASH_SCREEN_HPP_
#define _SPLASH_SCREEN_HPP_

#include <chrono>
#include "raylib.h"
#include "Camera.hpp"
#include <memory>
#include "raylib.h"
#include "raylib.hpp"
#include "allInclude.hpp"
#include <iostream>

class Splash_Screen {
    public:
        Splash_Screen();
        ~Splash_Screen();

        void Init_Object();
        void Position_Object(){};
        void Draw_Object(std::chrono::system_clock::time_point end, std::chrono::system_clock::time_point start);
        int Move_Object();
        int Loop();

    protected:
    private:
        float pos_h = 100;
        float Center_W = my_Raylib::_Window::Get_Screen_Width()/2;
        float Center_H = my_Raylib::_Window::Get_Screen_Height()/2;

        Displayable *SplashScreen;
        Displayable *Raylib_logo;
        Displayable *Name_dev;
};

#endif /* !_SPLASH_SCREEN_HPP_ */
