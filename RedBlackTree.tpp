#include "RedBlackTree.h"
template <typename T>
RBTreeNode<T>::RBTreeNode(T data)
        : data(data), color(true), left(nullptr), right(nullptr), parent(nullptr) {}


template <typename T>
RBTree<T>::RBTree() {
    nil = new RBTreeNode<T>(T());
    nil->color = false;
    root = nil;
}

template <typename T>
void RBTree<T>::left_rotate(RBTreeNode<T> *&node) {
    RBTreeNode<T> *rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nil) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

template <typename T>
void RBTree<T>::right_rotate(RBTreeNode<T> *&node) {
    RBTreeNode<T> *leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nil) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

template <typename T>
void RBTree<T>::fix_insertion(RBTreeNode<T> *&node) {
    RBTreeNode<T> *parent = nullptr;
    RBTreeNode<T> *grandparent = nullptr;

    while (node != root && node->color && node->parent->color) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            RBTreeNode<T> *uncle = grandparent->right;
            if (uncle->color) {
                grandparent->color = true;
                parent->color = false;
                uncle->color = false;
                node = grandparent;
            } else {
                //the if to check we need two rotation or only one is enuogh
                if (node == parent->right) {
                    left_rotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                right_rotate(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else {
            RBTreeNode<T> *uncle = grandparent->left;
            if (uncle->color) {
                grandparent->color = true;
                parent->color = false;
                uncle->color = false;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    right_rotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                left_rotate(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = false;
}

template <typename T>
void RBTree<T>::transplant(RBTreeNode<T> *u, RBTreeNode<T> *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template <typename T>
RBTreeNode<T>* RBTree<T>::minimum(RBTreeNode<T> *node) {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

template <typename T>
void RBTree<T>::DoupleBlackFix( RBTreeNode<T>  *x) {
    while (x != root && !x->color) {
        if (x == x->parent->left) {
            RBTreeNode<T>  *sibling = x->parent->right;
            if (sibling->color) {
                sibling->color = false;
                x->parent->color = true;
                left_rotate(x->parent);
                sibling = x->parent->right;
            }
            if (!sibling->left->color && !sibling->right->color) {
                sibling->color = true;
                x = x->parent;
            } else {
                //case 5 if needed
                // update we should check on the far before the near because if the far is red we will
                //apply case 6 and will not care about if the near is red or black
                if (!sibling->right->color) {
                    sibling->left->color = false;
                    sibling->color = true;
                    right_rotate(sibling);
                    sibling = x->parent->right;
                }
                // case 6 will always be excuted as we work on case 5 to case reach to case 6
                sibling->color = x->parent->color;
                x->parent->color = false;
                sibling->right->color = false;
                left_rotate(x->parent);
                x = root;
            }
        } else {
            RBTreeNode<T>  *sibling = x->parent->left;
            if (sibling->color) {
                sibling->color = false;
                x->parent->color = true;
                right_rotate(x->parent);
                sibling = x->parent->left;
            }
            if (!sibling->right->color && !sibling->left->color) {
                sibling->color = true;
                x = x->parent;
            } else {
                if (!sibling->left->color) {
                    sibling->right->color = false;
                    sibling->color = true;
                    left_rotate(sibling);
                    sibling = x->parent->left;
                }
                sibling->color = x->parent->color;
                x->parent->color = false;
                sibling->left->color = false;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false;   // to handle that the root should always be black(false)
}

template <typename T>
void RBTree<T>::insert(T data) {
    RBTreeNode<T> *nw = new RBTreeNode<T>(data), *par = nullptr, *curr = root;
    nw->left = nil;
    nw->right = nil;

    while (curr != nil) {
        par = curr;
        if (nw->data < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    nw->parent = par;
    if (par == nullptr) {
        root = nw;
    } else if (nw->data < par->data) {
        par->left = nw;
    } else {
        par->right = nw;
    }

    fix_insertion(nw);
}

template <typename T>
void RBTree<T>::remove(T data) {
    RBTreeNode<T> *z = root;
    while (z != nil) {
        if (z->data == data) {
            break;
        } else if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }
    if (z == nil) {
        cout << "Value not found in the tree." << endl;
        return;
    }

    RBTreeNode<T> *y = z;
    bool yOriginalColor = y->color;
    RBTreeNode<T> *x;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (!yOriginalColor) {
        DoupleBlackFix(x);
    }
}

template <typename T>
void RBTree<T>::dfs(RBTreeNode<T> *n) {
    cout << n->data << ' ' << ((n->color) ? "red" : "black") << endl;
    if (n->left != nil) {
        dfs(n->left);
    }
    if (n->right != nil) {
        dfs(n->right);
    }
}

template <typename T>
void RBTree<T>::traverse() {
    if (root != nil) {
        dfs(root);
    }
}