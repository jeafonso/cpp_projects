//
// Created by João Espada Afonso on 26/04/2021.
//

#ifndef GAMEOFLIFE_RECTANGLE_H
#define GAMEOFLIFE_RECTANGLE_H

#include "SDL.h"

class Rectangle {
    public:
        Rectangle(int a, int b, int w, int h, bool state);
        void setState(bool state);
        [[nodiscard]] bool getState() const;
        SDL_Rect *returnObj();

    private:
        bool _state;
        SDL_Rect _cell;
};

#endif //GAMEOFLIFE_RECTANGLE_H
