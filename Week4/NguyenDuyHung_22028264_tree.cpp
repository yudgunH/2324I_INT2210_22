#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* right;
    Node* left;
};

void init(Node* &root) {
    root = NULL;
}

void insert(Node* &root, int x) {
    if(root == NULL) {
        Node *p = new Node();
        p->data = x;
        p->left = NULL;
        p->right = NULL;
        root = p;
    }
    else {
        if(root->data > x) {
            insert(root->left, x);
        }
        else {
            insert(root->right, x);
        }
    }
}

void preOrder(Node* root) {
    if(root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if(root != NULL) {
        inOrder(root->left);
        cout<< root->data << " ";
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout<< root->data << " ";
    }
}

void remove(Node* &root, int x) {
    if(root != NULL) {
        Node *p = root;
        Node *parent = NULL;
        while (p != NULL && p->data != x) {
            parent = p;
            if(p->data > x) {
                p = p->left;
            } else {
                p = p->right;
            }
        }

        if(p != NULL) {
            if(p->left == NULL && p->right == NULL) {
                if(parent->data > p->data) {
                    parent->left = NULL;
                }
                else {
                    parent->right = NULL;
                }
                delete(p);
            }
        }
    }
}
