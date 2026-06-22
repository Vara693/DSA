#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Algorithm FractionalKnapsack(nums, capacity):
//     sort nums by (value/weight) in descending order
//     cost ← 0
//     w ← 0
//     i ← 0
//     while w < capacity and i < length(nums):
//         a ← min(nums[i].weight, capacity - w)
//         cost ← cost + (a / nums[i].weight) * nums[i].value
//         w ← w + a
//         i ← i + 1
//     return cost
//time complexity = O(nlogn)
//space complexity = O(1)

float knapsack(vector<vector<int>> &nums, int capacity) {
    float cost = 0;
    sort(nums.begin(), nums.end(), [](vector<int> &a, vector<int> &b) { //O(nlogn)
        return (double)a[0]/a[1] > (double)b[0]/b[1];
    });
    int i =0;
    int w = 0;
    while (capacity > w && i<nums.size()) {  //O(n)
        int a = min(nums[i][1], capacity-w);
        cost+= ((float)a/nums[i][1])*nums[i][0];
        w+=a;
        i++;
    }
    return cost;
}
int main() {
    vector<vector<int>> nums = {{60, 10}, {100, 20}, {140, 70}};
    int cost = knapsack(nums, 50);
    cout << "Max cost: " << cost << endl;
    return 0;
}