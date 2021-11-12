/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "nibbler.hpp"
#include <dlfcn.h>
#include <vector>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <chrono>

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
    glib->clearWindow();
    this->ppos.first = 22;
    this->ppos.second = 18;
    this->pdir = 0;
    this->score = 0;
    gameLoop(glib);
}

std::vector<std::string> Game::load_map(std::string path)
{
    std::vector<std::string> map;
    std::string line = "";
    std::ifstream file(path);
    char c;
    size_t i = 0;
    int j = 0;

    if (file) {
        while (file.get(c)) {
            line += c;
            if (c == '\n') {
                map.push_back(line);
                i++;
                j = 0;
                line = "";
            }   
            j++;
        }
    } else {
        std::cerr << "load_map: wrong path to map : \"" << path << "\"" << std::endl;
    }
    map.push_back(line); // ca prenais pas la derniere ligne
    return (map);
}

void Game::gest_exit(IGraphicLib *glib, int input)
{
    if (input == 'q') {
        glib->exit_lib();
        exit(0);
    }
}

std::string str_replace_str(std::string str, std::string str2, std::string str3)
{
    size_t a = 0;
    size_t b = 0;
    int x = 0;
    std::string str4 = "";

    while (a != str.size()) {
        b = 0;
        if (str[a] == str2[0]) {
            while (b != str2.size()) {
                x++;
                if (str[a] != str2[b]) {
                    b = str2.size();
                    str4 = str4 + str2[0];
                    a = ((a - x) + 1);
                }
                else {
                    a++;
                    b++;
                    if (b == str2.size()) {
                        str4 = str4 + str3;
                        a = a - 1;
                    }
                }
            }
        }
        x = 0;
        if (b == 0)
            str4 = str4 + str[a];
        a++;
    }
    return str4;
}

void Game::gest_input(IGraphicLib *glib, int input, std::vector<std::string> map)
{
    if (input == 259) 
        this->pdir = 0;
    if (input == 261)
        this->pdir = 1;
    if (input == 258)
        this->pdir = 2;
    if (input == 260) 
        this->pdir = 3;
}

std::vector<std::string> Game::move_nib(IGraphicLib *glib, int input, std::vector<std::string> map)
{
    std::vector<std::string> map_temp = map;
    int w = 0;

    printf("%d\n", this->pdir);
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "🐍", "P ");
        map_temp[i] = str_replace_str(map_temp[i], "🍎", "* ");
    }
    if(this->pdir == 3 and map_temp[this->ppos.second][this->ppos.first - 2] == '*') {  
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first - 2] = 'P';
        this->ppos.first = this->ppos.first - 2;
        map_temp[this->ppos.second][this->ppos.first - 2] == ' ';
        this->score = this->score + 1;
    } else if(this->pdir == 3 and map_temp[this->ppos.second][this->ppos.first - 2] == ' ') { 
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first - 2] = 'P';
        this->ppos.first = this->ppos.first - 2;
    }
    if (this->pdir == 0 and map_temp[this->ppos.second - 1][this->ppos.first] == '*' and map_temp[this->ppos.second - 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second - 1][this->ppos.first] = 'P'; 
        map_temp[this->ppos.second - 1][this->ppos.first] == ' ';
        this->ppos.second = this->ppos.second -1;
        this->score = this->score + 1;
    } else if(this->pdir == 0 and map_temp[this->ppos.second - 1][this->ppos.first] == ' ' and map_temp[this->ppos.second - 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second - 1][this->ppos.first] = 'P'; 
        this->ppos.second = this->ppos.second -1;
    }
    if (this->pdir == 1 and map_temp[this->ppos.second][this->ppos.first + 2] == '*') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first + 2] = 'P';
        this->ppos.first = this->ppos.first + 2;
        map_temp[this->ppos.second][this->ppos.first + 2] == ' ';
        this->score = this->score + 1;
    } else if (this->pdir == 1 and map_temp[this->ppos.second][this->ppos.first + 2] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second][this->ppos.first + 2] = 'P';
        this->ppos.first = this->ppos.first + 2;
    }
    if (this->pdir == 2 and map_temp[this->ppos.second + 1][this->ppos.first] == '*' and map_temp[this->ppos.second + 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second + 1][this->ppos.first] = 'P';
        this->ppos.second = this->ppos.second + 1;
        map_temp[this->ppos.second + 1][this->ppos.first] == ' ';
        this->score = this->score + 1;
    } else if(this->pdir == 2 and map_temp[this->ppos.second + 1][this->ppos.first] == ' ' and map_temp[this->ppos.second + 1][this->ppos.first + 1] == ' ') {
        map_temp[this->ppos.second][this->ppos.first] = ' ';
        map_temp[this->ppos.second + 1][this->ppos.first] = 'P';
        this->ppos.second = this->ppos.second + 1;
    }
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "P ", "🐍");
        map_temp[i] = str_replace_str(map_temp[i], "* ", "🍎");
    }
    return map_temp;
}

int Game::gameLoop(IGraphicLib *glib)
{
    int input = -1;
    auto pmove = std::chrono::high_resolution_clock::now();
    auto refresh = std::chrono::high_resolution_clock::now();
    std::vector<std::string> map_menu = this->load_map("assets/nibbler/maps/map.txt");

    while (1) {
        input = glib->keyPressed();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - refresh).count() > 10000000) {
            glib->clearWindow();
            glib->printMap(map_menu);
            if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - pmove).count() > 150000000) {
                map_menu = move_nib(glib, input, map_menu);
                pmove = std::chrono::high_resolution_clock::now();
            }
            glib->refreshWindow();
            refresh = std::chrono::high_resolution_clock::now();
        }
        this->gest_exit(glib, input);
        this->gest_input(glib, input, map_menu);
    }
    (void)glib;
}
