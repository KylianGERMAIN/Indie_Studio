/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Static
*/

#ifndef STATIC_HPP_
#define STATIC_HPP_

#include "Displayable.hpp"

class Static : public Displayable {
    public:
        Static(std::string name);
        Static(std::string name, const Vector3 &pos, const Vector3 &rot);
        Static(std::string name, const Vector3 &pos, const Vector3 &rot, std::string TexturePath);
        virtual ~Static();

    protected:
    private:
};

#endif /* !STATIC_HPP_ */
