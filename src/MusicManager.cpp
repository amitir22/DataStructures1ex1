//
// Created by shvmo on 03/05/2020.
//

#include "MusicManager.h"
#include <cassert>

namespace DataStructuresWet1 {
    MusicManager::MusicManager() : artistsToSongs(), streamCountGroups() {
        StreamCountGroup streamCountGroup(0);

        this->streamCountGroups.append(streamCountGroup);
    }

    MusicManager::~MusicManager() = default;

    StatusType MusicManager::addArtist(int artistId, int numOfSongs) {
        if (numOfSongs <= 0 || artistId <= 0) {
            return INVALID_INPUT;
        }

        if (this->artistsToSongs.find(artistId) != nullptr) {
            return FAILURE;
        }

        insertArtist(artistId, numOfSongs);

        return SUCCESS;
    }

    StatusType MusicManager::removeArtist(int artistId) {
        if (artistId <= 0) {
            return INVALID_INPUT;
        }

        shared_ptr<TNode<int, ArtistInfo>> artistInfoTreeNode = artistsToSongs.find(artistId);

        if (artistInfoTreeNode == nullptr) {
            return FAILURE;
        }

        ArtistInfo &artistInfo = artistInfoTreeNode->getInfo();

        removeSongsFromStreamCountGroup(artistId, artistInfo);

        artistsToSongs.remove(artistId);

        return SUCCESS;
    }

    StatusType MusicManager::addToSongCount(int artistId, int songId) {
        if (artistId <= 0 || songId < 0) {
            return INVALID_INPUT;
        }

        shared_ptr<TNode<int, ArtistInfo>> artistInfoTreeNode = artistsToSongs.find(artistId);

        if (artistInfoTreeNode == nullptr) {
            return FAILURE;
        }

        ArtistInfo &artistInfo = artistInfoTreeNode->getInfo();

        if (songId >= artistInfo.getNumOfSongs()) {
            return INVALID_INPUT;
        }

        SongInfo newSongInfo = artistInfo.getSongs()[songId];

        newSongInfo.setStreamCount(artistInfo.getSongs()[songId].getStreamCount() + 1);

        updateSongWithNewSongInfo(artistId, artistInfo, newSongInfo);

        return SUCCESS;
    }

    StatusType MusicManager::numberOfStreams(int artistId, int songId, int *streams) const {
        if (songId < 0 || artistId <= 0 || streams == nullptr) {
            return INVALID_INPUT;
        }

        shared_ptr<TNode<int, ArtistInfo>> artistInfoTreeNode = this->artistsToSongs.find(artistId);

        if (artistInfoTreeNode == nullptr) {
            return FAILURE;
        }

        ArtistInfo &artistInfo = artistInfoTreeNode->getInfo();

        if (songId >= artistInfo.getNumOfSongs()) {
            return INVALID_INPUT;
        }

        *streams = artistInfo.getSongs()[songId].getStreamCount();

        return SUCCESS;
    }

    StatusType MusicManager::getRecommendedSongs(int numOfSongs, int *artists, int *songs) const {
        if (numOfSongs <= 0) {
            return ALLOCATION_ERROR; // On purpose that's what the segel asked for
        }

        int iteratedSongs = 0;
        shared_ptr<BiDirectionalNode<StreamCountGroup>> currentStreamGroup;
        for (currentStreamGroup = this->streamCountGroups.getLast(); currentStreamGroup != nullptr &&
                                                                     iteratedSongs < numOfSongs;
             currentStreamGroup = currentStreamGroup->getPrevious().lock()) {
            // Iterating on each stream group node from the last
            BiDirectionalLinkedList<SongCollection> &songCollections =
                    currentStreamGroup->getValue().getOrderedSongsCollectionsByArtistId();

            iteratedSongs = insertSongsFromSongCollectionList(numOfSongs, artists, songs, iteratedSongs,
                                                              songCollections);
        }

        if (iteratedSongs < numOfSongs) {
            return FAILURE;
        } else {
            assert(iteratedSongs == numOfSongs);

            return SUCCESS;
        }
    }

