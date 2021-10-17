class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0], sum = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            if (sum + nums[i] >= nums[i]) {
                sum += nums[i];
            } else {
                sum = nums[i];
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};