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
    // O(1)
    TNode();

    // O(1)
    TNode(const Key &newKey, const Info &info);

    // O(1)
    ~TNode();

    // O(1)
    Key &getKey();

    // O(1)
    Info &getInfo();

    // O(1)
    shared_ptr<Info> getInfoPointer() const;

    // O(1)
    shared_ptr<TNode<Key, Info>> getLeft() const;

    // O(1)
    shared_ptr<TNode<Key, Info>> getRight() const;

    // O(1)
    int getHeight() const;

    // O(1)
    void setKey(const Key &newKey);

    // O(1)
    void setInfo(const Info &info);

    // O(1)
    void setInfoPointer(shared_ptr<Info> newInfoPointer);

    // O(1)
    void setLeft(shared_ptr<TNode<Key, Info>> left);

    // O(1)
    void setRight(shared_ptr<TNode<Key, Info>> right);

    // O(1)
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
