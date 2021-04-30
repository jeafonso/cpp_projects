//
// Created by João Espada Afonso on 26/04/2021.
//

#include <iostream>

#include "game.h"
#include "renderer.h"

Game::Game(Controller controller, Renderer renderer) : _render(renderer), _controller(controller), _running{false}, _started(false) {
    _render.randomizeBoard();
    _render.fillRectangles();

    while(!_started){
        SDL_Delay(500);
        _controller.HandleInput(_running, _started, _render);
    }

    Run();
}

void Game::Run() {
    int counter = 1;

    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;

    std::size_t target_frame_duration{1000 / 60};

    while(_running){
        frame_start = SDL_GetTicks();

        _controller.HandleInput(_running, _started, _render);
        _render.refreshBoard();
        _render.fillRectangles();

        frame_end = SDL_GetTicks();

        frame_duration = frame_end - frame_start;

        if(frame_duration < target_frame_duration){
            SDL_Delay(target_frame_duration - frame_duration);
        }

        _render.UpdateWindowTitle(counter);
        SDL_Delay(1000);
        counter++;
    }

    std::cout << "Total number of iterations was: " + std::to_string(counter) << std::endl;
}