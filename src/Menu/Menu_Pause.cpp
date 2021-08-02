/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_Pause
*/

#include "Menu_Pause.hpp"
#include <chrono>

Menu_Pause::Menu_Pause()
{
}

Menu_Pause::~Menu_Pause()
{
}

void Menu_Pause::Init_Object()
{
    Vector3 position = {0.0, 0.0, 0.0};
    float center = my_Raylib::_Window::Get_Screen_Width()/2;
    float centerheight = my_Raylib::_Window::Get_Screen_Height()/2;
    float centerheightt = my_Raylib::_Window::Get_Screen_Height()/4;
    Background_menu = new Displayable("Background_menu", {0, 0, 0}, position, "Ressources/menu.png");
    if (Background_menu->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    btn_settings = new Button("btn_settings", {center,centerheight,0}, position, "Ressources/Buttons/btn_settings.png", {398,235}, SOUND "SceneChange.wav");
    if (btn_settings->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    btn_exit = new Button("btn_exit", {center-(156/2),centerheightt-170, 0}, position, "Ressources/Buttons/btn_exit.png", {156,478}, SOUND "selection.wav");
    if (btn_exit->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    btn_continue = new Button("btn_continue", {center-470,centerheight, 0}, position, "Ressources/Buttons/btn_continue.png", {398,235}, SOUND "SceneChange.wav");
    if (btn_continue->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    btn_home = new Button("btn_home", {center-(156/2),centerheightt, 0}, position, "Ressources/Buttons/btn_home.png", {156,478}, SOUND "SceneChange.wav");
    if (btn_home->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
}

void Menu_Pause::Music_Gestion()
{
}

void Menu_Pause::Position_Object()
{
    float center = my_Raylib::_Window::Get_Screen_Width()/2;
    float centerheight = my_Raylib::_Window::Get_Screen_Height()/2;
    float centerheightt = my_Raylib::_Window::Get_Screen_Height()/4;
    btn_settings->Set_Position({center, centerheight, 0});
    btn_exit->Set_Position({center-(156/2),centerheightt-170, 0});
    btn_continue->Set_Position({center-470,centerheight, 0});
    btn_home->Set_Position({center-(156/2),centerheightt, 0});
}

void Menu_Pause::Draw_Object()
{
    my_Raylib::_Other::Clear_Background(BLACK);
    Background_menu->Draw_Texture(color);
    btn_settings->Draw_Button(color);
    btn_exit->Draw_Button(color);
    btn_continue->Draw_Button(color);
    btn_home->Draw_Button(color);
}

int Menu_Pause::Interaction_Object()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    btn_settings->Action(volumeEffect);
    btn_continue->Action(volumeEffect);
    btn_exit->Action(volumeEffect);
    btn_home->Action(volumeEffect);
    if (btn_settings->Get_Action() == true)
        return (2);
    if (btn_home->Get_Action() == true)
        return (1);
    if (btn_continue->Get_Action() == true)
        return (10);
    if (btn_exit->Get_Action() == true) {
        start = std::chrono::system_clock::now();
        end = std::chrono::system_clock::now();
        while ((elapsed_seconds = end - start).count() < 1) {
            end = std::chrono::system_clock::now();
            if (color.a - 4 > 0)
                color.a -= 4;
            else
                color.a = 0;
            BeginDrawing();
                Draw_Object();
            EndDrawing();
            my_Raylib::_Other::Clear_Background(color);
        }
        return (404);
    }
    return (0);
}

void Menu_Pause::Delete_Object()
{
    delete (Background_menu);
    delete (btn_settings);
    delete (btn_exit);
    delete (btn_continue);
    delete (btn_home);
}
