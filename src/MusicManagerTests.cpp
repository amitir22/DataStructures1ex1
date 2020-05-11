#include "MusicManager.h"
#include <iostream>
#include <sstream>

using DataStructuresWet1::MusicManager;
using DataStructuresWet1::SongCollection;

void addArtistTests() {
    MusicManager musicManager;
    if (musicManager.addArtist(2, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(4, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(5, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(6, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(7, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(3, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(1, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(10, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(11, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(12, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(17, 10) != SUCCESS) {
        assert(false);
    }
    if (musicManager.addArtist(15, 10) != SUCCESS) {
        assert(false);
    }

    std::ostringstream listContent;

    musicManager.getStreamCountGroups().getFirst()->getValue().getOrderedSongsCollectionsByArtistId().printList(
            listContent);

    if (listContent.str() != "1 2 3 4 5 6 7 10 11 12 15 17 \n") {
        assert(false);
    }

    std::ostringstream listContentReversed;

    musicManager.getStreamCountGroups().getFirst()->getValue().getOrderedSongsCollectionsByArtistId().printListReverse(
            listContentReversed);

    if (listContentReversed.str() != "17 15 12 11 10 7 6 5 4 3 2 1 \n") {
        assert(false);
    }

    BiDirectionalLinkedList<SongCollection> &songCollections =
            musicManager.getStreamCountGroups().getFirst()->getValue().getOrderedSongsCollectionsByArtistId();

    shared_ptr<BiDirectionalNode<SongCollection>> current = songCollections.getFirst();

    while (current != nullptr) {
        listContent.clear();
        listContent.str("");
        listContentReversed.clear();
        listContentReversed.str("");

        current->getValue().getOrderedSongs().printList(listContent);
        current->getValue().getOrderedSongs().printListReverse(listContentReversed);

        if (listContent.str() != "0 1 2 3 4 5 6 7 8 9 \n") {
            assert(false);
        }

        if (listContentReversed.str() != "9 8 7 6 5 4 3 2 1 0 \n") {
            assert(false);
        }

        current = current->getNext();
    }

    std::cout << "Add artist tests passed successfully!" << std::endl;
}

void removeArtistTests() {
    MusicManager musicManager;
    musicManager.addArtist(2, 5);
    musicManager.addArtist(4, 5);
    musicManager.addArtist(5, 5);
    musicManager.addArtist(6, 5);
    musicManager.addArtist(7, 5);
    musicManager.addArtist(3, 5);
    musicManager.addArtist(1, 10);
    musicManager.addArtist(10, 10);
    musicManager.addArtist(11, 10);
    musicManager.addArtist(12, 10);
    musicManager.addArtist(17, 10);
    musicManager.addArtist(15, 10);

    musicManager.removeArtist(15);

    std::ostringstream listContent;

    musicManager.getStreamCountGroups().getFirst()->getValue().getOrderedSongsCollectionsByArtistId().printList(
            listContent);

    if (listContent.str() != "1 2 3 4 5 6 7 10 11 12 17 \n") {
        assert(false);
    }

    std::ostringstream listContentReversed;

    musicManager.getStreamCountGroups().getFirst()->getValue().getOrderedSongsCollectionsByArtistId().printListReverse(
            listContentReversed);

    if (listContentReversed.str() != "17 12 11 10 7 6 5 4 3 2 1 \n") {
        assert(false);
    }

    if (musicManager.getStreamCountGroups().getFirst()->getValue().getArtistToSongCollectionPointers().find(15) !=
        nullptr) {
        assert(false);
    }

    if (musicManager.getArtistsToSongs().find(15) != nullptr) {
        assert(false);
    }

    musicManager.removeArtist(2);
    musicManager.removeArtist(4);
    musicManager.removeArtist(5);
    musicManager.removeArtist(6);
    musicManager.removeArtist(7);
    musicManager.removeArtist(3);
    musicManager.removeArtist(1);
    musicManager.removeArtist(10);
    musicManager.removeArtist(11);
    musicManager.removeArtist(12);
    musicManager.removeArtist(17);

    if (musicManager.getStreamCountGroups().getFirst() != nullptr ||
        musicManager.getArtistsToSongs().getRoot() != nullptr) {
        assert(false);
    }

    std::cout << "Remove artist tests passed successfully!" << std::endl;
}

void addToSongCountTests() {
    MusicManager musicManager;
    musicManager.addArtist(2, 10);
    musicManager.addArtist(4, 10);
    musicManager.addArtist(5, 10);
    musicManager.addArtist(6, 10);
    musicManager.addArtist(7, 10);
    musicManager.addArtist(3, 10);
    musicManager.addArtist(1, 10);
    musicManager.addArtist(10, 10);
    musicManager.addArtist(11, 10);
    musicManager.addArtist(12, 10);
    musicManager.addArtist(17, 10);
    musicManager.addArtist(15, 10);

    musicManager.addToSongCount(7, 2);

    std::ostringstream listContent;
    std::ostringstream listContentReversed;

    BiDirectionalLinkedList<SongCollection> &songCollections =
            musicManager.getStreamCountGroups().getFirst()->getValue().getOrderedSongsCollectionsByArtistId();

    shared_ptr<BiDirectionalNode<SongCollection>> current = songCollections.getFirst();

    while (current != nullptr) {
        listContent.clear();
        listContent.str("");
        listContentReversed.clear();
        listContentReversed.str("");

        current->getValue().getOrderedSongs().printList(listContent);
        current->getValue().getOrderedSongs().printListReverse(listContentReversed);

        if (current->getValue().getArtistId() == 7) {
            if (listContent.str() != "0 1 3 4 5 6 7 8 9 \n") {
                assert(false);
            }

            if (listContentReversed.str() != "9 8 7 6 5 4 3 1 0 \n") {
                assert(false);
            }
        } else {
            if (listContent.str() != "0 1 2 3 4 5 6 7 8 9 \n") {
                assert(false);
            }

            if (listContentReversed.str() != "9 8 7 6 5 4 3 2 1 0 \n") {
                assert(false);
            }
        }

        current = current->getNext();
    }

    listContent.clear();
    listContent.str("");
    listContentReversed.clear();
    listContentReversed.str("");

    songCollections =
            musicManager.getStreamCountGroups().getFirst()->getNext()->
            getValue().getOrderedSongsCollectionsByArtistId();

    songCollections.getFirst()->getValue().getOrderedSongs().printList(listContent);
    songCollections.getFirst()->getValue().getOrderedSongs().printList(listContentReversed);

    if (listContent.str() != "2 \n") {
        assert(false);
    }

    if (listContentReversed.str() != "2 \n") {
        assert(false);
    }

    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getValue().getStreamCount() == 1);
    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getNext() == nullptr);

    musicManager.addToSongCount(7, 2);

    listContent.clear();
    listContent.str("");
    listContentReversed.clear();
    listContentReversed.str("");

    songCollections =
            musicManager.getStreamCountGroups().getFirst()->getNext()->
                    getValue().getOrderedSongsCollectionsByArtistId();

    songCollections.getFirst()->getValue().getOrderedSongs().printList(listContent);
    songCollections.getFirst()->getValue().getOrderedSongs().printList(listContentReversed);

    if (listContent.str() != "2 \n") {
        assert(false);
    }

    if (listContentReversed.str() != "2 \n") {
        assert(false);
    }

    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getValue().getStreamCount() == 2);
    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getNext() == nullptr);

    musicManager.addToSongCount(7, 1);

    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getValue().getStreamCount() == 1);
    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getNext()->getNext() == nullptr);

    musicManager.addToSongCount(7, 1);

    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getValue().getStreamCount() == 2);
    assert(musicManager.getStreamCountGroups().getFirst()->getNext()->getNext()== nullptr);

    listContent.clear();
    listContent.str("");
    listContentReversed.clear();
    listContentReversed.str("");

    songCollections = musicManager.getStreamCountGroups().getFirst()->getNext()->
                    getValue().getOrderedSongsCollectionsByArtistId();

    songCollections.getFirst()->getValue().getOrderedSongs().printList(listContent);
    songCollections.getFirst()->getValue().getOrderedSongs().printListReverse(listContentReversed);

    if (listContent.str() != "1 2 \n") {
        assert(false);
    }

    if (listContentReversed.str() != "2 1 \n") {
        assert(false);
    }

    std::cout << "add to song count tests passed successfully!" << std::endl;
}

class A {
public:
    A() {
        std::cout << "constructor called!" << std::endl;
    }

    ~A() {
        std::cout << "destructor called!" << std::endl;
    }
};

class B {
public:
    B() {
        a = make_shared<A>();
        std::cout << "B constructor called!" << std::endl;
    }

    ~B() {
        std::cout << "B destructor called!" << std::endl;
    }

private:
    shared_ptr<A> a;
};

B bla() {
    B b = B();
    return b;
}

int main() {
    B b = bla();

    addArtistTests();

    removeArtistTests();

    addToSongCountTests();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
