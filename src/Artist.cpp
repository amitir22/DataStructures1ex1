#include "Artist.h"

Artist::Artist(int numOfSongs) {
    if (numOfSongs <= 0) {
        throw ArtistException();
    }

    assert(numOfSongs > 0);

    songIDToStreamsMap = NoInitArray(abs(numOfSongs));
}

void Artist::AddToSongCount(unsigned int songID) {
    if (this->songIDToStreamsMap.isIndexValid(songID)) {
        int newSongCount = songIDToStreamsMap.get(songID) + 1;
        songIDToStreamsMap.put(songID, newSongCount);
    } else {
        throw InvalidSongIDException();
    }
}

int Artist::GetNumberOfStreams(unsigned int songID) {
    if (this->songIDToStreamsMap.isIndexValid(songID)) {
        try {
            return songIDToStreamsMap.get(songID);
        } catch (NoInitArray::UnInitializedIndexException&) {
            return 0;
        }
    } else {
        throw InvalidSongIDException();
    }
}
