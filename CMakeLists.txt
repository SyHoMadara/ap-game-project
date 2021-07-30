cmake_minimum_required(VERSION 3.20)
project(ap_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Server src/server.cpp src/client.cpp libs/map.h)
add_executable(client src/client.cpp libs/map.h)
