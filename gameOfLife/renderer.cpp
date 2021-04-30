//
// Created by João Espada Afonso on 25/04/2021.
//
#include <string>
#include <iostream>
#include <random>
#include "renderer.h"

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width,
                   const std::size_t grid_height) : _screen_width(screen_width),
                                                    _screen_height(screen_height),
                                                    _rectangle_width(grid_width),
                                                    _rectangle_height(grid_height) {
    //Check if SDL is initialized
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Game of Life - arrow UP - Start, DOWN - Refresh, LEFT - Quit", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                    screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_Quit();
}

void Renderer::createBoard() {
    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;
    std::vector<Rectangle> aux;

    for(int i = 0; i < maxRows; i++){

        aux.clear();
        for(int j = 0; j < maxColumns; j++){
            aux.emplace_back(Rectangle(i * _rectangle_width, j * _rectangle_height, static_cast<int>(_rectangle_width), static_cast<int>(_rectangle_height), false));
        }
        _cells.emplace_back(aux);
        _cellsAux.emplace_back(aux);
    }
}

void Renderer::fillRectangles() {
    std::cout << "entrou" << std::endl;
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;

    for(int i = 0; i < maxRows; i++){
        for(int j = 0; j < maxColumns; j++){
            if(_cells[i][j].getState()){
                SDL_SetRenderDrawColor(sdl_renderer, 0x0, 0x0, 0x0, 0xFF);
                SDL_RenderFillRect(sdl_renderer, _cells[i][j].returnObj());
            } else {
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderFillRect(sdl_renderer, _cells[i][j].returnObj());
            }
        }
    }
    SDL_RenderPresent(sdl_renderer);
    SDL_Delay(300);
    std::cout << "saiu" << std::endl;
}

int Renderer::isNeighbourAlive(int x, int y) {
    int divX = x / static_cast<int>(_rectangle_width);
    int divY = y / static_cast<int>(_rectangle_height);
    int alive = 0;
    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;

    if( (divX >= 0 && divX <= maxColumns - 1) && ( divY >= 0 && divY <= maxRows - 1)) {
        if(_cells[divX][divY].getState()){
            alive = 1;
        }
    }

    return alive;
}

int Renderer::getAllNeighbours(int x, int y) {
    int neighboursCounter = 0;
    Rectangle center = _cellsAux[x][y];

    int xx = center.returnObj()->x ;
    int yy = center.returnObj()->y ;

    //Left Column
    int n0 = isNeighbourAlive(xx - _rectangle_width, yy - _rectangle_height);
    int n3 = isNeighbourAlive(xx - _rectangle_width, yy);
    int n5 = isNeighbourAlive(xx - _rectangle_width, yy + _rectangle_height);

    //Center Column
    int n1 = isNeighbourAlive(xx, yy - _rectangle_height);
    int n6 = isNeighbourAlive(xx, yy + _rectangle_height);

    //Right Column
    int n2 = isNeighbourAlive(xx + _rectangle_width, yy - _rectangle_height);
    int n4 = isNeighbourAlive(xx + _rectangle_width,  yy);
    int n7 = isNeighbourAlive(xx + _rectangle_width, yy + _rectangle_height);

    neighboursCounter = n0 + n1 + n2 + n3 + n4 + n5 + n6 + n7;

    return neighboursCounter;
}

//Reference for the rules of the game comes from Wikipedia - https://pt.wikipedia.org/wiki/Jogo_da_vida
void Renderer::refreshBoard() {
    updateAuxVector();

    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;

    for(int i = 0; i < maxRows; i++){
        for(int j = 0; j < maxColumns; j++){

            //1
            if(_cellsAux[i][j].getState() && getAllNeighbours(i, j) < 2){
                _cells[i][j].setState(false);
            }

            //4
            if(_cellsAux[i][j].getState() && (getAllNeighbours(i, j) == 2 || getAllNeighbours(i, j) == 3)){
                continue;
            }

            //2
            if(_cellsAux[i][j].getState() && getAllNeighbours(i, j) > 3){
                _cells[i][j].setState(false);
            }

            //3
            if(!_cellsAux[i][j].getState() && getAllNeighbours(i, j) == 3){
                _cells[i][j].setState(true);
            }
        }
    }
}

void Renderer::updateAuxVector() {
    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;

    for(int i = 0; i < maxRows; i++){
        for(int j = 0; j < maxColumns; j++){
            _cellsAux[i][j] = _cells[i][j];
        }
    }
}

void Renderer::UpdateWindowTitle(int iterations) {
    std::string header("Number of Iterations: " + std::to_string(iterations));
    SDL_SetWindowTitle(sdl_window, header.c_str());
}

void Renderer::randomizeBoard() {
    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;

    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<int> distrRows(0, maxRows);
    std::uniform_int_distribution<int> distrColumns(0, maxColumns);

    int countRect = 0;

    while(countRect < 100){
        auto x = distrColumns(gen);
        auto y = distrRows(gen);

        if((x >= 0 && x <= maxColumns - 1 ) && (y >= 0 && y <= maxRows - 1)){
            if(!_cells[x][y].getState()){
                _cells[x][y].setState(true);
                countRect++;
            }
        }
    }
} 

void Renderer::killAllCells() {
    int maxRows = _screen_height / _rectangle_height;
    int maxColumns = _screen_width / _rectangle_width;

    for (int i = 0; i < maxRows; i++) {
        for (int j = 0; j < maxColumns; j++) {
            _cells[i][j].setState(false);
        }
    }
}