    shared_ptr<TNode<int, ArtistInfo>>
    MusicManager::initializeArtistInfoTreePointer(int artistId, int numOfSongs,
                                                  const shared_ptr<BiDirectionalNode<SongCollection>> &
                                                  songCollectionsPointer) const {
        shared_ptr<ArtistInfo> artistInfoPointer = make_shared<ArtistInfo>(artistId, numOfSongs);

        // initializing the artistInfo list pointers to the streamCountGroup list to the first node
        for (int i = 0; i < numOfSongs; ++i) {
            artistInfoPointer->getSongsPos()[i] = this->streamCountGroups.getFirst();
        }

        shared_ptr<BiDirectionalNode<SongInfo>> currentSongInfo =
                songCollectionsPointer->getValue().getOrderedSongs().getFirst();
        int i;
        for (i = 0, currentSongInfo = songCollectionsPointer->getValue().getOrderedSongs().getFirst();
             i < numOfSongs; ++i, currentSongInfo = currentSongInfo->getNext()) {
            artistInfoPointer->getSongInfoListPointers()[i] = currentSongInfo;
        }

        assert(currentSongInfo == nullptr);

        shared_ptr<TNode<int, ArtistInfo>> newArtistIntoTreeNode =
                make_shared<TNode<int, ArtistInfo>>();

        newArtistIntoTreeNode->setKey(artistId);
        newArtistIntoTreeNode->setInfoPointer(artistInfoPointer);

        return newArtistIntoTreeNode;
    }

    void
    MusicManager::insertNewSongCollectionToTheFirstStreamCountGroup(int artistId,
                                                                    const BiDirectionalNode<SongCollection>
                                                                    &newSongCollectionNode,
                                                                    const shared_ptr<BiDirectionalNode<SongCollection>> &
                                                                    newSongCollectionNodePtr,
                                                                    const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>> &
                                                                    newSongCollectionTreeNode) {
        BiDirectionalLinkedList<SongCollection> &orderedSongsCollectionsByArtistId =
                this->streamCountGroups.getFirst()->getValue().getOrderedSongsCollectionsByArtistId();

        AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>> &artistToSongCollections =
                this->streamCountGroups.getFirst()->getValue().getArtistToSongCollectionPointers();

        insertToSongCollectionListAndTree(artistId, newSongCollectionNodePtr,
                                          newSongCollectionTreeNode,
                                          orderedSongsCollectionsByArtistId,
                                          artistToSongCollections);
    }

    BiDirectionalNode<SongCollection>
    MusicManager::initializeNewSongCollectionNode(int artistId, int numOfSongs) const {
        /** Initiating new song collection with streamCount equals to zero, without inserting to the inner tree
         * in this case the tree in the first node will not be needed because we will never insert a new song there
         * because the stream count of a song can only go up
         * /
         */
        SongCollection songCollection;

        for (int i = 0; i < numOfSongs; i++) {
            songCollection.getOrderedSongs().append(SongInfo(artistId, i, 0));
        }

        songCollection.setArtistId(artistId);

        BiDirectionalNode<SongCollection> newSongCollectionNode;
        newSongCollectionNode.setValue(songCollection);

        return newSongCollectionNode;
    }

    void MusicManager::removeSongsFromStreamCountGroup(int artistId, ArtistInfo &artistInfo) {
        for (int i = 0; i < artistInfo.getNumOfSongs(); ++i) {
            StreamCountGroup &streamCountNode = artistInfo.getSongsPos()[i]->getValue();

            shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>> songCollectionPointer =
                    streamCountNode.getArtistToSongCollectionPointers().find(artistId);

            // If it's null that means that we already removed a song from the same stream count group
            if (songCollectionPointer != nullptr) {
                // Remove the pointer from the list
                streamCountNode.getOrderedSongsCollectionsByArtistId().remove(songCollectionPointer->getInfo());

                // Remove the artist
                streamCountNode.getArtistToSongCollectionPointers().remove(artistId);

                // Check if the list and tree in this stream count group are empty if so then remove them

                removeLeftOverStreamNode(artistInfo.getSongsPos()[i],
                                         streamCountNode.getArtistToSongCollectionPointers());
            }
        }
    }

