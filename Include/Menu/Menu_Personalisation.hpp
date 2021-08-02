/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_Personalisation
*/

#ifndef MENU_PERSONALISATION_HPP_
#define MENU_PERSONALISATION_HPP_

#include "IMenu.hpp"
#include <string>
#include <vector>

class Menu_Personalisation : public IMenu {
    public:
        Menu_Personalisation();
        ~Menu_Personalisation();

        void Init_Object();
        void Draw_Object();
        void Position_Object();
        void Music_Gestion();
        int Interaction_Object();
        void Delete_Object();

        std::vector<float> getValue() const { return value; }
        float getJump() const { return value[0]; }
        float getGravity() const { return value[1]; }
        float getSpeed() const { return value[2]; }
        float getLife() const { return value[3]; }
    protected:
    private:
        Displayable *Background_menu;
        Button *Btn_Classic;
        std::vector<std::string> name_Btn = {"saut", "vie", "gravity", "vitesse"};
        std::vector<Button *> Btn_Next;
        std::vector<Button *> Btn_Back;
        Button *Btn_GetBack;
        Music _Music;

        Color color = {255,255,255,255};
        float center;
        float pos_W_Back;
        float pos_W_Next;
        float pos_W_classic;
        float pos_H;

        std::vector<float> value =      {2, 0.2, 1, 3};
        std::vector<float> rate_plus =  {1, 0.5, 2, 1};
        std::vector<float> rate_minus = {1, 0.15, 0.5, 1};
        
};

#endif /* !MENU_PERSONALISATION_HPP_ */
