//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_STREAMCOUNTGROUP_H
#define DATASTRUCTURESWET1_STREAMCOUNTGROUP_H

#include "AVLTree.h"
#include "SongCollection.h"
#include "BiDirectionalLinkedList.h"

namespace DataStructuresWet1 {
    typedef int ArtistID;

    class StreamCountGroup {
    public:
        // O(1)
        explicit StreamCountGroup(int streamCount);

        // O(1)
        StreamCountGroup();

        // O(1)
        ~StreamCountGroup();

        // O(1)
        AVLTree<ArtistID, shared_ptr<BiDirectionalNode<SongCollection>>> &getArtistToSongCollectionPointers();

        // O(1)
        BiDirectionalLinkedList<SongCollection> &getOrderedSongsCollectionsByArtistId();

        // O(1)
        int getStreamCount() const;

        // O(1)
        void setArtistToSongCollections(const AVLTree<ArtistID,
                shared_ptr<BiDirectionalNode<SongCollection>>> &newArtistToSongCollectionPointers);

        // O(1)
        void setOrderedSongsCollectionsByArtistId(
                const BiDirectionalLinkedList<SongCollection> &newOrderedSongsCollectionsByArtistId);

        // O(1)
        void setStreamCount(int newStreamCount);

    private:
        AVLTree<ArtistID, shared_ptr<BiDirectionalNode<SongCollection>>> artistToSongCollectionPointers;
        BiDirectionalLinkedList<SongCollection> orderedSongsCollectionsByArtistId;
        int streamCount;
    };
}


#endif //DATASTRUCTURESWET1_STREAMCOUNTGROUP_H
