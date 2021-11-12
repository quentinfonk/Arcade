/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** sfml
*/

#ifndef sfml_HPP_
#define sfml_HPP_

#include "IGraphicLib.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <dirent.h>
#include <iostream>
#include <string>
#include <locale.h>
#include <dirent.h>
#include <fstream>
#include <chrono>
#include <cstring>

class SfmlLib : public IGraphicLib
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
        std::map<std::string, sf::Text> text;
        void printOneSprite(int x, int y, sf::Texture texture);

    protected:
    private:
        sf::RenderWindow _window;
        sf::Font MyFont;
        std::map<std::string, std::string> emoji;
        std::map<std::string, sf::Texture> sprite;
        std::map<std::string, sf::Texture> bouton_sprite;
        int block_size;
};

#endif /* !sfml_HPP_ */
