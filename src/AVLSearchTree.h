#ifndef DEEZEL_AVLSEARCHTREE_H
#define DEEZEL_AVLSEARCHTREE_H

#include <algorithm>

typedef enum e_direction {
    LEFT = -1,
    RIGHT = 1
} RotationDirection, ChildDirection;

template <typename K, typename V>
class AVLSearchTree {
private:
    AVLSearchTree *right;
    AVLSearchTree *left;
    int count;
    K key;
    V value;

public:
    AVLSearchTree() = delete;
    AVLSearchTree(const K &key, const V &value);
    AVLSearchTree(const K &key, const V &value,
                  AVLSearchTree<K, V> *child, ChildDirection childDirection);
    AVLSearchTree(const K &key, const V &value,
            AVLSearchTree<K, V> *left, AVLSearchTree<K, V> *right);
    ~AVLSearchTree() = default; // todo: make sure

    AVLSearchTree<K, V> *getLeft();
    AVLSearchTree<K, V> *getRight();
    void setLeft(AVLSearchTree<K, V> *newLeft);
    void setRight(AVLSearchTree<K, V> *newRight);

    void rotateLeftChild(RotationDirection direction);
    void rotateRightChild(RotationDirection direction);
    void balance();

    bool hasLeft();
    bool hasRight();
    bool isRoot();
    int getHeight();
    int getCount();
    K getKey();
    V getValue();

};

#include "AVLSearchTreeImpl.h"

#endif //DEEZEL_AVLSEARCHTREE_H
