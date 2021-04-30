//
// Created by João Espada Afonso on 25/04/2021.
//
#ifndef GAMEOFLIFE_RENDERER_H
#define GAMEOFLIFE_RENDERER_H

#include <memory>
#include <vector>
#include "SDL.h"
#include "rectangle.h"

class Renderer {
    public:
        Renderer(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height);
        ~Renderer();
        void createBoard();
        void fillRectangles();
        int isNeighbourAlive(int x, int y);
        int getAllNeighbours(int x, int y);
        void refreshBoard();
        void UpdateWindowTitle(int iterations);
        void randomizeBoard();
        void killAllCells();

    private:
        //Functions
        void updateAuxVector();

        //Screen variables
        const std::size_t _screen_width;
        const std::size_t _screen_height;
        const std::size_t _rectangle_width;
        const std::size_t _rectangle_height;

        //SDL Pointers
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        //Game Variables
        std::vector<std::vector<Rectangle>> _cells;
        std::vector<std::vector<Rectangle>> _cellsAux;
};

#endif //GAMEOFLIFE_RENDERER_H
