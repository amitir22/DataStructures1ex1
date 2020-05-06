#ifndef DEEZEL_ARTIST_H
#define DEEZEL_ARTIST_H

#include <exception>
#include <cassert>
#include "NoInitArray.h"

typedef int Song;

class Artist {
private:
    NoInitArray songIDToStreamsMap;
public:
    Artist(int numOfSongs);

    void AddToSongCount(unsigned int songID);
    int GetNumberOfStreams(unsigned int songID);

    class ArtistException : public std::exception {
        const char *what() const noexcept override {
            return "Improper usage of Artist class";
        }
    };

    class InvalidSongIDException : public ArtistException {
        const char *what() const noexcept override {
            return "Invalid song id was given";
        }
    };
};

#endif //DEEZEL_ARTIST_H
