/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-alexis.thomas
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "IGraphicLib.hpp"

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void launchMenu(IGraphicLib *glib) = 0;
        virtual int launchGame(IGraphicLib *glib) = 0;
        virtual int gameLoop(IGraphicLib *glib) = 0;

    protected:
    private:
};

typedef IGame *(*MakerGame)();

#endif /* !IGAME_HPP_ */
