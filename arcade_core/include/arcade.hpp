/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <dlfcn.h>
#include <iostream>
#include "IGraphicLib.hpp"
#include <vector>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <chrono>

#define ARROW_DOWN 258
#define ARROW_UP 259
#define ARROW_LEFT 260
#define ARROW_RIGHT 261
#define KEY_DEL 263
#define ENTER_KEY 10

class Arcade
{
public:
    Arcade();
    ~Arcade();

    void get_shared_libs();
    void launch_menu(IGraphicLib *glib);
    std::vector<std::string> load_map(std::string path);
    void gest_input(IGraphicLib *glib, int input);
    void gest_bouton(int input);
    void print_bouton(IGraphicLib *glib);
    void print_leaderboard(IGraphicLib *glib);
    void init_bouton();
    std::string get_logo(std::string name);
    void gest_name(int input);
    IGraphicLib *switch_lib(IGraphicLib *glib, int input);
    IGraphicLib *open_lib(const char *lib_name);

private:
    std::vector<std::string> games;
    std::vector<std::string> libs;
    std::vector<std::vector<std::pair<bool, std::string>>> bouton;
    std::string player_name;
    void *handle;
};




#endif /* !CORE_HPP_ */
