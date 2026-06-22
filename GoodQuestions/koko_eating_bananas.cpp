#include <iostream>
#include <vector>
#include <algorithm>  // for max_element
#include <cmath>      // for ceil

using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        int result = right;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (canEatAll(piles, h, mid)) {
                result = mid;       // feasible, try smaller speed
                right = mid - 1;
            } else {
                left = mid + 1;     // not feasible, need faster speed
            }
        }
        return result;
    }

private:
    bool canEatAll(vector<int>& piles, int h, int k) {
        long long hours = 0;
        for (int bananas : piles) {
            hours += (bananas + k - 1) / k;  // ceil(bananas / k)
        }
        return hours <= h;
    }
};

int main() {
    Solution sol;
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;

    cout << "Minimum eating speed: " << sol.minEatingSpeed(piles, h) << endl;
    return 0;
}