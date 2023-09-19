#include<iostream>
#include<queue>
using namespace std;

class Stack
{
private:
    /* data */
    queue<int> q1, q2;
public:
    void push(int x)
    {
        // Nhét vào queue 1
        q1.push(x);
    }

    int pop()
    {
        // Cả 2 queue đều rỗng
        if (q1.empty() && q2.empty()) {
            return -1;
        }

        // Queue thứ nhất có phần tử
        if (!q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }

            // Trả về phần tử đầu tiên
            int top_val = q1.front();
            q1.pop();

            // Đổi chỗ 2 queue
            swap(q1, q2);
            return top_val;
        }
    }

};

int main() {
    Stack st;
    for (int i = 0; i < 5; i++)
    {
        /* code */
        int n;  cin >> n;
        st.push(n);
    }

    for (int i = 0; i < 5; i++)
    {
        /* code */
        cout << st.pop();
    }

    return 0;
}


