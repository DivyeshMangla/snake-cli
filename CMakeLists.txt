cmake_minimum_required(VERSION 3.31)
project(snake_cli C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
        snake_cli
        main.c
        src/Key.c
        src/KeyHandler.c
        src/Terminal.c
        src/util/Matrix.c
        src/game/Snake.c
        src/game/Food.c
        src/game/Game.c
)

target_include_directories(
        snake_cli
        PRIVATE
        include
)

if(MSVC)
    target_compile_options(snake_cli PRIVATE /W4)
else()
    target_compile_options(snake_cli PRIVATE -Wall -Wextra -pedantic)
endif()
