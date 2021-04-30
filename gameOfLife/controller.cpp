//
// Created by João Espada Afonso on 26/04/2021.
//

#include <iostream>

#include "controller.h"
#include "SDL.h"

void Controller::HandleInput(bool &running, bool &started, Renderer &renderer) {
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {
            running = false;
            return;
        }

        if(e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    started = true;
                    running = true;
                    break;

                case SDLK_DOWN:
                    renderer.killAllCells();
                    renderer.randomizeBoard();
                    renderer.fillRectangles();
                    break;

                case SDLK_LEFT:
                    running = false;
                    break;
            }
        }
    }
}