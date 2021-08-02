/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Player
*/

#include "Player.hpp"
#include <chrono>

Player::Player(std::string name, int nbPlayer) :  Model3D(name), nbPlayer(nbPlayer)
{
    initKey();
    initSound();
}

Player::Player(std::string name, int nbPlayer, float newPv, int life) : Model3D(name),  pv(newPv), savePv(newPv), nbPlayer(nbPlayer), life(life)
{
    initKey();
    initSound();
}

Player::Player(std::string name, int nbPlayer, const Vector3 &pos, const Vector3 &rot, float newPv, int life) : Model3D(name, pos, rot), pv(newPv), savePv(newPv), nbPlayer(nbPlayer), life(life)
{
    initKey();
    initSound();
}

Player::Player(std::string name, int nbPlayer, const Vector3 &pos, const Vector3 &rot,
            std::string modelPath, float newPv, int life) : Model3D(name, pos, rot, modelPath), pv(newPv), savePv(newPv), nbPlayer(nbPlayer), life(life)
{
    initKey();
    init_anim();
    initSound();
}

Player::Player(std::string name, int nbPlayer, const Vector3 &pos, const Vector3 &rot,
            std::string modelPath, std::string texturePath, float newPv, int newLife, int newJump, float grav, float newSpeed) : Model3D(name, pos, rot, texturePath, modelPath, grav), pv(newPv), savePv(newPv), nbPlayer(nbPlayer), life(newLife), nbMaxJump(newJump), normalSpeed(newSpeed)
{
    dashSpeed = newSpeed * 2;
    initKey();
    init_anim();
    initSound();
}

Player::~Player()
{
    for (int i = 0; i < anims.size(); i++) {
        my_Raylib::_Model::Unload_Model_Animation(*anims[i]);
        delete anims[i];
    }
    for (int i = 0; i < soundJump.size(); i++)
        if (soundJump[i].sampleCount > 0)
            my_Raylib::_Sound::Unload_Sound(soundJump[i]);
    for (int i = 0; i < soundLand.size(); i++)
        if (soundLand[i].sampleCount > 0)
            my_Raylib::_Sound::Unload_Sound(soundLand[i]);
    for (int i = 0; i < soundDash.size(); i++)
        if (soundDash[i].sampleCount > 0)
            my_Raylib::_Sound::Unload_Sound(soundDash[i]);
    if (soundWalk.sampleCount > 0)
        my_Raylib::_Sound::Unload_Sound(soundWalk);
    if (soundAttack.sampleCount > 0)
        my_Raylib::_Sound::Unload_Sound(soundAttack);
    if (soundDescend.sampleCount > 0)
        my_Raylib::_Sound::Unload_Sound(soundDescend);
    if (soundDeath.sampleCount > 0)
        my_Raylib::_Sound::Unload_Sound(soundDeath);
    if (soundFalling.sampleCount > 0)
        my_Raylib::_Sound::Unload_Sound(soundFalling);
    soundJump.clear();
    soundLand.clear();
    soundDash.clear();
    anims.clear();
}

