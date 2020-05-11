//
// Created by shvmo on 02/05/2020.
//

#ifndef DATASTRUCTURESWET1_BIDIRECTIONALNODE_H
#define DATASTRUCTURESWET1_BIDIRECTIONALNODE_H

#include <memory>

using std::shared_ptr;
using std::weak_ptr;

template<class Type>
class BiDirectionalNode {
public:
    BiDirectionalNode();

    ~BiDirectionalNode();

    Type &getValue();

    shared_ptr<BiDirectionalNode<Type>> getNext() const;

    // Done for optimization when we want to iterate a bit faster
    BiDirectionalNode<Type> *getNextPointer() const;

    weak_ptr<BiDirectionalNode<Type>> getPrevious();

    void setValue(const Type &newValue);

    void setNext(shared_ptr<BiDirectionalNode<Type>> newNext);

    void setPrevious(shared_ptr<BiDirectionalNode<Type>> newPrevious);

private:
    Type value;
    shared_ptr<BiDirectionalNode<Type>> next;
    // This is of type weak_ptr because otherwise it can create cyclic dependency and create memory leaks if shared_ptr is used
    weak_ptr<BiDirectionalNode<Type>> previous;
};

#include "BiDirectionalNodeImp.h"

#endif //DATASTRUCTURESWET1_BIDIRECTIONALNODE_H
