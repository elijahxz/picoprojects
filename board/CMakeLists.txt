cmake_minimum_required(VERSION 3.31)

include($ENV{pico}/pico_sdk_import.cmake)

project(board)

pico_sdk_init()

add_subdirectory($ENV{pico}/baremetalc baremetalc_build)

add_executable(
    board
    board.c
)

target_link_libraries(
    board 
    pico_stdlib
    baremetalc
)

pico_add_extra_outputs(board)
