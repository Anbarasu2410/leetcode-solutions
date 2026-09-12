class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    State better(const State& a, const State& b) {
        if (a.score != b.score)
            return (a.score > b.score) ? a : b;

        return (a.ids < b.ids) ? a : b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

      
        vector<array<long long, 4>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

     
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            if (a[1] != b[1])
                return a[1] < b[1];
            return a[0] < b[0];
        });

    
        vector<long long> rights(n);
        for (int i = 0; i < n; i++) {
            rights[i] = arr[i][1];
        }

     
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

      
        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int k = 1; k <= 4; k++) {
            for (int i = 1; i <= n; i++) {

               
                State skip = dp[k][i - 1];

             
                int current = i - 1;

                int previous = prev[current];

                State take = dp[k - 1][previous + 1];

                take.score += arr[current][2];

                int originalIndex = arr[current][3];

                
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