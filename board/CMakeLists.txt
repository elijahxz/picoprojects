cmake_minimum_required(VERSION 3.31)

include(../pico_sdk_import.cmake)

include_directories(../include)

project(board)

pico_sdk_init()

add_executable(board
    board.c
)

target_link_libraries(board pico_stdlib)

pico_add_extra_outputs(board)
