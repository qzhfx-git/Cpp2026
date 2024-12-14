cmake_minimum_required(VERSION 3.29)
project(programming_language)

set(CMAKE_CXX_STANDARD 20)

add_executable(programming_language main.cpp
        Val.cpp
        Val.h
        reader.cpp
        reader.h
        Token.cpp
        Token.h
        TreeNode.cpp
        TreeNode.h)
