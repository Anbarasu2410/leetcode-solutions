class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sx = 0, sy = 0, id = 0;
        vector<vector<int>> litter(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                if (classroom[i][j] == 'L') {
                    litter[i][j] = id++;
                }
            }
        }

        int fullMask = (1 << id) - 1;

        queue<tuple<int, int, int, int>> q;
        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << id, -1))
        );

        q.push({sx, sy, energy, 0});
        best[sx][sy][0] = energy;

        int moves = 0;
        int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                auto [r, c, e, mask] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                if (e == 0)
                    continue;

                for (auto &d : dir) {
                    int nr = r + d[0];
                    int nc = c + d[1];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nm = mask;

                    if (classroom[nr][nc] == 'L')
                        nm |= (1 << litter[nr][nc]);

                    if (classroom[nr][nc] == 'R')
                        ne = energy;

                    if (best[nr][nc][nm] >= ne)
                        continue;

                    best[nr][nc][nm] = ne;
                    q.push({nr, nc, ne, nm});
                }
            }

            moves++;
        }

        return -1;
    }
};