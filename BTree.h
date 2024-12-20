#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T, int ORDER>
class BTree {
private:
    struct BNode {
        vector<T> keys;
        vector<BNode*> childs;
        bool isLeaf;
        BNode(bool leaf = true) : isLeaf(leaf) {}
    };

    BNode* root;

    void split(BNode* parent, int i, BNode* child);
    void insertNonFull(BNode* node, const T& key);
    void printTree(BNode* node, int level = 0);

public:
    BTree();
    void Insert(const T& data);
    void Print();
};

#endif
