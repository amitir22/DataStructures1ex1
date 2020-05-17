//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_SONGCOLLECTION_H
#define DATASTRUCTURESWET1_SONGCOLLECTION_H


#include "AVLTree.h"
#include "BiDirectionalLinkedList.h"
#include "SongInfo.h"

namespace DataStructuresWet1 {
    typedef int SongID;

    class SongCollection {
    public:
        // O(1)
        SongCollection();

        // O(1)
        ~SongCollection();

        // O(1)
        int getArtistId() const;

        // O(1)
        AVLTree<SongID, shared_ptr<BiDirectionalNode<SongInfo>>> &getSongIdsToSongInfoPointers();

        // O(1)
        BiDirectionalLinkedList<SongInfo> &getOrderedSongs();

        // O(1)
        void setArtistId(int newArtistId);

        // O(1)
        void setSongIds(const AVLTree<SongID, shared_ptr<BiDirectionalNode<SongInfo>>> &newSongIdsToSongInfoPointers);

        // O(1)
        void setOrderedSongs(const BiDirectionalLinkedList<SongInfo> &newOrderedSongs);

        // O(1)
        friend ostream &operator<<(ostream &os, const SongCollection &songCollection);

    private:
        int artistId;
        AVLTree<SongID, shared_ptr<BiDirectionalNode<SongInfo>>> songIdsToSongInfoPointers;
        BiDirectionalLinkedList<SongInfo> orderedSongs;
    };
}

#endif //DATASTRUCTURESWET1_SONGCOLLECTION_H
