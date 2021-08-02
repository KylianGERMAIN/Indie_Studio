/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** End
*/

#ifndef End_HPP_
#define End_HPP_

#include "IMenu.hpp"

class End : public IMenu {
    public:
        End();
        virtual ~End();
        
        void Init_Object() {};
        void Init_Object(std::vector<Player *> Players);
        void Draw_Object();
        int Interaction_Object();
        void Delete_Object();

    protected:
    private:
        Color color = {255,255,255, 255};
        std::vector<Player *> _Players;
        Displayable *Background_menu;
        Button *btn_exit;
        Button *btn_home;
        Sound endSound;
        bool playSound = true;
};

#endif /* !End_HPP_ */
