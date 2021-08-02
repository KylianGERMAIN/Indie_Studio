/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Splash_Screen
*/

#include "Splash_Screen.hpp"

Splash_Screen::Splash_Screen()
{
}

Splash_Screen::~Splash_Screen()
{
}

void Splash_Screen::Init_Object()
{
    SplashScreen = new Displayable("SplashScreen", {0,0,0}, {0,0,0}, "Ressources/Splash_Screen.png");
    if (SplashScreen->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    Raylib_logo = new Displayable("Raylib_logo", {Center_W/4, Center_H,0}, {0,0,0}, "Ressources/Raylib_logo.png");
    if (Raylib_logo->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    Name_dev = new Displayable("Name_dev", {Center_W + Center_W/4 + 128/2,Center_H,0}, {0,0,0}, "Ressources/Name_dev.png");
     if (Name_dev->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
}

void Splash_Screen::Draw_Object(std::chrono::system_clock::time_point end, std::chrono::system_clock::time_point start)
{
    SplashScreen->Draw_Texture();
    if (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() > 1)
        Raylib_logo->Draw_Texture();
    if (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() > 2)
        Name_dev->Draw_Texture();
    
}

int Splash_Screen::Move_Object()
{
    Center_W = my_Raylib::_Window::Get_Screen_Width()/2;
    Center_H = my_Raylib::_Window::Get_Screen_Height()/2;
    if (pos_h != 350)
        pos_h++;
    Raylib_logo->Set_Position({Center_W/4,pos_h,0});
    Name_dev->Set_Position({Center_W + Center_W/4 + 128/2,pos_h,0});
    return (0);
}

int Splash_Screen::Loop()
{
    Sound entry = my_Raylib::_Sound::Load_Sound(SOUND "se_menu_dojo_yadon.wav");
    bool play = true;
    Init_Object();
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    while((std::chrono::duration_cast<std::chrono::seconds>(end - start).count() != 5)) {
        BeginDrawing();
        my_Raylib::_Other::Clear_Background(RAYWHITE);
        if ((std::chrono::duration_cast<std::chrono::seconds>(end - start).count() > 1.9 && play)) {
            my_Raylib::_Sound::Play_Sound(entry);
            play = false;
        };
        end = std::chrono::system_clock::now();

        Move_Object();
        Draw_Object(end, start);
        EndDrawing();
    }
    my_Raylib::_Sound::Unload_Sound(entry);
    delete (SplashScreen);
    delete (Raylib_logo);
    delete (Name_dev);
    return (0);
}