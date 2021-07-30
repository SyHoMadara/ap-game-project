cmake_minimum_required(VERSION 3.20)
project(ap_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(ap_project src/server.cpp src/client.cpp libs/map.h)
