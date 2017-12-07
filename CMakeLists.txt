cmake_minimum_required(VERSION 3.8)
project(PharmacyMS)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES  src/main.c src/add.c src/add.h src/MySqlManager.c src/MySqlManager.h)
add_executable(pharmacy ${SOURCE_FILES})
include_directories(/usr/include/mysql)
target_link_libraries(pharmacy mysqlclient)