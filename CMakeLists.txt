cmake_minimum_required(VERSION 3.8)
project(PharmacyMS)
include_directories(/usr/include/mysql)
set(CMAKE_C_STANDARD 11)
set (CMAKE_C_FLAGS "-pthread")

#server build
set(SOURCE_FILES_server src/server_client/server.c src/dbManagement/MySqlManager.c
        src/dbManagement/MySqlManager.h src/parser/cJSON.c src/server_client/server.h src/server_client/server_hander.c
        src/server_client/serviceHandler.c
        src/dbManagement/database.c)
add_executable(server ${SOURCE_FILES_server})
target_link_libraries(server mysqlclient)

# client build
set(SOURCE_FILES_client src/server_client/client.c src/dbManagement/MySqlManager.c
        src/dbManagement/MySqlManager.h src/parser/cJSON.c src/define/define.h
        src/server_client/client.h src/dbManagement/database.c)
add_executable(client ${SOURCE_FILES_client})
target_link_libraries(client mysqlclient)

# testing build
set(SOURCE_FILES_testing src/server_client/serviceHandler.c src/dbManagement/MySqlManager.c
        src/dbManagement/MySqlManager.h src/parser/cJSON.c
        src/dbManagement/database.c)
add_executable(testing ${SOURCE_FILES_testing})
target_link_libraries(testing mysqlclient)
