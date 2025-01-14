cmake_minimum_required(VERSION 3.28)
project(web_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(web_server cmake-build-debug/src/main.cpp
        cmake-build-debug/src/WebServer.cpp
        cmake-build-debug/include/WebServer.h
        cmake-build-debug/src/Middleware.cpp
        cmake-build-debug/include/Middleware.h)
