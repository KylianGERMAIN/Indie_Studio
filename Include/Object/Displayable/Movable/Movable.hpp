/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Movable
*/

#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include "Displayable.hpp"

class Movable : public Displayable {
    public:
        Movable(std::string name);
        Movable(std::string name, const Vector3 &pos, const Vector3 &rot);
        Movable(std::string name, const Vector3 &pos, const Vector3 &rot, std::string TexturePath);
        virtual ~Movable();

    protected:
    private:
};

#endif /* !MOVABLE_HPP_ */
