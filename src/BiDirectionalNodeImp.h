//
// Created by shvmo on 02/05/2020.
//

#ifndef DATASTRUCTURESWET1_BIDIRECTIONALNODEIMP_H
#define DATASTRUCTURESWET1_BIDIRECTIONALNODEIMP_H

#include "BiDirectionalNode.h"

template<class Type>
BiDirectionalNode<Type>::BiDirectionalNode() = default;

template<class Type>
BiDirectionalNode<Type>::~BiDirectionalNode() = default;

template<class Type>
Type &BiDirectionalNode<Type>::getValue() {
    return this->value;
}

template<class Type>
shared_ptr<BiDirectionalNode<Type>> BiDirectionalNode<Type>::getNext() const {
    return this->next;
}

template<class Type>
BiDirectionalNode<Type> *BiDirectionalNode<Type>::getNextPointer() const {
    return this->next.get();
}

template<class Type>
weak_ptr<BiDirectionalNode<Type>> BiDirectionalNode<Type>::getPrevious() const {
    return this->previous;
}

template<class Type>
void BiDirectionalNode<Type>::setValue(const Type &newValue) {
    this->value = newValue;
}

template<class Type>
void BiDirectionalNode<Type>::setNext(shared_ptr<BiDirectionalNode<Type>> newNext) {
    this->next = newNext;
}

template<class Type>
void BiDirectionalNode<Type>::setPrevious(shared_ptr<BiDirectionalNode<Type>> newPrevious) {
    this->previous = newPrevious;
}

#endif //DATASTRUCTURESWET1_BIDIRECTIONALNODEIMP_H
