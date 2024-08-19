cmake_minimum_required(VERSION 3.28)
project(JEAssetBundle)

set(CMAKE_CXX_STANDARD 20)

add_executable(JEAssetBundle src/main.cpp
        src/bundle.cpp
        src/bundle.h
        src/debundle.cpp
        src/debundle.h)
