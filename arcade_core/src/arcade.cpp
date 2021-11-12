/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** arcade
*/

#include "arcade.hpp"

Arcade::Arcade()
{
    get_shared_libs();
    this->player_name = "";
    this->my_exit = false;
}

Arcade::~Arcade()
{
}

IGraphicLib *Arcade::open_lib(const char *lib_name)
{
    MakerLib pMaker;
    this->handle = dlopen(lib_name, RTLD_LAZY);
    if(this->handle == NULL) {
        std::cerr << "dlopen : "<< dlerror() << std::endl; 
        std::exit(84);
    }
    void *mkr = dlsym(this->handle, "MakeGraphicLib");
    IGraphicLib *lib = NULL;
    if (mkr == NULL) {
        std::cerr << "dlsym : " << dlerror() << std::endl;
        std::exit(84);
    }
    pMaker = (MakerLib)mkr;
    lib = pMaker();
    return (lib);
}

IGame *Arcade::open_lib_game(const char *lib_name)
{
    MakerGame pMaker;
    this->game_handle = dlopen(lib_name, RTLD_LAZY);
    if(this->game_handle == NULL) {
        std::cerr << "dlopen : "<< dlerror() << std::endl; 
        std::exit(84);
    }
    void *mkr = dlsym(this->game_handle, "MakeGame");
    IGame *lib = NULL;
    if (mkr == NULL) {
        std::cerr << "dlsym : " << dlerror() << std::endl;
        std::exit(84);
    }
    pMaker = (MakerGame)mkr;
    lib = pMaker();
    return (lib);
}

void Arcade::get_shared_libs()
{
    DIR *rep = opendir("lib/");
    std::vector<std::string> shared_libs;
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".so") != NULL) {
                std::string mystring = std::string(ent->d_name);
                shared_libs.push_back("lib/" + mystring);
            }
        }
        closedir(rep);
    }
    void *handle = NULL;
    void *mkr = NULL;
    for (size_t i = 0 ; i != shared_libs.size() ; i++) {
        handle = dlopen(shared_libs[i].c_str(), RTLD_LAZY);
        if (handle != NULL) {
            mkr = dlsym(handle, "MakeGraphicLib");
            if (mkr != NULL)
                this->libs.push_back(shared_libs[i]);
            mkr = dlsym(handle, "MakeGame");
            if (mkr != NULL)
                this->games.push_back(shared_libs[i]);
        }
    }
}

void Arcade::launch_menu(IGraphicLib *glib)
{
    std::vector<std::string> map_menu = this->load_map("assets/arcade/maps/menu.txt");
    auto refresh = std::chrono::high_resolution_clock::now();
    int input = -1;

    this->init_bouton();
    while (1) {
        this->launch_game(glib, input);
        if (this->my_exit == true)
            return;
        glib = this->switch_lib(glib, input);
        if (this->my_exit == true)
            return;
        input = glib->keyPressed();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - refresh).count() > 10000000) {
            glib->clearWindow();
            glib->printMap(map_menu);
            this->print_bouton(glib);
            glib->printText(44, 1, "🎮 Arcade 🎮");
            glib->printText(2, 3, "💻 Librairies 💻");
            glib->printText(24, 3, "👾 Games 👾");
            glib->printText(61, 3, "🏆 Leaderboard 🏆");
            this->print_leaderboard(glib);
            glib->refreshWindow();
            refresh = std::chrono::high_resolution_clock::now();
        }
        this->gest_name(input);
        this->gest_bouton(input);
        this->gest_input(glib, input);
        if (this->my_exit == true)
            return;
    }
}

void Arcade::gest_leaderboard(std::string path, std::string name, int score)
{
    std::multimap<int, std::string> board;
    std::ifstream file(path + "/leaderboard");
    std::string line = "";
    char c;
    int i = 0;

    board.insert({score * -1, name});
    name = "";
    if (file) {
        while (file.get(c)) {
            if (c == '|') {
                name = line;
                line = "";
                continue;
            }
            if (c == '\n') {
                board.insert({std::stoi(line) * -1, name});
                line = "";
                continue;
            }
            line += c;
        }
    }
    std::ofstream flux(path + "/leaderboard");

    if (flux) {
        for (auto m = board.begin() ; m != board.end() && i != 3 ; m++) {
            flux << m->second << "|" << m->first * -1 << std::endl;
            i++;
        }
    }
}

