/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Bonus
*/

#include "Player.hpp"
#include "Bonus.hpp"
#include <chrono>


Bonus::Bonus(std::string name, type effect) : Model3D(name), effect(effect)
{
    texture.id = -1;
    tint= BLUE;
    Spawn();
}

Bonus::Bonus(std::string name, type effect, const Vector3 &pos, const Vector3 &rot) : Model3D(name, pos, rot), effect(effect)
{
    texture.id = -1;
    tint= BLUE;
    Spawn();
}

Bonus::Bonus(std::string name, type effect, const Vector3 &pos, const Vector3 &rot, std::string modelPath)
            : Model3D(name, pos, rot, modelPath), effect(effect)
{
    texture.id = -1;
    tint= BLUE;
    Spawn();
}

Bonus::Bonus(std::string name, type effect, const Vector3 &pos, const Vector3 &rot, std::string modelPath, std::string texturePath) 
            : Model3D(name, pos, rot, modelPath,  texturePath), effect(effect)
{
    tint= BLUE;
    Spawn();
}

Bonus::~Bonus()
{
}

void Bonus::Actualise()
{   static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;
    static bool startChrono = true;
    int respawnTime = rand() % 35 + 15;

    end = std::chrono::system_clock::now();
    if (fly && startChrono) {
        start = std::chrono::system_clock::now();
        startChrono = false;
    }
    if ((elapsed_seconds = end - start).count() > respawnTime) {
        fly = false;
        startChrono = true;
    }

    posFoot = {posHitBox.x, (posHitBox.y - size.y / 2) - 4, posHitBox.z};
    posHitBox = {position.x, position.y + size.y / 2, position.z};
}

void Bonus::Effect(Player &player)
{
    if (effect == type::invincible && !player.Get_Invincible()) {
        player.Set_Invincible(true);
    } else if (effect == type::invisible && !player.Get_Invisible()) {
        player.Set_Invisible(true);
    }
    fly = true;
    position = {0, 100, 0}; 
    Spawn();
}

void Bonus::Spawn()
{
    float z = rand() % 65 + -65;
    int newType = (rand() % 2);

    position = {0, 100, z};
    if (newType == 0) {
        tint = YELLOW;
        effect = type::invincible;
    }
    else if (newType == 1) {
        effect = type::invisible;
        tint = BLUE;
    }
}
