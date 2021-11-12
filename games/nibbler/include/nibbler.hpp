/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** centipede
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <iostream>
#include "IGame.hpp"
#include "IGraphicLib.hpp"

class Game : public IGame
{
public:
    Game();
    ~Game();
    virtual void launchMenu(IGraphicLib *glib);
    virtual int launchGame(IGraphicLib *glib);
    virtual int gameLoop(IGraphicLib *glib);
    std::vector<std::string> load_map(std::string path);
    void gest_exit(IGraphicLib *glib, int input);
    void gest_input(IGraphicLib *glib, int input, std::vector<std::string> map);
    std::vector<std::string> move_nib(IGraphicLib *glib, int input, std::vector<std::string> map);
private:
    std::pair<int, int> ppos;
    int pdir;
    int score;
};

#endif /* !NIBBLER_HPP_ */
