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
    BiDirectionalLinkedList();

    ~BiDirectionalLinkedList();

    shared_ptr<BiDirectionalNode<Type>> getFirst() const;

    // Done for optimization when we want to iterate a bit faster
    BiDirectionalNode<Type>* getFirstPointer() const;

    shared_ptr<BiDirectionalNode<Type>> getLast() const;

    void insert(const Type &newValue);

    shared_ptr<BiDirectionalNode<Type>> findNodeByValue(const Type &valueToFind) const;

    void deleteNodeByValue(const Type &valueToFind);

    void printList(ostream &os) const;

    void printListReverse(ostream &os) const;

    shared_ptr<BiDirectionalNode<Type>>insertNodeAfter(shared_ptr<BiDirectionalNode<Type>> nodeToInsertAfter,
                                                       shared_ptr<BiDirectionalNode<Type>> newNode);

    void remove(shared_ptr<BiDirectionalNode<Type>> nodeToDelete);

private:
    shared_ptr<BiDirectionalNode<Type>> first;
    shared_ptr<BiDirectionalNode<Type>> last;
};

#include "BiDirectionalLinkedListImp.h"

#endif //DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLIST_H
