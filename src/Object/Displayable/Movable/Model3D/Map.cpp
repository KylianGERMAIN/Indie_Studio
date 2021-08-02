/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Map
*/

#include "Player.hpp"
#include "Map.hpp"
#include <cstdlib>

Map::Map(const std::string path_main_mod, const std::string path_main_tex, const std::string path_mod, const std::string path_tex)
{
    Init_Map(path_main_mod, path_main_tex, path_mod, path_tex);
}

Map::~Map()
{
    Unload_Map();
}

void Map::Init_Map(const std::string path_main_mod, const std::string path_main_tex, const std::string path_mod, const std::string path_tex)
{
    platforms.push_back(new Model3D("Platform_principal", platformPos[0], {0.0f, 0.0f, 0.0f}, path_main_tex, path_main_mod));
    platforms[0]->Set_Size({platforms[0]->Get_Size().x, platforms[0]->Get_Size().y * 4, platforms[0]->Get_Size().z * 2});
    platforms[0]->Set_posHitBox({platforms[0]->Get_posHitBox().x, platforms[0]->Get_posHitBox().y - platforms[0]->Get_Size().y, platforms[0]->Get_posHitBox().z - platforms[0]->Get_Size().z / 2});
    for (int i = 1; platformPos.size() > i ;i++) {
        if (rand()%2 == 1) {
            platforms.push_back(new Model3D(("Platform_" + i),platformPos[i], {0.0f, 0.0f, 0.0f}, path_tex, path_mod));
            platforms[platforms.size() - 1]->Set_Size({platforms[platforms.size() - 1]->Get_Size().x,
                                                        platforms[platforms.size() - 1]->Get_Size().y * 2,
                                                        platforms[platforms.size() - 1]->Get_Size().z * 2});
            platforms[platforms.size() - 1]->Set_posHitBox({platforms[platforms.size() - 1]->Get_posHitBox().x,
                                        platforms[platforms.size() - 1]->Get_posHitBox().y - platforms[platforms.size() - 1]->Get_Size().y,
                                        platforms[platforms.size() - 1]->Get_posHitBox().z - platforms[platforms.size() - 1]->Get_Size().z / 2});
        }
    }
}

void Map::Draw_Map()
{
    for (int i = 0; platforms.size() > i ;i++)
        platforms[i]->Draw_Model();
}

void Map::Unload_Map()
{
    for (int i = 0; platforms.size() > i ;i++) {
        delete(platforms[i]);
    }
}