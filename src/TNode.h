//
// Created by shvmo on 29/04/2020.
//

#ifndef DATASTRUCTURESWET1_TNODE_H
#define DATASTRUCTURESWET1_TNODE_H


#include <memory>

using std::shared_ptr;

template<class Key, class Info>
class TNode {
public:
    TNode();

    ~TNode();

    Key &getKey();

    Info &getInfo();

    shared_ptr<Info> getInfoPointer();

    shared_ptr<TNode<Key, Info>> getLeft();

    shared_ptr<TNode<Key, Info>> getRight();

    void setKey(const Key &newKey);

    int getHeight();

    void setInfo(const Info &info);

    void setInfoPointer(shared_ptr<Info> newInfoPointer);

    void setLeft(shared_ptr<TNode<Key, Info>> left);

    void setRight(shared_ptr<TNode<Key, Info>> right);

    void setHeight(int height);

private:
    Key key;
    shared_ptr<Info> infoPointer;
    shared_ptr<TNode<Key, Info>> left;
    shared_ptr<TNode<Key, Info>> right;
    int height;
};

#include "TNodeImp.h"

#endif //DATASTRUCTURESWET1_TNODE_H
