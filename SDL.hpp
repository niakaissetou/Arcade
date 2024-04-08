/*
** EPITECH PROJECT, 2024
** sdl2_.hpp
** File description:
** arcade
*/

#ifndef SDL_HPP_
    #define SDL_HPP_
    #include <string>
    #include <iostream>
    #include <vector>
    #include <memory>
    #include <map>
    #include <SFML/Graphics.hpp>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <vector>
    #include <algorithm>
    #include <deque>
    #include <ctime>

class SDL {
    public:
    protected:
        int score;

};

enum Inputs {
    UP = SDLK_UP,
    DOWN = SDLK_DOWN,
    LEFT = SDLK_LEFT,
    RIGHT = SDLK_RIGHT,
    ACTION = SDLK_SPACE,
    BACK = SDLK_BACKSPACE,
    QUIT = SDLK_q
};

#endif
