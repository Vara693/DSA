#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

double fractionalKnapsack(pair<int,int> profits[], int n, int capacity) {
    sort(profits, profits+n, [](const pair<int,int>& a, const pair<int,int>& b) {
        return (double)a.first/a.second > (double)b.first/b.second;
    });

    int w = 0;
    double maxProfit = 0.0;
    int i = 0;

    while (capacity > w && i < n) {
        int take = min(profits[i].second, capacity - w);
        maxProfit += ((double)take / profits[i].second) * profits[i].first;
        w += take;
        i++;
    }
    return maxProfit;
}

int main() {
    pair<int,int> profits[] = {{10,2}, {5,3}, {20,1}};
    cout << fractionalKnapsack(profits, 3, 3);
    return 0;
}