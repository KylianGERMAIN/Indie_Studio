/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Model3D.hpp"
#include <map>
#include <vector>

class Player : public Model3D {
    public:
        Player(std::string name, int nbPlayer);
        Player(std::string name, int nbPlayer, float newPv, int life);
        Player(std::string name, int nbPlayer, const Vector3 &pos, const Vector3 &rot, float newPv, int life);
        Player(std::string name, int nbPlayer, const Vector3 &pos, const Vector3 &rot, std::string modelPath, float newPv, int life);
        Player(std::string name, int nbPlayer, const Vector3 &pos, const Vector3 &rot,
            std::string modelPath, std::string texturePath, float newPv, int life, int jump, float grav, float speed);
        ~Player();

        void Move(Model3D &platformPrinc);
        void HandleDash();
        void MovementZ();
        void MovementX(Model3D &platformPrinc);
        void Attack();
        void Check_Punch(std::vector<Player *> Players);
        void Invincible_Timer();
        void Invisible_Timer();
        void AddDammage(const float &value, const float &offset);
        void initKey();
        void initSound();
        void Actualise(float &volumeEffect);

        void Draw() {
            if (!invisible) { 
                Draw_Model(angle);
                Draw_Texture();
            }
        };


        void Draw_Hitbox_Player() {
            my_Raylib::_Model::Draw_Cube(posHitBox, size, HITBOX_PLAYER);
            my_Raylib::_Model::Draw_Cube(posFoot, sizeFoot, HITBOX_FOOT);
        }
        
        int getKey(std::string key) {
            if (Keys.find(key) != Keys.end())
                return (Keys[key]);
            else
                return -1;
        }

        void Dead() {
            life -= 1;
            pv = 0;
            savePv = 0;
            position = {0, 50, 20};
            gravity = 0;
            my_Raylib::_Sound::Play_Sound(soundDeath);
            my_Raylib::_Sound::Play_Sound(soundFalling);
        }

        void update_Sound();

        void set_animcount(const int &count) {
            animsCount = count;
        }

        int get_animcount() {
            return(animsCount);
        }
        
        void Set_Pv(float newPv) { pv = newPv;}
        float Get_Pv() { return pv;}
        int Get_Is_Light_Attack() {return isLightAttack;}
        Vector3 Get_Size_Light_Attack() {return sizeLightAttack;}
        Vector3 Get_Pos_Attack() {return posAttack;}
        int Get_Life() {return life;}
        int Get_nbJump() {return nbJump;}
        int Get_nbPunch() {return nbPunch;}
        bool Get_Invincible() {return invincible;}
        void Set_Invincible(bool value) {invincible = value;}
        bool Get_Invisible() {return invisible;}
        void Set_Invisible(bool value) {invisible = value;}

    protected:
        std::vector<float> coolDownLightAttack = {0.3, 0.2, 0.4};
        std::map<std::string, int> Keys {
            {"UP", 0},
            {"DOWN", 0},
            {"RIGHT", 0},
            {"LEFT", 0},
            {"LIGHT_ATTACK", 0}
        };

        std::vector<Sound> soundDash;
        std::vector<Sound> soundJump;
        std::vector<Sound> soundLand;
        Sound soundWalk;
        Sound soundAttack;
        Sound soundDescend;
        Sound soundDeath;
        Sound soundFalling;

        int nbPlayer = -1;

        int life = 1;
        float pv = 0;
        float savePv = 0;

        int dir;
        float dashSpeed = 2;
        float normalSpeed = 1;
        int nbMaxJump = 2;
        int actualJump = 0;
        float speed = normalSpeed;
        int nbJump = 0;

        int animFrameCounterJump = 0;
        int animFrameCounterWalk = 0;
        int animFrameCounterAttack = 0;
        int isLightAttack = -1;

        bool canAttack = true;
        bool canDash = false;
        bool hitHim = false;
        bool takeHit = false;
        bool invincible = false;
        bool invisible = false;
        bool playJump = false;
        bool playAttack = false;
        int nbPunch = 0;
        int damage = 6;

        float volumeEffect = 1;

        float force = (pv - savePv) * (pv / 60);

        Vector3 posAttack = {0,0,0};
        Vector3 sizeLightAttack = {3, 3 ,6};

    private:
};

#endif /* !PLAYER_HPP_ */
