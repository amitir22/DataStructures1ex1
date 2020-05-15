//
// Created by shvmo on 03/05/2020.
//

#include "ArtistInfo.h"

namespace DataStructuresWet1 {
    DataStructuresWet1::ArtistInfo::ArtistInfo(int artistId, int numOfSongs) : artistId(artistId),
                                                                               numOfSongs(numOfSongs) {
        auto *songInfosArray = new SongInfo[numOfSongs];
        auto *streamCountListPointersArray = new shared_ptr<BiDirectionalNode<StreamCountGroup>>[numOfSongs];
        auto *songInfoListPointersArray = new shared_ptr<BiDirectionalNode<SongInfo>>[this->numOfSongs];

        this->songs = unique_ptr<SongInfo[]>(songInfosArray);
        this->songsPos = unique_ptr<shared_ptr<BiDirectionalNode<StreamCountGroup>>[]>(
                streamCountListPointersArray);
        this->songInfoListPointers = unique_ptr<shared_ptr<BiDirectionalNode<SongInfo>>[]>(
                songInfoListPointersArray);

        for (int i = 0; i < numOfSongs; i++) {
            this->songs[i] = SongInfo(artistId, i, 0);
        }

        this->artistId = artistId;
    }

    ArtistInfo::~ArtistInfo() = default;

    unique_ptr<SongInfo[]> &ArtistInfo::getSongs() {
        return this->songs;
    }

    unique_ptr<shared_ptr<BiDirectionalNode<StreamCountGroup>>[]> &ArtistInfo::getSongsPos() {
        return this->songsPos;
    }

    unique_ptr<shared_ptr<BiDirectionalNode<SongInfo>>[]> &ArtistInfo::getSongInfoListPointers() {
        return this->songInfoListPointers;
    }

    int ArtistInfo::getArtistId() const {
        return this->artistId;
    }


    int ArtistInfo::getNumOfSongs() const {
        return this->numOfSongs;
    }
}
