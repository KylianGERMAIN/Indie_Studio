/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** playerMouv
*/

#include "Player.hpp"
#include <chrono>

void Player::HandleDash()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    if (my_Raylib::_Input::Is_Key_Pressed(Keys["RIGHT"]) || my_Raylib::_Input::Is_Key_Pressed(Keys["LEFT"])) {
        if (!canDash && speed == normalSpeed) {
            start = std::chrono::system_clock::now();
            end = std::chrono::system_clock::now();
            canDash = true;
        } else if (canDash && speed == normalSpeed) {
            end = std::chrono::system_clock::now();
            if ((elapsed_seconds = end - start).count() < 0.3) {
                my_Raylib::_Sound::Play_Sound(soundDash[0]);
                speed = dashSpeed;
            }
            canDash = false;
        }
    }
    if (my_Raylib::_Input::Is_Key_Released(Keys["RIGHT"]) || my_Raylib::_Input::Is_Key_Released(Keys["LEFT"])) {
        end = std::chrono::system_clock::now();
        if ((elapsed_seconds = end - start).count() > 0.3) {
            if (speed != normalSpeed)
                my_Raylib::_Sound::Play_Sound(soundDash[1]);
            speed = normalSpeed;
            canDash = false;
        }
    }
}

void Player::MovementZ()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    if (my_Raylib::_Input::Is_Key_Down(Keys["RIGHT"])) {
        if (rotation.y == -90)
            animFrameCounterWalk = 0;
        rotation = {0,90, 0};
        angle = 90;
        if (speed == normalSpeed && isGrounded) {
            end = std::chrono::system_clock::now();
            if ((elapsed_seconds = end - start).count() > 0.4) {
                start = std::chrono::system_clock::now();
                my_Raylib::_Sound::Play_Sound(soundWalk);
            }
        }
        if (speed == dashSpeed && isGrounded) {
            end = std::chrono::system_clock::now();
            if ((elapsed_seconds = end - start).count() > 0.4) {
                start = std::chrono::system_clock::now();
                my_Raylib::_Sound::Play_Sound(soundWalk);
            }
        }
        this->Add_Position_z(speed * (-1));
        
        if (!playJump && !playAttack) {
            animFrameCounterWalk++;
            my_Raylib::_Model::Update_Model_Animation(model, anims[0], animFrameCounterWalk);
            if (animFrameCounterWalk >= anims[0]->frameCount) animFrameCounterWalk = 0;
        }
    
    }
    if (my_Raylib::_Input::Is_Key_Down(Keys["LEFT"])) {
        if (rotation.y == 90)
            animFrameCounterWalk = 0;
        rotation = {0,-90, 0};
        angle = 90;
        if (speed == normalSpeed && isGrounded) {
            end = std::chrono::system_clock::now();
            if ((elapsed_seconds = end - start).count() > 0.4) {
                start = std::chrono::system_clock::now();
                my_Raylib::_Sound::Play_Sound(soundWalk);
            }
        }
        if (speed == dashSpeed && isGrounded) {
            end = std::chrono::system_clock::now();
            if ((elapsed_seconds = end - start).count() > 0.2) {
                start = std::chrono::system_clock::now();
                my_Raylib::_Sound::Play_Sound(soundWalk);
            }
        }
        this->Add_Position_z(speed);
        if (!playJump && !playAttack) {
            animFrameCounterWalk++;
            my_Raylib::_Model::Update_Model_Animation(model, anims[0], animFrameCounterWalk);
            if (animFrameCounterWalk >= anims[0]->frameCount) animFrameCounterWalk = 0;
        }
    }
}

void Player::MovementX(Model3D &platformPrinc)
{
    if (fly) {
        if (my_Raylib::_Input::Is_Key_Down(Keys["UP"]))
            this->Add_Position_y(1);
        if (my_Raylib::_Input::Is_Key_Down(Keys["DOWN"]))
            this->Add_Position_y(-1);
        return;
    }
    if (my_Raylib::_Input::Is_Key_Down(Keys["DOWN"])) {
        if (!Check_Collision_Foot_With(platformPrinc))
            this->Add_Position_y(speed * (-1));
        velocity.y = 0;
    }
    if (my_Raylib::_Input::Is_Key_Pressed(Keys["UP"])) {
        actualJump++;

        if (isGrounded) {
            my_Raylib::_Sound::Play_Sound(soundJump[rand()%3]);
            animFrameCounterJump = 0;
            playJump = true;
            velocity.y = 20;
            nbJump++;
        } else {
            if (actualJump < nbMaxJump) {
                my_Raylib::_Sound::Play_Sound(soundJump[rand()%3]);
                animFrameCounterJump = 0;
                playJump = true;
                velocity.y = 20;
                gravity = 0.2;
                nbJump++;
            }
        }
    } else if (my_Raylib::_Input::Is_Key_Pressed(Keys["DOWN"]))
        my_Raylib::_Sound::Play_Sound(soundDescend);
    if (playJump) {
        animFrameCounterJump++;
        my_Raylib::_Model::Update_Model_Animation(model, anims[2], animFrameCounterJump);
        if (animFrameCounterJump >= anims[2]->frameCount) {
            playJump = false;
            animFrameCounterJump = 0;
        }
    }
}

void Player::Move(Model3D &platformPrinc)
{
    HandleDash();
    if (canAttack) {
        if (!takeHit)
            MovementZ();
        MovementX(platformPrinc);
    }
    Attack();
}
