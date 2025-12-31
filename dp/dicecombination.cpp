#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

/*
Problem link: https://cses.fi/problemset/task/1633

====================================================
1️⃣ PURE RECURSIVE SOLUTION (THOUGHT PROCESS)
====================================================

Idea:
-----
We want to find how many ways we can reach sum = n.

To reach sum 'n':
- The last dice roll could be 1, 2, 3, 4, 5, or 6
- So we try all possibilities

Recursive relation:
solve(n) = solve(n-1) + solve(n-2) + ... + solve(n-6)

Base cases:
- If n == 0 → 1 way (valid combination found)
- If n < 0 → 0 ways (invalid path)

⚠️ This approach is only for understanding.
⚠️ It causes TLE for large n due to repeated work.
*/

int solveRecursive(int n) {
    // Base case: exact sum achieved
    if (n == 0) return 1;

    // Base case: invalid sum
    if (n < 0) return 0;

    int ways = 0;

    // Try all dice values from 1 to 6
    for (int dice = 1; dice <= 6; dice++) {
        ways = (ways + solveRecursive(n - dice)) % MOD;
    }

    return ways;
}

/*
====================================================
2️⃣ MEMOIZATION (RECURSION + DP)
====================================================

Problem with pure recursion:
----------------------------
Same subproblems are solved again and again.

Solution:
---------
- Use a dp array
- dp[n] stores number of ways to reach sum n
- If dp[n] is already calculated, reuse it

This keeps the recursive thinking but removes repetition.
Time Complexity becomes O(n).
*/

int solveMemo(int n, vector<int>& dp) {
    // Base case
    if (n == 0) return 1;
    if (n < 0) return 0;

    // If already computed, return stored value
    if (dp[n] != -1) return dp[n];

    int ways = 0;

    // Try all dice values
    for (int dice = 1; dice <= 6; dice++) {
        ways = (ways + solveMemo(n - dice, dp)) % MOD;
    }

    // Store result before returning
    return dp[n] = ways;
}

/*
====================================================
3️⃣ TABULATION (BOTTOM-UP DP) ✅ BEST APPROACH
====================================================

Idea:
-----
Instead of recursion, we build answers from 0 to n.

dp[i] = number of ways to reach sum i

Base:
-----
dp[0] = 1 (one way to make sum 0)

Transition:
-----------
dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-6]

This avoids recursion and stack usage.
*/

int solveTabulation(int n) {
    vector<int> dp(n + 1, 0);

    // Base case
    dp[0] = 1;

    // Build dp array from 1 to n
    for (int i = 1; i <= n; i++) {
        for (int dice = 1; dice <= 6; dice++) {
            if (i - dice >= 0) {
                dp[i] = (dp[i] + dp[i - dice]) % MOD;
            }
        }
    }

    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    /*
        Uncomment ONE method at a time if you want to test.
        For CSES submission, use TABULATION.
    */

    // 1️⃣ Pure Recursive (for learning only)
    // cout << solveRecursive(n) << "\n";

    // 2️⃣ Memoization
    // vector<int> dp(n + 1, -1);
    // cout << solveMemo(n, dp) << "\n";

    // 3️⃣ Tabulation (Final Answer)
    cout << solveTabulation(n) << "\n";

    return 0;
}
