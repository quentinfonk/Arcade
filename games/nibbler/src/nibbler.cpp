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
    std::pair<int, int> value;

    glib->clearWindow();
    value.first = 22;
    value.second = 17;
    this->npos.push_back(value);
    value.first = 20;
    value.second = 17;
    this->npos.push_back(value);
    value.first = 18;
    value.second = 17;
    this->npos.push_back(value);
    value.first = 16;
    value.second = 17;
    this->npos.push_back(value);
    this->pdir = 0;
    this->score = 0;
    this->nb_snake = 4;
    this->speed = 1;
    this->level = 1;
    return (gameLoop(glib));
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
    map.push_back(line);
    return (map);
}

void Game::gest_exit(IGraphicLib *glib, int input)
{
    if (input == 'q') {
        glib->exit_lib();
        std::exit(0);
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

void Game::gest_input(int input)
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

int Game::game_over(IGraphicLib *glib)
{
    glib->clearWindow();
    glib->printSelectedButton(20, 15, "Game Over");
    glib->printSelectedButton(17, 20, "Your score : " + std::to_string(this->score));
    glib->refreshWindow();
    sleep(3);
    return (this->score);
}

std::vector<std::string> Game::add_snake(std::vector<std::string> map, std::pair<int, int> prev, int b)
{
    std::pair<int, int> stock;

    if (map[this->npos[0].second][this->npos[0].first+2] != ' ' and map[this->npos[0].second-1][this->npos[0].first] != ' ' and map[this->npos[0].second+1][this->npos[0].first] != ' ' and map[this->npos[0].second][this->npos[0].first-2] != ' ') {
        if (map[this->npos[0].second][this->npos[0].first+2] != '*' and map[this->npos[0].second-1][this->npos[0].first] != '*' and map[this->npos[0].second+1][this->npos[0].first] != '*' and map[this->npos[0].second][this->npos[0].first-2] != '*') {
            map[0][0] = 'O';
            return (map);
        }
    }
    for (int a = 1; this->nb_snake != a; a++) {
        if (this->npos[0] != prev) {
            map[this->npos[a].second][this->npos[a].first] = ' ';
            stock = this->npos[a];
            this->npos[a] = prev;
            prev = stock;
            map[this->npos[a].second][this->npos[a].first] = 'P';
        }
    }
    if (b == 0)
        return (map);
    if (this->pdir >= 0 and this->pdir <= 3) {
        map[prev.second][prev.first] = 'P';
             this->npos.push_back(prev);
             this->nb_snake++;
    }
    return (map);
}

std::vector<std::string> Game::move_nib(std::vector<std::string> map)
{
    std::vector<std::string> map_temp = map;
    std::pair<int, int> prev = {this->npos[0]};

    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "🐍", "P ");
        map_temp[i] = str_replace_str(map_temp[i], "🍎", "* ");
        map_temp[i] = str_replace_str(map_temp[i], "█", "W");
    }
    if(this->pdir == 3 and map_temp[this->npos[0].second][this->npos[0].first - 2] == '*') {  
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second][this->npos[0].first - 2] = 'P';
        this->npos[0].first = this->npos[0].first - 2;
        this->score = this->score + 1;
        map_temp = add_snake(map_temp, prev, 1);
    } else if(this->pdir == 3 and map_temp[this->npos[0].second][this->npos[0].first - 2] == ' ') { 
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second][this->npos[0].first - 2] = 'P';
        this->npos[0].first = this->npos[0].first - 2;
    }
    if (this->pdir == 0 and map_temp[this->npos[0].second - 1][this->npos[0].first] == '*' and map_temp[this->npos[0].second - 1][this->npos[0].first + 1] == ' ') {
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second - 1][this->npos[0].first] = 'P'; 
        this->npos[0].second = this->npos[0].second -1;
        this->score = this->score + 1;
        map_temp = add_snake(map_temp, prev, 1);
    } else if(this->pdir == 0 and map_temp[this->npos[0].second - 1][this->npos[0].first] == ' ' and map_temp[this->npos[0].second - 1][this->npos[0].first + 1] == ' ') {
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second - 1][this->npos[0].first] = 'P'; 
        this->npos[0].second = this->npos[0].second -1;
    }
    if (this->pdir == 1 and map_temp[this->npos[0].second][this->npos[0].first + 2] == '*') {
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second][this->npos[0].first + 2] = 'P';
        this->npos[0].first = this->npos[0].first + 2;
        this->score = this->score + 1;
        map_temp = add_snake(map_temp, prev, 1);
    } else if (this->pdir == 1 and map_temp[this->npos[0].second][this->npos[0].first + 2] == ' ') {
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second][this->npos[0].first + 2] = 'P';
        this->npos[0].first = this->npos[0].first + 2;
    }
    if (this->pdir == 2 and map_temp[this->npos[0].second + 1][this->npos[0].first] == '*' and map_temp[this->npos[0].second + 1][this->npos[0].first + 1] == ' ') {
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second + 1][this->npos[0].first] = 'P';
        this->npos[0].second = this->npos[0].second + 1;
        this->score = this->score + 1;
        map_temp = add_snake(map_temp, prev, 1);
    } else if(this->pdir == 2 and map_temp[this->npos[0].second + 1][this->npos[0].first] == ' ' and map_temp[this->npos[0].second + 1][this->npos[0].first + 1] == ' ') {
        map_temp[this->npos[0].second][this->npos[0].first] = ' ';
        map_temp[this->npos[0].second + 1][this->npos[0].first] = 'P';
        this->npos[0].second = this->npos[0].second + 1;
    }
    map_temp = add_snake(map_temp, prev, 0);
    for (size_t i = 0; i != map_temp.size(); i++) {
        map_temp[i] = str_replace_str(map_temp[i], "P ", "🐍");
        map_temp[i] = str_replace_str(map_temp[i], "* ", "🍎");
        map_temp[i] = str_replace_str(map_temp[i], "WW", "██");

    }
    return map_temp;
}

