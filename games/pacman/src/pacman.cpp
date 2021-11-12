/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "pacman.hpp"


extern "C"
{
    Game *MakeGame()
    {
        return new Game();
    }
}

Game::Game(/* args */)
{
}

Game::~Game()
{
}

void Game::launchMenu(IGraphicLib *glib)
{
    (void)glib;
}

int Game::launchGame(IGraphicLib *glib)
{
    (void)glib;
}

int Game::gameLoop(IGraphicLib *glib)
{
    (void)glib;
}
