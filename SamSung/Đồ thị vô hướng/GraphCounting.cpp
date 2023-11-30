#include <iostream>
using namespace std;

// Hàm tính giai thừa
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Hàm tính tổ hợp chập k của n
unsigned long long binomialCoefficient(int n, int k) {
    if (k > n - k) k = n - k;
    unsigned long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Hàm tính số lượng đồ thị vô hướng khác nhau
unsigned long long countGraphs(int V, int E) {
    int maxEdges = V * (V - 1) / 2;
    if (E > maxEdges) return 0;
    return binomialCoefficient(maxEdges, E);
}

int main() {
    int V, E;
    cout << "Nhập số đỉnh (V): ";
    cin >> V;
    cout << "Nhập số cạnh (E): ";
    cin >> E;

    unsigned long long numberOfGraphs = countGraphs(V, E);
    cout << "Số lượng đồ thị vô hướng khác nhau có " << V << " đỉnh và " << E << " cạnh là: " << numberOfGraphs << endl;

    return 0;
}