void Player::initSound()
{
    for (int i = 0; i < 3; i++)
        soundJump.push_back(my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_jump0" + std::to_string(i + 1) + ".wav"));

    for (int i = 0; i < 3; i++)
        soundLand.push_back(my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_landing0" + std::to_string(i + 1) + ".wav"));

    soundDash.push_back(my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_dash_start.wav"));
    soundDash.push_back(my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_dash_stop.wav"));
    soundWalk = my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_step_left_m.wav");
    soundAttack = my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_special_N01.wav");
    soundDescend = my_Raylib::_Sound::Load_Sound(SOUNDCHAR "se_mario_squat.wav");
    soundDeath = my_Raylib::_Sound::Load_Sound(SOUNDCHAR "vc_mario_damage_twinkle.wav");
    soundFalling = my_Raylib::_Sound::Load_Sound(SOUNDCHAR "death_falling.mp3");
}

void Player::initKey()
{
    switch (nbPlayer)
    {
    case 1:
        Keys["UP"] = KEY_W;
        Keys["DOWN"] = KEY_S;
        Keys["RIGHT"] = KEY_D;
        Keys["LEFT"] = KEY_A;
        Keys["LIGHT_ATTACK"] = KEY_E;
        tint = RAYWHITE;
        break;
    case 2:
        Keys["UP"] = KEY_UP;
        Keys["DOWN"] = KEY_DOWN;
        Keys["RIGHT"] = KEY_RIGHT;
        Keys["LEFT"] = KEY_LEFT;
        Keys["LIGHT_ATTACK"] = KEY_RIGHT_CONTROL;
        tint = LIGHTGRAY;
        break;
    default:
        break;
    }
}


void Player::update_Sound()
{
    for (int i = 0; i < soundJump.size(); i++)
        if (soundJump[i].sampleCount > 0)
            my_Raylib::_Sound::Set_Volume(soundJump[i], volumeEffect);
    for (int i = 0; i < soundLand.size(); i++)
        if (soundLand[i].sampleCount > 0)
            my_Raylib::_Sound::Set_Volume(soundLand[i], volumeEffect);
    for (int i = 0; i < soundDash.size(); i++)
        if (soundDash[i].sampleCount > 0)
            my_Raylib::_Sound::Set_Volume(soundDash[i], volumeEffect);
    if (soundWalk.sampleCount > 0)
        my_Raylib::_Sound::Set_Volume(soundWalk, volumeEffect);
    if (soundAttack.sampleCount > 0)
        my_Raylib::_Sound::Set_Volume(soundAttack, volumeEffect);
    if (soundDescend.sampleCount > 0)
        my_Raylib::_Sound::Set_Volume(soundDescend, volumeEffect);
    if (soundDeath.sampleCount > 0)
        my_Raylib::_Sound::Set_Volume(soundDeath, volumeEffect);
    if (soundFalling.sampleCount > 0)
        my_Raylib::_Sound::Set_Volume(soundFalling, volumeEffect);
}

void Player::Actualise(float &nvolumeEffect) {
    volumeEffect = nvolumeEffect;
    posFoot = {posHitBox.x, posHitBox.y - size.y / 2, posHitBox.z};
    posHitBox = {position.x, position.y + size.y / 2, position.z};
    Invincible_Timer();
    Invisible_Timer();
    update_Sound();


    if (isGrounded)
        actualJump = 0;
    if (pv > savePv) {
        force = (pv - savePv) * (pv / 50);
        if (velocity.z != 0)
            Handle_Velocity("z", force, dir);
        if (velocity.y != 0)  
            Handle_Velocity("y", force / 10, 1);
        if (velocity.z == 0 && takeHit)
            velocity.y = 0;
        else {
            savePv = pv;
            takeHit = false;
        }
    } else {
        if (velocity.y != 0)
            Handle_Velocity("y", 3, 1);
        if (velocity.z != 0) {
            Handle_Velocity("z", force, dir);
        }
    }
}

void Player::Invincible_Timer()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static auto changeColor = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;
    static bool startChrono = true;

    end = std::chrono::system_clock::now(); 
    if (invincible) {
        if (startChrono) {
            start = std::chrono::system_clock::now();
            changeColor = std::chrono::system_clock::now();
            startChrono = false;
            tint = BLACK;
        }
        if ((elapsed_seconds = end - changeColor).count() > 0.5) {
            changeColor = std::chrono::system_clock::now();
            if (tint.r == 0 && tint.g == 0 && tint.b == 0)
                tint = WHITE;
            else if (tint.r == 255 && tint.g == 255 && tint.b == 255)
                tint = BLACK;
        }
    }
    if ((elapsed_seconds = end - start).count() > 5 && invincible) {
        invincible = false;
        startChrono = true;
        tint = WHITE;
    }
}

void Player::Invisible_Timer()
{
    static auto start = std::chrono::system_clock::now();
    static auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;
    static bool startChrono = true;

    end = std::chrono::system_clock::now(); 
    if (invisible && startChrono) {
            start = std::chrono::system_clock::now();
            startChrono = false;
            damage *= 2;
    }
    if ((elapsed_seconds = end - start).count() > 5 && invisible) {
        invisible = false;
        startChrono = true;
        damage = 6;
    }
}