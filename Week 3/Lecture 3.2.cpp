#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(NULL) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(NULL) {}

    void insert(int p, int x) {
        Node* newNode = new Node(x);
        if (p == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            for (int i = 0; i < p - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void deleteNode(int p) {
        if (head == NULL) {
            return;
        }
        if (p == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* temp = head;
            for (int i = 0; i < p - 1; i++) {
                temp = temp->next;
            }
            if (temp->next != NULL) {
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
            }
        }
    }

    void PrintNode() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList linkedList;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;
        if (operation == "insert") {
            int p, x;
            cin >> p >> x;
            linkedList.insert(p, x);
        } else if (operation == "delete") {
            int p;
            cin >> p;
            linkedList.deleteNode(p);
        }
    }

    linkedList.PrintNode();
    return 0;
}

