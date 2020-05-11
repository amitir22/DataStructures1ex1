//
// Created by shvmo on 29/04/2020.
//

#ifndef DATASTRUCTURESWET1_AVLTREE_H
#define DATASTRUCTURESWET1_AVLTREE_H

#include "TNode.h"


using std::shared_ptr;

template<class Key, class Info>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    shared_ptr<TNode<Key, Info>> getRoot() const;

    shared_ptr<TNode<Key, Info>> find(const Key &key) const;

    void insert(const Key &key, const Info &info);

    // This is done to allow pre allocation and deal with potential allocation errors gracefully
    void insert(shared_ptr<TNode<Key, Info>> newNode);

    void remove(const Key &key);

    void printTreeInfoInOrder(std::ostream &os);

    void treeClear();

    shared_ptr<TNode<Key, Info>> getNextNodeInOrder(shared_ptr<TNode<Key, Info>> node);

    class KeyAlreadyExistsException : std::exception {
    };

    class KeyDoesNotExistException : std::exception {
    };

private:
    shared_ptr<TNode<Key, Info>> root;

    shared_ptr<TNode<Key, Info>> searchBinaryTree(const Key &key, shared_ptr<TNode<Key, Info>> treeNode) const;

    /**
  * @brief Inserts new node to binary AVL tree while keeping balance factor in check
  *
  * @param newNode new node to add
  * @param treeNode Pointer of the tree root to add to
  *
  * @return Current root after inserting and balancing tree
  */
    shared_ptr<TNode<Key, Info>>
    insertAVLTree(shared_ptr<TNode<Key, Info>> newNode, shared_ptr<TNode<Key, Info>> treeNode);

    /**
  * @brief Performs right rotation on treeNode
  *
  * @param treeNode The root of the tree to perform rotation on
  *
  * @return New root after the rotation is done
  */
    shared_ptr<TNode<Key, Info>> rightRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
  * @brief Performs left rotation on treeNode
  *
  * @param treeNode The root of the tree to perform rotation on
  *
  * @return New root after the rotation is done
  */
    shared_ptr<TNode<Key, Info>> leftRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
  * @brief Performs right left rotation on treeNode
  *
  * @param treeNode The root of the tree to perform rotation on
  *
  * @return New root after the rotation is done
  */
    shared_ptr<TNode<Key, Info>> rightLeftRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
  * @brief Performs left right rotation on treeNode
  *
  * @param treeNode The root of the tree to perform right rotation on
  *
  * @return New root after the rotation is done
  */
    shared_ptr<TNode<Key, Info>> leftRightRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
  * @brief Calculates balance factor of current tree node
  *
  * @param treeNode The root of the tree to calculate balance factor on
  *
  * @return New root after the rotation is done
  */
    int getBalanceFactor(shared_ptr<TNode<Key, Info>> treeNode) const;

    /**
  * @brief Fixes balance factor by performing the needed rotation
  *
  * @param treeNode The root of the tree to perform fix on
  *
  * @return New root of current tree after the fix is done
  */
    shared_ptr<TNode<Key, Info>> fixTreeBalance(shared_ptr<TNode<Key, Info>> treeNode);

    void printTreeInfoInOrder(std::ostream &os, shared_ptr<TNode<Key, Info>> treeNode);

    void updateHeight(shared_ptr<TNode<Key, Info>> treeNode);

    shared_ptr<TNode<Key, Info>> removeFromAVLTree(shared_ptr<TNode<Key, Info>> treeNode, const Key &key);

    shared_ptr<TNode<Key, Info>> removeWithInOrderSwap(shared_ptr<TNode<Key, Info>> treeNode);

    shared_ptr<TNode<Key, Info>> removeWithInOrderSwap(shared_ptr<TNode<Key, Info>> nodeToSwapAndRemove,
                                                       shared_ptr<TNode<Key, Info>> treeNode);

    shared_ptr<TNode<Key, Info>> getNextNodeInOrderLeft(shared_ptr<TNode<Key, Info>> node);

    shared_ptr<TNode<Key, Info>> getNextNodeInOrderFromRoot(shared_ptr<TNode<Key, Info>> node,
                                                            shared_ptr<TNode<Key, Info>> nodeToFindNext,
                                                            shared_ptr<TNode<Key, Info>> lastLeft);
};


#include "AVLTreeImp.h"


#endif //DATASTRUCTURESWET1_AVLTREE_H
