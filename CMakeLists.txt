cmake_minimum_required(VERSION 3.8)
project(PharmacyMS)
include_directories(/usr/include/mysql)
set(CMAKE_C_STANDARD 11)
set (CMAKE_C_FLAGS "-Wall -g  -pthread -rdynamic")

#server build
set(SOURCE_FILES_server src/server/server.c
        src/parser/cJSON.c src/server/server.h src/server/serverStarter.c
        src/parser/request_parser.c
        src/dbManagement/dbManagement.c src/parser/request_parser.h
        src/dbManagement/dbManagement.h src/parser/object.c src/parser/object.h)
add_executable(server ${SOURCE_FILES_server})
target_link_libraries(server mysqlclient)

# client build
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

# Add the path to its header files to the compiler command line
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

set(SOURCE_FILES_client src/client/client.c
        src/parser/cJSON.c src/define/define.h
        src/client/client.h src/dbManagement/dbManagement.c
         src/parser/request_parser.c
        src/parser/object.c src/parser/object.h
        src/gui/guiStarter.c
        src/dbManagement/dbManagement.c
        src/parser/object.c)
add_executable(client ${SOURCE_FILES_client})
target_link_libraries(client mysqlclient ${GTK_LIBRARY_DIRS})

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(GTK "gtk+-3.0")
    if (GTK_FOUND)
        target_link_libraries(client ${GTK_LIBRARIES})
        add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
    endif()
endif()

#testing build
set(SOURCE_FILES_testing src/client/client.c src/client/clientStarter.c
        src/parser/request_parser.c src/parser/cJSON.c
        src/dbManagement/dbManagement.c
        src/parser/object.c)
add_executable(testing ${SOURCE_FILES_testing})
target_link_libraries(testing mysqlclient)