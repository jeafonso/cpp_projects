//
// Created by João Espada Afonso on 26/04/2021.
//

#ifndef GAMEOFLIFE_CONTROLLER_H
#define GAMEOFLIFE_CONTROLLER_H

#include "renderer.h"

class Controller {
public:
    static void HandleInput(bool &running, bool &started, Renderer &renderer);
};

#endif //GAMEOFLIFE_CONTROLLER_H
