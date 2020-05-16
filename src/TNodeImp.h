//
// Created by shvmo on 29/04/2020.
//

#ifndef DATASTRUCTURESWET1_TNODEIMP_H
#define DATASTRUCTURESWET1_TNODEIMP_H


#include "TNode.h"

using std::make_shared;

template<class Key, class Info>
TNode<Key, Info>::TNode() = default;

template<class Key, class Info>
TNode<Key, Info>::TNode(const Key &key, const Info &info)
        : TNode() {
    this->key = key;
    this->infoPointer = make_shared<Info>(info);
}

template<class Key, class Info>
TNode<Key, Info>::~TNode() = default;

template<class Key, class Info>
Key &TNode<Key, Info>::getKey() {
    return this->key;
}

template<class Key, class Info>
Info &TNode<Key, Info>::getInfo() {
    return *(this->infoPointer.get());
}

template<class Key, class Info>
shared_ptr<Info> TNode<Key, Info>::getInfoPointer() const {
    return this->infoPointer;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> TNode<Key, Info>::getLeft() const {
    return this->left;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> TNode<Key, Info>::getRight() const {
    return this->right;
}

template<class Key, class Info>
void TNode<Key, Info>::setKey(const Key &newKey) {
    this->key = newKey;
}

template<class Key, class Info>
void TNode<Key, Info>::setInfo(const Info &newInfo) {
    this->infoPointer = make_shared<Info>(newInfo);
}

template<class Key, class Info>
void TNode<Key, Info>::setInfoPointer(shared_ptr<Info> newInfoPointer) {
    this->infoPointer = newInfoPointer;
}


template<class Key, class Info>
void TNode<Key, Info>::setLeft(shared_ptr<TNode<Key, Info>> newLeft) {
    this->left = newLeft;
}

template<class Key, class Info>
void TNode<Key, Info>::setRight(shared_ptr<TNode<Key, Info>> newRight) {
    this->right = newRight;
}

template<class Key, class Info>
int TNode<Key, Info>::getHeight() const {
    return this->height;
}

template<class Key, class Info>
void TNode<Key, Info>::setHeight(int newHeight) {
    this->height = newHeight;
}

#endif //DATASTRUCTURESWET1_TNODEIMP_H
