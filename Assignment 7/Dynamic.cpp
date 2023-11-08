
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


int knapsackDP(vector<int>& weights, vector<int>& profits, int capacity) {
    int N = weights.size();
    vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + profits[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[N][capacity];
}

int main() {
    int N, W;
    cout << "Enter the number of artifacts (N): ";
    cin >> N;
    cout << "Enter the knapsack capacity (W): ";
    cin >> W;

    vector<int> weights(N);
    vector<int> profits(N);

    for (int i = 0; i < N; i++) {
        cout << "Enter weight and profit for artifact " << i + 1 << ": ";
        cin >> weights[i] >> profits[i];
    }

    int maxProfit = knapsackDP(weights, profits, W);

    cout << "The maximum total profit using dynamic programming is: " << maxProfit << endl;

    return 0;
}