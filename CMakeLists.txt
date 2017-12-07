cmake_minimum_required(VERSION 3.8)
project(PharmacyMS)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c src/adding.c src/adding.h)

add_executable(pharmacy ${SOURCE_FILES})