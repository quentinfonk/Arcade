/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** main
*/

#include "sdl2.hpp"

extern "C"
{
    sdl2Lib *MakeGraphicLib()
    {
        return new sdl2Lib();
    }
}

void sdl2Lib::init_lib()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    this->win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(this->win, -1, 0);
    this->block_size = 16;
    this->clearWindow();
}

void sdl2Lib::exit_lib()
{
    this->clearWindow();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->win);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int sdl2Lib::keyPressed()
{
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (SDL_PollEvent(&event) != 0 && event.type == SDL_KEYDOWN) {
        if (keys[SDL_SCANCODE_BACKSPACE])
            return 263;
        if (keys[SDL_SCANCODE_DOWN])
            return 258;
        if (keys[SDL_SCANCODE_UP])
            return 259;
        if (keys[SDL_SCANCODE_LEFT])
            return 260;
        if (keys[SDL_SCANCODE_RIGHT])
            return 261;
        if (keys[SDL_SCANCODE_RETURN])
            return 10;
        if (keys[SDL_SCANCODE_A])
            return 'q';
        if (keys[SDL_SCANCODE_B])
            return 'b';
        if (keys[SDL_SCANCODE_C])
            return 'c';
        if (keys[SDL_SCANCODE_D])
            return 'd';
        if (keys[SDL_SCANCODE_E])
            return 'e';
        if (keys[SDL_SCANCODE_F])
            return 'f';
        if (keys[SDL_SCANCODE_G])
            return 'g';
        if (keys[SDL_SCANCODE_H])
            return 'H';
        if (keys[SDL_SCANCODE_I])
            return 'i';
        if (keys[SDL_SCANCODE_J])
            return 'j';
        if (keys[SDL_SCANCODE_K])
            return 'k';
        if (keys[SDL_SCANCODE_L])
            return 'l';
        if (keys[SDL_SCANCODE_M])
            return ';';
        if (keys[SDL_SCANCODE_N])
            return 'n';
        if (keys[SDL_SCANCODE_O])
            return 'o';
        if (keys[SDL_SCANCODE_P])
            return 'p';
        if (keys[SDL_SCANCODE_Q])
            return 'a';
        if (keys[SDL_SCANCODE_R])
            return 'r';
        if (keys[SDL_SCANCODE_S])
            return 's';
        if (keys[SDL_SCANCODE_T])
            return 't';
        if (keys[SDL_SCANCODE_U])
            return 'u';
        if (keys[SDL_SCANCODE_V])
            return 'v';
        if (keys[SDL_SCANCODE_W])
            return 'z';
        if (keys[SDL_SCANCODE_X])
            return 'x';
        if (keys[SDL_SCANCODE_Z])
            return 'w';
    }
    return (-1);
}

std::string sdl2Lib::str_replace_str(std::string str, std::string str2, std::string str3)
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

void sdl2Lib::printMap(std::vector<std::string> vs)
{
    int x = 0;
    int y = 0;
    std::map<std::string, SDL_Texture *> texture;
    SDL_Rect dstrect = {x, y, this->block_size, this->block_size};
    std::string tmp = "";
    std::string tmp2 = "";
    std::string spe_char = "0";
    SDL_Texture *tex = NULL;

    for (size_t i = 0; i != vs.size(); i++) {
        for (auto m = this->sprite.begin() ; m != this->sprite.end() ; m++) {
            if (m->second->w > 25) {
                vs[i] = str_replace_str(vs[i], m->first, spe_char + " ");
            } else {
                vs[i] = str_replace_str(vs[i], m->first, spe_char);
            }
            spe_char[0]++;
        }
        spe_char = "0";
        for (auto m = this->sprite.begin() ; m != this->sprite.end() ; m++) {
            for (size_t h = 0 ; h != vs[i].size() ; h++, tmp = "") {
                if (vs[i][h] == spe_char[0]) {
                    tmp += m->first;
                    if (m->second->w > 25)
                        dstrect = {x, y, this->block_size * 2, this->block_size};
                    else
                        dstrect = {x, y, this->block_size, this->block_size};
                    tex = SDL_CreateTextureFromSurface(renderer, m->second);
                    SDL_RenderCopy(renderer, tex, NULL, &dstrect);
                    SDL_DestroyTexture(tex);
                }
                x = x + this->block_size;
            }
            x = 0;
            spe_char[0]++;
        }
        spe_char = "0";
        y = y + this->block_size;
    }
}
std::string sdl2Lib::begin_str(std::string str, char a)
{
    size_t b = 0;
    std::string str2;
    size_t c = 0;

    while (b != str.size()) {
        if (str[b] == a)
            break;
        b++;
    }
    while (c != b) {
        str2 = str2 + str[c];
        c++;
    }
    return str2;
}

int sdl2Lib::str_in_str(std::string str, std::string str2)
{
    size_t a = 0;
    size_t b = 0;
    size_t c = 0;
    int result = 0;

    while (a != str.size()) {
        if (str[a] == str2[0]) {
            b = 0;
            c = a;
            while (b != str2.size()) {
                if (str[c] != str2[b])
                    b = str2.size();
                else {
                    c++;
                    b++;
                    if (b == str2.size())
                        result++;
                }
            }
        }
        a++;
    }
    return result;
}

size_t sdl2Lib::strlen_emoji(const std::string& str)
{
    size_t length = 0;
    size_t emoji = 0;

    for (size_t i = 0 ; i != str.length() ; i++) {
        if ((str[i] & 0xC0) != 0x80) {
            length++;
        }
    }
    emoji += str_in_str(str, "🐍");
    emoji += str_in_str(str, "👻");
    return (length + emoji);
}

