//
// Created by shvmo on 29/04/2020.
//

#ifndef DATASTRUCTURESWET1_AVLTREEIMP_H
#define DATASTRUCTURESWET1_AVLTREEIMP_H

#include <cassert>
#include "AVLTree.h"
#include <iostream>
#include <algorithm>
#include <cmath>

const int STARTING_HEIGHT = 0;

using std::make_shared;

template<class Key, class Info>
AVLTree<Key, Info>::AVLTree() = default;

template<class Key, class Info>
AVLTree<Key, Info>::~AVLTree() = default;

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::getRoot() const {
    return this->root;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::find(const Key &key) const {
    return searchBinaryTree(key, this->root);
}

template<class Key, class Info>
void AVLTree<Key, Info>::insert(const Key &key, const Info &info) {
    shared_ptr<TNode<Key, Info>> newNode = make_shared<TNode<Key, Info>>(key, info);

    this->insert(newNode);
}

template<class Key, class Info>
void AVLTree<Key, Info>::insert(shared_ptr<TNode<Key, Info>> newNode) {
    newNode->setHeight(STARTING_HEIGHT);

    this->root = insertAVLTree(newNode, this->root);
}

template<class Key, class Info>
void AVLTree<Key, Info>::remove(const Key &key) {
    this->root = removeFromAVLTree(this->root, key);
}

template<class Key, class Info>
void AVLTree<Key, Info>::printTreeInfoInOrder(std::ostream &os) const {
    os << "Tree Info summary:" << std::endl;

    printTreeInfoInOrder(os, this->root);
}

template<class Key, class Info>
void AVLTree<Key, Info>::treeClear() {
    this->root = nullptr;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::getNextNodeInOrder(shared_ptr<TNode<Key, Info>> node) const {
    if (node == nullptr) {
        return nullptr;
    } else if (node->getRight() != nullptr) {
        return getNextNodeInOrderLeft(node->getRight());
    }

    return getNextNodeInOrderFromRoot(this->root, node, nullptr);
}

// Private Methods:

template<class Key, class Info>
shared_ptr<TNode<Key, Info>>
AVLTree<Key, Info>::searchBinaryTree(const Key &key, shared_ptr<TNode<Key, Info>> treeNode) const {
    if (treeNode == nullptr) {
        return nullptr;
    }

    if (key == treeNode->getKey()) {
        return treeNode;
    } else if (key < treeNode->getKey()) {
        return searchBinaryTree(key, treeNode->getLeft());
    } else if (key > treeNode->getKey()) {
        return searchBinaryTree(key, treeNode->getRight());
    }

    // Code execution should never get here
    assert(false);

    return nullptr;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::insertAVLTree(shared_ptr<TNode<Key, Info>> newNode,
                                                               shared_ptr<TNode<Key, Info>> treeNode) {
    if (treeNode == nullptr) {
        return newNode;
    }

    if (treeNode->getKey() == newNode->getKey()) {
        throw KeyAlreadyExistsException();
    } else if (treeNode->getKey() < newNode->getKey()) {
        treeNode->setRight(insertAVLTree(newNode, treeNode->getRight()));
    } else if (treeNode->getKey() > newNode->getKey()) {
        treeNode->setLeft(insertAVLTree(newNode, treeNode->getLeft()));
    }

    updateHeight(treeNode);

    return fixTreeBalance(treeNode);
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::rightRotate(shared_ptr<TNode<Key, Info>> treeNode) {
    // Code should never get here if left is null
    assert(treeNode->getLeft() != nullptr);

    shared_ptr<TNode<Key, Info>> leftTree = treeNode->getLeft();
    treeNode->setLeft(leftTree->getRight());
    leftTree->setRight(treeNode);

    updateHeight(treeNode);
    updateHeight(leftTree);

    return leftTree;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::leftRotate(shared_ptr<TNode<Key, Info>> treeNode) {
    // Code should never get here if right is null
    assert(treeNode->getRight() != nullptr);

    shared_ptr<TNode<Key, Info>> rightTree = treeNode->getRight();
    treeNode->setRight(rightTree->getLeft());
    rightTree->setLeft(treeNode);

    updateHeight(treeNode);
    updateHeight(rightTree);

    return rightTree;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::rightLeftRotate(shared_ptr<TNode<Key, Info>> treeNode) {
    // Code should never get here if either is null
    assert(treeNode->getRight() != nullptr);
    assert(treeNode->getRight()->getLeft() != nullptr);

    shared_ptr<TNode<Key, Info>> rightTree = rightRotate(treeNode->getRight());
    treeNode->setRight(rightTree);
    updateHeight(treeNode);

    return leftRotate(treeNode);
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::leftRightRotate(shared_ptr<TNode<Key, Info>> treeNode) {
    // Code should never get here if either is null
    assert(treeNode->getLeft() != nullptr);
    assert(treeNode->getLeft()->getRight() != nullptr);

    shared_ptr<TNode<Key, Info>> leftTree = leftRotate(treeNode->getLeft());
    treeNode->setLeft(leftTree);
    updateHeight(treeNode);

    return rightRotate(treeNode);
}

template<class Key, class Info>
int AVLTree<Key, Info>::getBalanceFactor(shared_ptr<TNode<Key, Info>> treeNode) const {
    int leftTreeHeight = treeNode->getLeft() != nullptr ? treeNode->getLeft()->getHeight() : STARTING_HEIGHT - 1;
    int rightTreeHeight = treeNode->getRight() != nullptr ? treeNode->getRight()->getHeight() : STARTING_HEIGHT - 1;

    int balanceFactor = leftTreeHeight - rightTreeHeight;

    return balanceFactor;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>> AVLTree<Key, Info>::fixTreeBalance(shared_ptr<TNode<Key, Info>> treeNode) {
    if (treeNode != nullptr) {
        int balanceFactor = this->getBalanceFactor(treeNode);

        if (balanceFactor == 2) {
            assert(treeNode->getLeft() != nullptr);

            int leftTreeBalanceFactor = this->getBalanceFactor(treeNode->getLeft());

            if (leftTreeBalanceFactor >= 0) {
                return this->rightRotate(treeNode);
            } else if (leftTreeBalanceFactor == -1) {
                return this->leftRightRotate(treeNode);
            }
        } else if (balanceFactor == -2) {
            assert(treeNode->getRight() != nullptr);

            int rightTreeBalanceFactor = this->getBalanceFactor(treeNode->getRight());

            if (rightTreeBalanceFactor <= 0) {
                return this->leftRotate(treeNode);
            } else if (rightTreeBalanceFactor == 1) {
                return this->rightLeftRotate(treeNode);
            }
        } else {
            assert(abs(balanceFactor) <= 1);

            return treeNode;
        }
    }

    return nullptr;
}

template<class Key, class Info>
void AVLTree<Key, Info>::updateHeight(shared_ptr<TNode<Key, Info>> treeNode) {
    if (treeNode != nullptr) {
        int leftTreeHeight = treeNode->getLeft() == nullptr ? STARTING_HEIGHT : treeNode->getLeft()->getHeight() + 1;
        int rightTreeHeight = treeNode->getRight() == nullptr ? STARTING_HEIGHT : treeNode->getRight()->getHeight() + 1;

        treeNode->setHeight(std::max(leftTreeHeight, rightTreeHeight));
    }
}

template<class Key, class Info>
void AVLTree<Key, Info>::printTreeInfoInOrder(std::ostream &os, shared_ptr<TNode<Key, Info>> treeNode) const {
    if (treeNode != nullptr) {
        printTreeInfoInOrder(os, treeNode->getLeft());

        os << "Key: " << treeNode->getKey() << " BF: " << getBalanceFactor(treeNode) << " Height: "
           << treeNode->getHeight()
           << std::endl;

        printTreeInfoInOrder(os, treeNode->getRight());
    }
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>>
AVLTree<Key, Info>::removeFromAVLTree(shared_ptr<TNode<Key, Info>> treeNode, const Key &key) {
    if (treeNode == nullptr) {
        throw KeyDoesNotExistException();
    }

    if (key == treeNode->getKey()) {
        if (treeNode->getRight() == nullptr) {
            treeNode = treeNode->getLeft();
        } else if (treeNode->getLeft() == nullptr) {
            treeNode = treeNode->getRight();
        } else {
            treeNode = removeWithInOrderSwap(treeNode);
        }
    } else if (treeNode->getKey() < key) {
        treeNode->setRight(removeFromAVLTree(treeNode->getRight(), key));
    } else if (treeNode->getKey() > key) {
        treeNode->setLeft(removeFromAVLTree(treeNode->getLeft(), key));
    }

    if (treeNode != nullptr) {
        updateHeight(treeNode);

        return fixTreeBalance(treeNode);
    } else {
        return nullptr;
    }
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>>
AVLTree<Key, Info>::removeWithInOrderSwap(shared_ptr<TNode<Key, Info>> treeNode) {
    treeNode->setRight(removeWithInOrderSwap(treeNode, treeNode->getRight()));

    // Now treeNode key and value are swapped and removed with its right subtree balanced
    return treeNode;
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>>
AVLTree<Key, Info>::removeWithInOrderSwap(shared_ptr<TNode<Key, Info>> nodeToSwapAndRemove,
                                          shared_ptr<TNode<Key, Info>> treeNode) {
    assert(treeNode != nullptr);
    assert(nodeToSwapAndRemove != nullptr);

    if (treeNode->getLeft() == nullptr) {
        // swap nodes with the current treeNode that is the next in order
        shared_ptr<Info> infoToSwapPointer = nodeToSwapAndRemove->getInfoPointer();
        Key keyToSwap = nodeToSwapAndRemove->getKey();

        nodeToSwapAndRemove->setInfoPointer(treeNode->getInfoPointer());
        nodeToSwapAndRemove->setKey(treeNode->getKey());

        treeNode->setInfoPointer(infoToSwapPointer);
        treeNode->setKey(keyToSwap);

        return removeFromAVLTree(treeNode, treeNode->getKey());
    } else {
        treeNode->setLeft(removeWithInOrderSwap(nodeToSwapAndRemove, treeNode->getLeft()));

        updateHeight(treeNode);

        return fixTreeBalance(treeNode);
    }
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>>
AVLTree<Key, Info>::getNextNodeInOrderLeft(shared_ptr<TNode<Key, Info>> node) const {
    if (node == nullptr) {
        return nullptr;
    } else if (node->getLeft() == nullptr) {
        return node;
    } else {
        return getNextNodeInOrder(node->getLeft());
    }
}

template<class Key, class Info>
shared_ptr<TNode<Key, Info>>
AVLTree<Key, Info>::getNextNodeInOrderFromRoot(shared_ptr<TNode<Key, Info>> currentNode,
                                               shared_ptr<TNode<Key, Info>> nodeToFind,
                                               shared_ptr<TNode<Key, Info>> lastLeft) const {
    if (currentNode == nullptr) {
        return lastLeft;
    }

    if (nodeToFind->getKey() < currentNode->getKey()) {
        return getNextNodeInOrderFromRoot(currentNode->getLeft(), nodeToFind, currentNode);
    } else if (nodeToFind->getKey() > currentNode->getKey()) {
        return getNextNodeInOrderFromRoot(currentNode->getRight(), nodeToFind, lastLeft);
    }

    assert(nodeToFind->getKey() == currentNode->getKey());

    return lastLeft;
}

#endif //DATASTRUCTURESWET1_AVLTREEIMP_H