    void MusicManager::removeSongFromStreamCountGroup(int artistId, int songId, ArtistInfo &artistInfo) {
        // Get the node in which the song is in the StreamCountGroup list
        shared_ptr<BiDirectionalNode<StreamCountGroup>> streamCountGroupPointer = artistInfo.getSongsPos()[songId];

        AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>> &songCollectionTree =
                streamCountGroupPointer->getValue().getArtistToSongCollectionPointers();

        // Get the songCollection in which the song is in. O(log(n)) worst case
        shared_ptr<BiDirectionalNode<SongCollection>> songCollectionPointer =
                songCollectionTree.find(artistId)->getInfo();

        AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> &songIdToSongInfoPointers =
                songCollectionPointer->getValue().getSongIdsToSongInfoPointers();

        if (songIdToSongInfoPointers.getRoot() != nullptr) {
            // Can't happen on zero stream count node
            assert(streamCountGroupPointer->getValue().getStreamCount() != 0);

            // Now remove the song from the tree in O(log(m))
            songIdToSongInfoPointers.remove(songId);
        }

        // Remove the song from the list in O(1) by sending the pointer of the node in the list
        songCollectionPointer->getValue().getOrderedSongs().remove(artistInfo.getSongInfoListPointers()[songId]);

        removeLeftOverEmptyNodes(artistId, streamCountGroupPointer, songCollectionTree,
                                 songCollectionPointer,
                                 songIdToSongInfoPointers);
    }

    shared_ptr<BiDirectionalNode<SongCollection>> MusicManager::initializeNewSongCollectionPointer(int artistId) const {
        SongCollection newSongCollection;
        newSongCollection.setArtistId(artistId);
        shared_ptr<BiDirectionalNode<SongCollection>> newSongCollectionPointer =
                make_shared<BiDirectionalNode<SongCollection>>();

        newSongCollectionPointer->setValue(newSongCollection);

        return newSongCollectionPointer;
    }

    void
    MusicManager::insertToSongCollectionListAndTree(int artistId,
                                                    const shared_ptr<BiDirectionalNode<SongCollection>>
                                                    &newSongCollectionNodePtr,
                                                    const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>>
                                                    &newSongCollectionTreeNode,
                                                    BiDirectionalLinkedList<SongCollection>
                                                    &orderedSongsCollectionsByArtistId,
                                                    AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>>
                                                    &artistToSongCollections) {
        // O(log(n))
        artistToSongCollections.insert(newSongCollectionTreeNode);

        // Now we get the next tree node in order to use it to insert to the orderedSongsCollectionsByArtistId list
        shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>> nextTreeNodeInOrder =
                artistToSongCollections.getNextNodeInOrder(artistToSongCollections.find(artistId));

        if (nextTreeNodeInOrder == nullptr) {
            // In this case we put it in te end of the list
            orderedSongsCollectionsByArtistId.insertNodeAfter(orderedSongsCollectionsByArtistId.getLast(),
                                                              newSongCollectionNodePtr);
        } else {
            // Put it right after the previous value of the next in order node
            orderedSongsCollectionsByArtistId.insertNodeAfter(nextTreeNodeInOrder->getInfo()->getPrevious().lock(),
                                                              newSongCollectionNodePtr);
        }
    }

    shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>>
    MusicManager::initializeNewSongCollectionTreePointer(int artistId,
                                                         const shared_ptr<BiDirectionalNode<SongCollection>> &
                                                         newSongCollectionPointer) const {
        shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>> newSongCollectionTreeNode =
                make_shared<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>>();

        newSongCollectionTreeNode->setInfo(newSongCollectionPointer);
        newSongCollectionTreeNode->setKey(artistId);

        return newSongCollectionTreeNode;
    }

    shared_ptr<BiDirectionalNode<StreamCountGroup>>
    MusicManager::createNewStreamCountNodeWithSongInfo(int artistId,
                                                       const shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                       &streamCountGroupPointer,
                                                       SongInfo &newSongInfo) {
        shared_ptr<BiDirectionalNode<SongCollection>> newSongCollectionPointer =
                initializeNewSongCollectionPointer(artistId);

        // Create a node between the current one and the next after it
        shared_ptr<BiDirectionalNode<StreamCountGroup>> newStreamCountGroupPointer =
                make_shared<BiDirectionalNode<StreamCountGroup>>();

        newStreamCountGroupPointer->setValue(StreamCountGroup(newSongInfo.getStreamCount()));

        shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>> newSongCollectionTreePointer =
                initializeNewSongCollectionTreePointer(artistId, newSongCollectionPointer);

        // in O(log(n))
        insertToSongCollectionListAndTree(artistId,
                                          newSongCollectionPointer,
                                          newSongCollectionTreePointer,
                                          newStreamCountGroupPointer->getValue()
                                                  .getOrderedSongsCollectionsByArtistId(),
                                          newStreamCountGroupPointer->getValue()
                                                  .getArtistToSongCollectionPointers());

        return newStreamCountGroupPointer;
    }

