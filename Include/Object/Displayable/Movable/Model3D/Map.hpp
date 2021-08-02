/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_
#include <vector>

#include "raylib.hpp"
#include "Model3D.hpp"

class Player;

class Map {
    public:
        Map(const std::string path_main_mod, const std::string path_main_tex, const std::string path_mod, const std::string path_tex);
        ~Map();
        void Init_Map(const std::string path_main_mod, const std::string path_main_tex, const std::string path_mod, const std::string path_tex);
        void Draw_Map();
        void Unload_Map();

        void Draw_Hitbox_Map() {
            Vector3 temp;
            for (int i = 0; i < platforms.size(); i++) {
                temp = {platforms[i]->Get_posHitBox().x, platforms[i]->Get_posHitBox().y, platforms[i]->Get_posHitBox().z + platforms[i]->Get_Size().z / 2};
                my_Raylib::_Model::Draw_Cube(temp, platforms[i]->Get_Size(), HITBOX_MAP);
            }
            my_Raylib::_Model::Draw_Cube(outPos, outSize, HITBOX_MAP);
        }
        std::vector<Model3D *> Get_Platforms(){return platforms;}
    protected:
    private:
        Vector3 outPos = {0, -200, 0};
        Vector3 outSize = {10, 1, 1000};
        std::vector<Model3D *> platforms;
        std::vector<Vector3> platformPos = {{0, 0, 0},
                                            {0, 25, -75},
                                            {0, 25, 0},
                                            {0, 25, 75}};
};


#endif /* !MAP_HPP_ */
