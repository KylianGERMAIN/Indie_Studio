/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** Game_Master
*/

#include "Game_Master.hpp"
#include "Camera.hpp"

Game_Master::Game_Master(float newmenu)
{
    menu = newmenu;
    camera = std::shared_ptr<_Cam> (new _Cam("Camera"));
    my_Raylib::_Window::Init("IndieStudio", 1280, 720);
    my_Raylib::_Other::Set_Exit_Key(0);

    if (menu != -1)
        Init_Menu();
    Gameloop();
}

void Game_Master::Init_Menu()
{
    std::vector<float> sound;
    menu_personalisation.Init_Object();
    menu_interface.Init_Object();
    menu_pause.Init_Object();
    menu_setting.Init_Object();

    sound = menu_setting.readInFile();
    if (sound.size() == 2) {
        volumeEffect = sound[0];
        volumeMusic = sound[1];
    }
    menu_personalisation.Update_sound(volumeMusic, volumeEffect);
    menu_interface.Update_sound(volumeMusic, volumeEffect);
    menu_pause.Update_sound(volumeMusic, volumeEffect);
    menu_setting.Update_sound(volumeMusic, volumeEffect);
    menu_setting.initSliders();
}

void Game_Master::SetVariable()
{
    Background = new Displayable("Background", position, position, RESSOURCES "fond.png");
    if (Background->Get_Texture().id <= 0)
        throw std::runtime_error("BAD PATH");
    my_map = new Map(RESSOURCES "platform_cloud.gltf", RESSOURCES "GrandePlateforme.png", RESSOURCES "little_platform.gltf", "Ressources/PetitePlateforme.png");
    bonus = new Bonus("test", type::invincible, {0, 100, 0}, {0, 0, 0}, BONUS "plus_attack.gltf");
}

int Game_Master::MenuPause()
{
    menu = menu_pause.Loop(volumeMusic, volumeEffect);
    while (menu != 1 && menu != 404 && menu != 10) {
        int i = 0;
        i = menu_setting.Loop(volumeMusic, volumeEffect);
        volumeEffect = menu_setting.getVolumeEffect();
        volumeMusic = menu_setting.getVolumeMusic();
        menu_setting.writeInFile();
        if (i == 1)
            menu = menu_pause.Loop(volumeMusic, volumeEffect);
    }
    if (menu != 1 && menu != 404)
        menu = 10;
    return menu;
}

void Game_Master::init_Players(const int nbPlayers)
{
    for (int i = 0; i < nbPlayers; i++) {
        float offset_z = i * 20;
        Vector3 pos = {0,50, offset_z};
        std::string name = "Player_" + std::to_string(i + 1);
        Players.push_back(new Player(name, i + 1, pos, {0,0,0}, CHARACTERS "personnage.iqm", "Ressources/Characters/Blue_Skin.png", 0, life, nbJump, gravity, speed));
    }
}

void Game_Master::Unload_Players()
{
    for (int i = 0; i < Players.size(); i++)
        delete(Players[i]);      
    Players.clear();
}

DeathParticles Game_Master::createDeathParticles(Vector3 pos)
{
    DeathParticles tmp;
    float max;
    Color color;
    unsigned char red;
    unsigned char y;

    tmp.gross = true;
    for (int i = 0; i < 100; i++) {
        max = 100 % (i + 1);
        red = 255 - i;
        y = i;
        color = {red, y, 0,255};
        tmp.particles.push_back({-1, 0, max, true, color, {pos.x, pos.y + i, pos.z}});
    }
    return tmp;
}


void Game_Master::Clear_All()
{
    if (my_map != NULL)
        delete my_map;
    if (Background != NULL)
        delete Background;
    if (bonus != NULL)
        delete bonus;
}

