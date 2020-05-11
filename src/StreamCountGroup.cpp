//
// Created by shvmo on 03/05/2020.
//

#include "StreamCountGroup.h"

namespace DataStructuresWet1 {
    StreamCountGroup::StreamCountGroup(int streamCount) : streamCount(streamCount) {
    }

    StreamCountGroup::StreamCountGroup() = default;

    DataStructuresWet1::StreamCountGroup::~StreamCountGroup() = default;

    AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>> &
    DataStructuresWet1::StreamCountGroup::getArtistToSongCollectionPointers() {
        return this->artistToSongCollectionPointers;
    }

    BiDirectionalLinkedList<SongCollection> &
    DataStructuresWet1::StreamCountGroup::getOrderedSongsCollectionsByArtistId() {
        return this->orderedSongsCollectionsByArtistId;
    }

    void DataStructuresWet1::StreamCountGroup::setArtistToSongCollections(
            const AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>> &newArtistToSongCollectionPointers) {
        this->artistToSongCollectionPointers = newArtistToSongCollectionPointers;
    }

    void DataStructuresWet1::StreamCountGroup::setOrderedSongsCollectionsByArtistId(
            const BiDirectionalLinkedList<SongCollection> &newOrderedSongsCollectionsByArtistId) {
        this->orderedSongsCollectionsByArtistId = newOrderedSongsCollectionsByArtistId;
    }

    int StreamCountGroup::getStreamCount() {
        return this->streamCount;
    }

    void StreamCountGroup::setStreamCount(int newStreamCount) {
        this->streamCount = newStreamCount;
    }
}