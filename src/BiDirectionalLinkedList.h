//
// Created by shvmo on 02/05/2020.
//

#ifndef DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLIST_H
#define DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLIST_H

#include "BiDirectionalNode.h"
#include <iostream>

using std::ostream;

template<class Type>
class BiDirectionalLinkedList {
public:
    // O(1)
    BiDirectionalLinkedList();

    // O(1)
    ~BiDirectionalLinkedList();

    // O(1)
    shared_ptr<BiDirectionalNode<Type>> getFirst() const;

    // O(1)
    // Done for optimization when we want to iterate a bit faster
    BiDirectionalNode<Type> *getFirstPointer() const;

    // O(1)
    shared_ptr<BiDirectionalNode<Type>> getLast() const;

    // O(1)
    void append(const Type &newValue);

    // O(n) - where n is the number of elements in the list
    shared_ptr<BiDirectionalNode<Type>> findNodeByValue(const Type &valueToFind) const;

    // O(n) - where n is the number of elements in the list
    void removeNodeByValue(const Type &valueToFind);

    // O(n) - where n is the number of elements in the list
    void printList(ostream &os) const;

    // O(n) - where n is the number of elements in the list
    void printListReverse(ostream &os) const;

    // O(1)
    shared_ptr<BiDirectionalNode<Type>> insertNodeAfter(shared_ptr<BiDirectionalNode<Type>> nodeToInsertAfter,
                                                        shared_ptr<BiDirectionalNode<Type>> newNode);

    // O(1)
    void remove(shared_ptr<BiDirectionalNode<Type>> nodeToDelete);

private:
    shared_ptr<BiDirectionalNode<Type>> first;
    shared_ptr<BiDirectionalNode<Type>> last;
};

#include "BiDirectionalLinkedListImp.h"

#endif //DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLIST_H
