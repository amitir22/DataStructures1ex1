#include <iostream>
#include "AVLSearchTree.h"

AVLSearchTree<int, int> *generateBalancedTree();
void freeBalancedTree(AVLSearchTree<int, int> *root);
AVLSearchTree<int, int> *generateUnbalancedTree();
void freeUnbalancedTree(AVLSearchTree<int, int> *root);

void testBalance();
void testRotateRightChild();
void testRotateLeftChild();
void runAll();

using namespace std;

int main() {
    runAll();
    return 0;
}

void runAll() {
    cout << "ctor works" << endl;

    testRotateRightChild();
    testRotateLeftChild();
    testBalance();
}

AVLSearchTree<int, int> *generateBalancedTree() {
    auto *rr = new AVLSearchTree<int, int>(7, 700);
    auto *rl = new AVLSearchTree<int, int>(5, 500);
    auto *r = new AVLSearchTree<int, int>(6, 600, rl, rr);

    auto *lr = new AVLSearchTree<int, int>(3, 300);
    auto *ll = new AVLSearchTree<int, int>(1, 100);
    auto *l = new AVLSearchTree<int, int>(2, 200, ll, lr);

    return new AVLSearchTree<int, int>(4, 400, l, r);
}

void freeBalancedTree(AVLSearchTree<int, int> *root) {
    delete root->getRight()->getRight();
    delete root->getRight()->getLeft();
    delete root->getRight();

    delete root->getLeft()->getRight();
    delete root->getLeft()->getLeft();
    delete root->getLeft();

    delete root;
}

AVLSearchTree<int, int> *generateUnbalancedTree() {
    auto *rrr = new AVLSearchTree<int, int>(7, 700);
    auto *rr = new AVLSearchTree<int, int>(6, 600, rrr, RIGHT);
    auto *r = new AVLSearchTree<int, int>(5, 500, rr, RIGHT);

    auto *lll = new AVLSearchTree<int, int>(1, 100);
    auto *ll = new AVLSearchTree<int, int>(2, 200, lll, LEFT);
    auto *l = new AVLSearchTree<int, int>(3, 300, ll, LEFT);

    return new AVLSearchTree<int, int>(4, 400, l, r);
}

void freeUnbalancedTree(AVLSearchTree<int, int> *root) {
    delete root->getRight()->getRight()->getRight();
    delete root->getRight()->getRight();
    delete root->getRight();

    delete root->getLeft()->getLeft()->getLeft();
    delete root->getLeft()->getLeft();
    delete root->getLeft();

    delete root;
}

void testBalance() {
    AVLSearchTree<int, int> *root = generateUnbalancedTree();

    root->balance();
    cout << "balance successful" << endl;

    freeUnbalancedTree(root);
}

void testRotateRightChild() {
    AVLSearchTree<int, int> *root = generateBalancedTree();

    cout << "\trotating right" << endl;
    root->rotateRightChild(RIGHT);

    cout << "\trotating left" << endl;
    root->rotateRightChild(LEFT);

    cout << "rotation of right child successful" << endl;

    freeBalancedTree(root);
}

void testRotateLeftChild() {
    AVLSearchTree<int, int> *root = generateBalancedTree();

    cout << "\trotating left" << endl;
    root->rotateLeftChild(LEFT);

    cout << "\trotating right" << endl;
    root->rotateLeftChild(RIGHT);

    cout << "rotation of left child successful" << endl;

    freeBalancedTree(root);
}
