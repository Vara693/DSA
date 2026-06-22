#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// Algorithm JobSequencing(jobs, profits):
//     sort jobs by profit descending        // O(n log n)
//     maxprofit ← 0

//     for each job in jobs:                 // O(n^2)
//         profit ← job.profit
//         deadline ← job.deadline

//         for j ← deadline downto 1:
//             if profits[j] == -1:
//                 profits[j] ← profit
//                 maxprofit ← maxprofit + profit
//                 break

//     return maxprofit
//Time complexity: O(n^2)
//Space complexity: O(n)

int jobSequencing(vector<pair<int, int>> &jobs, vector<int> &profits) {
    sort(jobs.begin(), jobs.end(), [](auto &a, auto &b) {  //O(nlogn)
        return a.first > b.first;
    });

    // int n = 0;
    // for (auto &it: jobs) {   //O(n)
    //     n = max(n, it.second);
    // }
    int maxprofit = 0;
    for (int i=0; i<jobs.size(); i++) {   //O(n^2)
        int profit = jobs[i].first;
        int delay = jobs[i].second;

        int idx = delay;
        for (int j=delay; j>0; j--) {
            if (profits[j] == -1) {
                maxprofit+=profit;
                profits[j] = profit;
                break;
            }
        }
    }
    return maxprofit;
}
int main() {
    vector<pair<int,int>> jobs = {
        {80, 2}, {70, 6}, {65, 6}, {60, 5},
        {25, 4}, {22, 2}, {20, 4}, {10, 2}
    };

    vector<int> profits(7, -1);
    cout << jobSequencing(jobs, profits) << endl;
    for (int val: profits) {
        cout << val << endl;
    }
    return 0;
}