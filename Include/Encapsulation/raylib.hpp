/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** raylib
*/

#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_

#include "raylib.h"
#include <string>

#define BOUNDING_BOX_PLAYER YELLOW
#define HITBOX_PLAYER RED
#define HITBOX_LIGHTATTACK BLUE
#define BOUNDING_BOX_LIGHTATTACK PURPLE
#define HITBOX_MAP PINK
#define HITBOX_FOOT WHITE
#define RESSOURCES std::string("Ressources/") +
#define BUTTON std::string("Ressources/Buttons/") +
#define ANNIMATION std::string("Ressources/Animation/") +
#define BONUS std::string("Ressources/Bonus/") +
#define CHARACTERS std::string("Ressources/Characters/") +
#define SOUND std::string("Ressources/Sound/") +
#define NARRATION std::string("Ressources/Sound/narration/") +
#define SOUNDCHAR std::string("Ressources/Sound/character/") +

namespace my_Raylib {
    class _Sound;
    class _Music;
    class _Cam;
    class _Window;
    class _Cursor;
    class _Texture2D;
    class _Text;
    class _Input;
    class _Model;
    class _Colision;
    class _Other;
    class _Mesh;
}

class my_Raylib::_Sound {
    public:
        static void Init() {
            InitAudioDevice();
        }

        static void Close() {
            CloseAudioDevice();
        }

        static Sound Load_Sound(std::string path) {
            return(LoadSound(path.c_str()));
        }

        static void Unload_Sound(Sound sound) {
            UnloadSound(sound);
        }

        static void Set_Volume(Sound sound, float volume) {
            SetSoundVolume(sound, volume);
        }

        static void Play_Sound(Sound sound) {
            PlaySound(sound);
        }

        static void Stop_Sound(Sound sound) {
            StopSound(sound);
        }
};

class my_Raylib::_Music {
    public:
        static Music Load_Music_Stream(std::string filename) {
            return (LoadMusicStream(filename.c_str()));
        }
        static void Unload_Music_Stream(Music music) {
            UnloadMusicStream(music);
        }
        static void Play_Music_Stream(Music music) {
            PlayMusicStream(music);
        }
        static bool Is_Music_Stream_Playing(Music music) {
            return (IsMusicStreamPlaying(music));
        }
        static void Stop_Music_Stream(Music music) {
            StopMusicStream(music);
        }
        static void Set_Music_Volume(Music music, float volume) {
            SetMusicVolume(music, volume);
        }
        static void Update_Music_Stream(Music music) {
            UpdateMusicStream(music);
        }
};


class my_Raylib::_Other {
    public:
        

        static void Clear_Background(Color color = Color {0,0,0,255}) {
            ClearBackground(color);
        }

        static void Draw_Grid(int slice = 10, float spacing = 1) {
            DrawGrid(slice, spacing);
        }
        static void Set_Exit_Key(int key) {
            SetExitKey(key);
        }


        static bool Compare_Vector3 (const Vector3 &v1, const Vector3 &v2) {
            return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
        }
};

class my_Raylib::_Mesh {
    public:
        static Mesh Gen_Mesh_Cube(float width, float height, float length) {
            return (GenMeshCube(width, height, length));
        }

        static BoundingBox Mesh_BoundingBox(Mesh mesh) {
            return (GetMeshBoundingBox(mesh));
        }

        static void Draw_BoundingBox(BoundingBox box, Color color = {255,255,255,255}) {
            DrawBoundingBox(box, color);
        }
};

class my_Raylib::_Colision {
    public:
        static bool Check_Collision_Point_Rec(Vector2 point, Rectangle rec) {
            return (CheckCollisionPointRec(point, rec));
        }

        static bool Check_Collision_Boxes(BoundingBox &box1, BoundingBox &box2) {
            return (CheckCollisionBoxes(box1, box2));
        }

        static bool Check_Collision_Boxes(Vector3 pos1, Vector3 size1, Vector3 pos2, Vector3 size2) {
            return (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x &&
                    pos1.y + size1.y >= pos2.y && pos1.y <= pos2.y + size2.y &&
                    pos1.z + size1.z >= pos2.z && pos1.z <= pos2.z + size2.z);

        }
};

class my_Raylib::_Model {
    public:
        static Model Load(std::string path) {
            Model model = LoadModel(path.c_str());
            return (model);
        }
        
        static void Draw(Model &model, Vector3 position, Vector3 rotation = {1, 0, 0}, float rotAngle = 0, Vector3 scale = {1,1,1}, Color tint = WHITE) {
            DrawModelEx(model, position, rotation, rotAngle, scale, tint);
        }

        static void Unload(Model &model) {
            UnloadModel(model);
        }

        static void Set_Material_Texture(Model &model, Texture2D texture, int diffuse = MAP_DIFFUSE) {
            SetMaterialTexture(&model.materials[0], diffuse, texture);
        }

        static void Draw_Cube(Vector3 pos, Vector3 size, Color color = WHITE) {
            DrawCube(pos, size.x, size.y, size.z, color);
        }