void Game_Master::Game_Introduction()
{
    std::vector<Sound> sounds;
    sounds.push_back(my_Raylib::_Sound::Load_Sound(SOUND "se_menu_watchfull_rise_crowd_ll.wav"));
    sounds.push_back(my_Raylib::_Sound::Load_Sound(SOUND "narration/one.wav"));
    sounds.push_back(my_Raylib::_Sound::Load_Sound(SOUND "narration/two.wav"));
    sounds.push_back(my_Raylib::_Sound::Load_Sound(SOUND "narration/three.wav"));
    for (Sound &sound : sounds)
        my_Raylib::_Sound::Set_Volume(sound, volumeEffect);

    my_Raylib::_Sound::Play_Sound(sounds[0]);
    camera->Set_Position({0,40,0});
    camera->Set_Up(camera->Get_saveUp());
    while (!my_Raylib::_Window::Should_Close()) {
        camera->Add_Position({0.8,0,0});
        BeginDrawing();
            my_Raylib::_Other::Clear_Background(RAYWHITE);
            Background->Draw_Texture();
            BeginMode3D(camera->Get());
                Draw_Assets();
            EndMode3D();
        EndDrawing();
        if (camera->Get_Position().x >= camera->Get_savePos().x)
            break;
    }
    camera->Set_Position(camera->Get_savePos());
    CountDown_Intro(sounds);
    for (Sound &sound : sounds)
        my_Raylib::_Sound::Unload_Sound(sound);
    sounds.clear();
}

void Game_Master::Actualise_Camera_Pres(int &nbTrav, Traveling &actualTrav, bool &change, int &newTrav, std::vector<Traveling> &allTrav)
{
    switch (nbTrav) {
        case 0:
            camera->Set_Up({0,actualTrav.upStart.y, camera->Get_Position().z});
            if (camera->Get_Position().z > actualTrav.posEnd.z)
                change = true;
            break;
        case 1:
            if (camera->Get_Position().z < actualTrav.posEnd.z && camera->Get_Position().y < actualTrav.posEnd.y)
                change = true;
            break;
        case 2:
            if (camera->Get_Position().y > actualTrav.posEnd.y)
                change = true;
            break;
        default:
            break;
    }
    if (change) {
        while (newTrav == nbTrav)
            newTrav = rand() %allTrav.size();
        nbTrav = newTrav;
        actualTrav = allTrav[nbTrav];
        camera->Set_Position(actualTrav.posStart);
        camera->Set_Up(actualTrav.upStart);
        change = false;
    }
}

void Game_Master::Delete_Menu()
{
    menu_interface.Delete_Object();
    menu_pause.Delete_Object();
    menu_setting.Delete_Object();
    menu_personalisation.Delete_Object();
}

bool Game_Master::waitLeave()
{
    static Sound soundLeave = my_Raylib::_Sound::Load_Sound(SOUND "PushStart.wav");
    static bool isStart = true;

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    static std::chrono::duration<double> elapsed_seconds = end - start;

    if (isStart)
        my_Raylib::_Sound::Set_Volume(soundLeave, volumeEffect);

    if (my_Raylib::_Input::Is_Key_Pressed(KEY_SPACE)) {
        menu = 1;
        my_Raylib::_Sound::Play_Sound(soundLeave);
        start = std::chrono::system_clock::now();
        end = std::chrono::system_clock::now();
        while ((elapsed_seconds = end - start).count() < 1) {
            end = std::chrono::system_clock::now();
        };
        my_Raylib::_Sound::Unload_Sound(soundLeave);
        return true;
    }
    return false;
}

