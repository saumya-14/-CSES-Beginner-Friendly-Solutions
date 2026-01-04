#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

/*
Problem:
--------
Given 'n' coin denominations and a target sum.

We want to:
1️⃣ Find the minimum number of coins needed to make the target (Memoization)
2️⃣ Count the number of ways to make the target (Tabulation)

====================================================
1️⃣ PURE RECURSIVE SOLUTION (THOUGHT PROCESS)
====================================================

Idea:
-----
At every coin index, we have two choices:
- ❌ Do NOT take the coin → move to previous index
- ✅ Take the coin → stay on same index, reduce target

Recursive relation:
-------------------
f(index, target) = min(
    f(index - 1, target),               // not take
    1 + f(index, target - coin[index]) // take
)

Base cases:
-----------
- If index == 0:
    - If target divisible by coin[0] → target / coin[0]
    - Else → impossible
- If target < 0 → impossible

⚠️ This approach is exponential and causes TLE.
*/

int solveRecursive(vector<int>& coins, int index, int target) {
    if (index == 0) {
        if (target % coins[0] == 0)
            return target / coins[0];
        return 1e9;
    }

    int notTake = solveRecursive(coins, index - 1, target);
    int take = 1e9;

    if (coins[index] <= target) {
        take = 1 + solveRecursive(coins, index, target - coins[index]);
    }

    return min(notTake, take);
}

/*
====================================================
2️⃣ MEMOIZATION (TOP-DOWN DP)
====================================================

Problem with recursion:
-----------------------
Same states (index, target) are recomputed many times.

Solution:
---------
- Use a 2D dp table
- dp[index][target] stores the minimum coins needed
- If already computed → reuse it

Time Complexity: O(n * target)
Space Complexity: O(n * target)
*/

int solveMemo(vector<int>& coins, int index, int target, vector<vector<int>>& dp) {
    if (index == 0) {
        if (target % coins[0] == 0)
            return target / coins[0];
        return 1e9;
    }

    if (dp[index][target] != -1)
        return dp[index][target];

    int notTake = solveMemo(coins, index - 1, target, dp);
    int take = 1e9;

    if (coins[index] <= target) {
        take = 1 + solveMemo(coins, index, target - coins[index], dp);
    }

    return dp[index][target] = min(notTake, take);
}

/*
====================================================
3️⃣ TABULATION (BOTTOM-UP DP)
====================================================

⚠️ NOTE:
--------
This version solves a DIFFERENT variant:
It counts the number of ways to form the target.

Idea:
-----
dp[i] = number of ways to make sum i

Base case:
----------
dp[0] = 1  (one way to form sum 0)

Transition:
-----------
For each sum i:
    Try all coins
    dp[i] += dp[i - coin]

This avoids recursion and is optimal.

Time Complexity: O(n * target)
Space Complexity: O(target)
*/

int solveTabulationWays(vector<int>& coins, int target) {
    vector<int> dp(target + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= target; i++) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = (dp[i] + dp[i - coin]) % MOD;
            }
        }
    }

    return dp[target];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;

    vector<int> coins(n);
    for (int &c : coins) cin >> c;

    /*
        Uncomment ONE approach at a time.
    */

    // 1️⃣ Pure Recursion (for understanding only)
    // cout << solveRecursive(coins, n - 1, target) << "\n";

    // 2️⃣ Memoization (Minimum coins)
    // vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    // cout << solveMemo(coins, n - 1, target, dp) << "\n";

    // 3️⃣ Tabulation (Number of ways)
    cout << solveTabulationWays(coins, target) << "\n";

    return 0;
}
