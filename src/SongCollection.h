//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_SONGCOLLECTION_H
#define DATASTRUCTURESWET1_SONGCOLLECTION_H


#include "AVLTree.h"
#include "BiDirectionalLinkedList.h"
#include "SongInfo.h"

namespace DataStructuresWet1 {
    class SongCollection {
    public:
        SongCollection();

        ~SongCollection();

        int getArtistId() const;

        AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> &getSongIdsToSongInfoPointers();

        BiDirectionalLinkedList<SongInfo> &getOrderedSongs();

        void setArtistId(int newArtistId);

        void setSongIds(const  AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> &newSongIdsToSongInfoPointers);

        void setOrderedSongs(const BiDirectionalLinkedList<SongInfo> &newOrderedSongs);

        friend ostream &operator<<(ostream &os, const SongCollection &songCollection);

    private:
        int artistId;
        AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> songIdsToSongInfoPointers;
        BiDirectionalLinkedList<SongInfo> orderedSongs;
    };
}

#endif //DATASTRUCTURESWET1_SONGCOLLECTION_H
