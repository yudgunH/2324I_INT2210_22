#include <iostream>
using namespace std;

// Hàm tính giai thừa
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Hàm tính tổ hợp chập k của n
long long nChooseK(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int V, E;
    cout << "Nhap so luong dinh (V): ";
    cin >> V;
    cout << "Nhap so luong canh (E): ";
    cin >> E;

    // Vì mỗi cặp đỉnh có thể tạo ra 2 cạnh (mỗi hướng một cạnh)
    // Tổng số cạnh có thể có là V * (V - 1)
    int maxEdges = V * (V - 1);

    // Nếu số cạnh nhập vào lớn hơn số cạnh tối đa có thể có
    // thì không thể tạo ra đồ thị
    if (E > maxEdges) {
        cout << "Khong the tao ra do thi voi " << E << " canh." << endl;
        return 0;
    }

    // Tính số lượng đồ thị có thể có
    long long numberOfGraphs = nChooseK(maxEdges, E);
    cout << "So luong do thi co the co la: " << numberOfGraphs << endl;

    return 0;
}