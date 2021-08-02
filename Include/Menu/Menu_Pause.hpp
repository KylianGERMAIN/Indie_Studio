/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Menu_pause
*/

#ifndef MENU_PAUSE_HPP_
#define MENU_PAUSE_HPP_

#include "IMenu.hpp"

class Menu_Pause : public IMenu {
    public:
        Menu_Pause();
        ~Menu_Pause();

        void Init_Object();
        void Draw_Object();
        void Position_Object();
        void Music_Gestion();
        int Interaction_Object();
        void Delete_Object();

    protected:
    private:
        Color color = {255,255,255,255};
        Displayable *Background_menu;
        Button *btn_settings;
        Button *btn_exit;
        Button *btn_continue;
        Button *btn_home;
};

#endif /* !MENU_PAUSE_HPP_ */
