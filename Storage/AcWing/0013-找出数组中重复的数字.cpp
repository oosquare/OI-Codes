class Solution {
public:
    int duplicateInArray(vector<int>& nums) {
        vector<int> cnt(nums.size());
        bool vaild = true, found = false;
        int ans;
        for (int v : nums) {
            if (v >= nums.size() || v < 0) {
                vaild = false;
                break;
            }
            ++cnt[v];
            if (cnt[v] > 1) {
                found = true;
                ans = v;
            }
        }
        return vaild && found ? ans : -1;
    }
};