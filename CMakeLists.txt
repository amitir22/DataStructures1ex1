cmake_minimum_required(VERSION 3.15)
project(DataStructures1ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DataStructures1ex1 src/main1.cpp src/AVLTree.h src/AVLTreeImp.h
        src/TNode.h src/TNodeImp.h src/BiDirectionalLinkedList.h
        src/BiDirectionalNode.h src/BiDirectionalNodeImp.h
        src/BiDirectionalLinkedListImp.h src/MusicManager.cpp src/MusicManager.h
        src/ArtistInfo.cpp src/ArtistInfo.h src/SongCollection.cpp
        src/SongCollection.h src/StreamCountGroup.cpp src/StreamCountGroup.h
        src/SongInfo.cpp src/SongInfo.h src/library1.h src/library1.cpp)