std::vector<std::string> Game::make_win(IGraphicLib *glib)
{
    std::pair<int, int> value;

    this->npos.clear();
    glib->clearWindow();
    value.first = 22;
    value.second = 17;
    this->npos.push_back(value);
    value.first = 20;
    value.second = 17;
    this->npos.push_back(value);
    value.first = 18;
    value.second = 17;
    this->npos.push_back(value);
    value.first = 16;
    value.second = 17;
    this->npos.push_back(value);
    this->pdir = 0;
    this->nb_snake = 4;
    this->speed += 2;
    std::vector<std::string> map_menu = this->load_map("assets/nibbler/maps/map.txt");
    this->level += 1;
    return (map_menu);
}

int Game::gameLoop(IGraphicLib *glib)
{
    int input = -1;
    auto pmove = std::chrono::high_resolution_clock::now();
    auto refresh = std::chrono::high_resolution_clock::now();
    std::vector<std::string> map_menu = this->load_map("assets/nibbler/maps/map.txt");
    std::string affich_score;

    while (1) {
        input = glib->keyPressed();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - refresh).count() > (10000000 / this->speed)) {
            glib->clearWindow();
            glib->printMap(map_menu);
            glib->printSelectedButton(50, 0, affich_score);
            if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - pmove).count() > (150000000 / this->speed)) {
                map_menu = move_nib(map_menu);
                if (map_menu[0][0] == 'O')
                    return (this->game_over(glib));
                if (this->score == (31 * this->level))
                    map_menu = make_win(glib);
                auto s = std::to_string(this->score);
                affich_score = "Score : " + s;
                pmove = std::chrono::high_resolution_clock::now();
            }
            glib->refreshWindow();
            refresh = std::chrono::high_resolution_clock::now();
        }
        this->gest_exit(glib, input);
        this->gest_input(input);
    }
    (void)glib;
}
