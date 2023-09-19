#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int countPair(int a[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int count = 0;
    count = countPair(a, n);
    cout << count;
    return 0;
}

