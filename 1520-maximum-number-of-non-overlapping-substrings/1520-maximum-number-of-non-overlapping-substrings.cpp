class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

      
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

   
        for (int c = 0; c < 26; c++) {
            if (first[c] == n)
                continue;

            int start = first[c];
            int end = last[c];
            bool valid = true;

            for (int i = start; i <= end; i++) {
                int ch = s[i] - 'a';

     
                if (first[ch] < start) {
                    valid = false;
                    break;
                }

            
                end = max(end, last[ch]);
            }

            if (valid) {
                intervals.push_back({start, end});
            }
        }

  
        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) {
                 if (a.second != b.second)
                     return a.second < b.second;
                 return a.first > b.first;
             });

        vector<string> ans;
        int previousEnd = -1;

        for (auto [start, end] : intervals) {
            if (start > previousEnd) {
                ans.push_back(s.substr(start, end - start + 1));
                previousEnd = end;
            }
        }

        return ans;
    }
};