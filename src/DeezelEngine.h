#ifndef DEEZEL_DEEZELENGINE_H
#define DEEZEL_DEEZELENGINE_H

#include "library1.h"
#include <exception>

class DeezelEngine {
private:

public:
    // O(1)
    void *Init();

    // log(n) + m
    StatusType AddArtist(int artistID, int numOfSongs);

    // m * log(n)
    StatusType RemoveArtist(int artistID);

    // log(n) + log(m)
    StatusType AddToSongCount(int artistID, int songID);

    // log(n)
    StatusType NumberOfStreams(int artistID, int songID, int *streams);

    // m
    StatusType GetRecommendedSongs(int numOfSongs, int *artists, int *songs);

    // n+m
    void Quit();

    class DeezelEngineException : public std::exception {
        const char *what() const noexcept override {
            return "Improper usage of DeezelEngine";
        }
    };
};


#endif //DEEZEL_DEEZELENGINE_H
