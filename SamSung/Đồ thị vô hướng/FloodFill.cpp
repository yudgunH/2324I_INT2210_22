#include <iostream>
#include <vector>
using namespace std;

void floodFillUtil(vector<vector<int>>& image, int x, int y, int prevColor, int newColor) {
    int M = image.size();
    int N = image[0].size();

    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (image[x][y] != prevColor)
        return;

    image[x][y] = newColor;

    floodFillUtil(image, x+1, y, prevColor, newColor);
    floodFillUtil(image, x-1, y, prevColor, newColor);
    floodFillUtil(image, x, y+1, prevColor, newColor);
    floodFillUtil(image, x, y-1, prevColor, newColor);
}

void floodFill(vector<vector<int>>& image, int x, int y, int newColor) {
    int prevColor = image[x][y];
    if (prevColor != newColor) {
        floodFillUtil(image, x, y, prevColor, newColor);
    }
}

int main() {
    int M, N;
    cout << "Nhập kích thước ảnh (M N): ";
    cin >> M >> N;

    vector<vector<int>> image(M, vector<int>(N));
    cout << "Nhập các giá trị màu của ảnh (dạng ma trận):" << endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> image[i][j];
        }
    }

    int x, y, newColor;
    cout << "Nhập vị trí bắt đầu của flood fill (x y): ";
    cin >> x >> y;
    cout << "Nhập màu mới: ";
    cin >> newColor;

    floodFill(image, x, y, newColor);

    // In ra kết quả
    cout << "Ảnh sau khi áp dụng flood fill:" << endl;
    for (const auto& row : image) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;
}
