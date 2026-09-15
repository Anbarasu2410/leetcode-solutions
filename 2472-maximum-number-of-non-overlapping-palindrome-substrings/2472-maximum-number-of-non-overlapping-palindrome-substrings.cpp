class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // dp[i] = maximum number of valid non-overlapping palindromes
        // using the first i characters.
        vector<int> dp(n + 1, 0);

        auto isPalindrome = [&](int l, int r) {
            while (l < r) {
                if (s[l] != s[r]) return false;
                l++;
                r--;
            }
            return true;
        };

        for (int i = 1; i <= n; i++) {
            // Don't select a palindrome ending at i - 1
            dp[i] = dp[i - 1];

            // Check palindrome of length k
            if (i >= k) {
                int l = i - k;
                int r = i - 1;

                if (isPalindrome(l, r)) {
                    dp[i] = max(dp[i], dp[l] + 1);
                }
            }

            // Check palindrome of length k + 1
            if (i >= k + 1) {
                int l = i - k - 1;
                int r = i - 1;

                if (isPalindrome(l, r)) {
                    dp[i] = max(dp[i], dp[l] + 1);
                }
            }
        }

        return dp[n];
    }
};