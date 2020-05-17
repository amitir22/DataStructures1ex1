//
// Created by shvmo on 03/05/2020.
//

#include "SongCollection.h"

namespace DataStructuresWet1 {
    DataStructuresWet1::SongCollection::SongCollection() = default;

    DataStructuresWet1::SongCollection::~SongCollection() = default;

    int SongCollection::getArtistId() const {
        return this->artistId;
    }

    AVLTree<SongID, shared_ptr<BiDirectionalNode<SongInfo>>> &
    DataStructuresWet1::SongCollection::getSongIdsToSongInfoPointers() {
        return this->songIdsToSongInfoPointers;
    }

    BiDirectionalLinkedList<SongInfo> &DataStructuresWet1::SongCollection::getOrderedSongs() {
        return this->orderedSongs;
    }


    void SongCollection::setArtistId(int newArtistId) {
        this->artistId = newArtistId;
    }

    void DataStructuresWet1::SongCollection::setSongIds(
            const AVLTree<SongID, shared_ptr<BiDirectionalNode<SongInfo>>> &newSongIdsToSongInfoPointers) {
        this->songIdsToSongInfoPointers = newSongIdsToSongInfoPointers;
    }

    void DataStructuresWet1::SongCollection::setOrderedSongs(const BiDirectionalLinkedList<SongInfo> &newOrderedSongs) {
        this->orderedSongs = newOrderedSongs;
    }

    ostream &operator<<(ostream &os, const SongCollection &songCollection) {
        os << songCollection.getArtistId();

        return os;
    }
}