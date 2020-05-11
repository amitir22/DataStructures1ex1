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
        SongInfo();

        SongInfo(int artistId, int songId, int streamCount);

        ~SongInfo();

        int getArtistId() const;

        int getSongId() const;

        int getStreamCount() const;

        void setArtistId(int newArtistId);

        void setSongId(int newSongId);

        void setStreamCount(int newStreamCount);

        friend ostream &operator<<(ostream &os, const SongInfo &songInfo);

    private:
        int artistId;
        int songId;
        int streamCount;
    };
}

#endif //DATASTRUCTURESWET1_SONGINFO_H
