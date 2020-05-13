//
// Created by shvmo on 03/05/2020.
//

#ifndef DATASTRUCTURESWET1_MUSICMANAGER_H
#define DATASTRUCTURESWET1_MUSICMANAGER_H


#include "AVLTree.h"
#include "ArtistInfo.h"
#include "BiDirectionalLinkedList.h"
#include "StreamCountGroup.h"
#include "library1.h"

namespace DataStructuresWet1 {
    class MusicManager {
    public:
        MusicManager();

        ~MusicManager();

        StatusType addArtist(int artistId, int numOfSongs);

        StatusType removeArtist(int artistId);

        StatusType addToSongCount(int artistId, int songId);

        StatusType numberOfStreams(int artistId, int songId, int *streams) const;

        StatusType getRecommendedSongs(int numOfSongs, int *artists, int *songs) const;

    private:
        AVLTree<int, ArtistInfo> artistsToSongs;
        BiDirectionalLinkedList<StreamCountGroup> streamCountGroups;

        BiDirectionalNode<SongCollection> initializeNewSongCollectionNode(int artistId, int numOfSongs) const;

        void
        insertNewSongCollectionToTheFirstStreamCountGroup(int artistId,
                                                          const BiDirectionalNode<SongCollection>
                                                          &newSongCollectionNode,
                                                          const shared_ptr<BiDirectionalNode<SongCollection>>
                                                          &newSongCollectionNodePtr,
                                                          const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>>
                                                          &newSongCollectionTreeNode);

        shared_ptr<TNode<int, ArtistInfo>>
        initializeArtistInfoTreePointer(int artistId, int numOfSongs,
                                        const shared_ptr<BiDirectionalNode<SongCollection>> &
                                        songCollectionsPointer) const;

        void removeSongsFromStreamCountGroup(int artistId, ArtistInfo &artistInfo);

        void removeSongFromStreamCountGroup(int artistId, int songId, ArtistInfo &artistInfo);

        shared_ptr<BiDirectionalNode<SongCollection>> initializeNewSongCollectionPointer(int artistId) const;

        static void
        insertToSongCollectionListAndTree(int artistId,
                                          const shared_ptr<BiDirectionalNode<SongCollection>>
                                          &newSongCollectionNodePtr,
                                          const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongCollection>>>>
                                          &newSongCollectionTreeNode,
                                          BiDirectionalLinkedList<SongCollection>
                                          &orderedSongsCollectionsByArtistId,
                                          AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>>
                                          &artistToSongCollections);

        shared_ptr<TNode<int, std::shared_ptr<BiDirectionalNode<SongCollection>>>>
        initializeNewSongCollectionTreePointer(int artistId,
                                               const shared_ptr<BiDirectionalNode<SongCollection>> &
                                               newSongCollectionPointer) const;

        shared_ptr<BiDirectionalNode<StreamCountGroup>>
        createNewStreamCountNode(int artistId,
                                 const shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                 &streamCountGroupPointer,
                                 SongInfo &newSongInfo);

        shared_ptr<BiDirectionalNode<SongCollection>>
        getNewSongCollectionPointer(int artistId,
                                    shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                    &streamCountGroupPointer,
                                    SongInfo &newSongInfo);

        void insertSongInfoToListAndTree(int songId,
                                         const shared_ptr<BiDirectionalNode<SongInfo>> &newSongInfoPointer,
                                         const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>>
                                         &newSongInfoPointerTreeNode,
                                         AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>> &
                                         songInfoPointers,
                                         BiDirectionalLinkedList<SongInfo> &
                                         orderedSongInfosBySongId) const;

        void performUpdateOnSong(int artistId, ArtistInfo &artistInfo,
                                 shared_ptr<BiDirectionalNode<SongInfo>> &newSongInfoPointer,
                                 const shared_ptr<TNode<int, shared_ptr<BiDirectionalNode<SongInfo>>>>
                                 &newSongInfoPointerTreeNode,
                                 shared_ptr<BiDirectionalNode<SongCollection>> &
                                 newSongCollectionPointer);

        void updateSongWithNewSongInfo(int artistId, ArtistInfo &artistInfo, SongInfo &newSongInfo);

        void
        removeLeftOverEmptyNodes(int artistId,
                                 shared_ptr<BiDirectionalNode<StreamCountGroup>> &streamCountGroupPointer,
                                 AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>> &songCollectionTree,
                                 shared_ptr<BiDirectionalNode<SongCollection>> &songCollectionPointer,
                                 const AVLTree<int, shared_ptr<BiDirectionalNode<SongInfo>>>
                                 &songIdToSongInfoPointers);

        static int insertSongsFromSongInfoList(int numOfSongs, int *artists, int *songs, int iteratedSongs,
                                               const BiDirectionalLinkedList<SongInfo> &songInfos);

        static int insertSongsFromSongCollectionList(int numOfSongs, int *artists, int *songs, int iteratedSongs,
                                                     const BiDirectionalLinkedList<SongCollection> &songCollections);

        shared_ptr<BiDirectionalNode<SongCollection>>
        initNewSongCollectionPointerInNewStreamCountNode(int artistId,
                                                         const shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                         &streamCountGroupPointer,
                                                         SongInfo &newSongInfo);

        shared_ptr<BiDirectionalNode<SongCollection>>
        getNewSongCollectionInExistingStreamToCountGroup(int artistId,
                                                         shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                         &streamCountGroupPointer) const;

        shared_ptr<BiDirectionalNode<SongCollection>>
        initNewSongCollectionInExistingStreamCountGroup(int artistId,
                                                        shared_ptr<BiDirectionalNode<StreamCountGroup>>
                                                        &newStreamCountGroupPointer) const;

        void insertArtist(int artistId, int numOfSongs);

        void removeLeftOverStreamNode(shared_ptr<BiDirectionalNode<StreamCountGroup>> &streamCountGroupPointer,
                                      const AVLTree<int, shared_ptr<BiDirectionalNode<SongCollection>>>
                                      &songCollectionTree);
    };
}

#endif //DATASTRUCTURESWET1_MUSICMANAGER_H
