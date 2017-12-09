cmake_minimum_required(VERSION 3.8)
project(PharmacyMS)
include_directories(/usr/include/mysql)
set(CMAKE_C_STANDARD 11)


#Client build
set(SOURCE_FILES_CLIENT src/server_client/client.c src/dbManagement/MySqlManager.c src/dbManagement/MySqlManager.h src/parser/cJSON.c)
add_executable(serverRun ${SOURCE_FILES_CLIENT})
target_link_libraries(serverRun mysqlclient)

# Client build
set(SOURCE_FILES_SERVER src/server_client/client.c src/dbManagement/MySqlManager.c src/dbManagement/MySqlManager.h src/parser/cJSON.c )
add_executable(clientRun ${SOURCE_FILES_CLIENT})
target_link_libraries(clientRun mysqlclient)
