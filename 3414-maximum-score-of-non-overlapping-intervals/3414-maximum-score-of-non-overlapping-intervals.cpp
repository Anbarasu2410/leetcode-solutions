class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    // Return the better state:
    // 1. Higher score wins
    // 2. If score is same, lexicographically smaller indices win
    State better(const State& a, const State& b) {
        if (a.score != b.score)
            return (a.score > b.score) ? a : b;

        return (a.ids < b.ids) ? a : b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, originalIndex}
        vector<array<long long, 4>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            if (a[1] != b[1])
                return a[1] < b[1];
            return a[0] < b[0];
        });

        // Store right endpoints for binary search
        vector<long long> rights(n);
        for (int i = 0; i < n; i++) {
            rights[i] = arr[i][1];
        }

        /*
            prev[i] = last interval j such that

                arr[j].right < arr[i].left

            Strict < is important because touching boundaries
            are considered overlapping.
        */
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            long long left = arr[i][0];

            int j = lower_bound(
                rights.begin(),
                rights.begin() + i,
                left
            ) - rights.begin() - 1;

            prev[i] = j;
        }

        /*
            dp[k][i]

            Best result using:
            - first i intervals
            - at most k intervals

            i ranges 0...n
            k ranges 0...4
        */
        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int k = 1; k <= 4; k++) {
            for (int i = 1; i <= n; i++) {

                // Option 1: don't take interval i-1
                State skip = dp[k][i - 1];

                // Option 2: take interval i-1
                int current = i - 1;

                int previous = prev[current];

                State take = dp[k - 1][previous + 1];

                take.score += arr[current][2];

                int originalIndex = arr[current][3];

                // Insert original index in sorted order.
                // Needed for lexicographical comparison.
                auto pos = lower_bound(
                    take.ids.begin(),
                    take.ids.end(),
                    originalIndex
                );

                take.ids.insert(pos, originalIndex);

                dp[k][i] = better(skip, take);
            }
        }

        return dp[4][n].ids;
    }
};