    shared_ptr<BiDirectionalNode<SongCollection>>
    MusicManager::getNewSongCollectionPointer(int artistId,
                                              shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                              &streamCountGroupPointer,
                                              SongInfo &newSongInfo) {
        // Check if the next node in the list doesn't have the same stream count number
        if (streamCountGroupPointer->getNext() == nullptr ||
            streamCountGroupPointer->getNext()->getValue().getStreamCount() != newSongInfo.getStreamCount()) {
            return initNewSongCollectionPointerInNewStreamCountNode(artistId, streamCountGroupPointer, newSongInfo);
        } else {
            return getNewSongCollectionInExistingStreamToCountGroup(artistId, streamCountGroupPointer);

        }
    }

    shared_ptr<BiDirectionalNode<SongCollection>>
    MusicManager::getNewSongCollectionInExistingStreamToCountGroup(int artistId,
                                                                   shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                                   &streamCountGroupPointer) const {
        std::shared_ptr<BiDirectionalNode<StreamCountGroup>> newStreamCountGroupPointer =
                streamCountGroupPointer->getNext();

        std::shared_ptr<TNode<int, std::shared_ptr<BiDirectionalNode<SongCollection>>>> newSongCollectionTreePointer =
                newStreamCountGroupPointer->getValue().getArtistToSongCollectionPointers().find(artistId);

        if (newSongCollectionTreePointer == nullptr) {
            // In this case we need to create and insert a new song collection into the tree and list in this node
            return initNewSongCollectionInExistingStreamCountGroup(artistId, newStreamCountGroupPointer);

        } else {
            return newSongCollectionTreePointer->getInfo();
        }
    }

    void
    MusicManager::insertSongInfoToListAndTree(int songId,
                                              const shared_ptr<BiDirectionalNode<SongInfo>> &newSongInfoPointer,
                                              const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>>
                                              &newSongInfoPointerTreeNode,
                                              AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> &
                                              songInfoPointers,
                                              BiDirectionalLinkedList<SongInfo> &
                                              orderedSongInfosBySongId) const {
        songInfoPointers.insert(newSongInfoPointerTreeNode);

        shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>> nextSongPointer =
                songInfoPointers.getNextNodeInOrder(songInfoPointers.find(songId));

        if (nextSongPointer == nullptr) {
            // In this case we put it in te end of the list
            orderedSongInfosBySongId.insertNodeAfter(orderedSongInfosBySongId.getLast(),
                                                     newSongInfoPointer);
        } else {
            // Put it right after the previous value of the next in order node
            orderedSongInfosBySongId.insertNodeAfter(nextSongPointer->getInfo()->getPrevious().lock(),
                                                     newSongInfoPointer);
        }
    }

    void MusicManager::performUpdateOnSong(int artistId,
                                           ArtistInfo &artistInfo,
                                           shared_ptr<BiDirectionalNode<SongInfo>> &newSongInfoPointer,
                                           const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>>
                                           &newSongInfoPointerTreeNode,
                                           shared_ptr<BiDirectionalNode<SongCollection>> &
                                           newSongCollectionPointer) {
        AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> &songInfoPointers =
                newSongCollectionPointer->getValue().getSongIdsToSongInfoPointers();

        BiDirectionalLinkedList<SongInfo> &orderedSongInfosBySongId =
                newSongCollectionPointer->getValue().getOrderedSongs();

        int songId = newSongInfoPointer->getValue().getSongId();
        // All allocations are finished now, it is safe to remove
        removeSongFromStreamCountGroup(artistId, songId, artistInfo);

        insertSongInfoToListAndTree(songId,
                                    newSongInfoPointer,
                                    newSongInfoPointerTreeNode,
                                    songInfoPointers,
                                    orderedSongInfosBySongId);

        // Update the relevant artistInfo fields
        artistInfo.getSongs()[songId] = newSongInfoPointer->getValue();
        artistInfo.getSongInfoListPointers()[songId] = newSongInfoPointer;

        assert(artistInfo.getSongsPos()[songId]->getNext() != nullptr);
        assert(artistInfo.getSongsPos()[songId]->getNext()->getValue().getStreamCount() ==
               artistInfo.getSongs()[songId].getStreamCount());

        artistInfo.getSongsPos()[songId] = artistInfo.getSongsPos()[songId]->getNext();
    }

