cmake_minimum_required(VERSION 3.31)
project(snake_cli C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(
        snake_cli
        main.c
        src/key.c
        src/KeyHandler.c
)

target_include_directories(
        snake_cli
        PRIVATE
        include
)
