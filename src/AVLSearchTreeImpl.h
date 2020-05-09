
#include "AVLSearchTree.h"

template <typename K, typename V>
AVLSearchTree<K, V>::AVLSearchTree(const K &key, const V &value) : count(1) {
    this->left = nullptr;
    this->right = nullptr;
    this->key = key;
    this->value = value;
}

template <typename K, typename V>
AVLSearchTree<K, V>::AVLSearchTree(const K &key, const V &value,
        AVLSearchTree<K, V> *left, AVLSearchTree<K, V> *right)
        : count(1 + left->count + right->count){
    this->left = left;
    this->right = right;
    this->key = key;
    this->value = value;
}

template <typename K, typename V>
AVLSearchTree<K, V>::AVLSearchTree(const K &key, const V &value,
              AVLSearchTree<K, V> *child, ChildDirection childDirection)
              : count(1 + child->count){
    if (childDirection == RIGHT) {
        this->right = child;
        this->left = nullptr;
    } else if (childDirection == LEFT) {
        this->left = child;
        this->right = nullptr;
    } else {
        // TODO: raise exception
    }

    this->key = key;
    this->value = value;
}

template <typename K, typename V>
AVLSearchTree<K, V> *AVLSearchTree<K, V>::getLeft() {
    return this->left;
}

template <typename K, typename V>
AVLSearchTree<K, V> *AVLSearchTree<K, V>::getRight() {
    return this->right;
}

template <typename K, typename V>
void AVLSearchTree<K, V>::setLeft(AVLSearchTree<K, V> *newLeft) {
    if (this->left != nullptr) {
        delete this->left;
    }

    this->left = newLeft;
}

template <typename K, typename V>
void AVLSearchTree<K, V>::setRight(AVLSearchTree<K, V> *newRight) {
    if (this->right != nullptr) {
        delete this->right;
    }

    this->right = newRight;
}

template <typename K, typename V>
void AVLSearchTree<K, V>::rotateLeftChild(RotationDirection direction) {
    AVLSearchTree *B;
    AVLSearchTree *A;

    switch (direction) {
        case RIGHT:
            if (this->left->hasLeft()) {
                B = this->left;
                A = B->left;
                B->left = A->right;
                A->right = B;
                this->left = A;
            } else {
                // todo: raise exception
            }
            break;
        case LEFT:
            if (this->left->hasRight()) {
                A = this->left;
                B = A->right;
                A->right = B->left;
                B->left = A;
                this->left = B;
            } else {
                // todo: raise exception
            }
            break;
        default:
            break; // todo: raise exception
    }
}

template <typename K, typename V>
void AVLSearchTree<K, V>::rotateRightChild(RotationDirection direction) {
    AVLSearchTree *B;
    AVLSearchTree *A;

   switch (direction) {
       case RIGHT:
           if (this->right->hasLeft()) {
               B = this->right;
               A = B->left;
               B->left = A->right;
               A->right = B;
               this->right = A;
           } else {
               // todo: raise exception
           }
           break;
       case LEFT:
           if (this->right->hasRight()) {
               A = this->right;
               B = A->right;
               A->right = B->left;
               B->left = A;
               this->right = B;
           } else {
               // todo: raise exception
           }
           break;
       default:
           break; // todo: raise exception
   }
}

template <typename K, typename V>
void AVLSearchTree<K, V>::balance() {
    int leftHeight;
    int rightHeight;

    bool hasLeft1 = this->hasLeft();
    bool hasRight1 = this->hasRight();
    bool hasLeft2;
    bool hasRight2;

    // Left child:
    if (hasLeft1) {
        this->left->balance();
        leftHeight = 0;
        rightHeight = 0;

        hasLeft2 = this->left->hasLeft();
        hasRight2 = this->left->hasRight();

        if (hasLeft2) {
            leftHeight = this->left->left->getHeight();
        }
        if (hasRight2) {
            rightHeight = this->left->right->getHeight();
        }

        if (leftHeight > rightHeight + 1) {
            this->rotateLeftChild(RIGHT);
        } else if (rightHeight > leftHeight + 1) {
            this->rotateLeftChild(LEFT);
        }
    }

    // Right child:
    if (hasRight1) {
        this->right->balance();
        leftHeight = 0;
        rightHeight = 0;

        hasLeft2 = this->right->hasLeft();
        hasRight2 = this->right->hasRight();

        if (hasLeft2) {
            leftHeight = this->right->left->getHeight();
        }
        if (hasRight2) {
            rightHeight = this->right->right->getHeight();
        }

        if (leftHeight > rightHeight + 1) {
            this->rotateRightChild(RIGHT);
        } else if (rightHeight > leftHeight + 1) {
            this->rotateRightChild(LEFT);
        }
    }
}

template <typename K, typename V>
int AVLSearchTree<K, V>::getHeight() {
    int leftHeight = 0;
    int rightHeight = 0;

    if (this->hasRight()) {
        rightHeight = this->right->getHeight();
    }
    if (this->hasLeft()) {
        leftHeight = this->left->getHeight();
    }

    return 1 + std::max(leftHeight, rightHeight);
}

template <typename K, typename V>
bool AVLSearchTree<K, V>::hasLeft() {
    bool res = this->left != nullptr;
    return res;
}

template <typename K, typename V>
bool AVLSearchTree<K, V>::hasRight() {
    return this->right != nullptr;
}

template <typename K, typename V>
bool AVLSearchTree<K, V>::isRoot() {
    return this->parent == nullptr;
}

template <typename K, typename V>
int AVLSearchTree<K, V>::getCount() {
    return this->count;
}

template<typename K, typename V>
K AVLSearchTree<K, V>::getKey() {
    return this->key;
}

template<typename K, typename V>
V AVLSearchTree<K, V>::getValue() {
    return this->value;
}
