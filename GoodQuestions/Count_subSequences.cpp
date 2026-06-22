#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool isSubsequence(string word, unordered_map<char, int> mp) {
    bool ans = false;
    for (char ch: word) {
        if (mp.find(ch) != mp.end() && mp[ch]>0) {
            mp[ch]--;
            ans = true;
        } else {
            ans = false;
        }
    }
    return ans;
}

int Count_subSequences(string &s, vector<string> &words) {
    unordered_map<char, int> mp;
    int counter = 0;
    for (char ch: s) {
        mp[ch]++;
    }

    for (auto &word: words) {
        if (isSubsequence(word, mp)) {
            counter++;
        }
    }
    return counter;
}

int main() {
    string ans = "abcdef";
    vector<string> words = {"aa", "a", "ab", "ace", "bd", "ee", "acf", "dg"};

    cout<< Count_subSequences(ans, words) << endl;
    return 0;
}