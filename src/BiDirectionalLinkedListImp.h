//
// Created by shvmo on 02/05/2020.
//

#ifndef DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLISTIMP_H
#define DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLISTIMP_H

#include <cassert>
#include "BiDirectionalLinkedList.h"

using std::make_shared;

template<class Type>
BiDirectionalLinkedList<Type>::BiDirectionalLinkedList() = default;

template<class Type>
BiDirectionalLinkedList<Type>::~BiDirectionalLinkedList() = default;

template<class Type>
shared_ptr<BiDirectionalNode<Type>> BiDirectionalLinkedList<Type>::getFirst() const {
    return this->first;
}

template<class Type>
BiDirectionalNode<Type> *BiDirectionalLinkedList<Type>::getFirstPointer() const {
    return this->first.get();
}

template<class Type>
shared_ptr<BiDirectionalNode<Type>> BiDirectionalLinkedList<Type>::getLast() const {
    return this->last;
}

template<class Type>
void BiDirectionalLinkedList<Type>::append(const Type &newValue) {
    shared_ptr<BiDirectionalNode<Type>> newLast = make_shared<BiDirectionalNode<Type>>();

    newLast->setValue(newValue);
    newLast->setNext(nullptr);

    if (this->first == nullptr) {
        newLast->setPrevious(nullptr);

        this->first = newLast;
        this->last = this->first;
    } else {
        newLast->setPrevious(this->last);
        this->last->setNext(newLast);

        this->last = newLast;
    }
}

template<class Type>
shared_ptr<BiDirectionalNode<Type>> BiDirectionalLinkedList<Type>::findNodeByValue(const Type &valueToFind) const {
    for (shared_ptr<BiDirectionalNode<Type>> current = this->first; current != nullptr; current = current->getNext()) {
        if (valueToFind == current->getValue()) {
            return current;
        }
    }
}

template<class Type>
void BiDirectionalLinkedList<Type>::removeNodeByValue(const Type &valueToFind) {
    for (shared_ptr<BiDirectionalNode<Type>> current = this->first; current != nullptr; current = current->getNext()) {
        if (valueToFind == current->getValue()) {
            remove(current);

            return;
        }
    }
}

template<class Type>
void BiDirectionalLinkedList<Type>::printList(ostream &os) const {
    for (shared_ptr<BiDirectionalNode<Type>> current = this->first; current != nullptr; current = current->getNext()) {
        os << current->getValue() << " ";
    }

    os << std::endl;
}

template<class Type>
void BiDirectionalLinkedList<Type>::printListReverse(ostream &os) const {
    for (shared_ptr<BiDirectionalNode<Type>> current = this->last; current != nullptr;
         current = current->getPrevious().lock()) {
        os << current->getValue() << " ";
    }

    os << std::endl;
}

template<class Type>
shared_ptr<BiDirectionalNode<Type>>
BiDirectionalLinkedList<Type>::insertNodeAfter(shared_ptr<BiDirectionalNode<Type>> nodeToInsertAfter,
                                               shared_ptr<BiDirectionalNode<Type>> newNode) {
    // If list is empty we insert it to the the head of the list
    if (this->first == nullptr) {
        assert(nodeToInsertAfter == nullptr);

        this->first = newNode;
        this->last = newNode;

        return this->first;
    }

    newNode->setPrevious(nodeToInsertAfter);

    if (nodeToInsertAfter == nullptr) {
        newNode->setNext(this->first);
        this->first = newNode;
    } else {
        newNode->setNext(nodeToInsertAfter->getNext());
        nodeToInsertAfter->setNext(newNode);
    }

    if (newNode->getNext() != nullptr) {
        newNode->getNext()->setPrevious(newNode);
    }

    if (nodeToInsertAfter == this->last) {
        this->last = newNode;
    }

    return newNode;
}

template<class Type>
void BiDirectionalLinkedList<Type>::remove(shared_ptr<BiDirectionalNode<Type>> nodeToDelete) {
    if (nodeToDelete == nullptr) {
        return;
    }

    if (nodeToDelete->getNext() != nullptr) {
        nodeToDelete->getNext()->setPrevious(nodeToDelete->getPrevious().lock());
    }

    if (nodeToDelete->getPrevious().lock() != nullptr) {
        nodeToDelete->getPrevious().lock()->setNext(nodeToDelete->getNext());
    }

    if (nodeToDelete == this->first) {
        this->first = nodeToDelete->getNext();
    }

    if (nodeToDelete == this->last) {
        this->last = nodeToDelete->getPrevious().lock();
    }
}

#endif //DATASTRUCTURESWET1_BIDIRECTIONALLINKEDLISTIMP_H
