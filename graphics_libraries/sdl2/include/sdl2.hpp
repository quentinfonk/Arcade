/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** SLD2
*/

#ifndef SLD2_HPP_
#define SLD2_HPP_

#include "IGraphicLib.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <locale.h>
#include <dirent.h>
#include <fstream>
#include <chrono>

class sdl2Lib : public IGraphicLib
{
public:
    virtual void init_lib();
    virtual void exit_lib();
    virtual int keyPressed();
    virtual void printMap(std::vector<std::string>);
    virtual void printButton(int x, int y, std::string);
    virtual void printSelectedButton(int x, int y, std::string);
    virtual void printText(int x, int y, std::string);
    virtual void clearWindow();
    virtual void refreshWindow();
    virtual void printWindow();
    virtual void printTitle(std::string);
    virtual std::pair<int, int> getWindowSize() const;
    virtual void assetLoader(const std::string);
    std::string clean_emoji(std::string str);
    void printOneSprite(int x, int y, SDL_Surface *surface);
    void reset_time();
protected:
private:
    SDL_Window* win;
    SDL_Renderer *renderer;
    std::string font;
    std::map<std::string, SDL_Surface *> sprite;
    std::map<std::string, SDL_Surface *> text;
    std::map<std::string, SDL_Surface *> bouton_sprite;
    std::map<std::string, std::string> emoji;
    int block_size;
};

#endif /* !SLD2_HPP_ */
