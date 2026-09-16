class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long power(long long a, long long b) {
        long long res = 1;

        while (b > 0) {
            if (b & 1)
                res = res * a % MOD;

            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1;
        int R = 2 * k;

        vector<long long> fact(N + 1);

        fact[0] = 1;

        for (int i = 1; i <= N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        long long numerator = fact[N];

        long long denominator =
            fact[R] * fact[N - R] % MOD;

        long long inverseDenominator =
            power(denominator, MOD - 2);

        return numerator * inverseDenominator % MOD;
    }
};