#include <iostream>

#include "renderer.h"
#include "controller.h"
#include "game.h"

int main() {
    constexpr std::size_t kScreenWidth{600};
    constexpr std::size_t kScreenHeight{600};
    constexpr std::size_t kCellWidth{30};
    constexpr std::size_t kCellHeight{30};

    Renderer renderer(kScreenWidth, kScreenHeight, kCellWidth, kCellHeight);
    renderer.createBoard();

    Controller controller;

    Game game(controller, renderer);

    return 0;
}
