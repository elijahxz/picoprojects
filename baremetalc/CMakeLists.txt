cmake_minimum_required(VERSION 3.31)

add_library(baremetalc baremetalc.c)

target_include_directories(baremetalc
    PUBLIC $ENV{pico}/include
)
