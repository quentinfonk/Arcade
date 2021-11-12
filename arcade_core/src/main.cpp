/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "arcade.hpp"

int main(int ac, char **av)
{
    IGraphicLib *lib = NULL;
    Arcade arcade;
    if (ac != 2)
        return (84);
    lib = arcade.open_lib(av[1]);
    if (lib == NULL)
        return (84);
    lib->assetLoader("assets/arcade");
    lib->init_lib();
    arcade.launch_menu(lib);
    return (0);
}
