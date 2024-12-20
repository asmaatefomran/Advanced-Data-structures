#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>
#include <algorithm>
#define ll long long

using namespace std;

// red--->true    black--->false
template <typename T>
class RBTreeNode {
public:
    T data;
    bool color;
    RBTreeNode *left, *right, *parent;
    RBTreeNode(T data);
};

template <typename T>
class RBTree {
private:
    RBTreeNode<T> *root, *nil;

    void left_rotate(RBTreeNode<T> *&node);
    void right_rotate(RBTreeNode<T> *&node);
    void fix_insertion(RBTreeNode<T> *&node);
    void transplant(RBTreeNode<T> *u, RBTreeNode<T> *v);
    RBTreeNode<T>* minimum(RBTreeNode<T> *node);
    void DoupleBlackFix(RBTreeNode<T> *x);
    void dfs(RBTreeNode<T> *n);

public:
    RBTree();
    void insert(T data);
    void remove(T data);
    void traverse();
};
#include "RedBlackTree.tpp"


#endif