    void MusicManager::updateSongWithNewSongInfo(int artistId, ArtistInfo &artistInfo,
                                                 SongInfo &newSongInfo) {
        // Get the node in which the song is in the StreamCountGroup list
        shared_ptr<BiDirectionalNode<StreamCountGroup>> streamCountGroupPointer =
                artistInfo.getSongsPos()[newSongInfo.getSongId()];

        // Allocate stuff first
        shared_ptr<BiDirectionalNode<SongInfo>> newSongInfoPointer =
                make_shared<BiDirectionalNode<SongInfo>>();

        newSongInfoPointer->setValue(newSongInfo);

        shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>> newSongInfoPointerTreeNode =
                make_shared<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>>();

        newSongInfoPointerTreeNode->setKey(newSongInfo.getSongId());
        newSongInfoPointerTreeNode->setInfo(newSongInfoPointer);

        shared_ptr<BiDirectionalNode<SongCollection>> newSongCollectionPointer =
                getNewSongCollectionPointer(artistId,
                                            streamCountGroupPointer,
                                            newSongInfo);

        performUpdateOnSong(artistId,
                            artistInfo,
                            newSongInfoPointer,
                            newSongInfoPointerTreeNode,
                            newSongCollectionPointer);
    }

    void MusicManager::removeLeftOverEmptyNodes(int artistId,
                                                shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                &streamCountGroupPointer,
                                                AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>>
                                                &songCollectionTree,
                                                shared_ptr<BiDirectionalNode<SongCollection>>
                                                &songCollectionPointer,
                                                const AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>>
                                                &songIdToSongInfoPointers) {
        // If the songCollection is empty we will remove the songCollection pointer from the songCollectionTree
        if (songCollectionPointer->getValue().getOrderedSongs().getFirst() == nullptr) {
            // If the list inside is empty so must be the tree but not vise versa when dealing with stream group 0
            assert(songIdToSongInfoPointers.getRoot() == nullptr);

            streamCountGroupPointer->getValue().getOrderedSongsCollectionsByArtistId().remove(songCollectionPointer);
            songCollectionTree.remove(artistId);
        }

        removeLeftOverStreamNode(streamCountGroupPointer, songCollectionTree);
    }

    int MusicManager::insertSongsFromSongInfoList(int numOfSongs, int *artists, int *songs, int iteratedSongs,
                                                  const BiDirectionalLinkedList<SongInfo> &songInfos) {
        BiDirectionalNode<SongInfo> *currentSongInfo;
        for (currentSongInfo = songInfos.getFirstPointer(); currentSongInfo != nullptr && iteratedSongs < numOfSongs;
             currentSongInfo = currentSongInfo->getNextPointer(), ++iteratedSongs) {
            // / Iterating on each song info node from the first

            artists[iteratedSongs] = currentSongInfo->getValue().getArtistId();
            songs[iteratedSongs] = currentSongInfo->getValue().getSongId();
        }

        return iteratedSongs;
    }

    int MusicManager::insertSongsFromSongCollectionList(int numOfSongs, int *artists, int *songs,
                                                        int iteratedSongs,
                                                        const BiDirectionalLinkedList<SongCollection>
                                                        &songCollections) {
        BiDirectionalNode<SongCollection> *currentSongCollection;
        for (currentSongCollection = songCollections.getFirstPointer(); currentSongCollection != nullptr &&
                                                                        iteratedSongs < numOfSongs;
             currentSongCollection = currentSongCollection->getNextPointer()) {
            // Iterating on each song collection node from the first
            BiDirectionalLinkedList<SongInfo> &songInfos = currentSongCollection->getValue().getOrderedSongs();

            iteratedSongs = insertSongsFromSongInfoList(numOfSongs, artists, songs, iteratedSongs, songInfos);
        }

        return iteratedSongs;
    }

