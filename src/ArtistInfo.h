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
        explicit ArtistInfo(int artistId, int numOfSongs);

        ~ArtistInfo();

        unique_ptr<SongInfo[]> &getSongs();

        unique_ptr<shared_ptr<BiDirectionalNode<StreamCountGroup>>[]> &getSongsPos();

        unique_ptr<shared_ptr<BiDirectionalNode<SongInfo>>[]> &getSongInfoListPointers();

        int getArtistId() const;

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
