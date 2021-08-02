/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** gmm_drawInGame
*/

#include "Game_Master.hpp"
#include <sstream>
#include <iomanip>

void Game_Master::drawDeathParticles()
{
    for (int i = 0; i < deathParticles.size(); i++) {
        for (int y = 0; y < deathParticles[i].particles.size(); y++) {
            if (deathParticles[i].particles[y].gross) {
                deathParticles[i].particles[y].actual += 2;
                if (deathParticles[i].particles[y].actual > deathParticles[i].particles[y].max) {
                    deathParticles[i].particles[y].gross = false;
                    if (y + 1 == deathParticles[i].particles.size())
                        deathParticles[i].gross = false;
                }
            } else {
                if (!deathParticles[i].gross)
                    deathParticles[i].particles[y].actual -= 2;
                if (deathParticles[i].particles[y].actual < deathParticles[i].particles[y].min)
                    deathParticles[i].particles.erase(deathParticles[i].particles.begin() + y);
            }
            my_Raylib::_Model::Draw_Sphere(deathParticles[i].particles[y].pos, deathParticles[i].particles[y].actual, deathParticles[i].particles[y].color);
        }
        if (deathParticles[i].particles.size() == 0)
            deathParticles.erase(deathParticles.begin() + i);
    }
}

void Game_Master::Draw_UI()
{
    Color color;
    std::string txt;
    std::stringstream ss;
    unsigned char r;
    float posW = my_Raylib::_Window::Get_Screen_Width() / 5;

    Background->Draw_Texture();
    for (int i = 0; i < Players.size(); i++) {
        if (Players[i]->Get_Pv() * 3 < 255)
            r = Players[i]->Get_Pv() * 3;
        else
            r = 255;
        color = {r, 10, 0, 255};
        ss << "PV: " << std::fixed << std::setprecision(2) << Players[i]->Get_Pv() << "%\nLife: " << Players[i]->Get_Life();
        my_Raylib::_Text::Draw_Text(Players[i]->Get_Name(), posW * (i + 1), my_Raylib::_Window::Get_Screen_Height() - 90, 25, BLACK);
        my_Raylib::_Text::Draw_Text(ss.str(), posW * (i + 1), my_Raylib::_Window::Get_Screen_Height() - 60, 25, color);
        ss.str("");
    }
}

void Game_Master::Draw_Players()
{
    for (int i = 0; i < Players.size(); i++)
        Players[i]->Draw();
}

void Game_Master::Draw_Players_Hitbox()
{
    bonus->Draw_Hitbox();
    for (int i = 0; i < Players.size(); i++) {
        std::cout << "body player " << i << " = " << Players[i]->Get_posHitBox().x << " " << Players[i]->Get_posHitBox().y << " " << Players[i]->Get_posHitBox().z << std::endl;
        Players[i]->Draw_Hitbox();
    }
}

void Game_Master::Draw_Players_Attack()
{
    for (int i = 0; i < Players.size(); i++) {
        if (Players[i]->Get_Is_Light_Attack() != -1) {
            Vector3 tempe = Players[i]->Get_Size_Light_Attack();
            DrawCube(Players[i]->Get_Pos_Attack(), tempe.x , tempe.y, tempe.z, HITBOX_LIGHTATTACK);
        }
    }
}

void Game_Master::Draw_Debug()
{
    my_map->Draw_Hitbox_Map();
    Draw_Players_Hitbox();
    Draw_Players_Attack();
}

void Game_Master::Draw_Assets()
{
    my_map->Draw_Map();
    Draw_Players();
    bonus->Draw_Model();
    if (drawDebug)
        Draw_Debug();
}

void Game_Master::CountDown_Intro(std::vector<Sound> &sounds)
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;
    std::string txt;

    bool playOne = true;
    bool playTwo = true;
    bool playThree = true;

    while ((elapsed_seconds = end - start).count() < 3) {
        end = std::chrono::system_clock::now();
        if (elapsed_seconds.count() < 1 && playThree) {
            txt = "3";
            my_Raylib::_Sound::Play_Sound(sounds[3]);
            playThree = false;
        } else if (elapsed_seconds.count() < 2 && elapsed_seconds.count() > 1 && playTwo) {
            txt = "2";
            my_Raylib::_Sound::Play_Sound(sounds[2]);
            playTwo = false;
        } else if (elapsed_seconds.count() < 3 && elapsed_seconds.count() > 2 && playOne) {
            txt = "1";
            my_Raylib::_Sound::Play_Sound(sounds[1]);
            playOne = false;
        }
        BeginDrawing();
            my_Raylib::_Other::Clear_Background(RAYWHITE);
            Background->Draw_Texture();
            BeginMode3D(camera->Get());
                Draw_Assets();
            EndMode3D();
            my_Raylib::_Text::Draw_Text(txt, my_Raylib::_Window::Get_Screen_Width() / 2 - 60, my_Raylib::_Window::Get_Screen_Height() / 2 - 60, 120, BLACK);
        EndDrawing();
    }
}