void sdl2Lib::printOneSprite(int x, int y, SDL_Surface *surface)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, this->bouton_sprite["clear"]);
    SDL_Rect dstrect = {x * this->block_size, y * this->block_size, this->block_size, this->block_size};
    SDL_RenderCopy(this->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_RenderCopy(this->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}

void sdl2Lib::printSelectedButton(int x, int y, std::string text)
{
    size_t len = strlen_emoji(text);

    this->printOneSprite(x, y, this->bouton_sprite["┏"]);
    this->printOneSprite(x, y + 2, this->bouton_sprite["┗"]);
    this->printOneSprite(x + (int)len + 3, y, this->bouton_sprite["┓"]);
    this->printOneSprite(x + (int)len + 3, y + 2, this->bouton_sprite["┛"]);
    this->printOneSprite(x + (int)len + 3, y + 1, this->bouton_sprite["┃"]);
    this->printOneSprite(x, y + 1, this->bouton_sprite["┃"]);

    for (size_t i = 0 ; i != len + 2 ; i++) {
        this->printOneSprite(x + (int)i + 1, y + 2, this->bouton_sprite["━"]);
        this->printOneSprite(x + (int)i + 1, y, this->bouton_sprite["━"]);
    }
    printText(x + 2, y + 1, text);
}

void sdl2Lib::printButton(int x, int y, std::string text)
{
    size_t len = strlen_emoji(text);

    this->printOneSprite(x, y, this->bouton_sprite["┌"]);
    this->printOneSprite(x, y + 2, this->bouton_sprite["└"]);
    this->printOneSprite(x + (int)len + 3, y, this->bouton_sprite["┐"]);
    this->printOneSprite(x + (int)len + 3, y + 2, this->bouton_sprite["┘"]);
    this->printOneSprite(x + (int)len + 3, y + 1, this->bouton_sprite["┆"]);
    this->printOneSprite(x, y + 1, this->bouton_sprite["┆"]);

    for (size_t i = 0 ; i != len + 2 ; i++) {
        this->printOneSprite(x + (int)i + 1, y + 2, this->bouton_sprite["┄"]);
        this->printOneSprite(x + (int)i + 1, y, this->bouton_sprite["┄"]);
    }
    printText(x + 2, y + 1, text);
}


std::string sdl2Lib::clean_emoji(std::string str)
{
    for (auto m = this->emoji.begin() ; m != this->emoji.end() ; m++)
        str = str_replace_str(str, m->first, m->second);
    return str;
}

void sdl2Lib::printText(int x, int y, std::string string)
{
    SDL_Color color = {255, 255, 255, 255};
    if (this->text.find(string) == this->text.end())
        this->text[string] = TTF_RenderText_Solid(TTF_OpenFont(this->font.c_str(), this->block_size + 2), clean_emoji(string).c_str(), color);
    
    SDL_Texture *tex_clear = SDL_CreateTextureFromSurface(this->renderer, this->bouton_sprite["clear"]);
    SDL_Rect dstrect_clear = {x * this->block_size, y * this->block_size, this->block_size * ((int)clean_emoji(string).size()), this->block_size};
    SDL_RenderCopy(this->renderer, tex_clear, NULL, &dstrect_clear);
    SDL_DestroyTexture(tex_clear);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, this->text[string]);
    int a = 0;
    int b = 0;
    SDL_QueryTexture(texture, NULL, NULL, &a, &b);
    SDL_Rect dstrect = {x * this->block_size, y * this->block_size - 3, a, b};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}

void sdl2Lib::clearWindow()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
}

void sdl2Lib::refreshWindow()
{
    SDL_RenderPresent(renderer);
}

void sdl2Lib::assetLoader(const std::string str)
{
    std::string tmp = "";
    std::string tmp2 = "";
    std::string font = str + "/font";
    DIR *rep = opendir(font.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".ttf") != NULL) {
                tmp = str + "/font/" + ent->d_name;
                this->font = tmp;
                tmp = "";
                break;
            }
        }
    }
    closedir(rep);
    std::string tex = str + "/sprites";
    rep = opendir(tex.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".png") != NULL) {
                tmp = str + "/sprites/" + ent->d_name;
                tmp2 += begin_str(ent->d_name, '.');
                this->sprite[tmp2] = IMG_Load(tmp.c_str());
            }
            tmp = "";
            tmp2 = "";
        }
    }
    closedir(rep);
    tex = "assets/sdl2/sprites";
    rep = opendir(tex.c_str());
    if (rep != NULL) {
        struct dirent* ent;
        tmp = "assets/sdl2/sprites/";
        while((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, ".png") != NULL) {
                tmp += ent->d_name;
                tmp2 += begin_str(ent->d_name, '.');
                this->bouton_sprite[tmp2] = IMG_Load(tmp.c_str());
            }
            tmp = "assets/sdl2/sprites/";
            tmp2 = "";
        }
    }
    closedir(rep);

    std::ifstream file(str + "/emoji");
    tmp = "";
    char c;
    std::string line = "";

    if (file) {
        while (file.get(c)) {
            if (c == '=') {
                tmp += line;
                line = "";
                continue;
            }
            if (c == '\n') {
                this->emoji[tmp] = line;
                line = "";
                tmp = "";
                continue;
            }
            line += c;
        }
    }
}