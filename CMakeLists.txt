cmake_minimum_required(VERSION 3.20)
project(ap_project_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs)

add_executable(
        Server
        src/server.cpp
        libs/httplib.h
        libs/map.h
        libs/map.cpp
        libs/handler/FileReader.h libs/handler/command.h)
target_link_libraries(
        Server
        pthread
)

add_executable(
        Client1
        src/client.cpp
        libs/map.h
        libs/httplib.h
        libs/map.cpp libs/handler/command.cpp libs/handler/FileReader.cpp
)
add_executable(
        Client2
        src/client.cpp
        libs/map.h
        libs/httplib.h
        libs/map.cpp libs/handler/command.cpp libs/handler/FileReader.cpp
)
add_executable(
        Client3
        src/client.cpp
        libs/map.h
        libs/httplib.h
        libs/map.cpp libs/handler/command.cpp libs/handler/FileReader.cpp
)
add_executable(
        Client4
        src/client.cpp
        libs/map.h
        libs/httplib.h
        libs/map.cpp libs/handler/command.cpp libs/handler/FileReader.cpp
)
