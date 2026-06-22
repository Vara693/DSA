#include <iostream>
#include <vector>
using namespace std;

int fibonacciUsingRecursion(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciUsingRecursion(n-1) + fibonacciUsingRecursion(n-2);
}

int fibonacciUsingMemoization(int n, vector<int> &dp) {
    if (n <= 1) {
        return n;
    }
    if (dp[n] != -1) {
        return dp[n];
    }
    return dp[n] = fibonacciUsingMemoization(n-1, dp) + fibonacciUsingMemoization(n-2, dp);
}

int fibonacciUsingTabulation(int n) {
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i=2; i<=n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int main() {
    int n = 10;
    cout << "Fibonacci using recursion: " << fibonacciUsingRecursion(n) << endl;    
    vector<int> dp(n+1, -1);
    cout << "Fibonacci using memoization: " << fibonacciUsingMemoization(n, dp) << endl;
    cout << "Fibonacci using tabulation: " << fibonacciUsingTabulation(n) << endl;
    return 0;
}