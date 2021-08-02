/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-kylian.germain
** File description:
** gm_inGame
*/

#include "Game_Master.hpp"

int Game_Master::GameLoop()
{
    init_Players(2);
    SetVariable();

    my_Raylib::_Cursor::Hide_Cursor();
    Game_Introduction();
    while (!my_Raylib::_Window::Should_Close()) {
        if (my_Raylib::_Input::Is_Key_Down(KEY_ESCAPE)) {
            my_Raylib::_Cursor::Show_Cursor();
            MenuPause();
            my_Raylib::_Cursor::Hide_Cursor();
        } else if (my_Raylib::_Input::Is_Key_Pressed(KEY_U))        
            drawDebug = !drawDebug;
        else if (my_Raylib::_Input::Is_Key_Pressed(KEY_I))
            for (int i = 0; Players.size() > i; i++)
                Players[i]->Set_Fly(!Players[i]->Get_Fly());
        Movement_Players_Gestion();
        Win_Condition();
        if (menu != 10)  {
            Clear_All();
            my_Raylib::_Cursor::Show_Cursor();
            return menu;
        }
        BeginDrawing();
            my_Raylib::_Other::Clear_Background(RAYWHITE);
            Draw_UI();
            BeginMode3D(camera->Get());
                Draw_Assets();
                drawDeathParticles();
            EndMode3D();
        EndDrawing();
    }
    Clear_All();
    return (404);
}

void Game_Master::Movement_Players_Gestion()
{
    Actualise_Players_Grounded();
    Move_Players();
    Actualise_Players();
    Dead_Players();
    CheckHit();
    Take_Bonus();    
}

void Game_Master::CheckHit()
{
    for (int i = 0; i < Players.size(); i++)
      Players[i]->Check_Punch(Players);  
}

void Game_Master::Take_Bonus()
{
    for (int i = 0; i < Players.size(); i++)
        if (Players[i]->Check_Collision_With(*bonus))
            bonus->Effect(*Players[i]);
}

void Game_Master::Win_Condition()
{
    int tempJump = 0;
    int tempPunch = 0;
    for (int i = 0; i < Players.size(); i++) {
        if (Players[i]->Get_Life() == 0)
            menu = 12;
        tempJump += Players[i]->Get_nbJump();
        tempPunch += Players[i]->Get_nbPunch();
    }
}

void Game_Master::Actualise_Players_Grounded()
{
    Actualise_Grounded(*bonus);
    for (int i = 0; i < Players.size(); i++)
        Actualise_Grounded(*Players[i]);
}

void Game_Master::Actualise_Players()
{
    bonus->Actualise();
    for (int i = 0; i < Players.size(); i++)
        Players[i]->Actualise(volumeEffect);
}

void Game_Master::Move_Players()
{
    for (int i = 0; i < Players.size(); i++)
        Players[i]->Move(*my_map->Get_Platforms()[0]);
}

void Game_Master::Dead_Players()
{
    for (int i = 0; i < Players.size(); i++)
        if (Players[i]->Get_Position().y <= -230) {
            deathParticles.push_back(createDeathParticles(Players[i]->Get_Position()));
            Players[i]->Dead();
        }

}

void Game_Master::Actualise_Grounded(Model3D &model)
{
    model.Set_Grounded(false);
    for (int i = 0; i < my_map->Get_Platforms().size(); i++)
        model.Check_Grounded(*my_map->Get_Platforms()[i]);
    if (!model.Get_Grounded())
        model.Fall();
}