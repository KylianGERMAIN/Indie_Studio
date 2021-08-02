/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Model3D
*/

#include "Model3D.hpp"

Model3D::Model3D(std::string name) : Movable(name)
{
}

Model3D::Model3D(std::string name, const Vector3 &pos,const Vector3 &rot) : Movable(name, pos, rot)
{
}

Model3D::Model3D(std::string name, const Vector3 &pos, const Vector3 &rot, std::string modelPath, float grav) : Movable(name, pos, rot), baseGravity(grav)
{
    Load_Model(modelPath);
    body = my_Raylib::_Mesh::Mesh_BoundingBox(model.meshes[0]);
    size = body.max;
    sizeFoot = {size.x, 1, size.z - 2};
    posHitBox = {position.x, position.y + size.y /2, position.z};
    gravity = baseGravity;
}

Model3D::Model3D(std::string name, const Vector3 &pos, const Vector3 &rot, std::string texturePath, std::string modelPath, float grav) : Movable(name, pos, rot, texturePath), baseGravity(grav)
{
    Load_Model(texturePath, modelPath);
    body = my_Raylib::_Mesh::Mesh_BoundingBox(model.meshes[0]);
    size = body.max;
    sizeFoot = {size.x, 1, size.z - 2};
    posHitBox = {position.x, position.y + size.y /2, position.z};
    gravity = baseGravity;
} 


Model3D::~Model3D()
{
    std::cout << "UNLOAD_MODEL3D " << name.c_str() << std::endl;
    Unload_Model();
}

bool Model3D::Check_Collision_With(Model3D &model2) {
    return(my_Raylib::_Colision::Check_Collision_Boxes(posHitBox, size, model2.Get_posHitBox(), model2.Get_Size()));
}

bool Model3D::Check_Collision_Foot_With(Model3D &model2) {
    return(my_Raylib::_Colision::Check_Collision_Boxes(posFoot, sizeFoot, model2.Get_posHitBox(), model2.Get_Size()));
};

void Model3D::Handle_Velocity(std::string direction, float value, float offset) {    
    if (direction == "y") {
        velocity.y -= My_Abs(value);
        Add_Position_y(value);
    } else if (direction == "z" && offset > 0) {
        velocity.z -= My_Abs(value);
        Add_Position_z(value * offset);
        if (velocity.z < 0)
            velocity.z = 0;
    } else if (direction == "z" && offset < 0) {
        velocity.z += My_Abs(value);
        Add_Position_z(value * offset);
        if (velocity.z > 0)
            velocity.z = 0;
    } else {
        velocity.x -= My_Abs(value);
        Add_Position_x(value);
    }       
    if (velocity.y < 0)
        velocity.y = 0;
    if (velocity.x < 0)
        velocity.x = 0;
}

void Model3D::Check_Grounded(Model3D &check) {
    if (isGrounded) {
        gravity = baseGravity;
    }
    else if (Check_Collision_Foot_With(check)) {
        if (posFoot.y <= check.Get_posHitBox().y && check.Get_Name() == "Platform_principal") {
            Set_Position_y(check.Get_posHitBox().y + 1);
        }
        isGrounded = true;
        gravity = baseGravity;
    }
}

void Model3D::Fall() {
    if (!fly) {
        position.y -= gravity;
        gravity += 0.05;
    } else {
        gravity = baseGravity;
        velocity.y = 0;
    }
}