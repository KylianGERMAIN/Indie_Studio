/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_Setting
*/

#ifndef MENU_SETTING_HPP_
#define MENU_SETTING_HPP_

#include "IMenu.hpp"
#include "Slider.hpp"
#include <vector>

class Menu_Setting : public IMenu {
    public:
        Menu_Setting();
        ~Menu_Setting();

        void Init_Object();
        void Draw_Object();
        void Position_Object();
        void Music_Gestion();
        int Interaction_Object();
        void Delete_Object();
        int Get_sounds() { return (sound); }

        void initSliders();
        bool checkFile(std::string path);
        std::vector<float> readInFile();
        void writeInFile();
        float getVolumeMusic() { return volumeMusic;}
        float getVolumeEffect() { return volumeEffect;}

    protected:
    private:
        Button *btn_back;
        Button *btn_resolution;
        Button *btn_sound;
        Button *btn_resolution_1920;
        Button *btn_resolution_1280;
        std::vector<Slider> sliders;
        Displayable *Background;

        std::string pathSound = "sound.txt";
        int solution = 0;
        int Height = 720;
        int sound = 0;
};

#endif /* !MENU_SETTING_HPP_ */
