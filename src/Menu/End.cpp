/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** End
*/

#include "End.hpp"
#include <chrono>

End::End()
{
}

End::~End()
{
}

void End::Init_Object(std::vector<Player *> Players)
{
    _Players = Players;

    endSound = my_Raylib::_Sound::Load_Sound(NARRATION "vc_narration_congratulation.wav");
    float center = my_Raylib::_Window::Get_Screen_Width()/2;
    float centerheightt = my_Raylib::_Window::Get_Screen_Height()/4;
    Background_menu = new Displayable("Background_menu", {0, 0, 0}, {0, 0, 0}, "Ressources/menu.png");
    btn_exit = new Button("btn_exit", {center-156*3,centerheightt, 0}, {0, 0, 0}, "Ressources/Buttons/btn_exit.png", {156,478}, SOUND "selection.wav");
    btn_home = new Button("btn_home", {center+156*2,centerheightt, 0}, {0, 0, 0}, "Ressources/Buttons/btn_home.png", {156,478}, SOUND "SceneChange.wav");
}

void End::Draw_Object()
{
    std::string winInfo;    
    std::string stats = "Statistic";
    std::string stat_jump = "Number of jumps = ";
    std::string stat_punch = "Number of punchs = ";
    std::string stat_damage = "Number of damages = ";
    float center_W = my_Raylib::_Window::Get_Screen_Width() / 2;
    float center_H = my_Raylib::_Window::Get_Screen_Height() / 2;
    float pos_H1 = my_Raylib::_Window::Get_Screen_Height() - my_Raylib::_Window::Get_Screen_Height() / 1.1;
    float pos_H2 = my_Raylib::_Window::Get_Screen_Height() / 1.70;
    float pos_H3 = my_Raylib::_Window::Get_Screen_Height() / 1.50;
    float pos_H4 = my_Raylib::_Window::Get_Screen_Height() / 1.40;
    float pos_H5 = my_Raylib::_Window::Get_Screen_Height() / 1.30;

    if (playSound) {
        my_Raylib::_Sound::Set_Volume(endSound, volumeEffect);
        my_Raylib::_Sound::Play_Sound(endSound);
        playSound = false;
    }

    for (int i = 0; _Players.size() > i; i++) {
        if (_Players[i]->Get_Life() != 0)
            winInfo = _Players[i]->Get_Name() + " WIN !";

    }

    my_Raylib::_Other::Clear_Background(RAYWHITE);
    Background_menu->Draw_Texture();
    my_Raylib::_Text::Draw_Text(winInfo, center_W - (winInfo.size() * 15), pos_H1, 60, WHITE);
    my_Raylib::_Text::Draw_Text(stats, center_W - (stats.size() * 10), center_H, 40, WHITE);
    my_Raylib::_Text::Draw_Text(stat_jump, (center_W - 400), pos_H3, 40, WHITE);
    my_Raylib::_Text::Draw_Text(stat_punch, (center_W - 400), pos_H4, 40, WHITE);
    my_Raylib::_Text::Draw_Text(stat_damage, (center_W - 400), pos_H5, 40, WHITE);


    for (int i = 0; _Players.size() > i; i++) {
        my_Raylib::_Text::Draw_Text(_Players[i]->Get_Name(), center_W + 200 * (i + 1) - (_Players[i]->Get_Name().size() * 10), pos_H2, 40, WHITE);
        my_Raylib::_Text::Draw_Text(std::to_string(_Players[i]->Get_nbJump()), center_W + 200 * (i + 1), pos_H3, 40, WHITE);
        my_Raylib::_Text::Draw_Text(std::to_string(_Players[i]->Get_nbPunch()), center_W +  200 * (i + 1), pos_H4, 40, WHITE);
        my_Raylib::_Text::Draw_Text(std::to_string(_Players[i]->Get_nbPunch() * 6), center_W +  200 * (i + 1), pos_H5, 40, WHITE);

    }

    btn_exit->Draw_Button(color);
    btn_home->Draw_Button(color);
}

int End::Interaction_Object()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    btn_exit->Action(volumeEffect);
    btn_home->Action(volumeEffect);
    if (btn_home->Get_Action() == true) {
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
        color.a = 255;
        playSound = true;
        return (1);
    }
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
        color.a = 255;
        playSound = true;
        return (404);
    }
    return (0);
}

void End::Delete_Object()
{
    delete (Background_menu);
    delete (btn_exit);
    delete (btn_home);
}