/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** playerAttack
*/

#include "Player.hpp"
#include <chrono>

void Player::Attack()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    if (my_Raylib::_Input::Is_Key_Pressed(Keys["LIGHT_ATTACK"])) {
        if (canAttack) {
            my_Raylib::_Sound::Play_Sound(soundAttack);
            isLightAttack = 0;
            start = std::chrono::system_clock::now();
            end = std::chrono::system_clock::now();
            canAttack = false;
            playAttack = true;
            hitHim = true;
            animFrameCounterAttack = 0;
            if (rotation.y == 90)
                posAttack = {position.x, position.y + (size.y / 2), position.z - (size.z)};
            else if (rotation.y == -90)
                posAttack = {position.x, position.y + (size.y / 2), position.z + (size.z)};
        }
    }
    end = std::chrono::system_clock::now();
    if (isLightAttack != -1) {
        if (playAttack) {
            animFrameCounterAttack++;
            my_Raylib::_Model::Update_Model_Animation(model, anims[1], animFrameCounterAttack);
            if (animFrameCounterAttack >= anims[1]->frameCount) {
                animFrameCounterAttack = 0;
                playAttack = false;
            }
        }
        if ((elapsed_seconds = end - start).count() > coolDownLightAttack[isLightAttack]) {
            canAttack = true;
            isLightAttack = -1;
        }
    }
}

void Player::AddDammage(const float &value, const float &offset) {
    if (!invincible) {
        float damage = (((pv + 1) / 2 + value) * 10);
        Add_Velocity({0, damage / 15 , damage / 5 * offset});
        Print_Velocity();
        pv += value;
        takeHit = true;
        dir = offset;
    }
}

void Player::Check_Punch(std::vector<Player *> Players)
{
    bool hit = false;

    for (int i = 0; i < Players.size(); i++)
        if (isLightAttack != -1) {
            if (this->nbPlayer != Players[i]->nbPlayer) {
                hit = my_Raylib::_Colision::Check_Collision_Boxes(posAttack,
                                                                sizeLightAttack,
                                                                Players[i]->Get_Position(),
                                                                Players[i]->Get_Size());
                if (hit && hitHim) {
                    nbPunch += 1;
                    hitHim = false;
                    Players[i]->AddDammage(damage, Players[i]->Get_Position().z > position.z ? 1 : -1);
                }
            }
        }
}