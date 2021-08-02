/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_Interface
*/

#include "Menu_Interface.hpp"
#include <iostream>
#include <chrono>

Menu_Interface::Menu_Interface()
{
}

Menu_Interface::~Menu_Interface()
{
}

void Menu_Interface::Init_Object()
{
    Vector3 position = {0.0, 0.0, 0.0};
    btn_play = new Button("btnplay", position, position, "Ressources/Buttons/btn_smash.png", {527, 972}, SOUND "SelectionMatch.wav");
    if (btn_play->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    btn_settings = new Button("btn_settings", position, position, "Ressources/Buttons/btn_settings.png", {398,235}, SOUND "SceneChange.wav");
    if (btn_settings->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    btn_exit = new Button("btn_exit", position, position, "Ressources/Buttons/btn_exit.png", {156,478}, SOUND "selection.wav");
    if (btn_exit->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    Background_menu = new Displayable("Background_menu", {0, 0, 0}, position, "Ressources/menu.png");
    if (Background_menu->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    _Music = my_Raylib::_Music::Load_Music_Stream(SOUND + "menu.mp3");
}

void Menu_Interface::Position_Object()
{
    float center = my_Raylib::_Window::Get_Screen_Width()/2;
    float pos_H = my_Raylib::_Window::Get_Screen_Height() / 4;
    float pos_H1 = my_Raylib::_Window::Get_Screen_Height() / 1.5;
    btn_play->Set_Position({center - 567, pos_H, 0});
    btn_settings->Set_Position({center-(79/2),(pos_H1 - 79),0});
    btn_exit->Set_Position({center-(79/2)+(527/4),pos_H, 0});
}

void Menu_Interface::Music_Gestion()
{
    SetMusicVolume(_Music, volumeMusic);
    my_Raylib::_Music::Play_Music_Stream(_Music);
}

void Menu_Interface::Draw_Object()
{
    my_Raylib::_Music::Update_Music_Stream(_Music);
    my_Raylib::_Other::Clear_Background(BLACK);
    Background_menu->Draw_Texture(color);
    btn_play->Draw_Button(color);
    btn_settings->Draw_Button(color);
    btn_exit->Draw_Button(color);
}

int Menu_Interface::Interaction_Object()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    if (my_Raylib::_Music::Is_Music_Stream_Playing(_Music) == false)
        my_Raylib::_Music::Play_Music_Stream(_Music);
    btn_play->Action(volumeEffect);
    btn_settings->Action(volumeEffect);
    btn_exit->Action(volumeEffect);
    if (btn_settings->Get_Action() == true)
        return (MENU_SETTINGS);
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
    if (btn_play->Get_Action() == true)
        return (MENU_PERSONALISATION);
    return (0);
}

void Menu_Interface::Delete_Object()
{
    my_Raylib::_Music::Unload_Music_Stream(_Music);
    delete (btn_play);
    delete (btn_settings);
    delete (btn_exit);
    delete (Background_menu);
}