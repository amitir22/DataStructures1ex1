#include "DeezelEngine.h"

void *DeezelEngine::Init() {
    return nullptr;
}

StatusType DeezelEngine::AddArtist(int artistID, int numOfSongs) {
    return INVALID_INPUT;
}

StatusType DeezelEngine::RemoveArtist(int artistID) {
    return INVALID_INPUT;
}

StatusType DeezelEngine::AddToSongCount(int artistID, int songID) {
    return INVALID_INPUT;
}

StatusType DeezelEngine::NumberOfStreams(int artistID, int songID, int *streams) {
    return INVALID_INPUT;
}

StatusType DeezelEngine::GetRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    return INVALID_INPUT;
}

void DeezelEngine::Quit() {

}

