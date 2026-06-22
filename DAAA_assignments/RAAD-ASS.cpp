#include <bits/stdc++.h>
using namespace std;

int minOperations(vector<int>& arr) {
    int n = arr.size();

    unordered_map<int, int> freq;

    // Count frequency of each value
    for (int x : arr) {
        freq[x]++;
    }

    unordered_set<int> targets;

    // Possible targets = original values + frequency values
    for (auto &p : freq) {
        targets.insert(p.first);
        targets.insert(p.second);
    }

    int ans = INT_MAX;

    for (int target : targets) {
        int ops = 0;
        bool possible = true;

        for (int x : arr) {
            if (x == target) {
                continue; // already correct
            }
            else if (freq[x] == target) {
                ops++; // convert this element
            }
            else {
                possible = false;
                break;
            }
        }

        if (possible) {
            ans = min(ans, ops);
        }
    }

    return (ans == INT_MAX ? -1 : ans);
}

int main() {
    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    cout << minOperations(arr) << endl;
    return 0;
}