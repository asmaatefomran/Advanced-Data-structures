/*
 * Important notes then implementation
 *
 *
 *
Advantages of Red-Black Trees:
-Balanced: Red-Black Trees are self-balancing, meaning they automatically maintain a balance between the heights of the left and right subtrees. This ensures that search, insertion, and deletion operations take O(log n) time in the worst case.
-Efficient search, insertion, and deletion: Due to their balanced structure, Red-Black Trees offer efficient operations. Search, insertion, and deletion all take O(log n) time in the worst case.
-Simple to implement: The rules for maintaining the Red-Black Tree properties are relatively simple and straightforward to implement.
-Widely used: Red-Black Trees are a popular choice for implementing various data structures, such as maps, sets, and priority queues.

Disadvantages of Red-Black Trees(in more details):
- More Complex than Other Balanced Trees
Explanation: Red-Black Trees are designed to ensure that the tree remains "approximately balanced" after each insertion and deletion.
 However, to achieve this, Red-Black Trees enforce a set of five rules that govern node colors (red or black) and their placement in the tree.
 These rules make the insertion and deletion processes more complicated than in simpler trees, like Binary Search Trees (BSTs), which have no balancing rules.
Comparison with AVL Trees: While AVL trees also balance after each operation, they only require a single type of rotation and no color changes, which simplifies their balancing logic.
 In contrast, Red-Black Trees have multiple cases for rotations and recoloring that must be handled carefully, making their code and maintenance more complex.
- Constant Overhead for Maintaining Red-Black Properties
Explanation: Every insertion or deletion in a Red-Black Tree requires the tree to check and potentially rebalance itself to maintain the Red-Black properties.
 This rebalancing can involve rotations and color changes, which add a constant time overhead to each operation.
 Although the cost of each individual operation is still logarithmic, this additional work means that, on average, Red-Black Trees have slightly slower insertions and deletions compared to simpler BSTs.
Impact on Efficiency: For most applications, this constant overhead is minimal and doesn't noticeably affect performance.
 However, in cases where many insertions and deletions are performed rapidly, such as in some real-time applications, this small overhead can accumulate and impact performance.
- Not Optimal for All Use Cases
Explanation: Red-Black Trees are excellent for scenarios where a balanced structure is needed, and the number of operations is relatively low or moderate.
 However, in applications where there are frequent or bulk insertions and deletions, the overhead of maintaining Red-Black properties can add up.
 For example, data structures like skip lists, hash tables, or even AVL trees might be better suited to handle cases with very high insertion or deletion rates since they either skip balancing or are optimized differently.
Alternatives: Other structures, like AVL trees, provide more strict balancing, making them more efficient for applications that require fast lookups but slightly fewer updates.
 Similarly, skip lists and hash tables provide alternatives that can avoid the complexities and overhead of maintaining a tree structure altogether.
:In summary, Red-Black Trees are balanced and efficient in many cases but come with trade-offs in complexity and overhead, making them less ideal for applications needing ultra-fast or very frequent modifications.

Applications of Red-Black Trees:
-Implementing maps and sets: Red-Black Trees are often used to implement maps and sets, where efficient search, insertion, and deletion are crucial.
-Priority queues: Red-Black Trees can be used to implement priority queues, where elements are ordered based on their priority.
-File systems: Red-Black Trees are used in some file systems to manage file and directory structures.
-In-memory databases: Red-Black Trees are sometimes used in in-memory databases to store and retrieve data efficiently.
-Graphics and game development: Red-Black Trees can be used in graphics and game development for tasks like collision detection and pathfinding.
 */

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

    void fix_insertion(Node *&node) {
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

    void transplant(Node *u, Node *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    void DoupleBlackFix(Node *x) {
        while (x != root && x->color == false) {
            if (x == x->parent->left) {
                Node *sibling = x->parent->right;
                if (sibling->color == true) {
                    sibling->color = false;
                    x->parent->color = true;
                    left_rotate(x->parent);
                    sibling = x->parent->right;
                }
                if (sibling->left->color == false && sibling->right->color == false) {
                    sibling->color = true;
                    x = x->parent;
                } else {
                    //case 5 if needed
                    // update we should check on the far before the near because if the far is red we will
                    //apply case 6 and will not care about if the near is red or black
                    if (sibling->right->color == false) {
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
                Node *sibling = x->parent->left;
                if (sibling->color == true) {
                    sibling->color = false;
                    x->parent->color = true;
                    right_rotate(x->parent);
                    sibling = x->parent->left;
                }
                if (sibling->right->color == false && sibling->left->color == false) {
                    sibling->color = true;
                    x = x->parent;
                } else {
                    if (sibling->left->color == false) {
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

        fix_insertion(nw);
    }
    void remove(ll data){
        Node *z = root;
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

        Node *y = z;
        bool yOriginalColor = y->color;
        Node *x;

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
        if (yOriginalColor == false) {
            DoupleBlackFix(x);
        }
    }
    void dfs(Node * n){
        cout<<n->data <<' '<<((n->color)?"red":"black")<<endl;
        if(n->left!= nil)
            dfs(n->left);
        if(n->right!= nil)
            dfs(n->right);
        return;

    }
    void traverse() {
        dfs(root);
    }


};

int main(){
    RBTree tree;
    tree.insert(2);
    tree.traverse();
    cout<<'\n';
    tree.insert( 5);
    tree.traverse();
    cout<<'\n';

    tree.insert(3);
    tree.insert(7);
    tree.insert(8);
    tree.insert(10);
    tree.remove(5);
    tree.traverse();



}