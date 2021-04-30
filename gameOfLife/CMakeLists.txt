cmake_minimum_required(VERSION 3.19)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(gameOfLife main.cpp renderer.h renderer.cpp rectangle.h rectangle.cpp controller.h controller.cpp game.h game.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(gameOfLife ${SDL2_LIBRARIES})