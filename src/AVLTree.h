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
    // O(1)
    AVLTree();

    // O(1)
    ~AVLTree();

    // O(1)
    shared_ptr<TNode<Key, Info>> getRoot() const;

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> find(const Key &key) const;

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    void insert(const Key &key, const Info &info);

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    // This is done to allow pre allocation and deal with potential allocation errors gracefully
    void insert(shared_ptr<TNode<Key, Info>> newNode);

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    void remove(const Key &key);

    // O(n) - where n is the number of elements and h is the height of AVL tree (log(n))
    void printTreeInfoInOrder(std::ostream &os) const;

    // O(n) - where n is the number of elements and h is the height of AVL tree (log(n))
    void treeClear();

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> getNextNodeInOrder(shared_ptr<TNode<Key, Info>> node) const;

    class KeyAlreadyExistsException : std::exception {
    };

    class KeyDoesNotExistException : std::exception {
    };

private:
    shared_ptr<TNode<Key, Info>> root;

    /**
     * @brief Searches for the given key in the given AVL tree
     *
     * @complexity O(log(n)) - where n is the number of elements in the given treeNode.
     *             explanation:
     *                  O(h) - where h is the height of the given treeNode.
     *                  h = log(n) in AVLTree (balanced)
     *
     * @param key - The key to search for
     * @param treeNode - Pointer of the tree root to search in
     *
     * @return The TNode matching the given key. (if not found then nullptr is returned)
     */
    shared_ptr<TNode<Key, Info>> searchBinaryTree(const Key &key, shared_ptr<TNode<Key, Info>> treeNode) const;

    /**
     * @brief Inserts new node to binary AVL tree while keeping balance factor in check
     *
     * @complexity O(log(n)) - where n is the number of elements in the given treeNode.
     *             explanation:
     *                  O(h) - where h is the height of the given treeNode.
     *                  h = log(n) in AVLTree (balanced)
     *
     * @param newNode - new node to add
     * @param treeNode - Pointer of the tree root to add to
     *
     * @return Current root after inserting and balancing tree
     */
    shared_ptr<TNode<Key, Info>>
    insertAVLTree(shared_ptr<TNode<Key, Info>> newNode, shared_ptr<TNode<Key, Info>> treeNode);

    /**
     * @brief Performs right rotation on treeNode
     *
     * @complexity O(1)
     *
     * @param treeNode The root of the tree to perform rotation on
     *
     * @return New root after the rotation is done
     */
    shared_ptr<TNode<Key, Info>> rightRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
     * @brief Performs left rotation on treeNode
     *
     * @complexity O(1)
     *
     * @param treeNode The root of the tree to perform rotation on
     *
     * @return New root after the rotation is done
     */
    shared_ptr<TNode<Key, Info>> leftRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
     * @brief Performs right left rotation on treeNode
     *
     * @complexity O(1)
     *
     * @param treeNode The root of the tree to perform rotation on
     *
     * @return New root after the rotation is done
     */
    shared_ptr<TNode<Key, Info>> rightLeftRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
     * @brief Performs left right rotation on treeNode
     *
     * @complexity O(1)
     *
     * @param treeNode The root of the tree to perform right rotation on
     *
     * @return New root after the rotation is done
     */
    shared_ptr<TNode<Key, Info>> leftRightRotate(shared_ptr<TNode<Key, Info>> treeNode);

    /**
     * @brief Calculates balance factor of current tree node
     *
     * @complexity O(1)
     *
     * @param treeNode The root of the tree to calculate balance factor on
     *
     * @return New root after the rotation is done
     */
    int getBalanceFactor(shared_ptr<TNode<Key, Info>> treeNode) const;

    /**
     * @brief Fixes balance factor by performing the needed rotation
     *
     * @complexity O(1)
     *
     * @param treeNode The root of the tree to perform fix on
     *
     * @return New root of current tree after the fix is done
     */
    shared_ptr<TNode<Key, Info>> fixTreeBalance(shared_ptr<TNode<Key, Info>> treeNode);

    // O(n) - where n is the number of elements in the given treeNode
    void printTreeInfoInOrder(std::ostream &os, shared_ptr<TNode<Key, Info>> treeNode) const;

    // O(1)
    void updateHeight(shared_ptr<TNode<Key, Info>> treeNode);

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> removeFromAVLTree(shared_ptr<TNode<Key, Info>> treeNode, const Key &key);

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> removeWithInOrderSwap(shared_ptr<TNode<Key, Info>> treeNode);

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> removeWithInOrderSwap(shared_ptr<TNode<Key, Info>> nodeToSwapAndRemove,
                                                       shared_ptr<TNode<Key, Info>> treeNode);

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> getNextNodeInOrderLeft(shared_ptr<TNode<Key, Info>> node) const;

    // O(log(n)) = O(h) - where n is the number of elements and h is the height of AVL tree (log(n))
    shared_ptr<TNode<Key, Info>> getNextNodeInOrderFromRoot(shared_ptr<TNode<Key, Info>> currentNode,
                                                            shared_ptr<TNode<Key, Info>> nodeToFind,
                                                            shared_ptr<TNode<Key, Info>> lastLeft) const;
};

#include "AVLTreeImp.h"

#endif //DATASTRUCTURESWET1_AVLTREE_H
