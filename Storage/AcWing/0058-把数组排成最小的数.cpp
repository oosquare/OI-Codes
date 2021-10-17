class Solution {
public:
    string printMinNumber(vector<int>& nums) {
        vector<string> tmp;
        string res;
        
        for (int x : nums)
            tmp.emplace_back(to_string(x));
        sort(tmp.begin(), tmp.end(), [&](const string &lhs, const string &rhs) {
            return lhs + rhs < rhs + lhs;
        });
        for (const string &s : tmp)
            res += s;
        return res;
    }
};