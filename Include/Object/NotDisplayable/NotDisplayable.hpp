/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** NotDisplayable
*/

#ifndef NOTDISPLAYABLE_HPP_
#define NOTDISPLAYABLE_HPP_

#include "Object.hpp"
#include <string>

class NotDisplayable : public Object {
    public:
        NotDisplayable(std::string name);
        NotDisplayable(std::string name, const Vector3 &pos, const Vector3 &rot);
        virtual ~NotDisplayable();

    protected:
    private:
};

#endif /* !NOTDISPLAYABLE_HPP_ */