    shared_ptr<BiDirectionalNode<SongCollection>>
    MusicManager::initNewSongCollectionPointerInNewStreamCountNode(int artistId,
                                                                   const shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                                   &streamCountGroupPointer,
                                                                   SongInfo &newSongInfo) {
        std::shared_ptr<BiDirectionalNode<StreamCountGroup>> newStreamCountGroupPointer =
                createNewStreamCountNodeWithSongInfo(artistId,
                                                     streamCountGroupPointer,
                                                     newSongInfo);

        // The first songCollection node will be the right one because the stream count node is new
        std::shared_ptr<BiDirectionalNode<SongCollection>> newSongCollectionPointer =
                newStreamCountGroupPointer->getValue().getOrderedSongsCollectionsByArtistId().getFirst();

        assert(newSongCollectionPointer != nullptr);

        // last allocation was made so it is safe to insert because song collection will be the last allocated object
        streamCountGroups.insertNodeAfter(streamCountGroupPointer, newStreamCountGroupPointer);

        return newSongCollectionPointer;
    }

    shared_ptr<BiDirectionalNode<SongCollection>>
    MusicManager::initNewSongCollectionInExistingStreamCountGroup(int artistId,
                                                                  shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                                  &newStreamCountGroupPointer) const {
        std::shared_ptr<BiDirectionalNode<SongCollection>> newSongCollectionPointer =
                initializeNewSongCollectionPointer(artistId);

        shared_ptr<TNode<int, std::shared_ptr<BiDirectionalNode<SongCollection>>>>
                newSongCollectionTreePointer = initializeNewSongCollectionTreePointer(artistId,
                                                                                      newSongCollectionPointer);
        // in O(log(n))
        insertToSongCollectionListAndTree(artistId,
                                          newSongCollectionPointer,
                                          newSongCollectionTreePointer,
                                          newStreamCountGroupPointer->getValue()
                                                  .getOrderedSongsCollectionsByArtistId(),
                                          newStreamCountGroupPointer->getValue()
                                                  .getArtistToSongCollectionPointers());

        return newSongCollectionPointer;
    }

    void MusicManager::insertArtist(int artistId, int numOfSongs) {
        // First we allocate all the memory needed
        BiDirectionalNode<SongCollection> newSongCollectionNode = initializeNewSongCollectionNode(artistId, numOfSongs);

        std::shared_ptr<BiDirectionalNode<SongCollection>> newSongCollectionNodePtr =
                std::make_shared<BiDirectionalNode<SongCollection>>(newSongCollectionNode);

        std::shared_ptr<TNode<int, std::shared_ptr<BiDirectionalNode<SongCollection>>>> newSongCollectionTreeNode =
                std::make_shared<TNode<int, std::shared_ptr<BiDirectionalNode<SongCollection>>>>();

        newSongCollectionTreeNode->setInfo(newSongCollectionNodePtr);
        newSongCollectionTreeNode->setKey(artistId);

        std::shared_ptr<TNode<int, ArtistInfo>> newArtistIntoTreeNode =
                initializeArtistInfoTreePointer(artistId,
                                                numOfSongs,
                                                newSongCollectionNodePtr);

        // All allocations finished, now inserting
        artistsToSongs.insert(newArtistIntoTreeNode);

        insertNewSongCollectionToTheFirstStreamCountGroup(artistId, newSongCollectionNode, newSongCollectionNodePtr,
                                                          newSongCollectionTreeNode);
    }

    void
    MusicManager::removeLeftOverStreamNode(shared_ptr<BiDirectionalNode<StreamCountGroup>> &streamCountGroupPointer,
                                           const AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>>
                                           &songCollectionTree) {
        if (songCollectionTree.getRoot() == nullptr && streamCountGroupPointer != streamCountGroups.getFirst()) {
            streamCountGroups.remove(streamCountGroupPointer);
        }
    }
}
