class Solution {
public:
    int len;
    vector<int> bitree;
    vector<int> data;
    
    void insert(int p, int v) {
        for (; p <= len; p += p & (-p))
            bitree[p] += v;
    }
    
    int query(int p) {
        int res = 0;
        for (; p; p -= p & (-p))
            res += bitree[p];
        return res;
    }
    
    int inversePairs(vector<int>& nums) {
        copy(nums.begin(), nums.end(), back_inserter(data));
        sort(data.begin(), data.end());
        len = unique(data.begin(), data.end()) - data.begin();
        for (int i = 0; i < nums.size(); ++i)
            nums[i] = lower_bound(data.begin(), data.end(), nums[i]) - data.begin() + 1;
        bitree = vector<int>(data.size() * 4);
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ans += query(len) - query(nums[i]);
            insert(nums[i], 1);
        }
        return ans;
    }
};