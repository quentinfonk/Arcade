/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** IGraphicLib
*/

#ifndef IGraphicLib_HPP_
#define IGraphicLib_HPP_

#include <map>
#include <vector>
#include <list>
#include <iostream>

class IGraphicLib {
    public:
        virtual ~IGraphicLib() {};
        virtual void init_lib() = 0;
        virtual void clearWindow() = 0;
        virtual int keyPressed() = 0;
        virtual void refreshWindow() = 0;
        virtual void assetLoader(const std::string) = 0;
        virtual void printMap(std::vector<std::string>) = 0;
        virtual void printText(int x, int y, std::string) = 0;
        virtual void printButton(int x, int y, std::string) = 0;
        virtual void printSelectedButton(int x, int y, std::string) = 0;
        virtual void exit_lib() = 0;

    protected:
    private:
};

typedef IGraphicLib *(*MakerLib)();

#endif /* !IGraphicLib_HPP_ */
