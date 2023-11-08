#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct artifact {
    int weight;
    int profit;
};

bool compareByRatio(artifact artifact1, artifact artifact2) {
    return (double)artifact1.profit / artifact1.weight > (double)artifact2.profit / artifact2.weight;
}

double knapsackGreedy(vector<artifact>& artifacts, int capacity) {
    sort(artifacts.begin(), artifacts.end(), compareByRatio);

    int totalProfit = 0;
    int remainingCapacity = capacity;

    for (int i = 0; i < artifacts.size(); i++) {
        if (artifacts[i].weight <= remainingCapacity) {
            totalProfit += artifacts[i].profit;
            remainingCapacity -= artifacts[i].weight;
        } else {
           continue;
        }
    }

    return totalProfit;
}

int main() {
    int N, W;
    cout << "Enter the knapsack capacity (W): ";
    cin >> W;
    cout << "Enter the number of artifacts (N): ";
    cin >> N;
    
    vector<artifact> artifacts(N);

    for (int i = 0; i < N; i++) {
        cout << "Enter weight and profit for artifact " << i + 1 << ": ";
        cin >> artifacts[i].weight >> artifacts[i].profit;
    }

    double maxProfit = knapsackGreedy(artifacts, W);

    cout << "The maximum total profit using the greedy algorithm is: " << maxProfit << endl;

    return 0;
}