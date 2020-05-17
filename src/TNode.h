//
// Created by shvmo on 29/04/2020.
//

#ifndef DATASTRUCTURESWET1_TNODE_H
#define DATASTRUCTURESWET1_TNODE_H


#include <memory>

using std::shared_ptr;

template<class Key, class Value>
class TNode {
public:
    // O(1)
    TNode();

    // O(1)
    TNode(const Key &newKey, const Value &value);

    // O(1)
    ~TNode();

    // O(1)
    Key &getKey();

    // O(1)
    Value &getValue();

    // O(1)
    shared_ptr<Value> getValuePointer() const;

    // O(1)
    shared_ptr<TNode<Key, Value>> getLeft() const;

    // O(1)
    shared_ptr<TNode<Key, Value>> getRight() const;

    // O(1)
    int getHeight() const;

    // O(1)
    void setKey(const Key &newKey);

    // O(1)
    void setValue(const Value &value);

    // O(1)
    void setValuePointer(shared_ptr<Value> newValuePointer);

    // O(1)
    void setLeft(shared_ptr<TNode<Key, Value>> left);

    // O(1)
    void setRight(shared_ptr<TNode<Key, Value>> right);

    // O(1)
    void setHeight(int height);

private:
    Key key;
    shared_ptr<Value> valuePointer;
    shared_ptr<TNode<Key, Value>> left;
    shared_ptr<TNode<Key, Value>> right;
    int height;
};

#include "TNodeImp.h"

#endif //DATASTRUCTURESWET1_TNODE_H
