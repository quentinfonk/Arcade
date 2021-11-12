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
#include <unistd.h>

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
    void gest_input(int input);
    std::vector<std::string> move_nib(std::vector<std::string> map);
    std::vector<std::string> add_snake(std::vector<std::string> map, std::pair<int, int> prev, int a);
    int game_over(IGraphicLib *glib);
    std::vector<std::string> make_win(IGraphicLib *glib);
private:
    std::vector<std::pair<int, int>> npos;
    int pdir;
    int score;
    int nb_snake;
    int speed;
    int level;
};

#endif /* !NIBBLER_HPP_ */
