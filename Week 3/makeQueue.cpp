#include <stack>
#include<iostream>
using namespace std;

class Queue {
    stack<int> s1, s2;

public:
    void enqueue(int x)
    {
        // Nhét vào stack 1
        s1.push(x);
    }

    int dequeue()
    {
        // Kiểm tra 2 stack xem có rỗng hay không
        if (s1.empty() && s2.empty()) {
            return -1;
        }

        // Nếu stack 2 rỗng và stack 1 đầy
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        // Trả về giá trị Front() và xóa nó
        int top_val = s2.top();
        s2.pop();
        return top_val;
    }
    
};

int main() {
    Queue test;
    int m;  cin >> m;
    for(int i = 0; i < m; i++)
    {
        int n; cin >> n;
        test.enqueue(n);
    }
    for (int i = 0; i < m; i++)
    {
        cout << test.dequeue() << " ";
    }
    return 0;

}