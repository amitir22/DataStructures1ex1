//
// Created by shvmo on 03/05/2020.
//

#include "ArtistInfo.h"

namespace DataStructuresWet1 {
    DataStructuresWet1::ArtistInfo::ArtistInfo(int artistId, int numOfSongs) : artistId(artistId),
                                                                               numOfSongs(numOfSongs) {
        this->songs = unique_ptr<SongInfo[]>(new SongInfo[numOfSongs]);
        this->songsPos = unique_ptr<shared_ptr<BiDirectionalNode<StreamCountGroup>>[]>(
                new shared_ptr<BiDirectionalNode<StreamCountGroup>>[numOfSongs]);
        this->songInfoListPointers = unique_ptr<shared_ptr<BiDirectionalNode<SongInfo>>[]>(
                new shared_ptr<BiDirectionalNode<SongInfo>>[this->numOfSongs]);

        for (int i = 0; i < numOfSongs; i++) {
            this->songs[i] = SongInfo(artistId, i, 0);
        }

        this->artistId = artistId;
    }

    ArtistInfo::ArtistInfo() = default;

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

    int ArtistInfo::getArtistId() {
        return this->artistId;
    }


    int ArtistInfo::getNumOfSongs() {
        return this->numOfSongs;
    }
}