        static void Draw_Sphere(Vector3 pos, float radius, Color color = WHITE) {
            DrawSphere(pos, radius, color);
        }

        static ModelAnimation *Load_Model_Animations(std::string path, int animcount) {
            return (LoadModelAnimations(path.c_str(), &animcount));
        }

        static void Update_Model_Animation(Model &model, ModelAnimation *anims, int animFrameCounter) {
            UpdateModelAnimation(model, *anims, animFrameCounter);
        }

        static void Unload_Model_Animation(ModelAnimation &anims) {
            UnloadModelAnimation(anims);
        }
};

class my_Raylib::_Input {
    public:

        // MOUSE

        static bool Is_Mouse_Button_Pressed(int input) {
            return (IsMouseButtonPressed(input));
        }

        static bool Is_Mouse_Button_Down(int input) {
            return (IsMouseButtonDown(input));
        }
        
        static bool Is_Mouse_Button_Released(int input) {
            return (IsMouseButtonReleased(input));
        }

        static bool Is_Mouse_Button_Up(int input) {
            return (IsMouseButtonUp(input));
        }

        static Vector2 Get_Mouse_Position(void) {
            return (GetMousePosition());
        }

        // KEYBOARD

        static bool Is_Key_Pressed(int input) {
            return (IsKeyPressed(input));
        }

        static bool Is_Key_Down(int input) {
            return (IsKeyDown(input));
        }

        static bool Is_Key_Released(int input) {
            return (IsKeyReleased(input));
        }

        static bool Is_Key_Up(int input) {
            return (IsKeyUp(input));
        }

        static int Get_Key_Pressed(void) {
            return (GetKeyPressed());
        }
};

class my_Raylib::_Text {
    public:
        static void Draw_Text(std::string str, int x, int y, int fontsize, Color color) {
            DrawText(str.c_str(), x, y, fontsize, color);
        }
};


class my_Raylib::_Texture2D {
    public:
        static void Draw(Texture2D &texture, int x, int y, Color tint = Color {245, 245, 245, 255}) {
            DrawTexture(texture, x, y, tint);
        }

        static void Draw_Texture_Rec(Texture2D texture, Rectangle source, Vector2 position, Color tint) {
            DrawTextureRec(texture, source, position, tint);
        }

        static Texture2D Load(const std::string path) {
            Texture2D texture = LoadTexture(path.c_str());
            return (texture);
        }

        static void Unload(Texture2D &texture) {
            UnloadTexture(texture);
        }
};

class my_Raylib::_Cursor {
    public:
        static void Show_Cursor() {
            ShowCursor();
        }

        static void Hide_Cursor() {
            HideCursor();
        }
};

class my_Raylib::_Window {
    public:
        static void Init(const std::string &name, int Width = 1280, int Height = 720) {
            InitWindow(Width, Height, name.c_str());
        }

        static void Close() {
            CloseWindow();
        }

        static int Get_Screen_Width() {
            return (GetScreenWidth());
        }

        static int Get_Screen_Height() {
            return (GetScreenHeight());
        }

        static void Set__Icon(Image &image) {
            void SetWindowIcon(Image image);
        }

        static bool Should_Close() {
            return (WindowShouldClose());
        }

        static void Set_Target_FPS(int fps) {
            SetTargetFPS(fps);
        }
        static void Set_Window_Size(int width, int height) {
            SetWindowSize(width, height);
        }
        static void Set_Window_Position(int width, int height) {
            SetWindowPosition(width, height);
        }
};

class my_Raylib::_Cam {
    public:
        static void Set_Position(Camera &camera, const Vector3 &pos) {
            camera.position = pos;
        }

        static void Set_Target(Camera &camera, const Vector3 &pos) {
            camera.target = pos;
        }

        static void Set_Up(Camera &camera, const Vector3 &pos) {
            camera.up = pos;
        }

        static void Set_FOV(Camera &camera, const float fov = 45.0f) {
            camera.fovy = fov;
        }

        static void Set_Projection(Camera &camera, const int projection = CAMERA_PERSPECTIVE) {
            camera.projection = projection;
        }

        static void Set_Mode(Camera &camera, const int mode = CAMERA_FREE) {
            SetCameraMode(camera, mode);
        }

        static void Update(Camera &camera) {
            UpdateCamera(&camera);
        }

        static void Init_Cam(Camera &camera, const Vector3 &pos, const Vector3 &up, const int mode = CAMERA_FREE, const float fov = 45, const int projection = CAMERA_PERSPECTIVE) {
            my_Raylib::_Cam::Set_Position(camera, pos);
            my_Raylib::_Cam::Set_Up(camera, up);
            my_Raylib::_Cam::Set_FOV(camera, fov);
            my_Raylib::_Cam::Set_Projection(camera, projection);
            my_Raylib::_Cam::Set_Mode(camera, mode);
        }
};


#endif /* !RAYLIB_HPP_ */
