#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#define Asma ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define testcase  while(t--)
#define ll long long
#define endl "\n"
using namespace std;

// red--->true    black--->false

class Node {
public:
    int data;
    bool color;
    Node *left, *right, *parent;
    Node(int data) : data(data), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree{
private:
    Node *root,*nil;

    void left_rotate(Node *&node) {
        Node *rightChild = node->right;
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

    void right_rotate(Node *&node) {
        Node *leftChild = node->left;
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

    void fix(Node *&node) {
        Node *parent = nullptr;
        Node *grandparent = nullptr;

        while (node != root && node->color == true && node->parent->color == true) {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node *uncle = grandparent->right;
                if (uncle->color == true) {
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
                Node *uncle = grandparent->left;
                if (uncle->color == true) {
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

public:
    RBTree(){
        nil=new Node(0);
        nil->color=false;
        root=nil;
    }
    void insert(ll data){
        Node* nw=new Node(data),*par=nullptr,*curr=root;
        nw->left=nil;
        nw->right=nil;
        //nw->color=true;  in the constructor of the node any node is red by default
        while(curr!=nil){
            par=curr;
            if(nw->data<curr->data){
                curr=curr->left;
            }else curr=curr->right;
        }
        nw->parent=par;
        if(par== nullptr){
            root=nw;
        }else if(nw->data<par->data){
            par->left=nw;
        }else par->right=nw;

        fix(nw);

    }

};
