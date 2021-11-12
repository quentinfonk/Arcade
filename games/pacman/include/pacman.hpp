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
#include <dlfcn.h>
#include <vector>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <chrono>
#include <cstdlib>
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
    std::vector<std::string> move_pac(std::vector<std::string> map);
    std::vector<std::string> move_ghost(std::vector<std::string> map);
    std::vector<std::string> make_win();
    int game_over(IGraphicLib *glib);
    std::string str_replace_str(std::string str, std::string str2, std::string str3);
private:
    std::vector<std::pair<int, int>> fpos;
    std::vector<char> behind_ghost;
    std::pair<int, int> ppos;
    std::vector<int> fdir;
    std::vector<int> fdead;
    std::chrono::_V2::system_clock::time_point time_boost;
    bool boost;
    int pdir;
    int score;
    int ghost;
    bool my_exit;
    float speed;
};

#endif /* !PACMAN_HPP_ */