void Arcade::launch_game(IGraphicLib *glib, int input)
{
    if (input != 10)
        return;
    IGame *game = NULL;
    int score = 0;
    for (size_t i = 0 ; i != this->bouton[1].size() ; i++) {
        if (this->bouton[1][i].first == 1) {
            game = this->open_lib_game(this->games[i].c_str());
            glib->assetLoader("assets/" + this->games[i].substr(11, this->games[i].find(".so") - 11));
            score = game->launchGame(glib);
            dlclose(this->game_handle);
            delete (game);
            if (score == -2 || this->player_name == "")
                return;
            if (score == -1) {
                glib->exit_lib();
                this->my_exit = true;
                return;
            }
            this->gest_leaderboard("assets/" + this->games[i].substr(11, this->games[i].find(".so") - 11), this->player_name, score);
            return;
        }
    }
}

IGraphicLib *Arcade::switch_lib(IGraphicLib *glib, int input)
{
    if (input != 10)
        return (glib);
    for (size_t i = 0 ; i != this->bouton[0].size() ; i++) {
        if (this->bouton[0][i].first == 1) {
            glib->exit_lib();
            delete (glib);
            dlclose(this->handle);
            glib = open_lib(this->libs[i].c_str());
            glib->init_lib();
            glib->assetLoader("assets/arcade");
            return (glib);
        }
    }
    return (glib);
}

void Arcade::gest_input(IGraphicLib *glib, int input)
{
    if (input == 'q' && this->bouton[2][0].first != 1) {
        glib->exit_lib();
        this->my_exit = true;
    }
}

std::vector<std::string> Arcade::load_map(std::string path)
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
    return (map);
}

void Arcade::gest_name(int input)
{
    std::string your_name = "Your name:            ";
    if (this->bouton[2][0].first == 1) {
        if (this->player_name.size() <= 10 && input >= 32 && input <= 126)
            this->player_name += input;
        if (input == KEY_DEL && this->player_name.size() > 0)
            this->player_name = this->player_name.erase(this->player_name.size() - 1);
        for (size_t i = 11, j = 0 ; j != this->player_name.size() ; i++, j++)
            your_name[i] = this->player_name[j];
        this->bouton[2][0].second = your_name;
    }
}

void Arcade::gest_bouton(int input)
{
    if (input == ARROW_UP) {
        for (size_t i = 0 ; i != this->libs.size() ; i++) {
            if (this->bouton[0][i].first == 1 && i != 0) {
                this->bouton[0][i].first = 0;
                this->bouton[0][i - 1].first = 1;
                break;
            }
        }
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1 && i != 0) {
                this->bouton[1][i].first = 0;
                this->bouton[1][i - 1].first = 1;
                break;
            }
        }
    }
    if (input == ARROW_DOWN) {
        for (size_t i = 0 ; i != this->libs.size() ; i++) {
            if (this->bouton[0][i].first == 1 && i + 1 != this->libs.size()) {
                this->bouton[0][i].first = 0;
                this->bouton[0][i + 1].first = 1;
                break;
            }
        }
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1 && i + 1 != this->games.size()) {
                this->bouton[1][i].first = 0;
                this->bouton[1][i + 1].first = 1;
                break;
            }
        }
    }

    if (input == ARROW_RIGHT) {
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1) {
                this->bouton[1][i].first = 0;
                this->bouton[2][0].first = 1;
                break;
            }
        }
        for (size_t i = 0 ; i != this->libs.size() ; i++) {
            if (this->bouton[0][i].first == 1) {
                this->bouton[0][i].first = 0;
                this->bouton[1][0].first = 1;
                break;
            }
        }
    }
    if (input == ARROW_LEFT) {
        for (size_t i = 0 ; i != this->games.size() ; i++) {
            if (this->bouton[1][i].first == 1) {
                this->bouton[1][i].first = 0;
                this->bouton[0][0].first = 1;
                break;
            }
        }
        if (this->bouton[2][0].first == 1) {
            this->bouton[2][0].first = 0;
            this->bouton[1][0].first = 1;
        }
    }
}