void Game_Master::Menu_Pres()
{
    SetVariable();
    bool change = false;
    Traveling actualTrav;
    std::vector<Traveling> allTrav = create_Trav();
    int nbTrav = rand() %allTrav.size();
    int newTrav = nbTrav;
    float pos_H = my_Raylib::_Window::Get_Screen_Height() / 1.15;
    float pos_W = my_Raylib::_Window::Get_Screen_Width() / 2;
    actualTrav = allTrav[nbTrav];
    Music _Music = my_Raylib::_Music::Load_Music_Stream(SOUND + "menu-start.mp3");
    my_Raylib::_Music::Play_Music_Stream(_Music);
    my_Raylib::_Music::Set_Music_Volume(_Music, volumeMusic);

    camera->Set_Position(actualTrav.posStart);
    camera->Set_Up(actualTrav.upStart);
    while (!my_Raylib::_Window::Should_Close()) {
        my_Raylib::_Music::Update_Music_Stream(_Music);
        if (my_Raylib::_Music::Is_Music_Stream_Playing(_Music) == false)
            my_Raylib::_Music::Play_Music_Stream(_Music);
        my_Raylib::_Other::Clear_Background(RAYWHITE);
        camera->Add_Position(actualTrav.posRate);
        camera->add_Up(actualTrav.upRate);
        BeginDrawing();
            Background->Draw_Texture();
            BeginMode3D(camera->Get());
                Draw_Assets();
            EndMode3D();
            std::string str = "Press space to start";
            my_Raylib::_Text::Draw_Text(str, pos_W - (str.size() * 5), pos_H, 20, DARKGRAY);
            if (waitLeave())
                break;
        EndDrawing();
        Actualise_Camera_Pres(nbTrav, actualTrav, change, newTrav, allTrav);
    }
    my_Raylib::_Music::Unload_Music_Stream(_Music);
    Clear_All();
}

void Game_Master::Draw()
{
    if (menu == SPLASH_SCREEN) {
        menu = splash_screen.Loop();
        Init_Menu();
    }
    if (menu == MENU_PRE) {
        Menu_Pres();
        menu = 1;
    }
    else if (menu == MENU_MENU)
        menu = menu_interface.Loop(volumeMusic, volumeEffect);
    else if (menu == MENU_SETTINGS) {
        menu = menu_setting.Loop(volumeMusic, volumeEffect);
        volumeEffect = menu_setting.getVolumeEffect();
        volumeMusic = menu_setting.getVolumeMusic();
        menu_setting.writeInFile();
    }
    else if (menu == MENU_PAUSE) {
        menu = menu_pause.Loop(volumeMusic, volumeEffect);
        if (menu == MENU_SETTINGS) {
            int i = 0;
            i = menu_setting.Loop(volumeMusic, volumeEffect);
            volumeEffect = menu_setting.getVolumeEffect();
            volumeMusic = menu_setting.getVolumeMusic();
            menu_setting.writeInFile();
            if (i ==  1)
                menu = MENU_PAUSE;
        }
        if (menu == MENU_GAME)
            menu = MENU_REAL_TOURNAMENT;
    }
    else if (menu == MENU_PERSONALISATION) {
        menu = menu_personalisation.Loop(volumeMusic, volumeEffect);
        gravity = menu_personalisation.getGravity();
        speed = menu_personalisation.getSpeed();
        life = menu_personalisation.getLife();
        nbJump = menu_personalisation.getJump();
    }
    else if (menu == MENU_GAME) {
        menu = GameLoop();
        if (menu != MENU_END)
            Unload_Players();
    }
    else if (menu == MENU_END) {
        end.Init_Object(Players);
        menu = end.Loop(volumeMusic, volumeEffect);
        Unload_Players();
        end.Delete_Object();
    }
}

void Game_Master::Gameloop()
{
    camera->Init({75, 40, 0}, {0, 40, 0}, CAMERA_PERSPECTIVE, 0);
    camera->Set_FOV(90);
    my_Raylib::_Window::Set_Target_FPS(60);
    my_Raylib::_Sound::Init();
    while (!my_Raylib::_Window::Should_Close())
    {
        
        camera->Update();
        if (menu >= 404)
            break;  
        Draw();
    }
    Delete_Menu();
    my_Raylib::_Sound::Close();
    my_Raylib::_Window::Close();
}

Game_Master::~Game_Master()
{
}