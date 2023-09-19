#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(NULL), next(NULL) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() : head(NULL), tail(NULL) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int count_triplets() {
        int count = 0;
        Node* current = head;
        while (current->next->next != NULL ) {
            int sum = current->data + current->next->data + current->next->next->data;
            if (sum == 0) {
                count++;
            }
            current = current->next;
        }
        return count;
    }
};

int main() {
    int n;
    cin >> n;
    DoublyLinkedList linkedList;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        linkedList.insert(m);
    }

    int result = linkedList.count_triplets();
    cout << result << endl;

    return 0;
}