void Arcade::print_bouton(IGraphicLib *glib)
{
    for (size_t i = 0 ; i != this->bouton[0].size() ; i++) {
        if (this->bouton[0][i].first == 1)
            glib->printSelectedButton(7.5 - this->bouton[0][i].second.size() / 2 , 5 + i * 4, this->bouton[0][i].second);
        else
            glib->printButton(7.5 - this->bouton[0][i].second.size() / 2 , 5 + i * 4, this->bouton[0][i].second);
    }
    for (size_t i = 0 ; i != this->bouton[1].size() ; i++) {
        if (this->bouton[1][i].first == 1)
            glib->printSelectedButton(29.5 - this->bouton[1][i].second.size() / 2, 5 + i * 4, this->bouton[1][i].second);
        else
            glib->printButton(29.5 - this->bouton[1][i].second.size() / 2, 5 + i * 4, this->bouton[1][i].second);
    }
    if (this->bouton[2][0].first == 1)
            glib->printSelectedButton(37, 19, this->bouton[2][0].second);
    else
        glib->printButton(37, 19, this->bouton[2][0].second);
}

std::string Arcade::get_logo(std::string name)
{
    std::ifstream file("assets/" + name + "/logo");
    char c;
    std::string line = "";

    if (file) {
        while (file.get(c)) {
            line += c;
        }
        return (line);
    } else {
        return (name);
    }
}

void Arcade::init_bouton()
{
    std::vector<std::pair<bool, std::string>> lib;
    std::vector<std::pair<bool, std::string>> game;
    std::vector<std::pair<bool, std::string>> name;
    std::pair<bool, std::string> tmp;
    int j = 1;

    for (size_t i = 0 ; i != this->libs.size() ; i++) {
        tmp.first = j;
        j = 0;
        tmp.second = this->libs[i].substr(11, this->libs[i].find(".so") - 11);
        lib.push_back(tmp);
    }
    for (size_t i = 0 ; i != this->games.size() ; i++) {
        tmp.first = 0;
        tmp.second = this->get_logo(this->games[i].substr(11, this->games[i].find(".so") - 11));
        game.push_back(tmp);
    }
    tmp.first = 0;
    tmp.second = "Your name:            ";
    name.push_back(tmp);
    this->bouton.push_back(lib);
    this->bouton.push_back(game);
    this->bouton.push_back(name);
}

void Arcade::print_leaderboard(IGraphicLib *glib)
{
    char c;
    std::string line = "";
    std::string name1 = "";
    std::string name2 = "";
    std::string name3 = "";
    std::string score1 = "";
    std::string score2 = "";
    std::string score3 = "";

    for (size_t i = 0 ; i != this->games.size() ; i++) {
        std::ifstream file("assets/" + this->games[i].substr(11, this->games[i].find(".so") - 11) + "/leaderboard");
        if (file) {
            while (file.get(c)) {
                if (c == '|') {
                    if (name1 == "")
                        name1 = line;
                    else if (name2 == "")
                        name2 = line;
                    else
                        name3 = line;
                    line = "";
                    continue;
                }
                if (c == '\n') {
                    if (score1 == "")
                        score1 = line;
                    else if (score2 == "")
                        score2 = line;
                    else
                        score3 = line;
                    line = "";
                    continue;
                }
                line += c;
            }
            line = "";
        }
        glib->printText(49, 5 + i * 4, "🥇");
        glib->printText(67, 5 + i * 4, "🥈");
        glib->printText(85, 5 + i * 4, "🥉");
        glib->printText(50 - name1.size() / 2, 6 + i * 4, name1);
        glib->printText(68 - name2.size() / 2, 6 + i * 4, name2);
        glib->printText(86 - name3.size() / 2, 6 + i * 4, name3);
        glib->printText(50 - score1.size() / 2, 7 + i * 4, score1);
        glib->printText(68 - score2.size() / 2, 7 + i * 4, score2);
        glib->printText(86 - score3.size() / 2, 7 + i * 4, score3);
        name1 = "";
        name2 = "";
        name3 = "";
        score1 = "";
        score2 = "";
        score3 = "";
    }
}
