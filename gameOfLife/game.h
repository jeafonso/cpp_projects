//
// Created by João Espada Afonso on 26/04/2021.
//

#ifndef GAMEOFLIFE_GAME_H
#define GAMEOFLIFE_GAME_H

#include "controller.h"
#include "renderer.h"
#include "rectangle.h"

class Game{
    public:
        Game(Controller controller, Renderer renderer);
        void Run();

    private:
        Renderer _render;
        Controller _controller;
        bool _running{true};
        bool _started{false};
};

#endif //GAMEOFLIFE_GAME_H
