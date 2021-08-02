/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_Personalisation
*/

#include "Menu_Personalisation.hpp"
#include <chrono>

Menu_Personalisation::Menu_Personalisation()
{
}

Menu_Personalisation::~Menu_Personalisation()
{
}

int Menu_Personalisation::Interaction_Object()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    Btn_GetBack->Action(volumeEffect);
    Btn_Classic->Action(volumeEffect);
    for (int i = 0; i < value.size(); i++) {
        Btn_Next[i]->Action(volumeEffect);
        Btn_Back[i]->Action(volumeEffect);
        if (Btn_Next[i]->Get_Action())
            value[i] += rate_plus[i];
        if (Btn_Back[i]->Get_Action())
            value[i] -= rate_minus[i];
    }
    if (Btn_GetBack->Get_Action())
        return (MENU_MENU);
    if (Btn_Classic->Get_Action()) {
        start = std::chrono::system_clock::now();
        end = std::chrono::system_clock::now();
        my_Raylib::_Music::Stop_Music_Stream(_Music);
        while ((elapsed_seconds = end - start).count() < 2) {
            end = std::chrono::system_clock::now();
            if (color.a > 0)
                color.a -= 2;
            BeginDrawing();
                Draw_Object();
            EndDrawing();
            my_Raylib::_Other::Clear_Background(color);
        }
        color.a = 255;
        return (MENU_GAME);
    }
    return (0);
}

void Menu_Personalisation::Init_Object()
{
    center = my_Raylib::_Window::Get_Screen_Width() / 2;
    pos_W_Back = 10;
    pos_W_Next = my_Raylib::_Window::Get_Screen_Width() - (my_Raylib::_Window::Get_Screen_Width() / 2);
    pos_W_classic = my_Raylib::_Window::Get_Screen_Width() - (my_Raylib::_Window::Get_Screen_Width() / 4);
    pos_H = my_Raylib::_Window::Get_Screen_Height() / 5;

    Btn_Classic = new Button("btn_classique", {pos_W_classic,pos_H,0}, {0,0,0}, BUTTON "btn_classique.png", {284, 1488}, SOUND "LancementMatch.wav");
    if (Btn_Classic->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    Btn_GetBack = new Button("btn_getBack", {0, 0, 0}, {0,0,0}, BUTTON "btn_back.png", {200, 300}, BUTTON "SceneChange.wav");
    if (Btn_GetBack->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    Background_menu = new Displayable("Background", {0, 0, 0}, {0,0,0}, RESSOURCES "menu.png");
    if (Background_menu->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    for (int i = 0; i < value.size(); i++) {
        Btn_Next.push_back(new Button(name_Btn[i] + "_next", {pos_W_Next, pos_H * (i + 1)}, {0,0,0}, BUTTON "btn_next.png", {200, 300}, SOUND "SettingChange.wav"));
        if (Btn_Next[Btn_Next.size()-1]->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
        Btn_Back.push_back(new Button(name_Btn[i] + "_back", {pos_W_Back, pos_H * (i + 1)}, {0, 0, 0}, BUTTON "btn_back.png", {200, 300}, SOUND "SettingChange.wav"));
        if (Btn_Back[Btn_Back.size()-1]->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    }
    _Music = my_Raylib::_Music::Load_Music_Stream(SOUND + "menu-tournament.mp3");
}

void Menu_Personalisation::Position_Object()
{
    float pos_W_classicc = my_Raylib::_Window::Get_Screen_Width() - (my_Raylib::_Window::Get_Screen_Width() / 4);
    float pos_HH = my_Raylib::_Window::Get_Screen_Height() / 5;
    Btn_Classic->Set_Position({pos_W_classicc, pos_HH, 0});
}

void Menu_Personalisation::Music_Gestion()
{
    my_Raylib::_Music::Play_Music_Stream(_Music);
    SetMusicVolume(_Music, volumeMusic);
}

void Menu_Personalisation::Draw_Object()
{
    my_Raylib::_Other::Clear_Background(BLACK);
    std::string txt;
    my_Raylib::_Music::Update_Music_Stream(_Music);
    if (my_Raylib::_Music::Is_Music_Stream_Playing(_Music) == false)
        my_Raylib::_Music::Play_Music_Stream(_Music);
    Background_menu->Draw_Texture(color);
    Btn_GetBack->Draw_Button(color);
    Btn_Classic->Draw_Button(color);

    for (int i = 0; i < value.size(); i++) {
        Btn_Next[i]->Draw_Button(color);
        Btn_Back[i]->Draw_Button(color);
        
        if (i == 0) {
            if (value[i] < 0)
                value[i] = 0;
            txt = "Jump(s): " + std::to_string(static_cast<int>(value[i]));
        } else if (i == 1) {
            if (value[i] <= 0.05) {
                value[i] = 0.2 - rate_minus[i];
                txt = "GRAVITY OF\nTHE MOON";
            } else if (value[i] >= 0.6) {
                value[i] = (0.2 + rate_plus[i]);
                txt = "GRAVITY OF\nTHE SUN";
            } else {
                value[i] = 0.2;
                txt = "GRAVITY OF\nTHE EARTH";
            }
        } else if (i == 2) {
            if (value[i] <= (1 - rate_minus[i])) {
                value[i] = (1 - rate_minus[i]);
                txt = "Speed: THEO";
            } else if (value[i] >= (1 + rate_plus[i])) {
                value[i] = (1 + rate_plus[i]);
                txt = "Speed: SONIC ?";
            } else {
                value[i] = 1;
                txt = "Speed: MARIO";
            }
        } else {
            if (value[i] <= 0)
                value[i] = 1;
            txt = "Life(s) :" + std::to_string(static_cast<int>(value[i]));
        }
        my_Raylib::_Text::Draw_Text(txt, pos_W_Back + 220, pos_H * (i + 1), 40, color);
    }
}

void Menu_Personalisation::Delete_Object()
{
    my_Raylib::_Music::Unload_Music_Stream(_Music);
    for (int i = 0; i < value.size(); i++) {
        delete(Btn_Next[i]);
        delete(Btn_Back[i]);
    }
    delete(Btn_GetBack);
    delete(Background_menu);
    delete(Btn_Classic);
    Btn_Next.clear();
    Btn_Back.clear();
}