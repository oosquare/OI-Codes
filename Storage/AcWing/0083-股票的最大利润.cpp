class Solution {
public:
    int maxDiff(vector<int>& nums) {
        if (nums.size() < 2)
            return 0;

        int ans = 0, mx = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            ans = max(ans, nums[i] - mx);
            mx = min(mx, nums[i]);
        }
        return ans;
    }
};