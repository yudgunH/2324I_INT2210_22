#include <iostream>
#include <vector>

using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int N = grid.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));

    dp[0][0] = grid[0][0];

    // Khởi tạo hàng đầu tiên và cột đầu tiên của ma trận dp
    for (int i = 1; i < N; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
        dp[0][i] = dp[0][i - 1] + grid[0][i];
    }

    // Xây dựng phần còn lại của ma trận dp
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    return dp[N - 1][N - 1];
}

int main() {
    int N;
    cout << "Enter the size of the grid (N): ";
    cin >> N;

    vector<vector<int>> grid(N, vector<int>(N));
    cout << "Enter the grid values:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    cout << "Minimum path sum: " << minPathSum(grid) << endl;

    return 0;
}
