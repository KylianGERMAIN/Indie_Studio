/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_Setting
*/

#include "Menu_Setting.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream> 

Menu_Setting::Menu_Setting()
{
}

Menu_Setting::~Menu_Setting()
{
}


void Menu_Setting::Init_Object()
{
    Vector3 position = {0.0, 0.0, 0.0};
    float pos_W = my_Raylib::_Window::Get_Screen_Width() / 2;
    float pos_H = my_Raylib::_Window::Get_Screen_Height() / 2;
    float posWHSlider = my_Raylib::_Window::Get_Screen_Width() - ((my_Raylib::_Window::Get_Screen_Width() / 4) * 3);
    Vector3 posSlider = {posWHSlider, posWHSlider, 0};

    btn_sound = new Button("btn_sound", {pos_W-200,25, 0}, position, "Ressources/Buttons/btn_sound.png", {200,443}, SOUND "SettingChange.wav");
    if (btn_sound->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    btn_resolution_1920 = new Button("btn_resolution_1920", {pos_W-521,pos_H - 100, 0}, position, "Ressources/Buttons/btn_resolution_1920.png", {511,689});
    if (btn_resolution_1920->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    btn_resolution_1280 = new Button("btn_resolution_1280", {pos_W+10,pos_H - 100, 0}, position, "Ressources/Buttons/btn_resolution_1280.png", {511,689});
    if (btn_resolution_1280->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    for (int i = 0; i < 2; i++)
        sliders.push_back(Slider("slider_" + i, {posWHSlider, posWHSlider * (i + 1), 0}, position, {100, 30, 0}, {5,2,0}, RED));
    btn_resolution = new Button("btn_resolution", {pos_W,25, 0}, position, "Ressources/Buttons/btn_resolution.png", {200,442}, SOUND "SettingChange.wav");
    if (btn_resolution->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    Background = new Displayable("Background", {0, 0, 0}, position, "Ressources/menu.png");
    if (Background->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
    btn_back = new Button("btn_back", {0, 0, 0}, position, "Ressources/Buttons/btn_back.png", {200, 300});
    if (btn_back->Get_Texture().id <= 0)
            throw std::runtime_error("BAD PATH");
}

void Menu_Setting::Position_Object()
{    
    float pos_W = my_Raylib::_Window::Get_Screen_Width() / 2;
    float pos_H = my_Raylib::_Window::Get_Screen_Height() / 2;
    float posWHSlider = my_Raylib::_Window::Get_Screen_Width() - ((my_Raylib::_Window::Get_Screen_Width() / 4) * 3);
    Vector3 posSlider = {posWHSlider, posWHSlider, 0};

    btn_sound->Set_Position({pos_W - 200, 25, 0});
    btn_resolution->Set_Position({pos_W,25, 0});
    btn_resolution_1920->Set_Position({pos_W-521,pos_H - 100, 0});
    btn_resolution_1280->Set_Position({pos_W+10,pos_H - 100, 0});
    for (int i = 0; i < sliders.size(); i++)
        sliders[i].Set_Position({posSlider.x, posSlider.y *(i + 1), posSlider.z});
}

void Menu_Setting::initSliders()
{
    sliders[0].setValue(volumeEffect * 100);
    sliders[1].setValue(volumeMusic * 100);
}

void Menu_Setting::Music_Gestion()
{
}

void Menu_Setting::Draw_Object()
{
    my_Raylib::_Other::Clear_Background(WHITE);
    Background->Draw_Texture();
    btn_back->Draw_Button();
    btn_sound->Draw_Button();
    btn_resolution->Draw_Button();
    if (solution == 1) { 
        btn_resolution_1920->Draw_Button();
        btn_resolution_1280->Draw_Button();
    }
    if (solution == 2) {
        my_Raylib::_Text::Draw_Text("Volume Effect", sliders[0].Get_Position().x, sliders[0].Get_Position().y - 50, 40, LIGHTGRAY);
        sliders[0].Draw();

        my_Raylib::_Text::Draw_Text("Volume Music", sliders[1].Get_Position().x, sliders[1].Get_Position().y - 50, 40, LIGHTGRAY);
        sliders[1].Draw();
    }
}

bool Menu_Setting::checkFile(std::string path)
{
    bool result = false;
    std::ifstream infile(path);
    if (infile.good())
        result = true;
    infile.close();
    return result;
}

std::vector<float> Menu_Setting::readInFile()
{
    std::vector<float> result;
    float buffer;

    if (!checkFile(pathSound)) {
        std::cout << "file not found" << std::endl;
        return result;
    }
    std::ifstream INFILE(pathSound, std::ios::in | std::ifstream::binary);
    INFILE.read(reinterpret_cast<char *>(&buffer), sizeof(float));
    result.push_back(buffer);
    buffer = 0;
    INFILE.read(reinterpret_cast<char *>(&buffer), sizeof(float));
    result.push_back(buffer);
    return result;
}

void Menu_Setting::writeInFile()
{
    std::ofstream FILE(pathSound, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary );
    
    FILE.write(reinterpret_cast<char *>(&volumeEffect), sizeof(float));
    FILE.write(reinterpret_cast<char *>(&volumeMusic), sizeof(float));
    FILE.close();
}

int Menu_Setting::Interaction_Object()
{
    btn_back->Action(volumeEffect);
    btn_resolution->Action(volumeEffect);
    btn_sound->Action(volumeEffect);
    if (solution == 1) { 
        btn_resolution_1920->Action(volumeEffect);
        btn_resolution_1280->Action(volumeEffect);
        if (btn_resolution_1920->Get_Action() == true) {
            my_Raylib::_Window::Set_Window_Size(1920, 1080);
            my_Raylib::_Window::Set_Window_Position(0, 0);
            Background->Draw_Texture();
        }
        if (btn_resolution_1280->Get_Action() == true) {
            my_Raylib::_Window::Set_Window_Size(1280, 720);
            my_Raylib::_Window::Set_Window_Position(0, 0);
            Background->Draw_Texture();
        }
        if (Height != my_Raylib::_Window::Get_Screen_Height()) {
            Height = my_Raylib::_Window::Get_Screen_Height();
            Delete_Object();
            Init_Object();
        }
    }
    if (solution == 2) {
        volumeEffect = sliders[0].Touch_Value() / 100;
        volumeMusic = sliders[1].Touch_Value() / 100;
    }
    if (btn_back->Get_Action() == true) {
        solution = 0;
        return (1);
    }
    if (btn_resolution->Get_Action() == true)
        solution = 1;
    if (btn_sound->Get_Action() == true)
        solution = 2;
    return (0);
}

void Menu_Setting::Delete_Object()
{
    delete (Background);
    delete (btn_back);
    delete (btn_resolution);
    delete (btn_sound);
    delete (btn_resolution_1920);
    delete (btn_resolution_1280);
    sliders.clear();
}