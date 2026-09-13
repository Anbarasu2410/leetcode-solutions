class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        vector<pair<int, int>> a, b;
        int n = img1.size();

        // Store coordinates of 1s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 1)
                    a.push_back({i, j});

                if (img2[i][j] == 1)
                    b.push_back({i, j});
            }
        }

        map<pair<int, int>, int> shifts;
        int ans = 0;

        // Find translation vector between every pair of 1s
        for (auto [x1, y1] : a) {
            for (auto [x2, y2] : b) {
                int dx = x2 - x1;
                int dy = y2 - y1;

                shifts[{dx, dy}]++;

                ans = max(ans, shifts[{dx, dy}]);
            }
        }

        return ans;
    }
};