//
// Created by shvmo on 03/05/2020.
//

#include "SongInfo.h"

namespace DataStructuresWet1 {
    SongInfo::SongInfo() = default;

    SongInfo::SongInfo(int artistId, int songId, int streamCount) : artistId(artistId), songId(songId),
                                                                    streamCount(streamCount) {}

    SongInfo::~SongInfo() = default;

    int SongInfo::getArtistId() {
        return this->artistId;
    }

    int SongInfo::getSongId() const {
        return this->songId;
    }

    int SongInfo::getStreamCount() {
        return this->streamCount;
    }

    void SongInfo::setArtistId(int newArtistId) {
        this->artistId = newArtistId;
    }

    void SongInfo::setSongId(int newSongId) {
        this->songId = newSongId;
    }

    void SongInfo::setStreamCount(int newStreamCount) {
        this->streamCount = newStreamCount;
    }

    ostream &operator<<(ostream &os, const SongInfo &songInfo) {
        os << songInfo.getSongId();

        return os;
    }
}