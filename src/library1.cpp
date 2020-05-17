#include "library1.h"
#include "MusicManager.h"

using DataStructuresWet1::MusicManager;
using std::bad_alloc;

void *Init() {
    try {
        auto *musicManager = new MusicManager();

        return (void *) musicManager;
    } catch (const bad_alloc &exception) {
        return nullptr;
    }
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    try {
        auto *musicManager = (MusicManager *) DS;

        return musicManager->addArtist(artistID, numOfSongs);
    } catch (const bad_alloc &exception) {
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveArtist(void *DS, int artistID) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    try {
        auto *musicManager = (MusicManager *) DS;

        return musicManager->removeArtist(artistID);
    } catch (const bad_alloc &exception) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    try {
        auto *musicManager = (MusicManager *) DS;

        return musicManager->addToSongCount(artistID, songID);
    } catch (const bad_alloc &exception) {
        return ALLOCATION_ERROR;
    }
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    try {
        auto *musicManager = (MusicManager *) DS;

        return musicManager->numberOfStreams(artistID, songID, streams);
    } catch (const bad_alloc &exception) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    try {
        auto *musicManager = (MusicManager *) DS;

        return musicManager->getRecommendedSongs(numOfSongs, artists, songs);
    } catch (const bad_alloc &exception) {
        return ALLOCATION_ERROR;
    }
}

void Quit(void **DS) {
    if (DS != nullptr) {
        auto *musicManager = (MusicManager *) *DS;

        delete musicManager;

        *DS = nullptr;
    }
}
