//
// Created by shvmo on 29/04/2020.
//

#ifndef DATASTRUCTURESWET1_TNODEIMP_H
#define DATASTRUCTURESWET1_TNODEIMP_H


#include "TNode.h"

using std::make_shared;

template<class Key, class Value>
TNode<Key, Value>::TNode() = default;

template<class Key, class Value>
TNode<Key, Value>::TNode(const Key &key, const Value &value)
        : TNode() {
    this->key = key;
    this->valuePointer = make_shared<Value>(value);
}

template<class Key, class Value>
TNode<Key, Value>::~TNode() = default;

template<class Key, class Value>
Key &TNode<Key, Value>::getKey() {
    return this->key;
}

template<class Key, class Value>
Value &TNode<Key, Value>::getValue() {
    return *(this->valuePointer.get());
}

template<class Key, class Value>
shared_ptr<Value> TNode<Key, Value>::getValuePointer() const {
    return this->valuePointer;
}

template<class Key, class Value>
shared_ptr<TNode<Key, Value>> TNode<Key, Value>::getLeft() const {
    return this->left;
}

template<class Key, class Value>
shared_ptr<TNode<Key, Value>> TNode<Key, Value>::getRight() const {
    return this->right;
}

template<class Key, class Value>
int TNode<Key, Value>::getHeight() const {
    return this->height;
}

template<class Key, class Value>
void TNode<Key, Value>::setKey(const Key &newKey) {
    this->key = newKey;
}

template<class Key, class Value>
void TNode<Key, Value>::setValue(const Value &newValue) {
    this->valuePointer = make_shared<Value>(newValue);
}

template<class Key, class Value>
void TNode<Key, Value>::setValuePointer(shared_ptr<Value> newValuePointer) {
    this->valuePointer = newValuePointer;
}

template<class Key, class Value>
void TNode<Key, Value>::setLeft(shared_ptr<TNode<Key, Value>> newLeft) {
    this->left = newLeft;
}

template<class Key, class Value>
void TNode<Key, Value>::setRight(shared_ptr<TNode<Key, Value>> newRight) {
    this->right = newRight;
}

template<class Key, class Value>
void TNode<Key, Value>::setHeight(int newHeight) {
    this->height = newHeight;
}

#endif //DATASTRUCTURESWET1_TNODEIMP_H
