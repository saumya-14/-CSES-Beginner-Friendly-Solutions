#include <bits/stdc++.h>
using namespace std;

/*
====================================================
PROBLEM:https://cses.fi/problemset/task/1634
====================================================


*/


/*
====================================================
1️⃣ RECURSIVE THOUGHT PROCESS (Top-Down Idea)
====================================================

func(index, target) = minimum coins needed
using coins from [0 ... index]

Choices:
---------
1. Do NOT take the current coin
   → move to previous index
2. Take the current coin
   → reduce target and stay at same index (unlimited usage)

Base Case:
----------
If index == 0:
- If target is divisible by v[0]
  → answer = target / v[0]
- Else
  → not possible (return large value)
*/

int func(vector<int>& v, int target, int index, vector<vector<int>>& dp) {

    // Base case: only one coin available
    if (index == 0) {
        if (target % v[0] == 0)
            return target / v[0];
        else
            return 1e9;   // represents impossible
    }

    // If already computed, reuse result
    if (dp[index][target] != -1)
        return dp[index][target];

    // Option 1: Do not take current coin
    int nottake = func(v, target, index - 1, dp);

    // Option 2: Take current coin (if possible)
    int take = 1e9;
    if (v[index] <= target) {
        take = 1 + func(v, target - v[index], index, dp);
    }

    // Store and return minimum
    return dp[index][target] = min(nottake, take);
}

/*
====================================================
2️⃣ TABULATION (Bottom-Up DP) – USED IN MAIN
====================================================

dp[i][j] = minimum coins needed to make sum j
using coins from [0 ... i]

Initialization:
---------------
dp[0][j]:
- If j divisible by v[0] → j / v[0]
- Else → impossible

Transition:
-----------
dp[i][j] = min(
    dp[i-1][j],                 // not take coin i
    1 + dp[i][j - v[i]]         // take coin i
)

Answer:
-------
dp[n-1][target]
====================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // dp table
    vector<vector<int>> dp(n, vector<int>(target + 1, 1e9));

    // Base case initialization for first coin
    for (int j = 0; j <= target; j++) {
        if (j % v[0] == 0)
            dp[0][j] = j / v[0];
        else
            dp[0][j] = 1e9;
    }

    // Fill dp table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= target; j++) {

            // Option 1: not take the coin
            int nottake = dp[i - 1][j];

            // Option 2: take the coin (if possible)
            int take = 1e9;
            if (v[i] <= j) {
                take = 1 + dp[i][j - v[i]];
            }

            // Store minimum
            dp[i][j] = min(take, nottake);
        }
    }

    int result = dp[n - 1][target];

    // Output result
    if (result >= 1e9)
        cout << -1 << "\n";
    else
        cout << result << "\n";

    return 0;
}
