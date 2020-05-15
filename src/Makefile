CC = g++
MUSIC_MANAGER_TESTS_OBJECTS = MusicManagerTests.o MusicManager.o ArtistInfo.o \
SongCollection.o SongInfo.o StreamCountGroup.o
AVL_TREE_TESTS_OBJECTS = AVLTreeTests.o
MAIN1_OBJECTS = main1.o library1.o MusicManager.o ArtistInfo.o \
SongCollection.o SongInfo.o StreamCountGroup.o
OBJS = ${MUSIC_MANAGER_TESTS_OBJECTS} ${AVL_TREE_TESTS_OBJECTS} ${MAIN1_OBJECTS}
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors
EXEC = MusicManagerTests AVLTreeTests main1

MusicManagerTests: ${MUSIC_MANAGER_TESTS_OBJECTS}
	${CC} ${MUSIC_MANAGER_TESTS_OBJECTS} -o $@
	
AVLTreeTests: ${AVL_TREE_TESTS_OBJECTS}
	${CC} ${AVL_TREE_TESTS_OBJECTS} -o $@
	
main1: ${MAIN1_OBJECTS}
	${CC} ${MAIN1_OBJECTS} -o $@
	
AVLTreeTests.o: AVLTreeTests.cpp AVLTree.h TNode.h TNodeImp.h \
 AVLTreeImp.h BiDirectionalNode.h BiDirectionalNodeImp.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp
	
MusicManagerTests.o: MusicManagerTests.cpp MusicManager.h AVLTree.h \
 TNode.h TNodeImp.h AVLTreeImp.h ArtistInfo.h StreamCountGroup.h \
 SongCollection.h BiDirectionalLinkedList.h BiDirectionalNode.h \
 BiDirectionalNodeImp.h BiDirectionalLinkedListImp.h SongInfo.h \
 library1.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp
	
MusicManager.o: MusicManager.cpp MusicManager.h AVLTree.h TNode.h \
 TNodeImp.h AVLTreeImp.h ArtistInfo.h StreamCountGroup.h SongCollection.h \
 BiDirectionalLinkedList.h BiDirectionalNode.h BiDirectionalNodeImp.h \
 BiDirectionalLinkedListImp.h SongInfo.h library1.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp
	
ArtistInfo.o: ArtistInfo.cpp ArtistInfo.h StreamCountGroup.h AVLTree.h \
 TNode.h TNodeImp.h AVLTreeImp.h SongCollection.h \
 BiDirectionalLinkedList.h BiDirectionalNode.h BiDirectionalNodeImp.h \
 BiDirectionalLinkedListImp.h SongInfo.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp
	
SongCollection.o: SongCollection.cpp SongCollection.h AVLTree.h TNode.h \
 TNodeImp.h AVLTreeImp.h BiDirectionalLinkedList.h BiDirectionalNode.h \
 BiDirectionalNodeImp.h BiDirectionalLinkedListImp.h SongInfo.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp
 
SongInfo.o: SongInfo.cpp SongInfo.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp
	
StreamCountGroup.o: StreamCountGroup.cpp StreamCountGroup.h AVLTree.h \
 TNode.h TNodeImp.h AVLTreeImp.h SongCollection.h \
 BiDirectionalLinkedList.h BiDirectionalNode.h BiDirectionalNodeImp.h \
 BiDirectionalLinkedListImp.h SongInfo.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp 

main1.o: main1.cpp library1.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp 
	
library1.o: library1.cpp library1.h MusicManager.h AVLTree.h TNode.h \
 TNodeImp.h AVLTreeImp.h ArtistInfo.h StreamCountGroup.h SongCollection.h \
 BiDirectionalLinkedList.h BiDirectionalNode.h BiDirectionalNodeImp.h \
 BiDirectionalLinkedListImp.h SongInfo.h
	${CC} ${DEBUG_FLAG} ${COMP_FLAG} -c $*.cpp 
	
clean:
	rm -f ${OBJS} ${EXEC}
	
	