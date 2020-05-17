//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_SONGINFO_H
#define DATASTRUCTURESWET1_SONGINFO_H


#include <iostream>

namespace DataStructuresWet1 {
    using std::ostream;

    class SongInfo {
    public:
        // O(1)
        SongInfo();

        // O(1)
        SongInfo(int artistId, int songId, int streamCount);

        // O(1)
        ~SongInfo();

        // O(1)
        int getArtistId() const;

        // O(1)
        int getSongId() const;

        // O(1)
        int getStreamCount() const;

        // O(1)
        void setArtistId(int newArtistId);

        // O(1)
        void setSongId(int newSongId);

        // O(1)
        void setStreamCount(int newStreamCount);

        // O(1)
        friend ostream &operator<<(ostream &os, const SongInfo &songInfo);

    private:
        int artistId;
        int songId;
        int streamCount;
    };
}

#endif //DATASTRUCTURESWET1_SONGINFO_H
