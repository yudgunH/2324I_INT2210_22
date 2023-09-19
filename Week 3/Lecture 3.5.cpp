#include <iostream>
#include <stack>
using namespace std;
int main() {
    int n;
    cin >> n;
    stack<int> stack;
    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;
        if (operation == "push") {
            int x;
            cin >> x;
            stack.push(x);
        } 
		else if (operation == "pop") {
            if (!stack.empty()) {
                stack.pop();
            }
        }
    }
 
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
    return 0;
}

