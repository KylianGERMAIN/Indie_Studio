/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Bonus
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "Model3D.hpp"


enum type {
    invincible = 0,
    invisible = 1,
    speed = 2
};

class Bonus : public Model3D{
    public:
        Bonus(std::string name, type effect);
        Bonus(std::string name, type effect, const Vector3 &pos, const Vector3 &rot);
        Bonus(std::string name, type effect, const Vector3 &pos, const Vector3 &rot, std::string modelPath);
        Bonus(std::string name, type effect, const Vector3 &pos, const Vector3 &rot, std::string modelPath, std::string texturePath);
        ~Bonus();
      
        void Actualise();
        void Effect(Player &player);
        void Spawn();

    protected:
        type effect;
    private:
};

#endif /* !BONUS_HPP_ */
