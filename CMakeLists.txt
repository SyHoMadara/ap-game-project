cmake_minimum_required(VERSION 3.20)
project(ap_project_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs)

add_executable(
        Server
        src/server.cpp
        libs/httplib.h
        src/handler/FileReader.h src/handler/FileReader.cpp)
target_link_libraries(
        Server
        pthread
)

add_executable(
        Client
        src/client.cpp
        libs/httplib.h
)