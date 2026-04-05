cmake_minimum_required(VERSION 4.1)
project(data-structures)

set(CMAKE_CXX_STANDARD 20)

add_executable(data-structures double_test.cpp
        forwardList.tpp
        forwardList.h
        nodes.tpp
        nodes.h
        list.tpp
        list.h
        )
