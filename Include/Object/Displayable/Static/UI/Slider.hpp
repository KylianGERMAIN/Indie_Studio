/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Slider
*/

#ifndef SLIDER_HPP_
#define SLIDER_HPP_

#include "Static.hpp"

class Slider : public Static{
    public:
        Slider();
        Slider(std::string name, const Vector3 &pos, const Vector3 &rot, const Vector3 &size, const Vector3 &scale = {1,1,1}, const Color &color = {255,255,255,255});
        ~Slider();

        void Draw();
        float Touch_Value();

        void setValue(const float &nvalue) {value = nvalue;}

        void set_Scale(const Vector3 &newscale) { scale = newscale;}
    protected:
        Vector3 size;
        Color color;
        float value;
        float max;
        float min;
        Vector3 scale;
    private:
};

#endif /* !SLIDER_HPP_ */
