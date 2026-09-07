class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        vector<long long> last(26, 0);
        long long total = 0;

        for (char ch : s) {
            int idx = ch - 'a';

            long long newTotal = (2 * total + 1 - last[idx] + MOD) % MOD;

            last[idx] = (total + 1) % MOD;
            total = newTotal;
        }

        return total;
    }
};