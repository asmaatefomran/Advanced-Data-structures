#include "BTree.h"

// Constructor
template <typename T, int ORDER>
BTree<T, ORDER>::BTree() : root(new BNode()) {}

// Method to split a child node
template <typename T, int ORDER>
void BTree<T, ORDER>::split(BNode* parent, int i, BNode* child) {
    BNode* newChild = new BNode(child->isLeaf);
    int mid = ORDER / 2;

    parent->keys.insert(parent->keys.begin() + i, child->keys[mid]);
    parent->childs.insert(parent->childs.begin() + i + 1, newChild);

    for (int j = mid + 1; j < ORDER; j++) {
        newChild->keys.push_back(child->keys[j]);
    }
    if (!child->isLeaf) {
        for (int j = mid + 1; j < ORDER + 1; j++) {
            newChild->childs.push_back(child->childs[j]);
        }
    }
    child->keys.resize(mid);
    child->childs.resize(mid + 1);
}

// Method to insert a key into a node that's not full
template <typename T, int ORDER>
void BTree<T, ORDER>::insertNonFull(BNode* node, const T& key) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, key);
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        BNode* child = node->childs[i];
        if (child->keys.size() == ORDER) {
            split(node, i, child);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->childs[i], key);
    }
}

// Method to print the tree recursively
template <typename T, int ORDER>
void BTree<T, ORDER>::printTree(BNode* node, int level) {
    if (node == nullptr) return;

    for (int i = 0; i < node->keys.size(); i++) {
        if (i > 0) std::cout << ',';
        std::cout << node->keys[i];
    }
    cout << endl;

    if (!node->isLeaf) {
        for (int i = 0; i < node->childs.size(); i++) {
            for (int j = 0; j < level + 1; j++) {
                cout << "  ";
            }
            printTree(node->childs[i], level + 1);
        }
    }
}

// Method to insert a key into the tree
template <typename T, int ORDER>
void BTree<T, ORDER>::Insert(const T& data) {
    BNode* r = root;
    if (r->keys.size() == ORDER) {
        BNode* newRoot = new BNode(false);
        newRoot->childs.push_back(r);
        split(newRoot, 0, r);
        root = newRoot;
    }
    insertNonFull(root, data);
}

// Method to print the whole tree
template <typename T, int ORDER>
void BTree<T, ORDER>::Print() {
    printTree(root);
}

// Explicit template instantiation
template class BTree<int, 3>;
template class BTree<char, 5>;
