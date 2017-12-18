cmake_minimum_required(VERSION 3.8)
project(PharmacyMS)
include_directories(/usr/include/mysql)
set(CMAKE_C_STANDARD 11)
set (CMAKE_C_FLAGS "-Wall -pthread")

#server build
set(SOURCE_FILES_server src/server/server.c
        src/parser/cJSON.c src/server/server.h src/server/serverStarter.c
        src/parser/request_parser.c
        src/dbManagement/dbManagement.c src/parser/request_parser.h src/dbManagement/dbManagement.h src/parser/object.c src/parser/object.h)
add_executable(server ${SOURCE_FILES_server})
target_link_libraries(server mysqlclient)

# client build
set(SOURCE_FILES_client src/client/client.c
        src/parser/cJSON.c src/define/define.h
        src/client/client.h src/dbManagement/dbManagement.c src/client/clientStarter.c src/parser/request_parser.c src/parser/object.c)
add_executable(client ${SOURCE_FILES_client})
target_link_libraries(client mysqlclient)

# testing build
set(SOURCE_FILES_testing src/parser/request_parser.c
        src/parser/cJSON.c
        src/dbManagement/dbManagement.c src/parser/request_parser.h src/dbManagement/dbManagement.h)
add_executable(testing ${SOURCE_FILES_testing})
target_link_libraries(testing mysqlclient)
