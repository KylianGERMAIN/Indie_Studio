/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:    
** Menu_Interface
*/

#ifndef MENU_INTERFACE_HPP_
#define MENU_INTERFACE_HPP_

#include "IMenu.hpp"

class Menu_Interface : public IMenu {
    public:
        Menu_Interface();
        virtual ~Menu_Interface();

        void Init_Object();
        void Draw_Object();
        void Position_Object();
        void Music_Gestion();
        int Interaction_Object();
        void Delete_Object();

    protected:
    private:
        Color color = {255,255,255,255};
        Button *btn_play;
        Button *btn_settings;
        Button *btn_exit;
        Displayable *Background_menu;

        Music _Music;
};

#endif /* !MENU_INTERFACE_HPP_ */
