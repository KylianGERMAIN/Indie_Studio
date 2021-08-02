/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** GameMaster
*/

#ifndef GAMEMASTER_HPP_
#define GAMEMASTER_HPP_

#include "raylib.h"
#include "Camera.hpp"
#include "Player.hpp"
#include <memory>
#include "raylib.h"
#include "raylib.hpp"
#include "allInclude.hpp"
#include "Menu_Interface.hpp"
#include "Menu_Setting.hpp"
#include "Menu_Personalisation.hpp"
#include "Menu_Pause.hpp"
#include "Splash_Screen.hpp"
#include "Bonus.hpp"
#include "End.hpp"
#include <chrono>

struct DeathParticle {
    int min;
    int actual;
    float max;
    bool gross;
    Color color;
    Vector3 pos;
};

struct DeathParticles {
    std::vector<DeathParticle> particles;
    bool gross;
};

class Game_Master {
    public:
        Game_Master(float menu = -1);
        ~Game_Master();

        void Gameloop();
        void SetVariable();
        void Interface();
        void Destruction();
        int GameLoop();
        void Draw();
        int MenuPause();
        void Actualise_Grounded(Model3D &model);
        void init_Players(const int nbPlayers);
        void Unload_Players();

        void CountDown_Intro(std::vector<Sound> &sound);
        void Game_Introduction();
        void Win_Condition();

        void drawDeathParticles();
        DeathParticles createDeathParticles(Vector3 pos);

        void Init_Menu();
        void Delete_Menu();
        void Menu_Pres();
        void Actualise_Camera_Pres(int &nbTrav, Traveling &actualTrav, bool &change, int &newTrav, std::vector<Traveling> &allTrav);

        void Draw_UI();
        void Draw_Players();
        void Draw_Assets();
        void Draw_Debug();
        void Draw_Players_Hitbox();
        void Draw_Players_Attack();

        bool waitLeave();
        void Clear_All();

        void Movement_Players_Gestion();
        void Actualise_Players();
        void Actualise_Players_Grounded();
        void Move_Players();
        void Dead_Players();
        void CheckHit();
        void Take_Bonus();

        std::vector<Traveling> create_Trav() {
            return(
            std::vector<Traveling> {
                Traveling{{75,40,-100}, {75,40,100}, {0,0,1}, {0,40,0}, {0,40,0}, {0,0,0}},
                Traveling{{75,80,100}, {75,-50,-100}, {0,-0.8,-1}, {0,40,0}, {0,40,0}, {0,0,0}},
                Traveling{{75,-80,0}, {75,80,0}, {0,1,0}, {0,40,0}, {0,40,0}, {0,0,0}}
                }
            );
        }


        std::shared_ptr<_Cam> Get_Cam_Object() {return camera;}
    private:
        std::shared_ptr<_Cam> camera;
        std::vector<Player *> Players;
        std::vector<DeathParticles> deathParticles;

        Displayable *Background;
        Map *my_map;
        Bonus *bonus;
        Menu_Interface menu_interface;
        Menu_Setting menu_setting;
        Menu_Pause menu_pause;
        Menu_Personalisation menu_personalisation;
        End end;
        Splash_Screen splash_screen;

        int nbJump = 0;
        float gravity = 0.2;
        float speed = 1;
        int life = 3;

        Vector3 position;
        int menu = -1;
        
        bool drawDebug = false;
        float volumeEffect = 1;
        float volumeMusic = 1;
};

#endif /* !GAMEMASTER_HPP_ */
