//
// Created by João Espada Afonso on 26/04/2021.
//

#include "rectangle.h"
#include "SDL.h"

Rectangle::Rectangle(int a, int b, int w, int h, bool state) : _cell{a, b, w, h}, _state(state) {

}

void Rectangle::setState(bool state) {
    _state = state;
}

bool Rectangle::getState() const {
    return _state;
}

SDL_Rect *Rectangle::returnObj() {
    return &_cell;
}