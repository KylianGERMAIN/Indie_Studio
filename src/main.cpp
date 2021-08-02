/*
** EPITECH PROJECT, 2021
** Indiestduio
** File description:
** main
*/

#include <iostream>
#include "Game_Master.hpp"

int main(int argc, char **argv)
{
    int menu;

    if (argv[1])
        menu = atoi(argv[1]);
    else
        menu = -1;
    try {
        std::unique_ptr<Game_Master> gameMaster (new Game_Master(menu));
    }
    catch (const std::exception &execpt){
        std::cout << execpt.what() << std::endl;
        return (84);
    }
    return 0;
}