/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** Game
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include "IGame.hpp"
#include "IGraphicLib.hpp"

class Game : public IGame
{
private:
    /* data */
public:
    Game();
    ~Game();
    virtual void launchMenu(IGraphicLib *glib);
    virtual int launchGame(IGraphicLib *glib);
    virtual int gameLoop(IGraphicLib *glib);
};


#endif /* !PACMAN_HPP_ */
