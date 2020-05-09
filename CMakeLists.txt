cmake_minimum_required(VERSION 3.15)
project(DataStructures1ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DataStructures1ex1 src/main1.cpp
        src/library1.cpp src/library1.h
        src/Artist.cpp src/Artist.h
        src/NoInitArray.cpp src/NoInitArray.h
        src/AVLSearchTreeImpl.h src/AVLSearchTree.h
        src/DeezelEngine.cpp src/DeezelEngine.h)

add_executable(AVLTester src/AVLSearchTreeTester.cpp
        src/AVLSearchTreeImpl.h src/AVLSearchTree.h)