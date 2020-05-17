//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_ARTISTINFO_H
#define DATASTRUCTURESWET1_ARTISTINFO_H

#include <memory>
#include "StreamCountGroup.h"
#include "SongInfo.h"

namespace DataStructuresWet1 {
    using std::unique_ptr;
    using std::weak_ptr;

    class ArtistInfo {
    public:
        // O(n) - where n is numOfSongs
        explicit ArtistInfo(int artistId, int numOfSongs);

        // O(1)
        ~ArtistInfo();

        // O(1)
        unique_ptr<SongInfo[]> &getSongs();

        // O(1)
        unique_ptr<shared_ptr<BiDirectionalNode<StreamCountGroup>>[]> &getSongsPos();

        // O(1)
        unique_ptr<shared_ptr<BiDirectionalNode<SongInfo>>[]> &getSongInfoListPointers();

        // O(1)
        int getArtistId() const;

        // O(1)
        int getNumOfSongs() const;

    private:
        int artistId;
        int numOfSongs;
        unique_ptr<SongInfo[]> songs;
        unique_ptr<shared_ptr<BiDirectionalNode<StreamCountGroup>>[]> songsPos;
        unique_ptr<shared_ptr<BiDirectionalNode<SongInfo>>[]> songInfoListPointers;
    };
}

#endif //DATASTRUCTURESWET1_ARTISTINFO_H
