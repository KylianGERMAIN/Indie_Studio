/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "Movable.hpp"
#include "raylib.hpp"
#include <iostream>
#include <filesystem>
#include <vector>

class Model3D : public Movable {
    public:
        Model3D(std::string name);
        Model3D(std::string name, const Vector3 &pos, const Vector3 &rot);
        Model3D(std::string name, const Vector3 &pos, const Vector3 &rot, std::string texturePath, std::string modelPath, float grav = 0.2);
        Model3D(std::string name, const Vector3 &pos, const Vector3 &rot, std::string modelPath, float grav = 0.2);
        virtual ~Model3D();

        void Load_Model(std::string modelPath) {
            model = my_Raylib::_Model::Load(modelPath);
        };

        void Load_Model(std::string TexturePath, std::string modelPath, int diffuse = MAP_DIFFUSE) {
            texture = my_Raylib::_Texture2D::Load(TexturePath);
            model = my_Raylib::_Model::Load(modelPath);
            my_Raylib::_Model::Set_Material_Texture(model, texture, diffuse); 
        };

        void Set_Model_Texture(std::string texturePath, int diffuse = MAP_DIFFUSE) {
            texture = my_Raylib::_Texture2D::Load(texturePath);
            my_Raylib::_Model::Set_Material_Texture(model, texture, diffuse); 
        }

        void Set_Model_Texture(Texture2D text, int diffuse = MAP_DIFFUSE) {
            my_Raylib::_Model::Set_Material_Texture(model, text, diffuse);
        }

        void Set_Model_Texture(int diffuse = MAP_DIFFUSE) {
            my_Raylib::_Model::Set_Material_Texture(model, texture, diffuse);
        }

        void Draw_Model(float angle = 0, Vector3 scale = {1,1,1}) {
            my_Raylib::_Model::Draw(model, position, rotation, angle, scale, tint);
        }

        void Unload_Model() {
            Unload_Texture();
            my_Raylib::_Model::Unload(model);
        }


        bool Check_Collision_With(Model3D &model2);
        bool Check_Collision_Foot_With(Model3D &model2);
        void Check_Grounded(Model3D &check);
        void Handle_Velocity(std::string direction, float value, float offset);
        void Fall();

        float My_Abs(float value) {
            if (value < 0)
                return value * -1;
            return value;
        }

        void Draw_Hitbox(float offset_y = 0) {
            my_Raylib::_Model::Draw_Cube(posHitBox, size, HITBOX_PLAYER);
            my_Raylib::_Model::Draw_Cube(posFoot, sizeFoot, HITBOX_FOOT);
        }

        void Print_Velocity() const {
            std::cout << "Velocity " << name << " x = " << velocity.x << ", y = " << velocity.y << ", z = " << velocity.z << std::endl;
        }

        void init_anim() {
            anims.push_back(my_Raylib::_Model::Load_Model_Animations("Ressources/Animation/courir1.iqm", animsCount));
            anims.push_back(my_Raylib::_Model::Load_Model_Animations("Ressources/Animation/la_claque1.iqm", animsCount));
            anims.push_back(my_Raylib::_Model::Load_Model_Animations("Ressources/Animation/jump1.iqm", animsCount));
        }

        void Set_Tint(Color color) {tint = color;}
        void Set_Gravity(float value) {gravity = value;}
        void Add_Gravity(float value) {gravity += value;}
        void Set_Grounded(bool value) {isGrounded = value;}
        bool Get_Grounded() {return isGrounded;}
        Color Get_Tint() {return tint;}
        Vector3 Get_Size() {return size;}
        void Set_Size(Vector3 value) {size = value;}
        Vector3 Get_Pos_Foot() {return posFoot;}
        Vector3 Get_Size_Foot() {return sizeFoot;}
        Vector3 Get_posHitBox() {return posHitBox;}
        void Set_posHitBox(Vector3 value) {posHitBox = value;}
        Model Get_Model() {return model;}
        void Set_Fly(bool value) {fly = value;}
        bool Get_Fly() {return fly;}
        void Add_Velocity(Vector3 value) {velocity.x += value.x;
                                            velocity.y += value.y;
                                            velocity.z += value.z;}
        Color Get_Color() {return tint;}

        BoundingBox body;
    protected:
        std::vector <ModelAnimation*> anims;
        int animsCount = 0;
        bool fly = false;
        Model model;
        bool isGrounded = false;
        Vector3 velocity = {0, 0, 0};
        float angle = 0;
        float gravity = 0;
        float baseGravity = 0.2;
        Color tint = {255,255,255,255};
        Vector3 posHitBox = {0,0,0};
        Vector3 size = {0,0,0};
        Vector3 posFoot = {posHitBox.x, posHitBox.y, posHitBox.z};
        Vector3 sizeFoot = {size.x, 1, size.z - 2};
    private:
};

#endif /* !MODEL_HPP_ */
