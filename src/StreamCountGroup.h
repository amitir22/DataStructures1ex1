//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_STREAMCOUNTGROUP_H
#define DATASTRUCTURESWET1_STREAMCOUNTGROUP_H

#include "AVLTree.h"
#include "SongCollection.h"
#include "BiDirectionalLinkedList.h"

namespace DataStructuresWet1 {
    class StreamCountGroup {
    public:
        explicit StreamCountGroup(int streamCount);

        StreamCountGroup();

        ~StreamCountGroup();

        AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>>& getArtistToSongCollectionPointers();

        BiDirectionalLinkedList<SongCollection>& getOrderedSongsCollectionsByArtistId();

        int getStreamCount();

        void setArtistToSongCollections(const AVLTree<int,
                shared_ptr<BiDirectionalNode<SongCollection>>>& newArtistToSongCollectionPointers);

        void setOrderedSongsCollectionsByArtistId(
                const BiDirectionalLinkedList<SongCollection>& newOrderedSongsCollectionsByArtistId);

        void setStreamCount(int newStreamCount);

    private:
        AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>> artistToSongCollectionPointers;
        BiDirectionalLinkedList<SongCollection> orderedSongsCollectionsByArtistId;
        int streamCount;
    };
}


#endif //DATASTRUCTURESWET1_STREAMCOUNTGROUP_H
