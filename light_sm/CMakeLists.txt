cmake_minimum_required(VERSION 3.31)

include($ENV{pico}/pico_sdk_import.cmake)

project(light_sm)

pico_sdk_init()

add_subdirectory($ENV{pico}/baremetalc baremetalc_build)

add_executable(
    light_sm
    light_sm.c
)

add_custom_command(
    OUTPUT light_sm.pio.h
    COMMAND pioasm -o c-sdk ${CMAKE_CURRENT_SOURCE_DIR}/light_sm.pio light_sm.pio.h
    DEPENDS light_sm.pio
)

add_custom_target(pio_headers DEPENDS light_sm.pio.h)

add_dependencies(light_sm pio_headers)

target_link_libraries(
    light_sm 
    baremetalc
    hardware_pio
    pico_stdlib
)

pico_add_extra_outputs(light_sm)
